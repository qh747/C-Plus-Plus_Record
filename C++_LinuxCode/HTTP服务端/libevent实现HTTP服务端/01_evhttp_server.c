#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/keyvalq_struct.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>  
#include <arpa/inet.h>

/*服务端宏定义								**/
#define HTTP_SERV_IP_ADDR "127.0.0.1"
#define HTTP_SERV_PORT    8080

/*服务端退出信号事件回调函数				**/
void funcServExitCb(evutil_socket_t fd, short event, void* arg);

/*响应客户端请求的回调函数					**/
void funcRespClientCb(struct evhttp_request* pReq, void* arg);

/*处理客户端断开连接回调函数				**/
void funcClientDisConnectCb(struct evhttp_connection* pConn, void* arg);


int main()
{
	/*创建event_base						**/
	struct event_base* pEvBase = event_base_new();

	/*监听服务端退出信号					**/
	struct event* pEvSignal = evsignal_new(pEvBase, SIGINT, funcServExitCb, (void *)pEvBase);
	evsignal_add(pEvSignal, NULL);

	/*创建evhttp							**/
	struct evhttp* pEvHttp = evhttp_new(pEvBase);

	/*绑定IP地址和端口						**/
	evhttp_bind_socket(pEvHttp, HTTP_SERV_IP_ADDR, HTTP_SERV_PORT);

	/*设置响应客户端请求的回调函数			**/
	evhttp_set_gencb(pEvHttp, funcRespClientCb, NULL);

	/*执行事件循环							**/
	event_base_dispatch(pEvBase);

	/*释放信号事件							**/
	evsignal_del(pEvSignal);
	event_free(pEvSignal);

	/*释放evhttp							**/
	evhttp_free(pEvHttp);

	/*释放event_base						**/
	event_base_free(pEvBase);

	return 0;
}

void funcServExitCb(evutil_socket_t fd, short event, void* arg)
{
	/*推出事件循环							**/
	printf("server will exit\n");
	struct event_base* pEvBase = (struct event_base *)arg;
	event_base_loopbreak(pEvBase);
}

