#include "WinPcap_BasicTest.h"

/*开发环境配置测试						**/
void funcWinPcapEnviromentTest()
{
	// 打开网卡并获取设备信息
	char errbuf[PCAP_ERRBUF_SIZE] = "\0";

	pcap_if_t* alldevs = nullptr;
	if (-1 == pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), NULL, &alldevs, errbuf))
	{
		cerr << "Func: pcap_findalldevs_ex() Error. ErrInfo: " << errbuf << endl;
		return;
	}

	// 打印网卡信息
	for (pcap_if_t* dev = alldevs; dev != NULL; dev = dev->next)
	{
		string formatDevName(dev->name);
		cout << "Adapter Name: " << formatDevName << endl;

		cout << "    Description: ";
		if (dev->description)
			cout << dev->description << endl;
		else
			cout << "No Description" << endl;
	}

	// 释放资源
	pcap_freealldevs(alldevs);
	return;
}

/*查找网卡信息接口函数测试				**/
void funcFindDevsTest()
{
	char errBuf[PCAP_ERRBUF_SIZE] = "\0";
	pcap_if_t* pDevList = NULL;

	// 使用pcap_findalldevs()函数获取网卡信息
	int findResult = pcap_findalldevs(&pDevList, errBuf);
	if (-1 == findResult)
	{
		cerr << "Func: pcap_findalldevs() Error. ErrInfo: " << errBuf << endl;
		return;
	}
	else
	{
		cout << "Using Func pcap_findalldevs() Function:" << endl;
		
		// 打印网卡信息
		for (pcap_if_t* dev = pDevList; dev != NULL; dev = dev->next)
		{
			string formatDevName(dev->name);
			cout << "Adapter Name: " << formatDevName << endl;

			cout << "    Description: ";
			if (dev->description)
				cout << dev->description << endl;
			else
				cout << "No Description" << endl;
		}

		cout << endl;
	}	

	pcap_freealldevs(pDevList);
	pDevList = NULL;
	memset(errBuf, 0, strlen(errBuf));

	// 使用pcap_findalldevs_ex()函数获取网卡信息
	findResult = pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), NULL, &pDevList, errBuf);
	if (-1 == findResult)
	{
		cerr << "Func: pcap_findalldevs() Error. ErrInfo: " << errBuf << endl;
		return;
	}
	else
	{
		cout << "Using pcap_findalldevs_ex() Function:" << endl;
		
		// 打印网卡信息
		for (pcap_if_t* dev = pDevList; dev != NULL; dev = dev->next)
		{
			string formatDevName(dev->name);
			cout << "Adapter Name: " << formatDevName << endl;

			cout << "    Description: ";
			if (dev->description)
				cout << dev->description << endl;
			else
				cout << "No Description" << endl;
		}

		cout << endl;
	}

	pcap_freealldevs(pDevList);
}

