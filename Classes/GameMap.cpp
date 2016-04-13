#include "GameMap.h"
#include "GlobalDefine.h"
#include "Hero.h"
#include "cocos2d.h"

USING_NS_CC;

GameMap::GameMap()
{
	m_map1 = NULL;
	m_map2 = NULL;
	m_map3 = NULL;
}

GameMap::~GameMap()
{

}

void GameMap::InitMap(const char* map_name1, const char* map_name2, const char* map_name3)
{
	this->m_map1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(map_name1));
	this->m_map2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(map_name2));
	this->m_map3 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(map_name3)); 

	m_map1->setAnchorPoint(Point(0,0));
	m_map1->setTag(11);

	m_map2->setAnchorPoint(Point(0,0));
	m_map3->setAnchorPoint(Point(0,0));

	parallax = ParallaxNode::create();
	parallax->addChild(m_map1, 1, Point(1.18, 0), Point(0, 360));
	parallax->addChild(m_map2, 2, Point(1,0), Point(0,0));
	parallax->addChild(m_map3, 3, Point(0.7, 0), Point(0, 0));


	this->setAnchorPoint(Point(0,0));
	this->addChild(parallax);

}

void GameMap::MoveMap(Hero* hero)
{
	auto map = (Sprite*)parallax->getChildByTag(11);
	if (hero->JudgePositon(WINSIZE) && hero->HeroDirection == false)//精灵向左到中间，地图才移动
	{
		if (this->getPositionX() >= -(m_map2->getContentSize().width - WINSIZE.width))//防止超出右边缘
		{
			this->setPosition(this->getPositionX() - hero->m_iSpeed, this->getPositionY());
		}
	}
	if (hero->JudgePositon(WINSIZE) && hero->HeroDirection == true)//地图向右移动到中间才移动
	{
		if (this->getPositionX() <= -10)//防止超出左边缘
		{
			this->setPosition(this->getPositionX() + hero->m_iSpeed, this->getPositionY());
		}
	}

}

bool GameMap::JudgeMap(Hero* hero)
{
	if (this->getPositionX() >= -(m_map2->getContentSize().width - WINSIZE.width) && hero->HeroDirection == false)
		return false;
	else if (this->getPositionX() <= -10 && hero->HeroDirection == true)
		return false;
	else
		return true;
}