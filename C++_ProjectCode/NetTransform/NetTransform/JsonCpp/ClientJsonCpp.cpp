#include "ClientJsonCpp.h"

ClientJsonCpp::ClientJsonCpp(const string& fileName, bool& isPraseOk)
{
	ifstream ifs(fileName);
	if (false == ifs.is_open())
	{
		cerr << "CLIENT JSON OPEN FILE FAILED. FILENAME: " << fileName << endl;
		isPraseOk = false;
		return;
	}

	Json::Value root;
	Json::Reader fileReader;
	fileReader.parse(ifs, root);

	ClitJsConf_dt clientJsonConf;
	clientJsonConf.iServerPort		 = root["ServerPt"].asInt();
	clientJsonConf.iClientMemShareId = root["MemShrId"].asInt();
	strcpy(clientJsonConf.sClientId, root["ClientId"].asString().data());
	strcpy(clientJsonConf.sServerId, root["ServerId"].asString().data());
	strcpy(clientJsonConf.sServerIp, root["ServerIp"].asString().data());
	this->setClientJsConf(clientJsonConf);

	ifs.close();
	isPraseOk = true;
}

ClientJsonCpp::~ClientJsonCpp()
{

}

ClitJsConf_dt ClientJsonCpp::getClientJsConf()
{
	return m_clitJsConf;
}

void ClientJsonCpp::setClientJsConf(const ClitJsConf_dt& conf)
{
	m_clitJsConf.iClientMemShareId  = conf.iClientMemShareId;
	m_clitJsConf.iServerPort		= conf.iServerPort;
	strcpy(m_clitJsConf.sClientId, conf.sClientId);
	strcpy(m_clitJsConf.sServerId, conf.sServerId);
	strcpy(m_clitJsConf.sServerIp, conf.sServerIp);
}