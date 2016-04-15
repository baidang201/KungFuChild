#ifndef PAUSELAYER_H
#define PAUSELAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class PauseLayer : public Layer
{
public:
	static Scene* createScene(RenderTexture* rt);
	virtual bool init();
	CREATE_FUNC(PauseLayer);

	Sprite* spriteOn;
	Sprite* spriteDown;

	void musicSet(Ref* pSender);
};


#endif //PAUSELAYER_H