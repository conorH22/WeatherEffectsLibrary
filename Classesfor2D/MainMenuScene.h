#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;

class MainMenuScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);

private:
	
	void GoToSunDayScene(Ref *sender);
	void GoToNightScene(Ref *sender);
	void GoToOvercastScene(Ref *sender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void GoToOvercastNightScene(Ref * sender);
	void GoToRainDayScene(Ref * sender);
	void GoToSnowDayScene(Ref *sender);
	void GoToFogDayScene(Ref *sender);
	void GoToRainNightScene(Ref * sender);
	void GoToSnowNightScene(Ref *sender);
	void GoToFogNightScene(Ref *sender);
	void GoToRealTimeWeatherScene(Ref *sender);
};

#endif // __MAIN_MENU_SCENE_H__
