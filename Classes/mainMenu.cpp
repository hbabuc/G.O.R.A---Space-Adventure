#include "mainMenu.h"
#include "levelScene.h"
#include "settingsScene.h"

USING_NS_CC;

Sprite *background, *title;
bool isReady = false;
Size _visibleSize;
Vec2 _origin;
Menu *menu;

Scene* mainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = mainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool mainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

	auto userDefaults = CCUserDefault::sharedUserDefault();

	userDefaults->sharedUserDefault()->flush();


	background = Sprite::create("background.jpg");
	background->setRotation(180);
	if (_visibleSize.width < _visibleSize.height)
		background->setScale(2);
	background->setPosition(Vec2(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2));
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(background, 0);
	

	title = Sprite::create("title.png");
	if (title->getContentSize().width > _visibleSize.width)
		title->setScale(_visibleSize.width / title->getContentSize().width - 0.1);
	title->setPosition(Vec2(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height - _visibleSize.height / 4));
	title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(title, 0);

    
	auto startLbl = Label::createWithTTF("Play", "fonts/divisibleinvisible.ttf", 36);
	startLbl->enableShadow();
	startLbl->enableOutline(Color4B::BLACK, 2);

	auto settingsLbl = Label::createWithTTF("Settings", "fonts/divisibleinvisible.ttf", 36);
	settingsLbl->enableShadow();
	settingsLbl->enableOutline(Color4B::BLACK, 2);

	auto exitLbl = Label::createWithTTF("Exit", "fonts/divisibleinvisible.ttf", 36);

	exitLbl->enableShadow();
	exitLbl->enableOutline(Color4B::BLACK, 2);

	auto startLabelMenu = MenuItemLabel::create(startLbl, CC_CALLBACK_0(mainMenu::startLabelCallBack, this));
	auto settingsLabelMenu = MenuItemLabel::create(settingsLbl, CC_CALLBACK_0(mainMenu::settingsLabelCallBack, this));
	auto exitLabelMenu = MenuItemLabel::create(exitLbl, CC_CALLBACK_0(mainMenu::exitLabelCallBack, this));

	startLabelMenu->setPosition(Vec2(0,144));
	settingsLabelMenu->setPosition(Vec2(0,72));
	exitLabelMenu->setPosition(Vec2(0,0));

	Vector<MenuItem*> menuItems;

	menuItems.pushBack(startLabelMenu);
	menuItems.pushBack(settingsLabelMenu);
	menuItems.pushBack(exitLabelMenu);


	menu = Menu::createWithArray(menuItems);
	
	menu->setPosition(Vec2(_origin.x + _visibleSize.width / 2,_origin.y + _visibleSize.height / 4));

	this->addChild(menu,0);

	auto accel = EventListenerAcceleration::create(CC_CALLBACK_2(mainMenu::onAccelerations, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(accel, this);

	Device::setAccelerometerEnabled(true);

	isReady = true;

    return true;
}

void mainMenu::startLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, levelScene::createScene(), Color3B(0, 0, 0)));
}

void mainMenu::settingsLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, settingsScene::createScene(), Color3B(0, 0, 0)));
}

void mainMenu::exitLabelCallBack() {
	Director::getInstance()->end();
}

void mainMenu::onAccelerations(Acceleration* ac, Event* e) {
	
	if (isReady)
	{
		background->setPositionX(_origin.x + _visibleSize.width / 2 + ac->x * 40);
		menu->setPosition(Vec2(_origin.x + _visibleSize.width / 2 + ac->x * 40, _origin.y + _visibleSize.height / 4 + ac->y * 40));
		title->setPosition(Vec2(_origin.x + _visibleSize.width / 2 + ac->x * 40, _origin.y + _visibleSize.height - _visibleSize.height / 4 + ac->y * 40));
	}
		

}