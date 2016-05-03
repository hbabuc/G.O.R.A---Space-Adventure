#include <string>
#include <sstream>
#include "Levels/gameLevel2.h"
#include "mainMenu.h"
#include "gameOverScene.h"
#include "gameWinScene.h"
#include "EnemyLayer.h"
#include "SimpleAudioEngine.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}



USING_NS_CC;



Scene* gameLevel2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vec2(0,0));

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = gameLevel2::create();

	layer->setPhysicalWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool gameLevel2::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
	 visibleSize = Director::getInstance()->getVisibleSize();
     origin = Director::getInstance()->getVisibleOrigin();

	 soundState = UserDefault::getInstance()->sharedUserDefault()->getBoolForKey("sound",true);


	 if(soundState)CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/backgroundMusic.mp3",true);
	
	 shipHealt = enemyCount = 3;
	 score = 0;
	 isEnemyReady = false;
	 isShipAlive = true;


	 

#pragma region PRELOAD EXPLOSION
	 SpriteBatchNode* spritebatch = SpriteBatchNode::create("animations/explosion.png");
	 SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	 cache->addSpriteFramesWithFile("animations/explosion.plist");

#pragma endregion

#pragma region Ship Sprite Creation

	ship = Sprite::create("ship.png");
	
	auto shipPhysics = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(0.1, 1.0, 0));

	shipPhysics->setDynamic(true);

	ship->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y -50));
	
	if (visibleSize.width < visibleSize.height)
		ship->setScale(1.2);

	shipPhysics->setCategoryBitmask(0x01);
	shipPhysics->setCollisionBitmask(0);
	shipPhysics->setContactTestBitmask(0x08);

	ship->setPhysicsBody(shipPhysics);

	this->addChild(ship, 2);

	auto shipMove = MoveTo::create(1, Vec3(ship->getPositionX(), origin.y + visibleSize.height / 4, ship->getPositionZ()));
	auto shipEase = EaseOut::create(shipMove, 1);

	ship->runAction(shipEase);


#pragma endregion

#pragma region Heart and ShipHealt Label Creation

	healtLbl = Label::createWithTTF("3", "fonts/divisibleinvisible.ttf", 24);

	healtLbl->setPosition(Vec2(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 40));

	this->addChild(healtLbl, 2);

	auto heart = Sprite::create("heart.png");
	heart->setScale(0.7);
	heart->setPosition(Vec2(healtLbl->getPositionX() - 10 - heart->getContentSize().width / 2, origin.y + visibleSize.height - 40));
	this->addChild(heart, 2);

	if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/shipexit.mp3");

#pragma endregion



#pragma region Enemy Count Label Creation


	enemyCountLbl = Label::createWithTTF("3", "fonts/divisibleinvisible.ttf", 24);

	enemyCountLbl->setPosition(Vec2(heart->getPositionX() - 10 - heart->getContentSize().width, origin.y + visibleSize.height - 40));

	this->addChild(enemyCountLbl, 2);

	auto enemySymbol = Sprite::create("enemysymbol.png");

	enemySymbol->setPosition(Vec2(enemyCountLbl->getPositionX() - 20 - enemySymbol->getContentSize().width / 2, origin.y + visibleSize.height - 40));

	this->addChild(enemySymbol, 2);


#pragma endregion




#pragma region Score icon and Label Creation


	scoreIcon = Sprite::create("score.png");

	scoreIcon->setPosition(Vec2(origin.x + 10 + scoreIcon->getContentSize().width / 2, origin.y + visibleSize.height - 40));

	this->addChild(scoreIcon, 2);

	scoreLbl = Label::createWithTTF("0", "fonts/divisibleinvisible.ttf", 24);

	scoreLbl->setPosition(Vec2(scoreIcon->getPositionX() + scoreLbl->getContentSize().width + 20, origin.y + visibleSize.height - 40));

	this->addChild(scoreLbl, 2);


	

#pragma endregion




