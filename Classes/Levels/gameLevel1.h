#ifndef __GAMELEVEL1_H__
#define __GAMELEVEL1_H__

#include "cocos2d.h"

class gameLevel1 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void createFirstEnemy();
	void createSecondEnemy();
	void createThirdEnemy();
	bool onContactBegins(cocos2d::PhysicsContact&);
	float random(float smallNumber, float bigNumber);
	void fireTheFuckinBullet();
	void enemiesBullet(float);
	void addStars(float);
	void lastEnemyMovement(float);
	void shipExplosions(cocos2d::Vec2,bool);
	void onAcceleration(cocos2d::Acceleration*,cocos2d::Event*);
    
    // implement the "static create()" method manually
    CREATE_FUNC(gameLevel1);

private:
	cocos2d::PhysicsWorld* sceneWorld;
	cocos2d::Sprite *ship, *enemy, *bulletFlame, *scoreIcon;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Label *scoreLbl, *healtLbl, *enemyCountLbl;
	cocos2d::PhysicsBody *enemyPhysics, *bulletPhysics;
	int score = 0, shipHealt = 3, enemyCount = 3, shipBulletSound = 0, enemyBulletSound = 0, enemyScore = 0;
	bool isEnemyReady = false, isShipAlive = true, soundState;
	void setPhysicalWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; }

};

#endif // __splashScreen_SCENE_H__
