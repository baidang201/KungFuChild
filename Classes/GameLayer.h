#ifndef GAMELAYER_H
#define GAMELAYER_H

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ActionTool.h"
#include "GlobalData.h"
#include "GlobalDefine.h"
#include "cocos-ext.h"
#include "Monster.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Hero;
class ProgressBar;
class GameMap;

class GameLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	void gamePause(Ref* pSender);
	void gameOver(float delta);
	void gameVictory(float delta);

	void fistAttack(Ref* pSender, Control::EventType type);
	void footAttack(Ref* pSender, Control::EventType type);
	void comboAttack(Ref* pSender, Control::EventType type);
	void jump(Ref* pSender, Control::EventType type);

	void forward(Ref* pSender, Control::EventType type);
	void backward(Ref* pSender, Control::EventType type);

	bool isAttackMonster(Hero* hero, Monster* monster);

	virtual void update(float delta);

	CREATE_FUNC(GameLayer);

private:
	Hero* m_pHero;
	Monster* m_pMonster1;

	GameMap* myMap;

	Sprite* m_pBG;

	ProgressTimer* m_pHPBar;
	ProgressTimer* m_pMPBar;

	ControlButton* m_pComboBtn;

	Sprite* m_pComboPic;


	RenderTexture* render;
	RenderTexture* renderResult;

	float velocity = 0.0f;
	float getVelocity();

	bool m_bDirection;
	bool m_bRun;
	bool m_bJump;
};



#endif //GAMELAYER_H