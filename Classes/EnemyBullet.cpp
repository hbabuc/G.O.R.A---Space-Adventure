#include <string>
#include <sstream>
#include "EnemyBullet.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;

EnemyBullet* EnemyBullet::getInstance() {
	return new EnemyBullet();
}


Sprite* EnemyBullet::create(Sprite* enemy,Layer *layer)
{

		gameLayer = layer;

		//ENEMY BULLET FLAME

		auto bulletFlame = Sprite::create("FlameEffect/red.png");
		bulletFlame->setRotation(180);
		bulletFlame->setPosition(Vec2(enemy->getPositionX(), enemy->getPositionY() - enemy->getContentSize().height / 2 - 10));
		bulletFlame->setScale(0.3);
		gameLayer->addChild(bulletFlame, 0);

		bulletFlame->runAction(Sequence::create(DelayTime::create(0.05), RemoveSelf::create(), NULL));


		//ENEMY BULLET CREATION
		auto enemyBullet = Sprite::create("FlameEffect/redbullet.png");

		enemyBullet->setPosition(Vec2(enemy->getPosition().x, enemy->getPosition().y - enemy->getContentSize().height / 2 - 20));

		enemyBullet->setScale(0.5);
		enemyBullet->setRotation(180);

		enemyBullet->setTag(1);

		auto enemyBulletPhysics = PhysicsBody::createBox(enemyBullet->getContentSize(), PhysicsMaterial(0.1, 1.0, 0));
		enemyBulletPhysics->setDynamic(true);

		enemyBulletPhysics->setCategoryBitmask(0x08);
		enemyBulletPhysics->setCollisionBitmask(0);
		enemyBulletPhysics->setContactTestBitmask(0x01);

		enemyBullet->setPhysicsBody(enemyBulletPhysics);

		gameLayer->addChild(enemyBullet, 0);


		auto bulletMove = MoveTo::create(0.7, Vec2(enemyBullet->getPosition().x, -20));
		auto easeMove = EaseIn::create(bulletMove, 0.7);

		auto seq = Sequence::create(easeMove, RemoveSelf::create(), NULL);

		enemyBullet->runAction(seq);

		return enemyBullet;

}