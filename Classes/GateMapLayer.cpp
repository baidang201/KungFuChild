#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GateMapLayer.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "StartLayer.h"
#include "SelectGate.h"
#include "HelloWorldScene.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* GateMapLayer::createScene()
{
	Scene* scene = Scene::create();
	GateMapLayer* layer = GateMapLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GateMapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)* 100.0f;
		audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (audioEngine->isBackgroundMusicPlaying())
		{
			audioEngine->pauseBackgroundMusic();			
		}
		audioEngine->playBackgroundMusic("Sound/gateMap.wav", true);
	}
	else
	{
		audioEngine->pauseBackgroundMusic();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/gateMap.plist");

	bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GateMapBG.png"));
	bgPic->setPosition(WINSIZE.width/2.0, WINSIZE.height/2.0);
	this->addChild(bgPic);

	auto closeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseSelected.png")),
		CC_CALLBACK_1(GateMapLayer::closeFunc, this)
	);

	auto challengeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiaozhanNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiaozhanSelected.png")),
		CC_CALLBACK_1(GateMapLayer::challengeFunc, this)
		);

	closeItem->setPosition(WINSIZE.width - 47, WINSIZE.height - 44);
	challengeItem->setPosition(WINSIZE.width - 253, 7*WINSIZE.height / 72);

	auto menu = Menu::create(closeItem, challengeItem, NULL);
	this->addChild(menu);

	auto gateOneItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
		CC_CALLBACK_1(GateMapLayer::gateOneCallBack, this)
	);

	auto gateTwoItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png")),
		CC_CALLBACK_1(GateMapLayer::gateTwoCallBack, this)
	);

	auto gateThreeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png")),
		CC_CALLBACK_1(GateMapLayer::gateThreeCallBack, this)
	);

	selectGateMenu = SelectGate::create();
	selectGateMenu->addMenuItem(gateOneItem);
	selectGateMenu->addMenuItem(gateTwoItem);
	selectGateMenu->addMenuItem(gateThreeItem);
	selectGateMenu->setPosition(visibleSize.width/2, visibleSize.height/2 + 74);
	this->addChild(selectGateMenu, 2);

	auto m_pMoneyLabel = LabelTTF::create("1000", "", 45);
	m_pMoneyLabel->setColor(ccc3(0, 255, 255));
	m_pMoneyLabel->setPosition(300, 60);

	auto m_pEnergyLabel = LabelTTF::create("10", "", 45);
	m_pEnergyLabel->setColor(ccc3(0, 255, 255));
	m_pEnergyLabel->setPosition(640, 60);

	this->addChild(m_pMoneyLabel);
	this->addChild(m_pEnergyLabel);

	return true;

}

void GateMapLayer::gateOneCallBack(Ref* pSender)
{
	PLAYEFFECT;
	setIntToXML(GAMELEVEL_KEY, 1);
	setIntToXML(SELECTGATE, 1);
	UserDefault::getInstance()->flush();
	m_iSelectGate = 1;
	log("first gate");
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

void GateMapLayer::gateTwoCallBack(Ref* pSender)
{
	PLAYEFFECT;
	if (getBoolFromXML(GATEONE, false))
	{
		setIntToXML(GAMELEVEL_KEY, 2);
		setIntToXML(SELECTGATE, 2);
		UserDefault::getInstance()->flush();
		m_iSelectGate = 2;
		log("second gate");
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
}

void GateMapLayer::gateThreeCallBack(Ref* pSender)
{
	PLAYEFFECT;
	if (getBoolFromXML(GATETWO, false))
	{
		setIntToXML(GAMELEVEL_KEY, 3);
		setIntToXML(SELECTGATE, 3);
		UserDefault::getInstance()->flush();
		m_iSelectGate = 3;
		log("second gate");
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
}

void GateMapLayer::closeFunc(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(StartLayer::createScene());
}

void GateMapLayer::challengeFunc(Ref* pSender)
{
	PLAYEFFECT;
	selectGateMenu->getCurrentItem()->activate();
	//m_iSelectGate = 1;
	//Director::getInstance()->replaceScene(GameLayer:;createScene());
}