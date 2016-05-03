#ifndef __ENEMYBULLET_H__
#define __ENEMYBULLET_H__

#include "cocos2d.h"

class EnemyBullet : public cocos2d::Node
{
public:
	cocos2d::Layer *gameLayer;
	static EnemyBullet* getInstance();
	cocos2d::Sprite* create(cocos2d::Sprite*, cocos2d::Layer*);

};

#endif 
