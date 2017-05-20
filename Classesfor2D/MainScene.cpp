#include "MainScene.h"
//#include "WeatherEffectsUtils.h"
#include "RainDayTime.h"
#include "SnowDayTime.h"
#include "FogDayTime.h"



USING_NS_CC;

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
   // scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

   // this->setKeypadEnabled(true);
    
    Size size = Director::sharedDirector()->getWinSize(); 
	//this->scheduleOnce(schedule_selector(MainScene::goToFogDayTime), DISPLAY_TIME_SPLASH_SCENE);//going to the main menu 
    //background image
    Sprite *bgSprite = Sprite::create("ld_bg_fine_day.jpg");
    float bgSpritespx = bgSprite->getTextureRect().getMaxX();
    float bgSpritespy = bgSprite->getTextureRect().getMaxY();
    // position the sprite on the center of the screen
    bgSprite->setPosition(ccp(0,size.height/2));
    bgSprite->setScaleX(size.width/bgSpritespx*2);
    bgSprite->setScaleY(size.height/bgSpritespy);
    // add the sprite as a child to this layer
    this->addChild(bgSprite, 0);
    
    return true;
}

void MainScene::goToRainDayTime(float dt)
{
	auto scene = RainDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

}

void MainScene::goToSnowDayTime(float dt)
{
	auto scene = SnowDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

}

void MainScene::goToFogDayTime(float dt)
{
	auto scene = FogDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

}
/*
void MainScene::keyBackClicked(){
    CCLog("Android- KeyBackClicked!");
    WeatherEffectsUtils::android_back_click();
}



void MainScene::keyMenuClicked(){
    CCLog("Android- keyMenuClicked!");
    WeatherEffectsUtils::android_menu_click();
}

*/