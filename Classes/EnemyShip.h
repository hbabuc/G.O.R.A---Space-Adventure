#ifndef __ENEMYSHIP_H__
#define __ENEMYSHIP_H__

#include "cocos2d.h"

class EnemyShip : public cocos2d::Node
{
public:
	static EnemyShip* getInstance();
	cocos2d::Sprite* createRed();
	cocos2d::Sprite* createGreen();
	cocos2d::Sprite* createBlue();
	bool isEnemyAlive = true;
	

private:
	cocos2d::Sprite* create(char*);
	cocos2d::Sprite* ship;
};

#endif 
