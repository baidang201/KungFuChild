#ifndef HERO_H
#define HERO_H

#include "cocos2d.h"

USING_NS_CC;

class Hero : public Node
{
public:
	void InitHeroSprite(char* hero_name, int iLevel);
	
	Sprite* GetSprite();
	
	//run_direction 精灵脸朝向 false朝右
	void SetAnimation(const char* frameName, float delay, bool run_direction);
	
	void StopAnimation();
	
	void JumpUpAnimation(const char* name_each, float delay, bool run_direction);
	
	void JumpDownAnimation(const char* name_each, float delay, bool run_direction);
	
	void JumpEnd();
	
	void AttackAnimatiion(const char* name_each, float delay, bool run_direction);
	
	void AttackEnd();
	
	void HurtByMonsterAnimatioin(const char* name_each, float delay, bool run_direction);

	void HurtByMonsterEnd();

	void DeadAnimation(const char* name_each, float delay, bool run_direction);
	
	void DeadEnd();
	
	bool JudgePositon(Size visibleSize);//判断是否运动到窗口中间
	
	void StopAllActionAndRestoreFrame(char* frame_name);

	bool IsDead;
	
	float m_iCurrentHp;
	float m_iTotleHp;
	float m_iCurrentMp;
	float m_iTotleMp;
	
	float percentage;
	float m_iSpeed;
	
	bool m_bIsAction;
	bool m_bIsJumping;
	bool IsRunning;
	bool IsAttack;
	
	bool IsHurt;
	
	bool HeroDirection;
	bool m_bCanCrazy;
	
	CREATE_FUNC(Hero);
private:
		Sprite* m_HeroSprite;
		char* Hero_name;
};


#endif //HERO_H