#include <string>
#include <sstream>
#include "gameWinScene.h"
#include "mainMenu.h"
#include "levelScene.h"
#include "SimpleAudioEngine.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;



Scene* gameWinScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = gameWinScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool gameWinScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }



	scheduleOnce(schedule_selector(gameWinScene::waitForASec), 1);
    
	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	auto userDefaults = CCUserDefault::getInstance()->sharedUserDefault();

	userDefaults->flush();


	auto gameOverLbl = Label::createWithTTF("Nice!", "fonts/divisibleinvisible.ttf", 48);

	auto highScoreLbl = Label::createWithTTF("High Score : " + to_string(userDefaults->getIntegerForKey("highscore",0)), "fonts/divisibleinvisible.ttf", 36);

	auto scoreLbl = Label::createWithTTF("Your Score : " + to_string(userDefaults->getIntegerForKey("score",0)), "fonts/divisibleinvisible.ttf", 36);

	auto nextLevelLbl = Label::createWithTTF("Next Level", "fonts/divisibleinvisible.ttf", 36);

	auto playAgainLbl = Label::createWithTTF("Play Again", "fonts/divisibleinvisible.ttf", 36);

	auto menuLbl = Label::createWithTTF("Menu", "fonts/divisibleinvisible.ttf", 36);


	auto gameOverLblMenu = MenuItemLabel::create(gameOverLbl);
	auto highScoreLblMenu = MenuItemLabel::create(highScoreLbl);
	auto scoreLblMenu = MenuItemLabel::create(scoreLbl);
	auto nextLevelLblMenu = MenuItemLabel::create(nextLevelLbl, CC_CALLBACK_0(gameWinScene::nextLevelLabelCallBack, this));
	auto menuLblMenu = MenuItemLabel::create(menuLbl, CC_CALLBACK_0(gameWinScene::exitLabelCallBack, this));


	gameOverLblMenu->setPosition(Vec2(0, 170));
	highScoreLblMenu->setPosition(Vec2(0, 96));
	scoreLblMenu->setPosition(Vec2(0, 48));
	nextLevelLblMenu->setPosition(Vec2(0, -15));
	menuLblMenu->setPosition(Vec2(0, -85));
	

	Vector<MenuItem*> menuItems;

	menuItems.pushBack(gameOverLblMenu);
	menuItems.pushBack(highScoreLblMenu);
	menuItems.pushBack(scoreLblMenu);
	menuItems.pushBack(nextLevelLblMenu);
	menuItems.pushBack(menuLblMenu);


	auto menu = Menu::createWithArray(menuItems);

	menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 65));

	this->addChild(menu, 0);

	return true;
}


void gameWinScene::exitLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, mainMenu::createScene(), Color3B(0, 0, 0)));
}

void gameWinScene::nextLevelLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, levelScene::createScene(), Color3B(0, 0, 0)));
}

void gameWinScene::waitForASec(float dt) {
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}
