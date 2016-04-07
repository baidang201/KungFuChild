#include "MijiLayer.h"
#include "GlobalDefine.h"
#include "StartLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* MijiLayer::createScene()
{
	Scene* scene = Scene::create();
	MijiLayer* layer = MijiLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MijiLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	flag = true;
	spriteBG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsBackground.png"));
	spriteBG->setPosition(WINSIZE.width/2, WINSIZE.height/2);
	this->addChild(spriteBG);

	interface_1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsInterface1.png"));
	interface_2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsInterface2.png"));
	interface_1->setPosition(WINSIZE.width/2, WINSIZE.height/2 - 10);
	interface_1->setVisible(true);
	interface_2->setPosition(WINSIZE.width/2, WINSIZE.height/2 - 10);
	interface_2->setVisible(false);

	spriteBG->addChild(interface_1);
	spriteBG->addChild(interface_2);

	auto closeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("OffNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("offSelected.pnd")),
		[](Ref* ref)
	{
		PLAYEFFECT;
		Director::getInstance()->replaceScene(StartLayer::createScene());
	}
	);
	closeItem->setPosition(WINSIZE.width - 164, WINSIZE.height -132);

	auto nextRightItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnSelected.png")),
		[&](Ref* ref)
	{
		PLAYEFFECT;
		if (flag)
		{
			interface_2->setVisible(true);
			flag = false;
		}
		else
		{
			interface_2->setVisible(false);
			flag = true;
		}
	}
	);
	nextRightItem->setPosition(WINSIZE.width - 55 , WINSIZE.height / 2 - 14);

	auto nor = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnNormal.png"));
	nor->setFlippedX(true);
	auto sel = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnSelected.png"));
	sel->setFlippedX(true);

	auto nextLeftItem = MenuItemSprite::create
	(
		nor,
		sel,
		[&](Ref* ref)
	{
		PLAYEFFECT;
		if (flag)
		{
			interface_2->setVisible(true);
			flag = false;
		}
		else
		{
			interface_2->setVisible(false);
			flag = true;
		}
	}
	);
	nextLeftItem->setPosition(55, WINSIZE.height/2 -14);


	auto menu = Menu::create(closeItem, nextRightItem, nextLeftItem, NULL);
	menu->setPosition(Point::ZERO);

	spriteBG->addChild(menu);

	return true;
}