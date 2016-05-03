#ifndef __GAMEWINSCENE_H__
#define __GAMEWINSCENE_H__

#include "cocos2d.h"

class gameWinScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void exitLabelCallBack();
	void nextLevelLabelCallBack();
	void waitForASec(float);
    
    // implement the "static create()" method manually
    CREATE_FUNC(gameWinScene);
};

#endif // __HELLOWORLD_SCENE_H__
