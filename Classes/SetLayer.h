#ifndef SETLAYER_H
#define SETLAYER_H
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SetLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SetLayer);

	void changeMusicVol(Ref* pSender, Control::EventType type);
	void changeEffectVol(Ref* pSender, Control::EventType type);
	void saveSet(Ref* pSender);
	void closeBtn(Ref* pSender);
	void musicSet(Ref* pSender);
	void effectSet(Ref* pSender);
};

#endif//SETLAYER_H