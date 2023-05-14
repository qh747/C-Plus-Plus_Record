#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*新客户端连接处理函数		**/
void funcAcceptNew(struct epoll_event* pEv, int* pEplFd);

/*读取客户端数据函数		**/
void funcReadNew(struct epoll_event* pEv, int* pEplFd);

/*按行读取HTTP请求			**/
size_t funcReadHTTPLine(int fd, void* buf, int buflen, bool* pIsCliExit);

/*解析客户端请求行			**/
void funcPraseHTTPReqLine(char* pReqLine, int reqLineSize, char* pMethod, char* pURL, char* pVersion);

/*服务端响应501未实现		**/
void funcRepNotImplement(int fd);

/*服务端响应目录			**/
void funcRepDir(int fd);

/*服务端响应文件			**/
void funcRepFile(int fd, const char* url);

/*获取HTTP首部响应首部		**/
void getHTTPRepHead(char* pHead, int* pLength, int code, const char* pInfo, const char* pFileFullPath);

/*获取HTTP首部响应文件类型	**/
const char* getHTTPContentType(const char* pFileFullPath); 

int main()
{
	/*创建socket			**/
	int servFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bool isReuseable = true;
	setsockopt(servFd, SOL_SOCKET, SO_REUSEADDR, (void *)&isReuseable, sizeof(isReuseable));

	/*绑定socket			**/
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("192.168.0.192");
	servAddr.sin_port = htons(8000);
	int bindRet = bind(servFd, (struct sockaddr *)&servAddr, sizeof(servAddr));

	/*监听socket			**/
	int listenRet = listen(servFd, 1024);

	/*接受socket			**/
	int eplFd = epoll_create(1);
	struct epoll_event servEvnt;
	servEvnt.events = EPOLLIN;
	servEvnt.data.fd = servFd;
	epoll_ctl(eplFd, EPOLL_CTL_ADD, servFd, &servEvnt);

	while(true)
	{
		struct epoll_event eplEvntVec[16];
		memset(eplEvntVec, 0, sizeof(eplEvntVec));

		int nReadys = epoll_wait(eplFd, eplEvntVec, 16, -1);
		for(int i = 0; i < nReadys; ++i)
		{
			if(servFd == eplEvntVec[i].data.fd && EPOLLIN & eplEvntVec[i].events)
			{
				/*新客户端接入			**/
				funcAcceptNew(&eplEvntVec[i], &eplFd);
			}
			else
			{
				/*已连接客户端发来数据	**/
				funcReadNew(&eplEvntVec[i], &eplFd);
			}
		}
	}

	/*关闭socket			**/
	close(servFd);
	return 0;
}

void funcAcceptNew(struct epoll_event* pEv, int* pEplFd)
{
	/*接受客户端连接		**/
	struct sockaddr_in cliAddr;
	memset(&cliAddr, 0, sizeof(cliAddr));
	socklen_t cliAddrlen = sizeof(cliAddr);
	int cliFd = accept(pEv->data.fd, (struct sockaddr *)&cliAddr, &cliAddrlen);
	if(-1 == cliFd)
	{
		/*接受错误，退出	**/
		perror("accept() error");
		return;
	}
	else
	{
		/*接受正确，打印	**/
		char ipBuf[16] = "\0";
		inet_ntop(AF_INET,  &cliAddr.sin_addr.s_addr, ipBuf, INET_ADDRSTRLEN);
		int port = ntohs(cliAddr.sin_port);
		printf("new client connect server. ip: %s port: %d.\n", ipBuf, port);

		/*设置为端口复用	**/
		bool isReuseable = true;
    	setsockopt(cliFd, SOL_SOCKET, SO_REUSEADDR, (void *)&isReuseable, sizeof(isReuseable));
	}

	/*事件添加				**/
	struct epoll_event cliEvnt;
	cliEvnt.events = EPOLLIN;
	cliEvnt.data.fd = cliFd;
	epoll_ctl(*pEplFd, EPOLL_CTL_ADD, cliFd, &cliEvnt);
}

