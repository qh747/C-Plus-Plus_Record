#pragma once
#include <string>

/*±à½âÂë»ùÀà						**/
class Codec_Base
{
public:
	Codec_Base();
    virtual ~Codec_Base();

public:
    virtual std::string encodeMsg();
    virtual void*       decodeMsg();

};