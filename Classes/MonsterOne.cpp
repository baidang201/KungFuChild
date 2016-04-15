#include "MonsterOne.h"
#include "cocos2d.h"
#include "GameMap.h"
#include "GlobalData.h"
#include "GlobalDefine.h"
#include "Monster.h"
#include "Hero.h"

MonsterOne::MonsterOne()
{

}

MonsterOne::~MonsterOne()
{

}

bool MonsterOne::initMonster(GameMap* map, Hero* hero)
{
	this->m_pMap = map;
	this->m_pHero = hero;

	monsterOneList.clear();
	monsterTwoList.clear();
	monsterThreeList.clear();
	monsterShowList.clear();

	auto m_pMonster1 = Monster::create();
	m_pMonster1->InitMonsterSprite("monsterWalk5.png", "monsterA", "monsterDie", "monsterWalk", "monsterDie6.png", 1);
	m_pMonster1->m_iType = 1;
	m_pMonster1->setVisible(true);
	m_pMonster1->setPosition(1100, 365);
	m_pMap->addChild(m_pMonster1);
	m_pMonster1->StartListen(m_pHero, m_pMap);
	monsterShowList.pushBack(m_pMonster1);
	m_bFlag1 = false;

	//第二波
	auto m_pMonster2 = Monster::create();
	m_pMonster2->InitMonsterSprite("monsterWalk5.png", "monsterA", "monsterDie", "monsterWalk", "monsterDie6.png", 1);
	m_pMonster2->m_iType = 1;
	m_pMonster2->setVisible(false);
	m_pMonster2->setPosition(2000, 365);
	monsterTwoList.pushBack(m_pMonster2);

	auto m_pMonster3 = Monster::create();
	m_pMonster3->InitMonsterSprite("monsterWalk5.png", "monsterA", "monsterDie", "monsterWalk", "monsterDie6.png", 1);
	m_pMonster3->m_iType = 1;
	m_pMonster3->setVisible(false);
	m_pMonster3->setPosition(-150, 365);
	monsterTwoList.pushBack(m_pMonster3);
	m_bFlag2 = true;

	//第三波
	for (int i = 0; i < 3; i++)
	{
		auto m_pMonster = Monster::create();
		m_pMonster->InitMonsterSprite("monsterWalk5.png", "monsterA", "monsterDie", "monsterWalk", "monsterDie6.png", 1);
		m_pMonster->m_iType = 1;
		if (i == 0 || i == 1)
		{
			m_pMonster->setPosition(-100*i, 365);
		}
		else
		{
			m_pMonster->setPosition(2000, 365);
		}
		m_pMonster->setVisible(false);
		monsterThreeList.pushBack(m_pMonster);
	}
	m_bFlag3 = true;

	this->schedule(schedule_selector(MonsterOne::updateMonster));

	return true;
}

void MonsterOne::updateMonster(float delta)
{
	//第二波
	if (m_bFlag1 == false && m_bFlag2 == true)
	{
		bool noMonster = true;
		for (auto monster : monsterShowList)
		{
			if (!monster->IsDead)
			{
				noMonster = false;
			}
		}

		if (noMonster)
		{
			this->scheduleOnce(schedule_selector(MonsterOne::showSecMon), 4.0f);
		}
	}

	//第三波
	if (m_bFlag2 == false && m_bFlag3 == true)
	{
		bool noMonster = true;
		for (auto monster : monsterShowList)
		{
			if (!monster->IsDead)
			{
				noMonster = false;
			}
		}

		if (noMonster)
		{
			this->scheduleOnce(schedule_selector(MonsterOne::showThrMon), 3.0f);
		}
	}

}
void MonsterOne::showSecMon(float delta)
{
	for (auto monster : monsterTwoList)
	{
		monster->setVisible(true);
		m_pMap->addChild(monster);
		monster->StartListen(m_pHero, m_pMap);
		monsterShowList.pushBack(monster);
		m_bFlag2 = false;
	}
}
void MonsterOne::showThrMon(float delta)
{
	for (auto monster : monsterThreeList)
	{
		monster->setVisible(true);
		m_pMap->addChild(monster);
		monster->StartListen(m_pHero, m_pMap);
		monsterShowList.pushBack(monster);
		m_bFlag3 = false;
	}
}

MonsterOne* MonsterOne::createWithMapAndHero(GameMap* map, Hero* hero)
{
	MonsterOne* monsterOne = new MonsterOne();
	if (monsterOne && monsterOne->initMonster(map, hero))
	{
		monsterOne->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monsterOne);
	}
	return monsterOne;
}