void funcReadNew(struct epoll_event* pEv, int* pEplFd)
{
	/*读取客户端请求行						**/	
	char reqLine[256];
	memset(reqLine, 0, sizeof(reqLine));
	bool isCliExit = false;
	size_t curLineSize = funcReadHTTPLine(pEv->data.fd, reqLine, sizeof(reqLine), &isCliExit);
	if(curLineSize < 0 || (0 == curLineSize && true == isCliExit))
	{
		/*读取异常或客户端断开连接			**/
		if(curLineSize < 0)		                   
			perror("recv() error");
		else                                          
			printf("client disconnect server.\n");
		
		/*将当前客户端节点下树				**/
		epoll_ctl(*pEplFd, EPOLL_CTL_DEL, pEv->data.fd, pEv);
       	close(pEv->data.fd);
        return;
	}

	/*读取客户端请求首部					**/
	char headBuf[256];
	memset(headBuf, 0, sizeof(headBuf));
	while(funcReadHTTPLine(pEv->data.fd, headBuf, sizeof(headBuf), &isCliExit) > 0)
		continue;
	
	/*解析客户端请求行						**/
	char method[32];
	memset(method, 0, sizeof(method));
	char url[128];
	memset(url, 0, sizeof(url));
	char version[32];
	memset(version, 0, sizeof(version));
	funcPraseHTTPReqLine(reqLine, strlen(reqLine), method, url, version);
	printf("[%s] [%s] [%s]\n", method, url, version);

	/*客户端请求方法判断					**/
	if(0 != strncmp("GET", method, strlen("GET")))
	{
		/*当前客户端只支持GET方法			**/
		funcRepNotImplement(pEv->data.fd);

		/*断开客户端连接					**/
		epoll_ctl(*pEplFd, EPOLL_CTL_DEL, pEv->data.fd, pEv);
		close(pEv->data.fd);
		return;
	}

	/*客户端请求资源解析					**/
	if(0 == strcmp("/", url))
	{
		/*客户端请求目录					**/
		funcRepDir(pEv->data.fd);
	}
	else
	{
		/*客户端请求文件					**/
		funcRepFile(pEv->data.fd, url);
	}

	/*断开客户端连接						**/
	epoll_ctl(*pEplFd, EPOLL_CTL_DEL, pEv->data.fd, pEv);
    close(pEv->data.fd);
    return;
}

size_t funcReadHTTPLine(int fd, void* buf, int buflen, bool* pIsCliExit)
{
	int spot = 0;
	int curReadSize = 0;
	char* readBuf = (char *)buf;
	char ch = 0;
	while(spot < (buflen - 1) && ch != '\n')
	{
		curReadSize = recv(fd, &ch, 1, 0);
		if(curReadSize < 0)							// 读取错误
			return -1;
		else if(0 == curReadSize)       			// 客户端断开连接
		{
			*pIsCliExit = true;
			return 0;
		}
		else if(curReadSize > 0 && '\r' != ch)		// 读取客户端发送的数据
			readBuf[spot++] = ch;
		else if(curReadSize > 0 && '\r' == ch)		// 读取当前有效数据的行尾
		{
			curReadSize = recv(fd, &ch, 1, MSG_PEEK);
			if('\n' == ch && curReadSize > 0)
				recv(fd, &ch, 1, 0);
			else
				ch = '\n';
		}
		else										// 异常
			ch = '\n';
	}

	readBuf[spot] = '\0';
	*pIsCliExit = false;
	return spot;
}

void funcPraseHTTPReqLine(char* pReqLine, int reqLineSize, char* pMethod, char* pURL, char* pVersion)
{
	/*查找请求方法与URL之间的空格位置、URL与版本之间的空格位置		**/
	int posMethod = 0; 
	int posURL = 0;
	for(int i = 0; i < reqLineSize; ++i)
	{
		if(' ' == pReqLine[i] && 0 == posMethod)
			posMethod = i;
		else if(' ' == pReqLine[i] && 0 != posMethod)
			posURL = i;
	}

	/*根据空格位置依次拷贝请求方法、URL、版本						**/
	strncpy(pMethod, pReqLine, posMethod);
	strncpy(pURL, pReqLine + posMethod + 1, posURL - posMethod - 1);
	strncpy(pVersion, pReqLine + posURL + 1, reqLineSize + 1 - posURL);
}

