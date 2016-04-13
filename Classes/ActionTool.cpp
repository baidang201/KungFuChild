#include "ActionTool.h"

USING_NS_CC;

Animate* ActionTool::animationWithFrameName(const char* each_name, int iloops, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	int index = 1;
	do
	{
		String* name = String::createWithFormat("%s%d.png", each_name, index++);
		frame =SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		if(NULL == frame)
		{
			break;
		}
		animation->addSpriteFrame(frame);
	}while(true);
	
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(iloops);
	Animate* animate = Animate::create(animation);
	
	return animate;	
}


Animate* ActionTool::animationWithFrameAndNum(const char* frameName, int framecount, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	
	for(int index =1; index <=framecount; index++)
	{
		String* name = String::createWithFormat("%s%d.png", frameName, index++);
		frame =SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);		
	}
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);
	
	
	/*
	//function 2
	Vecotr<SpriteFrame* > animFrames;
	char str[20];
	for(int k=1; k<=framecount; k++)
	{
		sprintf(str, "%s%d.png", frameName, k);
		SpriteFrame* frame = SpriteFrameCache::getInstance()-?spriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	Animate* animate = Animate::create(Animation::createWithSpriteFrames(animFrames, delay));
	
	*/
	
	
	return animate;
	
}