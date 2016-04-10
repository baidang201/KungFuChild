#include "HelpLayer.h"
#include "StartLayer.h"
#include "GlobalDefine.h"
#include "XMLParser.h"

Scene * HelpLayer::createScene()
{
	Scene* scene = Scene::create();
	HelpLayer* layer = HelpLayer::create();
	scene->addChild(layer);

	return scene;
}

bool HelpLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bgSprite = Sprite::create("Help.png");
	bgSprite->setPosition(WINSIZE.width/2, WINSIZE.height/2);
	this->addChild(bgSprite);


	auto closeItem = MenuItemSprite::create
	(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffSelected.png")),
		[&](Ref* ref)
	{
		PLAYEFFECT;
		Director::getInstance()->replaceScene(StartLayer::createScene());
	}
	);
	closeItem->setPosition(WINSIZE.width/2 + 580, WINSIZE.height/2 + 320);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto titleSp = Sprite::create("TitleLogo.png");
	titleSp->setPosition(WINSIZE.width/2 + 200, WINSIZE.height/2);
	this->addChild(titleSp);

	XMLParser* pXmlParser = XMLParser::parseWithFile("tujiLayer.xml");
	String* label = pXmlParser->getString("label_help");
	text = LabelTTF::create(label->getCString(), "", 23);
	text->setColor(ccc3(0, 255, 255));
	text->setTag(15);
	text->setPosition(250, 100);
	
	//»æÖÆ²Ã¼ôÇøÓò
	DrawNode* area = DrawNode::create();
	Point points[4] = { Point(50,100), Point(500, 100), Point(500,450), Point(50,450) };
	area->drawPolygon(points, 4, ccc4f(255,255,255,255), 0, ccc4f(255,255,255,255));

	//´´½¨ÕÚÕÖ²ã
	ClippingNode* m_pClipArea = ClippingNode::create();
	m_pClipArea->setInverted(false);
	m_pClipArea->setStencil(area);
	m_pClipArea->addChild(text);
	this->addChild(m_pClipArea);

	MoveBy* moveact = MoveBy::create(5.0f, Point(0, 400));
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(HelpLayer::scrollback) );
	ActionInterval* attackact = Sequence::create(moveact, callFunc, NULL);
	text->runAction(RepeatForever::create(attackact));

	return true;
}

void HelpLayer::scrollback()
{
	text->setPosition(250, 100);
}
