
#ifndef MainScene_h
#define MainScene_h
#define DISPLAY_TIME_SPLASH_SCENE 1

#include "cocos2d.h"

class MainScene : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainScene);

private:
	void goToRainDayTime(float dt);
	void goToSnowDayTime(float dt);
	void goToFogDayTime(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
