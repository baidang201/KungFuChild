#ifndef  MONSTER_H
#define MONSTER_H

#include "cocos2d.h"
class Hero;
class GameMap;

USING_NS_CC;

class Monster : public Node
{
public:
	Monster();
	~Monster();

	int m_iType;
	bool IsRunning;
	bool IsAttack;
	bool IsHurt;
	bool IsDead;
	bool MonsterDirection;

	void InitMonsterSprite(char* name, char* a, char* die, char* walk, char* dieLast, int m_iLevel);

	Sprite* getSprite();

	void SetAnimation(const char* name_each, bool run_dirction, float delay, int iLoops);
	
	void StopAnimation();

	void AttackAnimation(const char* name_each, bool run_dirction, float delay, int iLoops);
	void AttackEnd();

	void HurntAnimation(const char* name_each, bool run_dirction, float delay, int iLoops);
	void HurnEnd();

	void DeadAnimation(const char* name_each, bool run_dirction, float delay, int iLoops);
	void DeadEnd();

	void BlinkEnd();

	void FollowRun(Hero* m_hero, GameMap* m_map);

	void JudegeAttack(float dt);


	void StartListen(Hero* m_hero, GameMap* m_map);
	void updateMonster(float delta);

	void Update(float delta);

	void StopAllActionAndRestoreFrame(char* frame_name);

	CREATE_FUNC(Monster);


private:
	Sprite* m_MonsterSprite;
	char* Monster_name;
	char* Monster_a;
	char* Monster_die;
	char* Monster_walk;
	char* Die_name;

	Hero* my_hero;
	GameMap* my_map;
	float dis;
	float m_iHP;
};

#endif // MONSTER_H