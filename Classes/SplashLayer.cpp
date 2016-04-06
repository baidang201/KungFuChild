#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "SplashLayer.h"
#include "StartLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SplashLayer::createScene()
{
	Scene* splashScene = Scene::create();
	SplashLayer* layer = SplashLayer::create();
	splashScene->addChild(layer);
	return splashScene;
}

bool SplashLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	logoSprite = Sprite::create("logo.png");
	logoSprite->setPosition(WINSIZE.width/2, WINSIZE.height/2);
	this->addChild(logoSprite);

	if(! getBoolFromXML("_IS_EXISTED"))
	{
		initUserData();
		setBoolToXML("_IS_EXISTED", true);
		UserDefault::getInstance()->flush();
	}
	
	setFloatToXML(SOUNDVOL, 0.80f);
	setFloatToXML(MUSICVOL, 0.35f);
	UserDefault::getInstance()->flush();
	m_iNumOfLoad = 0;

	//Í¼Æ¬ºÍÉùÒôÒì²½¼ÓÔØ
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/startGame.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/gameLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/setLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/cheatsLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/gateMap.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/pauseLayer.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/hero.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/heroComobo.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("pnglist/heroGun.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	

	_loadingAudioThread = new std::thread(&SplashLayer::loadingAudio, this);

	return true;
}

void SplashLayer::loadingTextureCallBack(Texture2D* texture)
{
	switch (m_iNumOfLoad++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/startGame.plist", texture);
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/gameLayer.plist", texture);
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/setLayer.plist", texture);
		break;
	case 3:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/cheatsLayer.plist", texture);
		break;
	case 4:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/gateMap.plist", texture);
		break;
	case 5:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/pauseLayer.plist", texture);
		break;
	case 6:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/hero.plist", texture);
		break;
	case 7:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/heroComobo.plist", texture);
		break;
	case 8:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/heroGun.plist", texture);
		this->schedule(schedule_selector(SplashLayer::nextScene), 1, 1, 1);
		break;
	default:
		break;
	}
}


void SplashLayer::loadingAudio()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/startBGM.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound/button.wav");
}

void SplashLayer::initUserData()
{
	setIntToXML(GAMELEVEL_KEY, 1);
	setIntToXML(HEROENERGY_KEY, 10);
	setIntToXML(HEROCOIN_KEY, 1000);
	setBoolToXML(SOUND_KEY, true);
	setBoolToXML(MUSIC_KEY, true);
	UserDefault::getInstance()->flush();
}

void SplashLayer::nextScene(float dt)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StartLayer::createScene()));
}

void SplashLayer::onExit()
{
	Layer::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
	this->unschedule(schedule_selector(SplashLayer::nextScene));
}