/*显示网卡详细信息测试					**/
void funcDisplayDevsDetailInfo()
{
	pcap_if_t* pAllDevs = nullptr;
	char errBuf[PCAP_ERRBUF_SIZE] = "\0";

	// 捕获网卡信息
	if (-1 == pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), nullptr, &pAllDevs, errBuf))
	{
		cout << "Find Devs Failed. ErrInfo: " << errBuf << endl;
		return;
	}

	// 显示网卡详细信息
	int index = 1;
	pcap_if_t* pCurDev = pAllDevs;
	while (nullptr != pCurDev)
	{
		cout << "Adapter Index: " << index << endl;
		cout << "Adapter Name: " << string(pCurDev->name).substr(16) << endl;	// 截取"rpcap:\\/Device\"字符
		cout << "Adapter Description: " << pCurDev->description << endl;
		cout << "Adapter IsLoopback: " << ((pCurDev->flags & PCAP_IF_LOOPBACK) ? "Yes" : "No") << endl;
		
		pcap_addr* pCurAddr = pCurDev->addresses;
		while (nullptr != pCurAddr)
		{
			switch (pCurAddr->addr->sa_family)
			{
				case AF_INET:
				{
					if(nullptr != pCurAddr->addr)
						cout << "Adapter IpAddr: " << funcIPIntToStr(((struct sockaddr_in *)pCurAddr->addr)->sin_addr.s_addr) << endl;

					if (nullptr != pCurAddr->netmask)
						cout << "Adapter Netmask: " << funcIPIntToStr(((struct sockaddr_in *)pCurAddr->netmask)->sin_addr.s_addr) << endl;
					
					if (nullptr != pCurAddr->broadaddr)
						cout << "Adapter BroadcastAddr: " << funcIPIntToStr(((struct sockaddr_in *)pCurAddr->broadaddr)->sin_addr.s_addr) << endl;
					
					if (nullptr != pCurAddr->dstaddr)
						cout << "Adapter DestAddr: " << funcIPIntToStr(((struct sockaddr_in *)pCurAddr->dstaddr)->sin_addr.s_addr) << endl;

					break;
				}
				default:
					break;
			}
			pCurAddr = pCurAddr->next;
		}
		
		cout << endl;
		pCurDev = pCurDev->next;
		++index;
	}
	
	// 释放网卡信息
	pcap_freealldevs(pAllDevs);
	return;
}

string funcIPIntToStr(u_long pAddr)
{
	char ipBuf[256] = "\0";
	u_char* pcAddr = (u_char *)&pAddr;
	
	sprintf_s(ipBuf, "%d.%d.%d.%d", pcAddr[0], pcAddr[1], pcAddr[2], pcAddr[3]);
	ipBuf[strlen(ipBuf)] = '\0';

	return ipBuf;
}


/*打开网卡, 回调函数形式捕获数据包		**/
void funcOpenAdapterTest()
{
	pcap_if_t* pDevList = nullptr;
	char errbuf[PCAP_ERRBUF_SIZE] = "\0";

	// 获取当前设备的所有网卡信息
	int openResult = pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), nullptr, &pDevList, errbuf);
	if (-1 == openResult)
	{
		cout << "Func Error: pcap_findalldevs_ex(). Error Info: " << errbuf << endl;
		return;
	}

	// 展示所有的网卡信息并让用户选择要捕获数据的网卡索引
	cout << "Adapter List: " << endl;
	int index = 1;
	pcap_if_t* pCurDev = pDevList;
	while (nullptr != pCurDev)
	{
		cout << "  Adapter Index: " << index << endl;
		cout << "  Adapter Name: " << pCurDev->name << endl;
		cout << "  Adapter Description: " << pCurDev->description << endl;

		pcap_addr* pCurAddr = pCurDev->addresses;
		while (pCurAddr)
		{
			switch (pCurAddr->addr->sa_family)
			{
				case AF_INET:
				{
					cout << "  Adapter Address: " << funcIPIntToStr(((struct sockaddr_in *)pCurDev->addresses->addr)->sin_addr.s_addr) << endl;
					break;
				}
				default:
					break;
			}
			
			pCurAddr = pCurAddr->next;
		}
		cout << endl;

		pCurDev = pCurDev->next;
		++index;
	}
	cout << endl << "Enter Adapter Index  To Capture: ";

	// 向用户展示即将捕获数据的网卡信息
	cin >> index;
	pCurDev = pDevList;
	for (int i = 0; i < index; ++i)
	{
		pCurDev = pCurDev->next;
	}
	cout << endl << pCurDev->name << " Start Listening..." << endl << endl;

	// 打开并捕获网卡上收到的数据包
	pcap_t* pOpenInterface = pcap_open_live(pCurDev->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1, errbuf);
	if (nullptr != pOpenInterface)
	{
		cout << pCurDev->name << " Start Capturing..." << endl << endl;
		pcap_loop(pOpenInterface, -1, funcOpenCb, nullptr);
	}
	else
	{
		cout << "Func Error: pcap_open_live(). Error Info: " << errbuf << endl;
	}

	// 资源销毁
	pcap_close(pOpenInterface);
	pcap_freealldevs(pDevList);
}

