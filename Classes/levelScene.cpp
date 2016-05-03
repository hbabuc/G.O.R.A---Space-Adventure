#include <string>
#include <sstream>
#include "levelScene.h"
#include "Levels/gameLevel1.h"
#include "Levels/gameLevel2.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;


int currentLevel;



Scene* levelScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = levelScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool levelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
  

	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


	auto userDefaults = CCUserDefault::sharedUserDefault();

	userDefaults->flush();

	currentLevel = userDefaults->getIntegerForKey("level",1);

	auto level = Label::createWithTTF("Level " + to_string(currentLevel), "fonts/divisibleinvisible.ttf", 48);

	level->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(level, 0);



	scheduleOnce(schedule_selector(levelScene::nextScene), 1.5);


	
	return true;
}

void levelScene::nextScene(float dt) {

#pragma region LEVEL DEFINITIONS
	Scene *nextLevel;

	switch (currentLevel)
	{
	case 1:
		nextLevel = gameLevel1::createScene();
		break;
	case 2:
		nextLevel = gameLevel2::createScene();
		break;

	default:
		nextLevel = gameLevel1::createScene();
		break;
	}

#pragma endregion

	Director::getInstance()->replaceScene(TransitionFade::create(1,nextLevel, Color3B(0, 0, 0)));
}
