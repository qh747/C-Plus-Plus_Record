#include "FuncTest.h"

/*Request_Codec模块测试						**/
void funcModelRequestCodecTest()
{
	/*请求消息初始化						**/
	RequestMsg_dt srcMsg;
	srcMsg.cmdType  = 1;
	srcMsg.clientId = "Client No.1";
	srcMsg.serverId = "Server No.1";
	srcMsg.sign     = "Source Message";
	srcMsg.data		= "Register Server";

	Request_Codec reqEncodeModel;
	reqEncodeModel.initMessage(srcMsg);

	cout << "REQUEST SOURCE MSG:" << " "
		 << srcMsg.cmdType		  << " "
		 << srcMsg.clientId		  << " "
		 << srcMsg.serverId       << " "
		 << srcMsg.sign			  << " "
		 << srcMsg.data			  << endl << endl;

	/*请求消息编码							**/
	string encodeMsg = reqEncodeModel.encodeMsg();
	cout << "REQUEST ENCODE MSG: " << encodeMsg << endl << endl;

	/*请求消息解码							**/
	Request_Codec reqDecodeModel;
	reqDecodeModel.initMessage(encodeMsg);
	RequestMsg_dt* pDstMsg = static_cast<RequestMsg_dt *>(reqDecodeModel.decodeMsg());
	
	cout << "REQUEST DEST MSG:" << " "
		 << pDstMsg->cmdType	<< " "
		 << pDstMsg->clientId   << " "
		 << pDstMsg->serverId   << " "
		 << pDstMsg->sign		<< " "
		 << pDstMsg->data		<< endl << endl;
}

/*Response_Codec模块测试					**/
void funcModelResponseCodecTest()
{
	/*响应消息初始化						**/
	ResponseMsg_dt srcMsg;
	srcMsg.clientId = "Client No.1";
	srcMsg.serverId = "Server No.1";
	srcMsg.seckeyId = 1;
	srcMsg.data     = "Register Server";
	srcMsg.status   = true;

	Response_Codec respEncodeModel;
	respEncodeModel.initMessage(srcMsg);

	cout << "RESPONSE SOURCE MSG:" << " "
		 << srcMsg.status		   << " "
		 << srcMsg.clientId		   << " "
		 << srcMsg.serverId		   << " "
		 << srcMsg.seckeyId		   << " "
		 << srcMsg.data			   << endl << endl;

	/*响应消息编码							**/
	string encodeMsg = respEncodeModel.encodeMsg();
	cout << "RESPONSE ENCODE MSG: " << encodeMsg << endl << endl;

	/*响应消息解码							**/
	Response_Codec respDecodeModel;
	respDecodeModel.initMessage(encodeMsg);
	ResponseMsg_dt* pDstMsg = static_cast<ResponseMsg_dt *>(respDecodeModel.decodeMsg());

	cout << "RESPONSE DEST MSG:" << " "
		 << pDstMsg->status      << " "
		 << pDstMsg->clientId	 << " "
		 << pDstMsg->serverId	 << " "
		 << pDstMsg->seckeyId	 << " "
		 << pDstMsg->data        << endl << endl;
}