#ifndef TUJILAYER_H
#define TUJILAYER_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class TujiLayer : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TujiLayer);

	ListView* listView;
	void selectedItemEvent(Ref* pSender, ListViewEventType type);

private:
	size_t m_iBeforeSel;

	Sprite* m_pMZ_Pic;
	LabelTTF* m_pMZLable;
	Sprite* m_pMZ_Txt;

	Sprite* m_pLion_Pic;
	LabelTTF* m_pLionLable;

	Sprite* m_pStone_Pic;
	LabelTTF* m_pStoneLable;
};

#endif//TUJILAYER_H