void funcRespClientCb(struct evhttp_request* pReq, void* arg)
{
	/*设置客户端断开连接处理回调函数		**/
	struct evhttp_connection* pConn = evhttp_request_get_connection(pReq);
	evhttp_connection_set_timeout(pConn, 10);
	evhttp_connection_set_closecb(pConn, funcClientDisConnectCb, NULL);

	/*获取客户端请求方法					**/
	enum evhttp_cmd_type reqType =  evhttp_request_get_command(pReq);
	if(EVHTTP_REQ_GET != reqType)
	{
		/*服务端只支持GET方法				**/
		evhttp_send_error(pReq, HTTP_NOTIMPLEMENTED, "501 NOT IMPLEMENTED");
		return;
	}

	/*获取客户端请求URL						**/
	const struct evhttp_uri* pURL = evhttp_request_get_evhttp_uri(pReq);
	const char* pURLPath = evhttp_uri_get_path(pURL);

	/*根据URL拼装资源路径					**/
	char sPath[256] = "\0";
	const char* sCurPath = getenv("PWD");
	sprintf(sPath, "%s/http_resource%s", sCurPath, pURLPath);
	sPath[strlen(sPath)] = '\0';
	
	/*判断客户端请求资源是否存在            **/
    if(0 != access(sPath, F_OK))
    {
        evhttp_send_error(pReq, HTTP_NOTFOUND, "404 NOT FOUND");
        printf("acess() error. filePath: %s\n", sPath);
        return;
    }

	/*获取文件信息							**/
	struct stat st;
	int ret = stat(sPath, &st);
	if(-1 == ret)
	{
		evhttp_send_error(pReq, HTTP_INTERNAL, "500 SERVER INTERNAL ERROR");
		printf("stat() error. url: %s\n", pURLPath);
		return;
	}

	if (S_IFDIR & st.st_mode)
	{
		/*客户端请求目录                        **/
		char sIndexHtmlPath[512] = "\0";
		sprintf(sIndexHtmlPath, "%s/index.html", sPath);
		sIndexHtmlPath[strlen(sIndexHtmlPath)] = '\0';

		/*响应首部								**/
		struct evkeyvalq* pHeaders = evhttp_request_get_output_headers(pReq);
		evhttp_add_header(pHeaders, "Content-Type", "text/html; charset=utf-8");

		/*响应数据								**/
		struct evbuffer* pOutBuffer =  evhttp_request_get_output_buffer(pReq);
		char dataBuf[1024] = "\0";
        FILE* pFile = fopen(sIndexHtmlPath, "r");
        if(NULL != pFile)
        {
            fgets(dataBuf, sizeof(dataBuf), pFile);
            while(!feof(pFile))
            {
                evbuffer_add(pOutBuffer, dataBuf, strlen(dataBuf));

				memset(dataBuf, 0, sizeof(dataBuf));
                fgets(dataBuf, sizeof(dataBuf), pFile);
            }
            fclose(pFile);

			evhttp_send_reply(pReq, HTTP_OK, "200 OK", pOutBuffer);
        }
		else
		{
			evhttp_remove_header(pHeaders, "Content-Type");
			evhttp_send_error(pReq, HTTP_INTERNAL, "500 SERVER INTERNAL ERROR");
        	printf("fopen() error. filePath: %s\n", sIndexHtmlPath);
		}
	}
	else
	{
		/*客户端请求文件						**/
		char sFilePath[512] = "\0";
        sprintf(sFilePath, "%s", sPath);
        sFilePath[strlen(sFilePath)] = '\0';
			
		const char* pSuffix = NULL;
		for(int i = strlen(sFilePath) - 1; i >0; --i)
		{
			/*获取文件后缀						**/
			if('.' == sFilePath[i])
			{
				pSuffix = &sFilePath[i] + 1;
				break;
			}
		}
		if(NULL == pSuffix)
		{
			evhttp_send_error(pReq, HTTP_BADREQUEST, "400 BAD REQUEST");
            printf("get suffix error. filePath: %s\n", sFilePath);
			return;
		}

		/*响应首部                              **/
        struct evkeyvalq* pHeaders = evhttp_request_get_output_headers(pReq);
		if(0 == strncmp("html", pSuffix, 4))
        	evhttp_add_header(pHeaders, "Content-Type", "text/html; charset=utf-8");
		else if(0 == strncmp("jpg", pSuffix, 3))
			evhttp_add_header(pHeaders, "Content-Type", "image/jpg");
        else if(0 == strncmp("png", pSuffix, 3))
			evhttp_add_header(pHeaders, "Content-Type", "image/png");
		else
		{
			/*不支持的文件类型					**/
			evhttp_send_error(pReq, HTTP_INTERNAL, "500 SERVER INTERNAL ERROR");
            printf("get mime-type error. filePath: %s\n", sFilePath);
            return;
		}

        /*响应数据                              **/
        struct evbuffer* pOutBuffer = evhttp_request_get_output_buffer(pReq);
		if(0 == strncmp("html", pSuffix, 4))
		{
			/*读取html文件						**/
			struct evbuffer* pOutBuffer =  evhttp_request_get_output_buffer(pReq);
	        char dataBuf[1024] = "\0";
    	    FILE* pFile = fopen(sFilePath, "r");
        	if(NULL != pFile)
        	{
        	    fgets(dataBuf, sizeof(dataBuf), pFile);
        	    while(!feof(pFile))
        	    {
        	        evbuffer_add(pOutBuffer, dataBuf, strlen(dataBuf));

        	        memset(dataBuf, 0, sizeof(dataBuf));
        	        fgets(dataBuf, sizeof(dataBuf), pFile);
        	    }
        	    fclose(pFile);
            	evhttp_send_reply(pReq, HTTP_OK, "200 OK", pOutBuffer);
        	}
        	else
        	{
        	    evhttp_remove_header(pHeaders, "Content-Type");
        	    evhttp_send_error(pReq, HTTP_INTERNAL, "500 SERVER INTERNAL ERROR");
        	    printf("fopen() error. filePath: %s\n", sFilePath);
        	}
		}
		else if((0 == strncmp("jpg", pSuffix, 3)) || (0 == strncmp("png", pSuffix, 3)))
		{
			/*读取二进制图片文件		        **/
            FILE *pixmap = fopen(sFilePath, "rb");
			if(NULL != pixmap)
			{
            	fseek(pixmap, 0, SEEK_END);
            	int length = ftell(pixmap);                     // 读取图片的大小长度
            	unsigned char* pBuffer = (unsigned char *)malloc(length * sizeof(unsigned char));
            	fseek(pixmap, 0, SEEK_SET);                     // 把光标设置到文件的开头

            	unsigned char* pTmp = pBuffer;
            	size_t curReadCount = fread(pTmp, sizeof(unsigned char), length, pixmap);
            	size_t totalReadCount = curReadCount;
            	while(0 != curReadCount)
            	{
            	    pTmp += curReadCount;
            	    curReadCount = fread(pTmp, sizeof(unsigned char), length, pixmap);
            	    totalReadCount += curReadCount;
            	}
            	fclose(pixmap);
				evbuffer_add(pOutBuffer, pBuffer, totalReadCount);
				evhttp_send_reply(pReq, HTTP_OK, "200 OK", pOutBuffer);	
				free(pBuffer);
			}
			else
            {
                evhttp_remove_header(pHeaders, "Content-Type");
                evhttp_send_error(pReq, HTTP_INTERNAL, "500 SERVER INTERNAL ERROR");
                printf("fopen() error. filePath: %s\n", sFilePath);
            }
		}
		else
		{
			/*不支持的文件类型                  **/
            evhttp_send_error(pReq, HTTP_NOTIMPLEMENTED, "501 NOT IMPLEMENTED");
            printf("get mime-type error. filePath: %s\n", sFilePath);
            return;
		}
	}
}

void funcClientDisConnectCb(struct evhttp_connection* pConn, void* arg)
{
	const struct sockaddr_in* pSock = (const struct sockaddr_in*)evhttp_connection_get_addr(pConn);
	char ipAddr[16] = "\0";
    inet_ntop(AF_INET, &(pSock->sin_addr), ipAddr, INET_ADDRSTRLEN);
    int port = ntohs(pSock->sin_port);
    printf("client %s %d disconnect\n", ipAddr, port);
}
