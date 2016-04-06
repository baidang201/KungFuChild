#include "Hero.h"
#include "ActionTool.h"

void Hero::InitHeroSprite(char* hero_name, int m_iLevel)
{
	m_HeroSprite = NULL;
	m_bCanCrazy = false;
	m_bIsAction = false;
	m_bIsJumping = false;
	HeroDirection - false;//init turn right
	Hero_name = NULL;
	IsRunning = false;
	IsAttack = false;
	IsHurt = false;
	IsDead = false;

	m_iCurrentMp = 0.0f;
	m_iTotleMp = 100.0f;
	m_iSpeed = 5;

	Hero_name = hero_name;
	m_iCurrentHp = m_iTotleHp = 300.0f* m_iLevel;
	percentage = 100.0f;

	this->m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hero_name));


}


Sprite* Hero::GetSprite()
{
	return m_HeroSprite;
}


//run_direction ¾«ÁéÁ³³¯Ïò false³¯ÓÒ
void Hero::SetAnimation(const char* frameName, float delay, bool run_direction)
{
	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
		m_HeroSprite->setFlippedX(run_direction);
	}
	if (IsRunning || IsHurt || IsAttack)
		return;

	Animate* action = ActionTool::animationWithFrameName(frameName, -1, delay);
	m_HeroSprite->runAction(action);
	IsRunning = true;
}


void Hero::StopAnimation()
{
	if (!IsRunning)
	{
		return;
	}

	StopAllActionAndRestoreFrame(Hero_name);

	IsRunning = false;
}


void Hero::JumpUpAnimation(const char* name_each, float delay, bool run_direction)
{
	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
		m_HeroSprite->setFlippedX(run_direction);
	}

	if (IsHurt || IsAttack || IsDead)
	{
		return;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, -1, delay);
	m_HeroSprite->runAction(action);
	m_bIsJumping = true;
}


void Hero::JumpDownAnimation(const char* name_each, float delay, bool run_direction)
{
	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
		m_HeroSprite->setFlippedX(run_direction);
	}

	if (IsHurt || IsAttack)
	{
		return;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, -1, delay);
	m_HeroSprite->runAction(action);
	m_bIsJumping = true;
}


void Hero::JumpEnd()
{
	StopAllActionAndRestoreFrame(Hero_name);
	m_bIsJumping = false;
}


void Hero::AttackAnimatiion(const char* name_each, float delay, bool run_direction)
{
	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
		m_HeroSprite->setFlippedX(HeroDirection);
	}

	if (IsAttack || m_bIsJumping)
	{
		return;
	}

	Animate* act = ActionTool::animationWithFrameName(name_each, 1, delay);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::AttackEnd));
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);
	IsAttack = true;
	m_HeroSprite->runAction(attackact);
}


void Hero::AttackEnd()
{
	m_HeroSprite->setFlippedX(HeroDirection);
	IsAttack = false;

	if (true == m_bCanCrazy)
	{
		m_bCanCrazy = false;
		m_iCurrentMp = 0;
	}
}

void Hero::HurtByMonsterAnimatioin(const char* name_each, float delay, bool run_direction)
{
	if (IsHurt || IsDead)
	{
		return;
	}

	//hurn first
	if (IsRunning || IsAttack)
	{
		StopAllActionAndRestoreFrame(Hero_name);

		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::HurtByMonsterEnd));
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_HeroSprite->runAction(hurtackact);
	IsHurt = true;
}


void Hero::HurtByMonsterEnd()
{
	m_iCurrentHp -= 20.0f;
	IsHurt = false;
	percentage = m_iCurrentHp / m_iTotleHp * 100.0f;
	if (m_iCurrentHp < 0.0f)
	{
		DeadAnimation("dead", 0, HeroDirection);
	}
}

void Hero::DeadAnimation(const char* name_each, float delay, bool run_direction)
{
	m_HeroSprite->stopAllActions();

	if (HeroDirection != run_direction)
	{
		HeroDirection = run_direction;
		m_HeroSprite->setFlippedX(run_direction);
	}

	Animate* act = ActionTool::animationWithFrameName(name_each, 1, delay);
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::DeadEnd));
	
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);
	m_HeroSprite->runAction(attackact);
	Director::getInstance()->getScheduler()->setTimeScale(0.5);
}


void Hero::DeadEnd()
{
	IsDead = true;

	StopAllActionAndRestoreFrame("monsterDie6.png");
}

//is in middle
bool Hero::JudgePositon(Size visibleSize)
{
	if (
			this->getPositionX() >(visibleSize.width/2.0 + 2.0)
		|| this->getPositionX()<(visibleSize.width/2.0 - 2.0)
		)
		return false;
	else
		return true;
}

void Hero::StopAllActionAndRestoreFrame(char* frame_name )
{
	m_HeroSprite->stopAllActions();
	this->removeChild(m_HeroSprite, true); // remove old sprite
	this->m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frame_name));
	m_HeroSprite->setFlippedX(HeroDirection);
	this->addChild(m_HeroSprite);
}

