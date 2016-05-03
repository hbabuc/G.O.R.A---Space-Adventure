#include "splashScreen.h"
#include "mainMenu.h"
#include "Levels/gameLevel1.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene* splashScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = splashScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool splashScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

#pragma region Preload sounds

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/backgroundMusic.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/wav/bullet1.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/wav/hbabuc.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/hbabuc.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/wav/health1.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/wav/explosion.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/shipexit.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/explosionships.mp3");
#pragma endregion

    
	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/wav/hbabuc.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/hbabuc.ogg");


	auto splash = Sprite::create("splashscreen.png");

	splash->setScale(1.5);

	splash->setPosition(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2);

	this->addChild(splash, 0);
	
	scheduleOnce(schedule_selector(splashScreen::mainScene),0.5);
    
	
    return true;
}

void splashScreen::mainScene(float dt) {

	Director::getInstance()->replaceScene(TransitionFade::create(1, mainMenu::createScene(),Color3B(0,0,0)));
}