#ifndef HELPLAYER_H
#define HELPLAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelpLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpLayer);

private:
	LabelTTF* text;
	void scrollback();

};

#endif //HELPLAYER_H