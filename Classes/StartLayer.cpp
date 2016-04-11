#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "StartLayer.h"
#include "MijiLayer.h"
#include "HelloWorldScene.h"
#include "SetLayer.h"
#include "TujiLayer.h"
#include "HelpLayer.h"
#include "GateMapLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* StartLayer::createScene()
{
	Scene* startScene = Scene::create();
	StartLayer* layer = StartLayer::create();
	startScene->addChild(layer);

	return startScene;
}

bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/galerLayer.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/monster.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/resultLayer.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBg.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapMid.plist");

	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL) * 100.0f;
		audioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (audioEngine->isBackgroundMusicPlaying())
		{
			audioEngine->pauseBackgroundMusic();
			audioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);			
		}
		else
		{
			audioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);
		}
	}
	else
	{
		audioEngine->pauseBackgroundMusic();
	}

	title = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Title.png"));
	title->setPosition(WINSIZE.width/2, WINSIZE.height/2 + 186);

	bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MainMenuBackground.png"));
	bgPic->setPosition(WINSIZE.width/2, WINSIZE.height/2);

	this->addChild(title);
	this->addChild(bgPic);

	auto helpItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpSelected.png")),
		CC_CALLBACK_1(StartLayer::touchHelp, this)
	);

	auto tujiItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PhotoGalleryNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PhotoGallerySelected.png")),
		CC_CALLBACK_1(StartLayer::touchLib, this)
	);

	auto setItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetSelected.png")),
		CC_CALLBACK_1(StartLayer::touchSet, this)
	);

	auto mijiItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsSelected.png")),
		CC_CALLBACK_1(StartLayer::touchMiJi, this)
	);

	auto chuangguanItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("EmigratedNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("EmigratedSelected.png")),
		CC_CALLBACK_1(StartLayer::touchCG, this)
	);

	auto tiaozhanItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ChallengeNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ChallengeSelected.png")),
		CC_CALLBACK_1(StartLayer::touchTZ, this)
	);

	tujiItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 73);
	mijiItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 209);
	setItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 346);
	helpItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 473);
	chuangguanItem->setPosition(WINSIZE.width/2 - 240, WINSIZE.height/2 - 86);
	tiaozhanItem->setPosition(WINSIZE.width/2 - 240, WINSIZE.height/2 - 250);

	auto menu = Menu::create(tujiItem, mijiItem, setItem, helpItem, chuangguanItem, tiaozhanItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);

	return true;
}


void StartLayer::touchSet(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::touchLib(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(TujiLayer::createScene());
}

void StartLayer::touchMiJi(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(MijiLayer::createScene());
}

void StartLayer::touchCG(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(GateMapLayer::createScene());
}

void StartLayer::touchTZ(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(GateMapLayer::createScene());
}

void StartLayer::touchHelp(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(HelpLayer::createScene());
}
