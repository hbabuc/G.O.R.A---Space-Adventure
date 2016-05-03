#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

class mainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void startLabelCallBack();
	void exitLabelCallBack();
	void settingsLabelCallBack();
	void onAccelerations(cocos2d::Acceleration*, cocos2d::Event*);
    // implement the "static create()" method manually
    CREATE_FUNC(mainMenu);
};

#endif // __SECONDSCENE_H__