void funcRepNotImplement(int fd)
{
	/*获取当前目录						**/
	char* curPath = getenv("PWD");
    if(NULL == curPath)
        return;

	/*获取当前文件绝对路径				**/
	char fileFullPath[256];
	memset(fileFullPath, 0, sizeof(fileFullPath));
	sprintf(fileFullPath, "%s/http_resource/501.html", curPath);
	
	/*文件信息解析						**/
	struct stat fileStat;
	stat(fileFullPath, &fileStat);

	/*发送HTTP响应首部					**/
	char head[1024];
	memset(head, 0, sizeof(head));
	int headLen = 0;
	getHTTPRepHead(head, &headLen, 501, "Not Implemented", fileFullPath);
	send(fd, head, headLen, 0);

	/*发送HTTP响应数据					**/
	char dataBuf[1024];
	memset(dataBuf, 0, sizeof(dataBuf));
	FILE* pFile = fopen(fileFullPath, "r");
	if(NULL != pFile)
	{
		fgets(dataBuf, sizeof(dataBuf), pFile);
		while(!feof(pFile))
		{
			send(fd, dataBuf, strlen(dataBuf), 0);
			fgets(dataBuf, sizeof(dataBuf), pFile);
		}
		fclose(pFile);
	}

	printf("server response 501 not implemented.\n");
}

void funcRepDir(int fd)
{
	/*获取当前目录                      **/
    char* curPath = getenv("PWD");
    if(NULL == curPath)
        return;

    /*获取当前文件绝对路径              **/
    char fileFullPath[256];
    memset(fileFullPath, 0, sizeof(fileFullPath));
    sprintf(fileFullPath, "%s/http_resource/index.html", curPath);

    /*文件信息解析                      **/
    struct stat fileStat;
    stat(fileFullPath, &fileStat);

    /*发送HTTP响应首部                  **/
    char head[1024];
    memset(head, 0, sizeof(head));
    int headLen = 0;
    getHTTPRepHead(head, &headLen, 200, "OK", fileFullPath);
    send(fd, head, headLen, 0);

    /*发送HTTP响应数据                  **/
    char dataBuf[1024];
    memset(dataBuf, 0, sizeof(dataBuf));
    FILE* pFile = fopen(fileFullPath, "r");
    if(NULL != pFile)
    {
        fgets(dataBuf, sizeof(dataBuf), pFile);
        while(!feof(pFile))
        {
            send(fd, dataBuf, strlen(dataBuf), 0);
            fgets(dataBuf, sizeof(dataBuf), pFile);
        }
        fclose(pFile);
    }

    printf("server response 200 ok of index.html.\n");
}

