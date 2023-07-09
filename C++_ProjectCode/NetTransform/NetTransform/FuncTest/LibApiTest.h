#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <fstream>
#include <openssl\md5.h>
#include <openssl\sha.h>
#include <openssl\rsa.h>
#include <openssl\pem.h>
#include <openssl\aes.h>
#include <json\json.h>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
using namespace Json;

/*OpenSSL MD5 API≤‚ ‘					**/
void funcOpensslMd5ApiTest();

/*OpenSSL SHA API≤‚ ‘					**/
void funcOpensslShaApiTest();

/*OpenSSL RSA API≤‚ ‘					**/
void funcOpensslRsaSaveApiTest();
void funcOpensslRsaBIOSaveApiTest();
void funcOpensslRsaEnCodeApiTest();
void funcOpensslRsaVertifyApiTest();

/*OpenSSL AES API≤‚ ‘					**/
void funcOpensslAesApiTest();

/*OpenSSL Base64 API≤‚ ‘				**/
void funcOpensslBase64ApiTest();

/*JsonCpp –¥Œƒº˛ API≤‚ ‘				**/
void funcJsonCppOfstreamWriteFileApiTest();
void funcJsonCppFastWriterWriteFileApiTest();

/*JsonCpp ∂¡Œƒº˛ API≤‚ ‘				**/
void funcJsonCppReadFileApiTest();
void funcArrayProcess(Value& nodeVec);
void funcObjectProcess(Value& nodeObj);

