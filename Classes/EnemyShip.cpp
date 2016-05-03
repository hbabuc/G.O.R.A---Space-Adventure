#include <string>
#include <sstream>
#include "EnemyShip.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;

EnemyShip* EnemyShip::getInstance() {
	return new EnemyShip();
}

Sprite* EnemyShip::createRed()
{
	return EnemyShip::getInstance()->create("enemyred.png");
}

Sprite* EnemyShip::createGreen()
{
	return EnemyShip::getInstance()->create("enemygreen.png");
}

Sprite* EnemyShip::createBlue()
{
	return EnemyShip::getInstance()->create("enemyblue.png");
}



Sprite* EnemyShip::create(char *filename)
{

	ship = Sprite::create(filename);

	ship->setRotation(180);

	auto physicsBody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(0.1, 1.0, 0));

	physicsBody->setDynamic(true);

	physicsBody->setCategoryBitmask(0x09);
	physicsBody->setCollisionBitmask(0);
	physicsBody->setContactTestBitmask(0x05);

	ship->setPhysicsBody(physicsBody);

	return ship;
}