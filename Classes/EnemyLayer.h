#ifndef __ENEMYLAYER_H__
#define __ENEMYLAYER_H__

#include "cocos2d.h"

class EnemyLayer : public cocos2d::Layer
{
public:
	static EnemyLayer* getInstance();
	cocos2d::Layer* create(cocos2d::Vec2, bool);
	cocos2d::Sprite *_ship, *_bullet;
	void FireBullet(float);
	cocos2d::Sprite* getShip();
	cocos2d::Sprite* getBullet();
	int enemyBulletSound = 0;
	bool isAlive;
	cocos2d::Layer* _layer;

};

#endif 
