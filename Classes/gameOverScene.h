#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__

#include "cocos2d.h"

class gameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void startLabelCallBack();
	void exitLabelCallBack();
	void waitForASec(float);
    
    // implement the "static create()" method manually
    CREATE_FUNC(gameOverScene);
};

#endif // __HELLOWORLD_SCENE_H__
