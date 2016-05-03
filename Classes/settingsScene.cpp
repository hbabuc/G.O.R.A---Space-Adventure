#include <string>
#include <sstream>
#include "settingsScene.h"
#include "mainMenu.h"


template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


USING_NS_CC;

bool soundStates = true;
MenuItemSprite *menuItemSoundsOff, *menuItemSoundsOn;


Scene* settingsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = settingsScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool settingsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
  

	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();


	soundStates = CCUserDefault::getInstance()->sharedUserDefault()->getBoolForKey("sound",true);



#pragma region  SOUND ON OF LABEL AND SPRITES

	auto soundOn = Sprite::create("soundon.png");

	auto soundsLbl = Label::createWithTTF("Sounds : ", "fonts/divisibleinvisible.ttf", 32);

	menuItemSoundsOn = MenuItemSprite::create(soundOn, soundOn, CC_CALLBACK_0(settingsScene::soundCallBack, this));

	soundsLbl->setPosition(Vec2(origin.x + visibleSize.width / 2 - soundsLbl->getContentSize().width / 2, origin.y + visibleSize.height - visibleSize.height / 4));

	soundOn->setPosition(Vec2(0, 0));


	auto soundOff = Sprite::create("soundoff.png");

	menuItemSoundsOff = MenuItemSprite::create(soundOff, soundOff, CC_CALLBACK_0(settingsScene::soundCallBack, this));

	soundOff->setPosition(Vec2(0, 0));

	soundOff->setScale(soundsLbl->getContentSize().height / soundOff->getContentSize().height);

	soundOn->setScale(soundsLbl->getContentSize().height / soundOn->getContentSize().height);

	Vector<MenuItem*> menuItems;

	menuItems.pushBack(menuItemSoundsOn);
	menuItems.pushBack(menuItemSoundsOff);

	auto menu = Menu::createWithArray(menuItems);

	menu->setPosition(Vec2(origin.x + visibleSize.width / 2 + 30 + soundOff->getContentSize().width, origin.y + visibleSize.height - visibleSize.height / 4));



	this->addChild(soundsLbl, 0);
	this->addChild(menu, 0);

#pragma endregion


#pragma region MENU LABELS AND ITS MENU
	auto menuLbl = Label::createWithTTF("Menu", "fonts/divisibleinvisible.ttf", 32);

	auto menuLblMenu = MenuItemLabel::create(menuLbl, CC_CALLBACK_0(settingsScene::exitLabelCallBack, this));

	menuLbl->setPosition(Vec2(0,0));


	auto menuLblmenuMenu = Menu::createWithItem(menuLblMenu);

	menuLblmenuMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(menuLblmenuMenu, 0);


#pragma endregion


		
		if (soundStates)
			menuItemSoundsOff->setVisible(false);
		else
			menuItemSoundsOn->setVisible(false);
		

	
	return true;
}

void settingsScene::soundCallBack() {
	soundStates = !soundStates;

	if (soundStates)
	{
		menuItemSoundsOn->setVisible(true);
		menuItemSoundsOff->setVisible(false);
		CCUserDefault::getInstance()->sharedUserDefault()->setBoolForKey("sound", true);
	}
	else
	{
		menuItemSoundsOn->setVisible(false);
		menuItemSoundsOff->setVisible(true);
		CCUserDefault::getInstance()->sharedUserDefault()->setBoolForKey("sound", false);
	}
		

}

void settingsScene::exitLabelCallBack() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, mainMenu::createScene(), Color3B(0, 0, 0)));
}

