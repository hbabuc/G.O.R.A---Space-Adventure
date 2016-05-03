#include <string>
#include <sstream>
#include "gameOverScene.h"
#include "mainMenu.h"
#include "Levels/gameLevel1.h"
#include "SimpleAudioEngine.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;




Scene* gameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = gameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool gameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	scheduleOnce(schedule_selector(gameOverScene::waitForASec), 1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


	auto userDefaults = CCUserDefault::getInstance()->sharedUserDefault();

	userDefaults->flush();


	auto gameOverLbl = Label::createWithTTF("Game Over", "fonts/divisibleinvisible.ttf", 48);

	auto highScoreLbl = Label::createWithTTF("High Score : " + to_string(userDefaults->getIntegerForKey("highscore",0)), "fonts/divisibleinvisible.ttf", 36);

	auto scoreLbl = Label::createWithTTF("Your Score : " + to_string(userDefaults->getIntegerForKey("score",0)), "fonts/divisibleinvisible.ttf", 36);

	auto playAgainLbl = Label::createWithTTF("Play Again", "fonts/divisibleinvisible.ttf", 36);

	auto menuLbl = Label::createWithTTF("Menu", "fonts/divisibleinvisible.ttf", 36);


	auto gameOverLblMenu = MenuItemLabel::create(gameOverLbl);
	auto highScoreLblMenu = MenuItemLabel::create(highScoreLbl);
	auto scoreLblMenu = MenuItemLabel::create(scoreLbl);
	auto playAgainLblMenu = MenuItemLabel::create(playAgainLbl, CC_CALLBACK_0(gameOverScene::startLabelCallBack, this));
	auto menuLblMenu = MenuItemLabel::create(menuLbl, CC_CALLBACK_0(gameOverScene::exitLabelCallBack, this));


	gameOverLblMenu->setPosition(Vec2(0, 170));
	highScoreLblMenu->setPosition(Vec2(0, 96));
	scoreLblMenu->setPosition(Vec2(0, 48));
	menuLblMenu->setPosition(Vec2(0, -10));
	playAgainLblMenu->setPosition(Vec2(0, -65));

	Vector<MenuItem*> menuItems;

	menuItems.pushBack(gameOverLblMenu);
	menuItems.pushBack(highScoreLblMenu);
	menuItems.pushBack(scoreLblMenu);
	menuItems.pushBack(playAgainLblMenu);
	menuItems.pushBack(menuLblMenu);


	auto menu = Menu::createWithArray(menuItems);

	menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 65));

	this->addChild(menu, 0);

	return true;
}

void gameOverScene::startLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, gameLevel1::createScene(), Color3B(0, 0, 0)));
}

void gameOverScene::exitLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, mainMenu::createScene(), Color3B(0, 0, 0)));
}


void gameOverScene::waitForASec(float dt) {
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}
