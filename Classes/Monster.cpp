#include "Monster.h"
#include "ActionTool.h"
#include "Hero.h"
#include "GameMap.h"

USING_NS_CC;

Monster::Monster()
{
	IsRunning = false;
	MonsterDirection = true;
	Monster_name = NULL;
	IsAttack = false;
	my_hero = NULL;
	my_map = NULL;
	dis = 10000;

	IsHurt = false;
	IsDead = false;
}


Monster::~Monster()
{
}


void Monster::InitMonsterSprite(char* name, char* a, char* die, char* walk, char* dieLast, int m_iLevel)
{
	Monster_name = name;
	Monster_a = a;
	Monster_walk = walk;
	Monster_die = die;
	Die_name = dieLast;

	m_iHP = 100 * (1 + 0.3*m_iLevel);
	this->m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	this->addChild(m_MonsterSprite);
}


Sprite* Monster::getSprite()
{
	return m_MonsterSprite;
}


void Monster::SetAnimation(const char* name_each, bool run_dirction, float delay, int iLoops)
{
	if (MonsterDirection != run_dirction)
	{
		MonsterDirection = run_dirction;
		m_MonsterSprite->setFlippedX(run_dirction);
	}

	if (IsRunning || IsAttack || IsHurt || IsDead)
	{
		return;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, iLoops, delay);
	m_MonsterSprite->runAction(RepeatForever::create(action));
	IsRunning = true;
}


void Monster::StopAnimation()
{
	if (!IsRunning)
	{
		return;
	}

	StopAllActionAndRestoreFrame(Monster_name);

	IsRunning = false;
}


void Monster::AttackAnimation(const char* name_each, bool run_dirction, float delay, int iLoops)
{
	if (IsRunning || IsAttack || IsHurt || IsDead)
	{
		return;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));

	m_MonsterSprite->runAction(Sequence::create(action, callFunc, NULL));
	IsAttack = true;
}

void Monster::AttackEnd()
{
	StopAllActionAndRestoreFrame(Monster_name);

	IsAttack = false;
}


void Monster::HurntAnimation(const char* name_each, bool run_dirction, float delay, int iLoops)
{
	if (IsHurt || IsDead)
	{
		return;
	}

	if (IsRunning || IsAttack)
	{
		StopAllActionAndRestoreFrame(Monster_name);

		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::HurnEnd));
	m_MonsterSprite->runAction(Sequence::create(action, callFunc, NULL));
	IsHurt = true;
}

void Monster::HurnEnd()
{
	IsHurt = false;

	if (my_hero->m_bCanCrazy)
	{
		m_iHP -= 100;
	}
	else
	{
		m_iHP -= 30;
	}

	if (m_iHP <= 0)
	{
		DeadAnimation(Monster_die, MonsterDirection, 0.1f, 1.0f);
	}
}

void Monster::DeadAnimation(const char * name_each, bool run_dirction, float delay, int iLoops)
{
	IsDead = true;

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::DeadEnd));
	m_MonsterSprite->runAction(Sequence::create(action, callFunc, NULL));

	if (my_hero->m_iCurrentMp < 100)
	{
		my_hero->m_iCurrentMp = (my_hero->m_iCurrentMp + 50);
		if (my_hero->m_iCurrentMp > 100)
		{
			my_hero->m_iCurrentMp = 100;
		}
	}
 
}

void Monster::DeadEnd()
{
	StopAllActionAndRestoreFrame(Die_name);

	Blink* blinkact = Blink::create(3,3);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::BlinkEnd));
	m_MonsterSprite->runAction(Sequence::create(blinkact, callFunc, NULL));
}


void Monster::BlinkEnd()
{
	this->removeAllChildren();
}


void Monster::FollowRun(Hero* m_hero, GameMap* m_map)
{
	float x = m_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	dis = fabs(x);

	if (x > 1280)
	{
		return;
	}
	if(dis <= 120)
	{
		this->StopAnimation();
		scheduleOnce(schedule_selector(Monster::JudegeAttack), 2.5f);
		return;
	}

	if (x < -100)
	{
		MonsterDirection = false;
		m_MonsterSprite->setFlippedX(MonsterDirection);

		if (IsAttack)
			return;

		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);
		this->setPosition(this->getPositionX() - 1.5, this->getPositionY());
	}
	else if (x > 100)
	{
		MonsterDirection = true;
		m_MonsterSprite->setFlippedX(MonsterDirection);

		if (IsAttack)
			return;

		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);
		this->setPosition(this->getPositionX() + 1.5, this->getPositionY());
	}

}


void Monster::JudegeAttack(float dt)
{
	this->AttackAnimation(Monster_a, MonsterDirection, 0.08f, -1);
}



void Monster::StartListen(Hero* m_hero, GameMap* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	this->schedule(schedule_selector(Monster::updateMonster), 1.0);
	this->scheduleUpdate();

}

void Monster::updateMonster(float delta)
{
	if (IsDead || my_hero->IsDead)
	{
		return;
	}

	float x =  my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	dis = fabs(x);
}


void Monster::Update(float delta)
{
	if (IsDead || my_hero->IsDead)
	{
		return;
	}

	if (dis < 1280 && my_hero->IsDead == false)
	{
		FollowRun(my_hero, my_map);
	}
}

void Monster::StopAllActionAndRestoreFrame(char* frame_name)
{
	m_MonsterSprite->stopAllActions();
	this->removeChild(m_MonsterSprite, true); // remove old sprite
	this->m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name));
	m_MonsterSprite->setFlippedX(MonsterDirection);
	this->addChild(m_MonsterSprite);
}