void funcOpenCb(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct tm* ltime = nullptr;
	char timestr[64] = "\0";

	time_t local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ltime);
	sprintf(timestr, "%s.%ld", timestr, header->ts.tv_usec);

	cout << "Packet Timestamp: " << timestr << endl;
	cout << "Packet Length   : " << header->len << endl << endl;
}


/*打开网卡, 非回调函数形式捕获数据包	**/
void funcOpenAdapterNonCbTest()
{
	pcap_if_t* pDevList = nullptr;
	char errBuf[PCAP_BUF_SIZE] = "\0";

	int findResult = pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), nullptr, &pDevList, errBuf);
	if (-1 == findResult)
	{
		cout << "Func pcap_findalldevs_ex() Error. Error Info: " << errBuf << endl;
		return;
	}

	cout << "Adapter List: " << endl;

	int index = 1;
	pcap_if_t* pCurDev = pDevList;
	while (nullptr != pCurDev)
	{
		cout << "  Adapter Index: " << index << endl;
		cout << "  Adapter Name: " << pCurDev->name << endl;
		cout << "  Adapter Description: " << pCurDev->description << endl;

		pcap_addr* pCurAddr = pCurDev->addresses;
		while (pCurAddr)
		{
			if (AF_INET == pCurAddr->addr->sa_family)
				cout << "  Adapter Address: " << funcIPIntToStr(((struct sockaddr_in *)pCurDev->addresses->addr)->sin_addr.s_addr) << endl;
		
			pCurAddr = pCurAddr->next;
		}
		cout << endl;

		pCurDev = pCurDev->next;
		++index;
	}
	cout << endl << "Enter Adapter Index  To Capture: ";
	cin >> index;

	pCurDev = pDevList;
	for (int i = 0; i < index - 1; ++i)
	{
		pCurDev = pCurDev->next;
	}

	cout << pCurDev->name << " " << pCurDev->description << " Start Capturing..." << endl;

	int count = 0;
	memset(errBuf, 0, strlen(errBuf));
	pcap_t* pCurOpen = pcap_open(pCurDev->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 10, nullptr, errBuf);
	if (nullptr != pCurOpen)
	{
		pcap_pkthdr* pHeader = nullptr;
		const u_char* pData = nullptr;

		int res = 0;
		while (true)
		{
			res = pcap_next_ex(pCurOpen, &pHeader, &pData);
			if (0 == res)
				continue;
			else if (res < 0)
			{
				cout << "Func pcap_next_ex() Error. Error Info: " << pcap_geterr(pCurOpen) << endl;
				break;
			}
			
			struct tm* ltime = nullptr;
			char timestr[64] = "\0";

			time_t local_tv_sec = pHeader->ts.tv_sec;
			ltime = localtime(&local_tv_sec);

			strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ltime);
			sprintf(timestr, "%s.%ld", timestr, pHeader->ts.tv_usec);

			cout << "Packet Timestamp: " << timestr << endl;
			cout << "Packet Length   : " << pHeader->len << endl << endl;

			if (++count >= 20)
				break;
		}
	}
	else
		cout << "Func pcap_open() Error. Error Info: " << errBuf << endl;

	pcap_close(pCurOpen);
	pcap_freealldevs(pDevList);
}


