#include "XMLParser.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

const static int SPACE = 32;
const static int NEXTLINE = 10;
const static int TAB = 9;

string replace(string source, string pattern, string dstPattern)
{
	string result;
	string::size_type pos;

	int lenSource = source.length();
	int i = 0;

	for(i =0; i<lenSource; i++)
	{
		pos = source.find(pattern, i);
		if (string::npos == pos)
			break;

		if (pos < lenSource)
		{
			string s = source.substr(i, pos -i);
			result += s;
			result += dstPattern;
			i = pos + pattern.length() - 1;
		}
	}

	result += source.substr(i);
	return result;
}

XMLParser* XMLParser::parseWithFile(const char* xmlFileName)
{
	XMLParser* pXMLParser = new XMLParser();
	if (pXMLParser->initWithFile(xmlFileName))
	{
		pXMLParser->autorelease();
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithFile(const char* xmlFileName)
{
	m_map = new Map<string, String*>();
	SAXParser _parser;
	_parser.setDelegator(this);

	string fullPath = FileUtils::getInstance()->fullPathForFilename(xmlFileName);
	log("xml full path: %s", fullPath.c_str());

	return _parser.parse(fullPath);

}

XMLParser* XMLParser::parseWithString(const char* content)
{
	XMLParser* pXMLParser = new XMLParser();
	if (pXMLParser->initWithString(content))
	{
		pXMLParser->autorelease();
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithString(const char* content)
{
	m_map = new Map<string, String*>();
	SAXParser _parse;
	_parse.setDelegator(this);
	return _parse.parse(content, strlen(content));
}

/*
<string name="muzhuang" app_name="hong">木\n桩\n怪</string>
[in] name 节点名 
[in] atts 属性列表
atts[0] 为 name
atts[1] 为属性值 muzhuang
atts[2] 为下一个节点名 app_name
atts[3] 为下一个节点属性值 hong
以此类推
*/
void XMLParser::startElement(void* ctx, const char* name, const char** atts)
{
	this->startXMLElement = (char*)name;
	log("start= %s", startXMLElement.c_str());

	if (this->startXMLElement == "string")
	{
		while (atts && *atts)
		{
			log("atts0 %s", atts[0]);
			log("atts1 %s", atts[1]);

			const char* attsKey = *atts;
			if (0 == strcmp(attsKey, "name"))
			{
				++atts;
				const char* attsValue = *atts;
				m_key = attsValue;
				break;
			}
			++atts;
		}
	}
}

void XMLParser::endElement(void* ctx, const char* name)
{
	this->endXMLElement = (char*)name;
	log("end = %s", endXMLElement.c_str());
}

void XMLParser::textHandler(void* ctx, const char* s, int len)
{
	string value((char*)s, 0, len);

	//是否全非正正常字符
	bool noValue = true;
	for (int i = 0; i < len; i++)
	{
		if (SPACE != s[i] && NEXTLINE != s[i] && TAB != s[i])
		{
			noValue = false;
			break;
		}
	}

	if (noValue)
		return;

	string result = replace(value, string("\\n"), string("\n"));
	String* pString = String::create(result);

	log("key = %s Value = %s", m_key.c_str(), pString->getCString());
	this->m_map->insert( this->m_key, pString);
}

String* XMLParser::getString(const char* key)
{
	string strKey(key);
	return (String*)this->m_map->at(strKey);
}

XMLParser::XMLParser()
{

}

XMLParser::~XMLParser()
{
	CC_SAFE_DELETE(this->m_map);
}
