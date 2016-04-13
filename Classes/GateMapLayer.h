#ifndef GATEMAPLAYER_H
#define GATEMAPLAYER_H
#include "cocos2d.h"
USING_NS_CC;

class SelectGate;

class GateMapLayer : Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GateMapLayer);

	Sprite* bgPic;
	Sprite* closeBtn;
	Sprite* tips;
	LabelTTF* coin;
	LabelTTF* energy;

	SelectGate* selectGateMenu;

	void gateOneCallBack(Ref* pSender);
	void gateTwoCallBack(Ref* pSender);
	void gateThreeCallBack(Ref* pSender);

	void closeFunc(Ref* pSender);
	void challengeFunc(Ref* pSender);
	
};

#endif //GATEMAPLAYER_H