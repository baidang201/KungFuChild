#ifndef MIJILAYER_H
#define MIJILAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MijiLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MijiLayer);

	Sprite* spriteBG;
	Sprite* interface_1;
	Sprite* interface_2;

	bool flag;
};

#endif // MIJILAYER_H