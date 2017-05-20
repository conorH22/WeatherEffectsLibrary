#ifndef __REALTIME_
#define __REALTIME_

#include "cocos2d.h"
#include "network\HttpClient.h"

class RealTime : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(RealTime);
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse* response);
private:
	void GoToTheOptionsScene(Ref *sender);
	void GoToSunDayScene(Ref *sender);
	void GoToNightScene(Ref *sender);
	void GoToOvercastScene(Ref *sender);
	//void menuCloseCallback(cocos2d::Ref* pSender);
	void GoToOvercastNightScene(Ref * sender);
	void GoToRainDayScene(Ref * sender);
	void GoToSnowDayScene(Ref *sender);
	void GoToFogDayScene(Ref *sender);
	void GoToRainNightScene(Ref * sender);
	void GoToSnowNightScene(Ref *sender);
	void GoToFogNightScene(Ref *sender);
};

#endif // __RealTime_SCENE_H__
