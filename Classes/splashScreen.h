#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include "cocos2d.h"

class splashScreen : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void mainScene(float);
    
    // implement the "static create()" method manually
    CREATE_FUNC(splashScreen);
};

#endif // __splashScreen_SCENE_H__