/*数据包过滤							**/
void funcPacketFliterTest()
{
	pcap_if_t* pDevList = nullptr;
	char errbuf[PCAP_BUF_SIZE] = "\0";

	int findResult = pcap_findalldevs_ex(const_cast<char*>(PCAP_SRC_IF_STRING), nullptr, &pDevList, errbuf);
	if (-1 == findResult)
	{
		cout << "Err: pcap_findalldevs_ex(). ErrInfo: " << errbuf << endl;
		return;
	}

	int index = 1;
	pcap_if_t* pDev = pDevList;
	while (pDev)
	{
		cout << index << " " << pDev->name << " " << pDev->description << endl;
		
		++index;
		pDev = pDev->next;
	}

	cout << endl << "Select Adapter Index: ";
	cin >> index;
	
	pDev = pDevList;
	for (int i = 0; i < index; ++i)
	{
		pDev = pDev->next;
	}
	cout << pDev->name << " Start Capturing..." << endl;

	memset(errbuf, 0, sizeof(errbuf));
	pcap_t* pOpen = pcap_open_live(pDev->name, 65535, PCAP_OPENFLAG_PROMISCUOUS, 10, errbuf);
	if (nullptr != pOpen)
	{
		bpf_program compileCode;
		const char* sFilter = "ip or arp or tcp or udp";
		bpf_u_int32 netmask = ((sockaddr_in *)(pDev->addresses->netmask))->sin_addr.S_un.S_addr;

		int compileResult = pcap_compile(pOpen, &compileCode, sFilter, 1, netmask);
		if (compileResult >= 0)
		{
			int filterResult = pcap_setfilter(pOpen, &compileCode);
			if (0 == filterResult)
			{
				pcap_loop(pOpen, 10, &funcPacketFliterTestCb, nullptr);
				pcap_freecode(&compileCode);
			}
			else
			{
				cout << "Err: pcap_setfilter(). ErrInfo: " << pcap_geterr(pOpen) << endl;
			}
		}
		else
		{
			cout << "Err: pcap_compile(). ErrInfo: " << pcap_geterr(pOpen) << endl;
		}
	}
	else
		cout << "Err: pcap_open_live(). ErrInfo: " << errbuf << endl;

	pcap_close(pOpen);
	pcap_freealldevs(pDevList);
}

void funcPacketFliterTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	struct tm* ltime = nullptr;
	char timestr[64] = "\0";

	time_t local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ltime);
	sprintf(timestr, "%s.%ld", timestr, header->ts.tv_usec);

	cout << "Packet Timestamp: " << timestr << endl;
	cout << "Packet Length   : " << header->len << endl << endl;
}


/*数据包解析							**/
void funcPacketPraseTest()
{
	pcap_if_t* pDevList = nullptr;
	char errbuf[PCAP_BUF_SIZE] = "\0";
	int findResult = pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), nullptr, &pDevList, errbuf);
	if (-1 == findResult)
	{
		cout << "ErrFunc: pcap_findalldevs_ex(). ErrInfo: " << errbuf << endl;
		return;
	}

	int index = 0;
	pcap_if_t* pCurDev = pDevList;
	while (pCurDev)
	{
		cout << index << " " << pCurDev->name << " " << pCurDev->description << endl;
		pCurDev = pCurDev->next;
		++index;
	}

	cout  << endl << "Enter Adapter Index To Capture: ";
	cin >> index;

	pCurDev = pDevList;
	for (int i = 0; i < index; ++i)
	{
		pCurDev = pCurDev->next;
	}
	cout << "Start Capture " << pCurDev->name << endl << endl;

	pcap_t* pOpenAdapter = pcap_open_live(pCurDev->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 10, errbuf);
	if (nullptr != pOpenAdapter)
	{
		bpf_program pbfCode;
		const char* sFilter = "ip";
		bpf_u_int32 netmask = ((const sockaddr_in*)(pCurDev->addresses->netmask))->sin_addr.S_un.S_addr;
		int compileResult = pcap_compile(pOpenAdapter, &pbfCode, sFilter, 1, netmask);
		if (-1 != compileResult)
		{
			int setFilterResult = pcap_setfilter(pOpenAdapter, &pbfCode);
			if (-1 != setFilterResult)
			{
				pcap_loop(pOpenAdapter, 10, &funcPacketPraseTestCb, nullptr);
			}
			else
				cout << "ErrFunc: pcap_setfilter(). ErrInfo: " << pcap_geterr(pOpenAdapter) << endl;

			pcap_freecode(&pbfCode);
		}
		else
			cout << "ErrFunc: pcap_compile(). ErrInfo: " << pcap_geterr(pOpenAdapter) << endl;
	}
	else
		cout << "ErrFunc: pcap_open_live(). ErrInfo: " << errbuf << endl;

	
	pcap_close(pOpenAdapter);
	pcap_freealldevs(pDevList);
}

void funcPacketPraseTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	/*解析数据首部							**/
	struct tm* ltime = nullptr;
	char timestr[64] = "\0";

	time_t local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ltime);
	sprintf(timestr, "%s.%ld", timestr, header->ts.tv_usec);

	cout << "Packet Timestamp: " << timestr << endl;
	cout << "Packet Length   : " << header->len << endl;

	/*解析数据								**/
	IPHeader_dt* pIPHeader = (IPHeader_dt*)pkt_data + 6 + 6 + 2;			// 链路层数据长度为源MAC(6 Byte) + 目的MAC(6 Byte) + 类型(2 Byte)
	
	char sSrcAddr[32] = "\0";
	IPAddress_dt& pSrcAddr = pIPHeader->ipSrcAddr;
	sprintf(sSrcAddr, "%d.%d.%d.%d", pSrcAddr.ucByteFst, pSrcAddr.ucByteSec, pSrcAddr.ucByteTrd, pSrcAddr.ucByteFrth);
	sSrcAddr[strlen(sSrcAddr)] = '\0';
	
	char sDstAddr[32] = "\0";
	IPAddress_dt& pDstAddr = pIPHeader->ipDstAddr;
	sprintf(sDstAddr, "%d.%d.%d.%d", pDstAddr.ucByteFst, pDstAddr.ucByteSec, pDstAddr.ucByteTrd, pDstAddr.ucByteFrth);
	sDstAddr[strlen(sDstAddr)] = '\0';
	
	UDPHeader_dt* pUDPHeader = (UDPHeader_dt*)((u_char*)pIPHeader + (pIPHeader->ucVersionAndLength & 0xf) * 4);
	u_short srcPort = ntohs(pUDPHeader->usSrcPort);	

	u_short dstPort = ntohs(pUDPHeader->usDstPort);

	cout << "Packet Source IP Addr: " << sSrcAddr << endl;
	cout << "Packet Source Port: " << srcPort << endl;
	cout << "Packet Dest IP Addr: " << sDstAddr << endl;
	cout << "Packet Dest Port: " << dstPort << endl << endl;
}


/*数据包存储							**/
void funcPacketDumpTest()
{
	pcap_if_t* pDevList = nullptr;
	char errbuf[PCAP_BUF_SIZE] = "\0";
	int findResult = pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), nullptr, &pDevList, errbuf);
	if (-1 == findResult)
	{
		cout << "ErrFunc: pcap_findalldevs_ex(). ErrInfo: " << errbuf << endl;
		return;
	}

	int index = 0;
	pcap_if_t* pCurDev = pDevList;
	while (pCurDev)
	{
		cout << index << " " << pCurDev->name << " " << pCurDev->description << endl;
		pCurDev = pCurDev->next;
		++index;
	}
	cout << endl;

	cout << "Enter Adapter Index: ";
	cin >> index;
	
	pCurDev = pDevList;
	for (int i = 0; i < index; ++i)
	{
		pCurDev = pCurDev->next;
	}
	cout << "Start Capture " << pCurDev->name << endl << endl;

	pcap_t* pOpenAdapter = pcap_open(pCurDev->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 10, nullptr, errbuf);
	if (pOpenAdapter)
	{
		const char* fileName = "./Winpcap.pcap";
		pcap_dumper_t* pDumpHandle = pcap_dump_open(pOpenAdapter, fileName);
		if (pDumpHandle)
		{
			pcap_loop(pOpenAdapter, 10, &funcPacketDumpTestCb, (u_char *)pDumpHandle);
			pcap_dump_close(pDumpHandle);
		}
		else
			cout << "ErrFunc: pcap_dump_open(). ErrInfo: " << pcap_geterr(pOpenAdapter) << endl;

		pcap_close(pOpenAdapter);
	}
	else
		cout << "ErrFunc: pcap_open(). ErrInfo: " << errbuf << endl;

	
	pcap_freealldevs(pDevList);
}

void funcPacketDumpTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	pcap_dump(param, header, pkt_data);
}


/*打开抓包文件							**/
void funcOpenCaptureFileTest()
{
	const char* fileName = "./Winpcap.pcap";
	char errbuf[PCAP_ERRBUF_SIZE] = "\0";
	char src[PCAP_BUF_SIZE] = "\0";
	int creatResult = pcap_createsrcstr(src,  PCAP_SRC_FILE, nullptr, nullptr, fileName, errbuf);
	if (-1 == creatResult)
	{
		cout << "ErrFunc: pcap_createsrcstr(). ErrInfo: " << errbuf << endl;
		return;
	}

	pcap_t* pOpenHandle = pcap_open(src, 65536, PCAP_OPENFLAG_PROMISCUOUS, 10, nullptr, errbuf);
	if (pOpenHandle)
	{
		pcap_loop(pOpenHandle, 10, &funcOpenCaptureFileTestCb, nullptr);
		pcap_close(pOpenHandle);
	}
	else
		cout << "ErrFunc: pcap_open(). ErrInfo: " << errbuf << endl;
}

void funcOpenCaptureFileTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	struct tm* ltime = nullptr;
	char timestr[64] = "\0";

	time_t local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ltime);
	sprintf(timestr, "%s.%ld", timestr, header->ts.tv_usec);

	cout << "Packet Timestamp: " << timestr << endl;
	cout << "Packet Length   : " << header->len << endl << endl;
}


/*发送数据								**/
static int			PacketVecSize		= 0;
static const int	PacketVecMaxSize	= 10;

void funcSendPacketTest()
{
	pcap_if_t* pDevList = nullptr;
	char errbuf[PCAP_ERRBUF_SIZE] = "\0";
	int findResult = pcap_findalldevs_ex(const_cast<char *>(PCAP_SRC_IF_STRING), nullptr, &pDevList, errbuf);
	if (-1 == findResult)
	{
		cout << "ErrFunc: pcap_findalldevs_ex(). ErrInfo: " << errbuf << endl;
		return;
	}

	int index = 1;
	pcap_if_t* pCurdev = pDevList;
	while (pCurdev)
	{
		cout << index << " " << pCurdev->name << " " << pCurdev->description << endl;

		pcap_addr* pCurAddr = pCurdev->addresses;
		while (nullptr != pCurAddr)
		{
			if (AF_INET == (pCurAddr->addr->sa_family))
			{
				if (nullptr != pCurAddr->addr)
					cout << "Adapter IpAddr: " << funcIPIntToStr(((struct sockaddr_in *)pCurAddr->addr)->sin_addr.s_addr) << endl;
			}
			pCurAddr = pCurAddr->next;
		}
		cout << endl;

		++index;
		pCurdev = pCurdev->next;
	}
	cout << endl;

	cout << "Enter Adapter Index To Capture Packet: ";
	cin >> index;

	pCurdev = pDevList;
	for (int i = 1; i < index; ++i)
	{
		pCurdev = pCurdev->next;
	}
	cout << "Satrt Capture " << pCurdev->name << endl;

	pcap_t* pOpenAdapter = pcap_open(pCurdev->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1, nullptr, errbuf);
	if(nullptr == pOpenAdapter)
		cout << "ErrFunc: pcap_open(). ErrInfo: " << errbuf << endl;
	else
	{
		bpf_program fcode;
		const char* sFilter = "udp";
		bpf_u_int32 netmask = ((const sockaddr_in*)(pCurdev->addresses->netmask))->sin_addr.S_un.S_addr;

		int compileResult = pcap_compile(pOpenAdapter, &fcode, sFilter, 1, netmask);
		if (-1 != compileResult)
		{
			int filterResult = pcap_setfilter(pOpenAdapter, &fcode);
			if (-1 != filterResult)
			{
				SendData_dt sendDataVec[PacketVecMaxSize];
				memset(sendDataVec, 0, sizeof(sendDataVec));

				pcap_loop(pOpenAdapter, 10, &funcSendPacketTestCb, (u_char *)sendDataVec);

				for (int i = 0; i < PacketVecSize; ++i)
				{
					SendData_dt& curSendData = sendDataVec[i];
					pcap_sendpacket(pOpenAdapter, (u_char *)(curSendData.pData), curSendData.iDataSize);

					delete curSendData.pData;
				}
			}
			else
				cout << "ErrFunc: pcap_setfilter(). ErrInfo: " << pcap_geterr(pOpenAdapter) << endl;

			pcap_freecode(&fcode);
		}
		else
			cout << "ErrFunc: pcap_compile(). ErrInfo: " << pcap_geterr(pOpenAdapter) << endl;

		pcap_close(pOpenAdapter);
	}
		
	pcap_freealldevs(pDevList);
}

