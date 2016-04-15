#ifndef MONSTERONE_H
#define MONSTERONE_H

#include "cocos2d.h"
#include "GameMap.h"

USING_NS_CC;

class Monster;
class Hero;
class GameMap;

class MonsterOne : public Node
{
public:
	MonsterOne();
	~MonsterOne();

	void updateMonster(float delta);
	void showSecMon(float delta);
	void showThrMon(float delta);

	static MonsterOne* createWithMapAndHero(GameMap* map, Hero* hero);
	bool initMonster(GameMap* map, Hero* hero);

private:
	GameMap* m_pMap;
	Hero* m_pHero;

};


#endif //MONSTERONE_H