void funcRepFile(int fd, const char* url)
{
	/*获取当前目录                      **/
    char* curPath = getenv("PWD");
    if(NULL == curPath)
        return;

    /*获取当前文件绝对路径              **/
    char fileFullPath[256];
    memset(fileFullPath, 0, sizeof(fileFullPath));
    sprintf(fileFullPath, "%s/http_resource%s", curPath, url);

    /*文件信息解析                      **/
    struct stat fileStat;
    stat(fileFullPath, &fileStat);

	/*判断文件是否存在					**/
	if(0 == access(fileFullPath, F_OK))
	{
		/*文件存在						**/
		/*发送HTTP响应首部              **/
	    char head[1024];
	    memset(head, 0, sizeof(head));
	    int headLen = 0;
    	getHTTPRepHead(head, &headLen, 200, "OK", fileFullPath);
    	send(fd, head, headLen, 0);

    	/*发送HTTP响应数据              **/		
		FILE* pFile = NULL;
		char* pSuffix = strrchr(fileFullPath, '.');    
		if(0 == strcmp(".png", pSuffix) || 0 == strcmp(".jpg", pSuffix) || 0 == strcmp(".jpeg", pSuffix))
		{
			/*读取二进制图片文件		**/
     		FILE *pixmap = fopen(fileFullPath, "rb");
 			fseek(pixmap, 0, SEEK_END);     
     		int length = ftell(pixmap);						// 读取图片的大小长度
     		unsigned char* pBuffer = (unsigned char *)malloc(length * sizeof(unsigned char));
 			fseek(pixmap, 0, SEEK_SET);						// 把光标设置到文件的开头
 
			unsigned char* pTmp = pBuffer;
     		size_t curReadCount = fread(pTmp, sizeof(unsigned char), length, pixmap);
			size_t totalReadCount = curReadCount;
			while(0 != curReadCount)
     		{
				pTmp += curReadCount;
				curReadCount = fread(pTmp, sizeof(unsigned char), length, pixmap);
	   			totalReadCount += curReadCount;
     		}
			send(fd, pBuffer, totalReadCount, 0);
			free(pBuffer);
     		fclose(pixmap);
		}
		else
		{
			char dataBuf[1024];
	        memset(dataBuf, 0, sizeof(dataBuf));

			/*读取html文件				**/
			pFile = fopen(fileFullPath, "r");
			if(NULL != pFile)
        	{
            	fgets(dataBuf, sizeof(dataBuf), pFile);
            	while(!feof(pFile))
            	{
            	    send(fd, dataBuf, strlen(dataBuf), 0);
            	    fgets(dataBuf, sizeof(dataBuf), pFile);
           		}
            	fclose(pFile);
        	}
		}

    	printf("server response 200 ok of %s.\n", url);
	}
	else
	{
		/*文件不存在					**/
		/*发送HTTP响应首部              **/
        char head[1024];
        memset(head, 0, sizeof(head));
        int headLen = 0;
        getHTTPRepHead(head, &headLen, 404, "Not Found", fileFullPath);
        send(fd, head, headLen, 0);

        /*发送HTTP响应数据              **/
		char nfFileFullPath[256];
		memset(nfFileFullPath, 0, sizeof(nfFileFullPath));
		sprintf(nfFileFullPath, "%s/http_resource/404.html", curPath);

        char dataBuf[1024];
        memset(dataBuf, 0, sizeof(dataBuf));
        FILE* pFile = fopen(nfFileFullPath, "r");
        if(NULL != pFile)
        {
            fgets(dataBuf, sizeof(dataBuf), pFile);
            while(!feof(pFile))
            {
                send(fd, dataBuf, strlen(dataBuf), 0);
                fgets(dataBuf, sizeof(dataBuf), pFile);
            }
            fclose(pFile);
        }

        printf("server response 404 not found of %s.\n", url);
	}
}

void getHTTPRepHead(char* pHead, int* pLength, int code, const char* pInfo, const char* pFileFullPath)
{
	char* pTmpHead = pHead;
	char buf[256];
	memset(buf, 0, sizeof(buf));

	/*拷贝状态行			**/
	sprintf(buf, "HTTP/1.1 %d %s\r\n", code, pInfo);
 	*pLength += strlen(buf);
	strncpy(pTmpHead, buf, strlen(buf));
	pTmpHead += strlen(buf);

	/*拷贝响应首部			**/
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "Content-Type: %s\r\n", getHTTPContentType(pFileFullPath));
	*pLength += strlen(buf);
	strncpy(pTmpHead, buf, strlen(buf));
	pTmpHead += strlen(buf);

	/*拷贝空行				**/
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "\r\n");
	*pLength += strlen(buf);
	strncpy(pTmpHead, buf, strlen(buf));
	
	pTmpHead[*pLength] = '\0';
}

const char* getHTTPContentType(const char* pFileFullPath)
{
	char* dot;
    dot = strrchr(pFileFullPath, '.');		// 从pFileFullPath末端向前端查找

    if (NULL == dot)
        return "text/plain; charset=utf-8";
	else if (0 == strcmp(dot, ".html"))
        return "text/html; charset=utf-8";
	else if (0 == strcmp(dot, ".jpeg"))
        return "image/jpeg";
	else if (0 == strcmp(dot, ".jpg"))
		return "image/jpg";
	else if (0 == strcmp(dot, ".png"))
        return "image/png";
	else
    	return "text/plain; charset=utf-8";
}
