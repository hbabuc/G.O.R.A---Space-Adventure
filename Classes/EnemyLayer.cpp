#include <string>
#include <sstream>
#include "EnemyLayer.h"
#include "EnemyBullet.h"
#include "EnemyShip.h"
#include "SimpleAudioEngine.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;

EnemyLayer* EnemyLayer::getInstance() {
	return new EnemyLayer();
}

Sprite* EnemyLayer::getShip() {
	return _ship;
}

Sprite* EnemyLayer::getBullet() {
	return _bullet;
}



Layer* EnemyLayer::create(Vec2 firstPos,bool soundState)
{

		//if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(enemyBulletSound);

		_ship = EnemyShip::getInstance()->createRed();

		_ship->setPosition(firstPos);

		this->addChild(_ship, 0);

		schedule(schedule_selector(EnemyLayer::FireBullet), 1.5);
		
		return this;
}

void EnemyLayer::FireBullet(float dt) {
	if (_ship != nullptr)
		_bullet = EnemyBullet::getInstance()->create(_ship, this);
	else
		unschedule(schedule_selector(EnemyLayer::FireBullet));
}