#pragma region TouchEvents

	auto lis = EventListenerTouchOneByOne::create();

	lis->onTouchBegan = [=](Touch *t, Event *e) {

		return true;
	};

	lis->onTouchMoved = [=](Touch *t, Event *e) {

	};


	lis->onTouchEnded = [=](Touch *t, Event *e) {
		gameLevel2::fireTheFuckinBullet();
	};

	auto dispatcher = this->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(lis, this);

#pragma endregion


#pragma region Contact defining

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(gameLevel2::onContactBegins,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

#pragma endregion




#pragma region Create first enemy and schedulers
	
	gameLevel2::createFirstEnemy();

	schedule(schedule_selector(gameLevel2::addStars), 1);

	auto accel = EventListenerAcceleration::create(CC_CALLBACK_2(gameLevel2::onAcceleration,this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(accel,this);

	Device::setAccelerometerEnabled(true);

#pragma endregion


    return true;
}



#pragma region Fire the FUCKIN ships Bullet

void gameLevel2::fireTheFuckinBullet() {

	if (isShipAlive)
	{
		if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(shipBulletSound);

		//BULLET FLAME

		bulletFlame = Sprite::create("FlameEffect/red.png");
		bulletFlame->setPosition(Vec2(ship->getPositionX(), ship->getPositionY() + ship->getContentSize().height / 2 + 10));
		bulletFlame->setScale(0.3);
		this->addChild(bulletFlame, 2);

		bulletFlame->runAction(Sequence::create(DelayTime::create(0.05), RemoveSelf::create(), NULL));

		//BULLET CREATION

		auto bullet = Sprite::create("FlameEffect/redbullet.png");

		bullet->setPosition(Vec2(ship->getPosition().x, ship->getPosition().y + ship->getContentSize().height / 2));

		bullet->setScale(0.5);
		bullet->setTag(2);

		bulletPhysics = PhysicsBody::createBox(bullet->getContentSize(), PhysicsMaterial(0.1, 1.0, 0));
		bulletPhysics->setDynamic(true);

		bulletPhysics->setCategoryBitmask(0x05);
		bulletPhysics->setCollisionBitmask(0);
		bulletPhysics->setContactTestBitmask(0x09);

		bullet->setPhysicsBody(bulletPhysics);

		this->addChild(bullet, 2);


		auto bulletMove = MoveTo::create(0.7, Vec3(bullet->getPosition().x, visibleSize.height + 30, 0));
		auto easeMove = EaseIn::create(bulletMove, 0.7);

		auto seq = Sequence::create(easeMove, RemoveSelf::create(), NULL);

		bullet->runAction(seq);

		if (soundState)
		shipBulletSound = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/wav/bullet1.wav");

	}
	
}

#pragma endregion


#pragma region When the contacts begin

bool gameLevel2::onContactBegins(PhysicsContact &contact) {

	auto userDefault = CCUserDefault::getInstance()->sharedUserDefault();
	auto nodeA = contact.getShapeA()->getBody();
	auto nodeB = contact.getShapeB()->getBody();

	
	if (nodeA->getContactTestBitmask() == 5 && nodeB->getContactTestBitmask() == 9 || nodeA->getContactTestBitmask() == 9 && nodeB->getContactTestBitmask() == 5)
	{
		isEnemyReady = false;

		if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/explosionships.mp3");


		gameLevel2::shipExplosions(enemy->getPosition(),false);	//BOOOOOM


		nodeA->getNode()->removeFromParentAndCleanup(true);
		nodeB->getNode()->removeFromParentAndCleanup(true);

		
		scoreLbl->setString(to_string(score += enemyScore));
		scoreLbl->setPosition(Vec2(scoreIcon->getPositionX() + scoreLbl->getContentSize().width + 10, origin.y + visibleSize.height - 40));

		enemyCountLbl->setString(to_string(--enemyCount));

		if (enemyCount == 2) gameLevel2::createSecondEnemy();
		if (enemyCount == 1) gameLevel2::createThirdEnemy();
		if (enemyCount == 0)
		{
			this->stopAllActionsByTag(1);
			this->stopAllActionsByTag(2);

			isShipAlive = false;

			if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/shipexit.mp3");

			ship->runAction(Sequence::create(MoveTo::create(0.5, Vec2(origin.x + visibleSize.width / 2, ship->getPositionY())), MoveTo::create(0.5, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height)),NULL));


			userDefault->setIntegerForKey("score", score);

			if (score > userDefault->getIntegerForKey("highscore",0))
				userDefault->setIntegerForKey("highscore", score);

			userDefault->setIntegerForKey("level", 2);

			userDefault->flush();
			Director::getInstance()->replaceScene(TransitionFade::create(2.2, gameWinScene::createScene(), Color3B(0, 0, 0)));
		}

	}

	if (nodeA->getContactTestBitmask() == 8 && nodeB->getContactTestBitmask() == 1 || nodeA->getContactTestBitmask() == 1 && nodeB->getContactTestBitmask() == 8)
	{
		if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/wav/explosion.wav");

		if (--shipHealt == 0)
		{
			isShipAlive = false;
			this->stopAllActionsByTag(1);
			this->stopAllActionsByTag(2);

			gameLevel2::shipExplosions(ship->getPosition(),false);	//BOOOOOM

			nodeA->getNode()->removeFromParentAndCleanup(true);
			nodeB->getNode()->removeFromParentAndCleanup(true);

			if (soundState)CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/explosionships.mp3");

			userDefault->setIntegerForKey("score", score);

			if (score > userDefault->getIntegerForKey("highscore",0))
				userDefault->setIntegerForKey("highscore", score);

			userDefault->flush();
			
			Director::getInstance()->replaceScene(TransitionFade::create(1, gameOverScene::createScene(), Color3B(0, 0, 0)));
		}
		else
		{

			if (nodeA->getCollisionBitmask() == 4)
			{
				gameLevel2::shipExplosions(nodeA->getNode()->getPosition(), true);	//LITTLE BOOOM
				nodeA->getNode()->removeFromParentAndCleanup(true);
			}
			else
			{
				gameLevel2::shipExplosions(nodeB->getNode()->getPosition(), true);	//LITTLE BOOOM
				nodeB->getNode()->removeFromParentAndCleanup(true);
			}
				

			

			healtLbl->setString(to_string(shipHealt));
		}
	}
	
	return true;
}
#pragma endregion


#pragma region Random Function
float gameLevel2::random(float smallNumber, float bigNumber) {
	float diff = bigNumber - smallNumber;
	return (((float)rand() / RAND_MAX) * diff) + smallNumber;

}
#pragma endregion


#pragma region Adding stars to the screen

void gameLevel2::addStars(float dt) {

	float rands = (random(10, 60) / 100), parallax = 0;
	auto star = Sprite::create("star.png");
	star->setPosition(Vec2(origin.x + random(50, visibleSize.width - 50), origin.y + visibleSize.height + 20));
	star->setScale(rands);

	if (rands > 0.5)parallax = 3;
	if (rands > 0.4 && rands < 0.5)parallax = 5;
	if (rands > 0.3 && rands < 0.4)parallax = 7;
	if (rands > 0.2 && rands < 0.3)parallax = 9;
	if (rands > 0.1 && rands < 0.2)parallax = 11;

	this->addChild(star, 1);
	auto moveStar = MoveTo::create(parallax, Vec3(star->getPositionX(), -20, 0));
	auto seq = Sequence::create(moveStar, RemoveSelf::create(), NULL);
	star->runAction(seq);

}
#pragma endregion





#pragma region EnemyShip Sprite Creation 1
void gameLevel2::createFirstEnemy() {

	auto _enemyLayer = new EnemyLayer();

	auto enemyLayer = _enemyLayer->create(Vec2(origin.x - 120,origin.y + visibleSize.height - visibleSize.height / 4), soundState);

	enemyLayer->setPosition(Vec2(0,0));

	this->addChild(enemyLayer, 2);

	if (visibleSize.width < visibleSize.height)
		enemyLayer->setScale(1.2);

	enemy = _enemyLayer->getShip();



	auto right = MoveTo::create(2, Vec2(origin.x + visibleSize.width - enemy->getContentSize().width, enemy->getPositionY()));
	auto left = MoveTo::create(2, Vec2(origin.x + enemy->getContentSize().width, enemy->getPositionY()));
	auto seq = Sequence::create(right, left, NULL);

	enemy->runAction(RepeatForever::create(seq));

	enemyScore = 100;

	isEnemyReady = true;
	

}
#pragma endregion

#pragma region EnemyShip Sprite Creation 2
void gameLevel2::createSecondEnemy() {

	auto _enemyLayer = new EnemyLayer();

	auto enemyLayer = _enemyLayer->create(Vec2(origin.x + visibleSize.width + enemy->getContentSize().width, origin.y + visibleSize.height - visibleSize.height / 4), soundState);

	enemyLayer->setPosition(Vec2(0, 0));

	this->addChild(enemyLayer, 2);

	if (visibleSize.width < visibleSize.height)
		enemyLayer->setScale(1.2);

	enemy = _enemyLayer->getShip();

	auto right = MoveTo::create(2, Vec2(origin.x + enemy->getContentSize().width, enemy->getPositionY()));
	auto left = MoveTo::create(2, Vec2(origin.x + visibleSize.width - enemy->getContentSize().width, enemy->getPositionY()));
	auto seq = Sequence::create(right, left, NULL);

	enemy->runAction(RepeatForever::create(seq));

	enemyScore = 150;

	isEnemyReady = true;
}
#pragma endregion

#pragma region EnemyShip Sprite Creation 3
void gameLevel2::createThirdEnemy() {

	auto _enemyLayer = new EnemyLayer();

	auto enemyLayer = _enemyLayer->create(Vec2(origin.x + visibleSize.width + enemy->getContentSize().width, origin.y + visibleSize.height - visibleSize.height / 4), soundState);

	enemyLayer->setPosition(Vec2(0, 0));

	this->addChild(enemyLayer, 2);

	if (visibleSize.width < visibleSize.height)
		enemyLayer->setScale(1.2);

	enemy = _enemyLayer->getShip();

	auto top = MoveTo::create(1, Vec2(enemy->getPositionX(), origin.y + visibleSize.height - visibleSize.height / 4));
	
	enemy->runAction(top);
	
	enemyScore = 250;

	isEnemyReady = true;

	scheduleOnce(schedule_selector(gameLevel2::lastEnemyMovement), 1);
}
#pragma endregion

#pragma region Third enemy entering animation
void gameLevel2::lastEnemyMovement(float dt) {
	if (isEnemyReady)
	{
		auto right = MoveTo::create(2, Vec2(origin.x + visibleSize.width - enemy->getContentSize().width, enemy->getPositionY()));
		auto left = MoveTo::create(2, Vec2(origin.x + enemy->getContentSize().width, enemy->getPositionY()));
		auto seq = Sequence::create(right, left, NULL);
		enemy->runAction(RepeatForever::create(seq));
	}
}
#pragma endregion


#pragma region Ship explosions function

void gameLevel2::shipExplosions(Vec2 vec,bool scale) {

	SpriteBatchNode* spritebatch = SpriteBatchNode::create("animations/explosion.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/explosion.plist");
	auto explosion = Sprite::createWithSpriteFrameName("explosion_01.png");
	explosion->setPosition(vec);
	if (scale) explosion->setScale(0.5);
	spritebatch->addChild(explosion);
	this->addChild(spritebatch);
	Vector<SpriteFrame*> animFrames(48);

	char str[100] = { 0 };
	for (int i = 1; i < 49; i++)
	{
		sprintf(str, "explosion_%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.02);
	explosion->runAction(Sequence::create(Animate::create(animation),RemoveSelf::create(),NULL));
	
}

#pragma endregion

#pragma region ON ACCELERATION
void gameLevel2::onAcceleration(Acceleration* ac, Event* e) {
	if (isShipAlive) {
		int velX = ship->getPositionX() + ac->x * 17;
		if (velX >= origin.x + ship->getContentSize().width / 2 && velX <= origin.x + visibleSize.width - ship->getContentSize().width / 2)
			ship->setPosition(Vec2(velX, ship->getPositionY()));
		else
			ship->setPosition(Vec2(ship->getPositionX(), ship->getPositionY()));
	}
	
}
#pragma endregion

