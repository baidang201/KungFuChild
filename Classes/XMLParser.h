#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <string>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class XMLParser : public Ref, public SAXDelegator
{
public:
	static XMLParser* parseWithFile(const char* xmlFileName);
	static XMLParser* parseWithString(const char* content);

	XMLParser();
	virtual ~XMLParser();

	bool initWithFile(const char* xmlFileName);
	bool initWithString(const char* content);

	//标签开始，如<string name="app_name">
	virtual void startElement(void* ctx, const char* name, const char** atts);

	//标签结束，如</string>
	virtual void endElement(void* ctx, const char* name);

	virtual void textHandler(void* ctx, const char*s, int len);

	String* getString(const char* key);

private:
	Map<string, String*>* m_map;
	std::string m_key;

	std::string startXMLElement;
	std::string endXMLElement;
	

};





#endif //XMLPARSER_H