void funcSendPacketTestCb(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	/*解析数据								**/
	IPHeader_dt* pIPHeader = (IPHeader_dt*)(pkt_data + 14);			// 链路层数据长度为源MAC(6 Byte) + 目的MAC(6 Byte) + 类型(2 Byte)

	char sSrcAddr[32] = "\0";
	IPAddress_dt& pSrcAddr = pIPHeader->ipSrcAddr;
	sprintf(sSrcAddr, "%d.%d.%d.%d", pSrcAddr.ucByteFst, pSrcAddr.ucByteSec, pSrcAddr.ucByteTrd, pSrcAddr.ucByteFrth);
	sSrcAddr[strlen(sSrcAddr)] = '\0';

	char sDstAddr[32] = "\0";
	IPAddress_dt& pDstAddr = pIPHeader->ipDstAddr;
	sprintf(sDstAddr, "%d.%d.%d.%d", pDstAddr.ucByteFst, pDstAddr.ucByteSec, pDstAddr.ucByteTrd, pDstAddr.ucByteFrth);
	sDstAddr[strlen(sDstAddr)] = '\0';

	UDPHeader_dt* pUDPHeader = (UDPHeader_dt*)((u_char*)pIPHeader + (pIPHeader->ucVersionAndLength & 0xf) * 4);
	u_short srcPort = ntohs(pUDPHeader->usSrcPort);
	u_short dstPort = ntohs(pUDPHeader->usDstPort);

	/*拷贝数据								**/
	if (8002 == srcPort || 8001 == dstPort)
	{
		cout << "Packet Source IP Addr: " << sSrcAddr << endl;
		cout << "Packet Source Port: " << srcPort << endl;
		cout << "Packet Dest IP Addr: " << sDstAddr << endl;
		cout << "Packet Dest Port: " << dstPort << endl << endl;

		pcap_t* pOpenAdapter = (pcap_t *)param;
		char* pCopyData = new char[header->len + 1];
		memcpy(pCopyData, pkt_data, header->len);
		pCopyData[header->len] = '\0';

		SendData_dt* pSendDataVec = (SendData_dt *)param;
		pSendDataVec[PacketVecSize].pData = pCopyData;
		pSendDataVec[PacketVecSize].iDataSize = header->len;

		++PacketVecSize;
	}
}