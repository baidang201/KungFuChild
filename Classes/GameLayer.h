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
	CREATE_FUNC(GameLayer);

	void gamePause(Ref* pSender);

	void fistAttack(Ref* pSender, Control::EventType type);
	void footAttack(Ref* pSender, Control::EventType type);
	void comboAttack(Ref* pSender, Control::EventType type);
	void jump(Ref* pSender, Control::EventType type);

	void forward(Ref* pSender, Control::EventType type);
	void backward(Ref* pSender, Control::EventType type);

	virtual void update(float delta);

private:
	Hero* m_pHero;
	Monster* m_pMonster;

	GameMap* myMap;

	Sprite* m_pBG;

	ProgressTimer* m_pHPBar;
	ProgressTimer* m_pMPBar;

	ControlButton* m_pComboBtn;

	Sprite* m_pComboPic;

};



#endif //GAMELAYER_H