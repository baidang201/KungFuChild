#ifndef STARTLAYER_H
#define STARTLAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class StartLayer : Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(StartLayer);

private:

	void touchSet(Ref* pSender);
	void touchLib(Ref* pSender);
	void touchMiJi(Ref* pSender);
	void touchCG(Ref* pSender);
	void touchTZ(Ref* pSender);
	void touchHelp(Ref* pSender);

	Sprite* title;
	Sprite* bgPic;

};


#endif STARTLAYER_H