#ifndef __LEVELSCENE_H__
#define __LEVELSCENE_H__

#include "cocos2d.h"

class levelScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	void nextScene(float);
    virtual bool init();
	
    
    // implement the "static create()" method manually
    CREATE_FUNC(levelScene);

};

#endif // __HELLOWORLD_SCENE_H__
