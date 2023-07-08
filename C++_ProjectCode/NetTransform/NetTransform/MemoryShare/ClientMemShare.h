#pragma once
#include "../PublicDataDef/PublicDataDef.h"
#include "MemoryShare.h"

class ClientMemShare : public MemoryShare
{
public:
	ClientMemShare(int keyId = -1);
	virtual ~ClientMemShare();

public:
	bool			createKeyInfo(int keyId);
	int				writeKeyInfo(KeyInfo_dt* pKeyInfo);
	int				readKeyInfo(KeyInfo_dt* pKeyInfo);

private:																	// ½ûÖ¹¿½±´
	ClientMemShare(const ClientMemShare& other) {}
	void operator=(const ClientMemShare& other) {}

private:
	int				m_keyId;
};

