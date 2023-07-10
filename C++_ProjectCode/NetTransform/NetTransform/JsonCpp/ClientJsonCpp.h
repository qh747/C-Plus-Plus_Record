#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <json\json.h>
#include <cstring>
#include <string>
#include "../PublicDataDef/PublicDataDef.h"
using namespace std;

class ClientJsonCpp
{
public:
	ClientJsonCpp(const string& fileName, bool& isPraseOk);
	~ClientJsonCpp();

public:
	ClitJsConf_dt	getClientJsConf();
	DBJsConf_dt		getDBJsConf();

private:
	void			setClientJsConf(const ClitJsConf_dt& conf);
	void			setDBJsConf(const DBJsConf_dt& conf);

public:
	ClitJsConf_dt	m_clitJsConf;
	DBJsConf_dt		m_DbJsConf;
};