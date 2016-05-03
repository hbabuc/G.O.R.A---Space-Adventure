#ifndef __SETTINGSSCENE_H__
#define __SETTINGSSCENE_H__

#include "cocos2d.h"

class settingsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void soundCallBack();
	void exitLabelCallBack();



    
    // implement the "static create()" method manually
    CREATE_FUNC(settingsScene);
};

#endif // __HELLOWORLD_SCENE_H__
