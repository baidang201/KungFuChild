#ifndef SELECTGATE_H
#define SELECTAGTE_H

#include "cocos2d.h"

USING_NS_CC;


//模仿轮播图片选择菜单
class SelectGate : public Layer
{
public:
	CREATE_FUNC(SelectGate);

	void addMenuItem(MenuItem* item);

	void updatePosition();

	void updatePositionWithAnimation();

	//位置矫正，当超过1/3，进1， true为正向
	void rectify(bool forward);

	virtual bool init();

	void reset();

	MenuItem* getCurrentItem();

private:
	void setIndex(int index);

	float getIndex();

	//数学公式 width*index /(abs(index)+CALC_A)   其中CALC_A为常数
	float calcFunction(float index, float width);


private:
	float _index;

	float _lastIndex;

	Vector<MenuItem*> _items;

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);

	//确定哪个菜单项在前面
	void actionEndCallBack(float dx);

	MenuItem* _selectedItem;
};




#endif //SELECTGATE_H