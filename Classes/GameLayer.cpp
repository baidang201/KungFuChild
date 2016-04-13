#include "GameLayer.h"
#include "GameMap.h"
#include "Hero.h"
#include "Monster.h"
#include "GateMapLayer.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

Scene* GameLayer::createScene()
{
	Scene* scene = Scene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//音乐
	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		audioEngine->setBackgroundMusicVolume(music);

		if (audioEngine->isBackgroundMusicPlaying())
		{
			audioEngine->pauseBackgroundMusic();
		}
		audioEngine->playBackgroundMusic("Sound/GameBGM.wav", true);
	}
	else
	{
		audioEngine->pauseBackgroundMusic();
	}

	//资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBefore.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapRoad.plist");

	//初始化
	String* bgName = String::createWithFormat("bgmp%d.png", m_iSelectGate);
	String* miName = String::createWithFormat("MapMiddle%d", m_iSelectGate);
	String* groundName = String::createWithFormat("MapGround%d", m_iSelectGate);
	String* beforeName = String::createWithFormat("MapBefore%d", m_iSelectGate);
	String* comboName = String::createWithFormat("comboBtn%d", m_iSelectGate);

	auto bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgName->getCString()));
	bgPic->setPosition(WINSIZE.width/2, WINSIZE.height/2);
	this->addChild(bgPic);

	myMap = GameMap::create();
	myMap->InitMap(miName->getCString(), groundName->getCString(), beforeName->getCString());
	this->addChild(myMap, 1);

	//技能键
	auto m_pFistBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fist.png"));
	auto m_pFistBtn = ControlButton::create(m_pFistBG);
	m_pFistBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fist.png"))->getContentSize());

	auto m_pFootBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("foot.png"));
	auto m_pFootBtn = ControlButton::create(m_pFootBG);
	m_pFootBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("foot.png"))->getContentSize());

	auto m_pJumpBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump.png"));
	auto m_pJumpBtn = ControlButton::create(m_pJumpBG);
	m_pJumpBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump.png"))->getContentSize());

	auto m_pComboBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("combo.png"));
	auto m_pComboBtn = ControlButton::create(m_pComboBG);
	m_pComboBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("combo.png"))->getContentSize());

	//按键背景
	auto m_pFistPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("quan.png"));
	auto m_pFootPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jiao.png"));
	auto m_pJumpPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiao.png"));
	auto m_pComboPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiao.png"));

	auto m_pFistPicSize = m_pFistPic->getContentSize();
	m_pFistBtn->setPosition(ccp(m_pFistPicSize.width/2, m_pFistPicSize.height/2));
	m_pFistBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::fistAttack), Control::EventType::TOUCH_UP_INSIDE);

	auto m_pFootPicSize = m_pFootPic->getContentSize();
	m_pFootBtn->setPosition(ccp(m_pFootPicSize.width / 2, m_pFootPicSize.height / 2));
	m_pFootBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::footAttack), Control::EventType::TOUCH_UP_INSIDE);

	auto m_pJumpPicSize = m_pJumpPic->getContentSize();
	m_pJumpBtn->setPosition(ccp(m_pJumpPicSize.width / 2, m_pJumpPicSize.height / 2));
	m_pJumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::comboAttack), Control::EventType::TOUCH_UP_INSIDE);

	auto m_pComboPicSize = m_pComboPic->getContentSize();
	m_pComboBtn->setPosition(ccp(m_pComboPicSize.width / 2, m_pComboPicSize.height / 2));
	m_pComboBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::jump), Control::EventType::TOUCH_UP_INSIDE);

	m_pFistPic->addChild(m_pFistBtn, 1);
	m_pFootPic->addChild(m_pFootBtn, 1);
	m_pJumpPic->addChild(m_pJumpBtn, 1);
	m_pComboPic->addChild(m_pComboBtn, 1);

	m_pFistPic->setPosition(WINSIZE.width - 230, 76);
	m_pFootPic->setPosition(WINSIZE.width - 73, 76);
	m_pJumpPic->setPosition(WINSIZE.width - 60, 220);
	m_pComboPic->setPosition(WINSIZE.width - 387, 67);


	m_pComboPic->setVisible(false);

	this->addChild(m_pFistPic, 1);
	this->addChild(m_pFootPic, 1);
	this->addChild(m_pJumpPic, 1);
	this->addChild(m_pComboPic, 1);

	//行走 暂停按键
	auto pauseGameItem = MenuItemSprite::create(
	Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseNormal.png")),
	Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseSelected.png")),
		CC_CALLBACK_1(GameLayer::gamePause, this)
	);

	auto backwardGB = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionNormal.png"));
	auto backwardSelBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionSelected.png"));
	auto backwardBtn = ControlButton::create(backwardGB);
	backwardBtn->setBackgroundSpriteForState(backwardSelBG, Control::State::HIGH_LIGHTED);
	backwardBtn->setZoomOnTouchDown(false);
	backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::TOUCH_DOWN);
	backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::TOUCH_UP_INSIDE);
	backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::DRAG_OUTSIDE);
	backwardBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionNormal.png"))->getContentSize());

	auto forwardGB = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForNormal.png"));
	auto forwardSelBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForSelected.png"));
	auto forwardBtn = ControlButton::create(forwardGB);
	forwardBtn->setBackgroundSpriteForState(forwardSelBG, Control::State::HIGH_LIGHTED);
	forwardBtn->setZoomOnTouchDown(false);
	forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::TOUCH_DOWN);
	forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::TOUCH_UP_INSIDE);
	forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::DRAG_OUTSIDE);
	forwardBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForNormal.png"))->getContentSize());


	pauseGameItem->setPosition(WINSIZE.width - 50, WINSIZE.height - 40);
	backwardBtn->setPosition(117, 70);
	forwardBtn->setPosition(304, 70);

	auto menuWalk = Menu::create(pauseGameItem, NULL);
	menuWalk->setPosition(Point::ZERO);
	this->addChild(backwardBtn, 1);
	this->addChild(forwardBtn, 1);
	this->addChild(menuWalk, 1);

	//英雄
	m_pHero = Hero::create();
	m_pHero->InitHeroSprite("idle.png", 1);
	m_pHero->setPosition(100, 360);
	m_pHero->addChild(m_pHero, 3);

	//状态栏
	m_pBG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("barGround.png"));

	m_pHPBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HPBar.png")));
	m_pHPBar->setType(ProgressTimer::Type::BAR);
	m_pHPBar->setMidpoint(ccp(0, 0.5));
	m_pHPBar->setBarChangeRate(ccp(1, 0));
	m_pHPBar->setPercentage(100);

	m_pMPBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MPBar.png")));
	m_pMPBar->setType(ProgressTimer::Type::BAR);
	m_pMPBar->setMidpoint(ccp(0, 0.5));
	m_pMPBar->setBarChangeRate(ccp(1,0));
	m_pHPBar->setPercentage(100);

	m_pBG->addChild(m_pHPBar);
	m_pBG->addChild(m_pMPBar);

	m_pBG->setPosition(260, WINSIZE.height - 60);

	this->addChild(m_pBG, 1);

	this->scheduleUpdate();

	return true;

	return true;
}

void GameLayer::gamePause(Ref * pSender)
{
}

void GameLayer::fistAttack(Ref * pSender, Control::EventType type)
{
}

void GameLayer::footAttack(Ref * pSender, Control::EventType type)
{
}

void GameLayer::comboAttack(Ref * pSender, Control::EventType type)
{
}

void GameLayer::jump(Ref * pSender, Control::EventType type)
{
}

void GameLayer::forward(Ref * pSender, Control::EventType type)
{
}

void GameLayer::backward(Ref * pSender, Control::EventType type)
{
}

void GameLayer::update(float delta)
{
}
