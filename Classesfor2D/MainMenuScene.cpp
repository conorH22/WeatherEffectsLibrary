// main menu  for weathereffects2d
#include "MainMenuScene.h"
#include "FogDayTime.h"
#include "RainDayTime.h"
#include "SnowDayTime.h"
#include "SunnyDayTime.h"
#include "FogNights.h"
#include "RainNight.h"
#include "SnowNight.h"
#include "Night.h"
#include "MainScene.h"
#include "CloudyDayTime.h"
#include "CloudyNight.h"
#include "RealTime.h"

//namespace cocos2d
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();


	// add layer as a child to scene banna
	scene->addChild(layer);

	// return the scene
	return scene;
}



// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//  super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 


	auto backgroundSprite = Sprite::create("HelloWorld.png");// main menu image 
	backgroundSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/1.3 + origin.y));
	this->addChild(backgroundSprite);
	//background image
	auto titleSprite = Sprite::create("title2d.png");//image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2.2 + origin.y));
	this->addChild(titleSprite);

	//button mapping to other scenes

	//when click on weather effect buttons goes to suitable weather scene
	auto fogscene = MenuItemImage::create("fogbutton2d.png", "fogbutton2d.png", CC_CALLBACK_1(MainMenuScene::GoToFogDayScene, this));
	fogscene->setPosition(Point(visibleSize.width /10 + origin.x, visibleSize.height /1.2 + origin.y));

	auto fogNightscene = MenuItemImage::create("FogNightButton.png", "FogNightButton.png", CC_CALLBACK_1(MainMenuScene::GoToFogNightScene, this));
	fogNightscene->setPosition(Point(visibleSize.width /10 + origin.x, visibleSize.height / 1.5 + origin.y));

	auto Sunscene = MenuItemImage::create("SunDaybutton.png", "SunDaybutton.png", CC_CALLBACK_1(MainMenuScene::GoToSunDayScene, this));
	Sunscene->setPosition(Point(visibleSize.width/1.1 + origin.x, visibleSize.height/1.2 + origin.y));

	auto Nightscene = MenuItemImage::create("NightClearButton.png", "NightClearButton.png", CC_CALLBACK_1(MainMenuScene::GoToNightScene, this));
	Nightscene->setPosition(Point(visibleSize.width /1.1 + origin.x, visibleSize.height / 1.5 + origin.y));

	//options
	auto rainscene = MenuItemImage::create("rainbutton2d.png", "rainbutton.png", CC_CALLBACK_1(MainMenuScene::GoToRainDayScene, this));
	rainscene->setPosition(Point(visibleSize.width /10 + origin.x, visibleSize.height / 2.0 + origin.y));

	auto rainNightscene = MenuItemImage::create("RainNightButton.png", "RainNightButton.png", CC_CALLBACK_1(MainMenuScene::GoToRainNightScene, this));
	rainNightscene->setPosition(Point(visibleSize.width /10 + origin.x, visibleSize.height / 3.0 + origin.y));

	auto closeItem = MenuItemImage::create("Exitbutton.png", "Exitbutton.png", CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
	closeItem->setPosition(Point(visibleSize.width / 3 + origin.x, visibleSize.height / 5 + origin.y));

	auto snowscene = MenuItemImage::create("snowday2d.png", "snowday2d.png", CC_CALLBACK_1(MainMenuScene::GoToSnowDayScene, this));
	snowscene->setPosition(Point(visibleSize.width / 1.1 + origin.x, visibleSize.height /2.0 + origin.y));

	auto snowNightscene = MenuItemImage::create("SnowNightButton.png", "SnowNightButton.png", CC_CALLBACK_1(MainMenuScene::GoToSnowNightScene, this));
	snowNightscene->setPosition(Point(visibleSize.width /1.1 + origin.x, visibleSize.height / 3.0 + origin.y));

	auto overcastscene = MenuItemImage::create("overcast2d.png", "overcast2d.png", CC_CALLBACK_1(MainMenuScene::GoToOvercastScene, this));
	overcastscene->setPosition(Point(visibleSize.width /1.1 + origin.x, visibleSize.height / 5.0 + origin.y));

	auto overcastnightscene = MenuItemImage::create("overcastnight2d.png", "overcastnight2d.png", CC_CALLBACK_1(MainMenuScene::GoToOvercastNightScene, this));
	overcastnightscene->setPosition(Point(visibleSize.width /1.5 + origin.x, visibleSize.height /5 + origin.y));

	auto realtime = MenuItemImage::create("realtimebutton2d.png", "realtimebutton2d.png", CC_CALLBACK_1(MainMenuScene::GoToRealTimeWeatherScene, this));
	realtime->setPosition(Point(visibleSize.width / 10 + origin.x, visibleSize.height / 5.0 + origin.y));

	auto fogsceneButton = Menu::create(fogscene, NULL);
	fogsceneButton->setPosition(Point::ZERO);
	this->addChild(fogsceneButton);

	auto fogNightsceneButton = Menu::create(fogNightscene, NULL);
	fogNightsceneButton->setPosition(Point::ZERO);
	this->addChild(fogNightsceneButton);

	auto sunsceneButton = Menu::create(Sunscene, NULL);
	sunsceneButton->setPosition(Point::ZERO);
	this->addChild(sunsceneButton);

	auto NightsceneButton = Menu::create(Nightscene, NULL);
	NightsceneButton->setPosition(Point::ZERO);
	this->addChild(NightsceneButton);

	auto rainscenebutton = Menu::create(rainscene, NULL);
	rainscenebutton->setPosition(Point::ZERO);
	this->addChild(rainscenebutton);

	auto rainNightscenebutton = Menu::create(rainNightscene, NULL);
	rainNightscenebutton->setPosition(Point::ZERO);
	this->addChild(rainNightscenebutton);

	auto exit = Menu::create(closeItem, NULL);
	exit->setPosition(Point::ZERO);
	this->addChild(exit);

	auto snowsceneButton = Menu::create(snowscene, NULL);
	snowsceneButton->setPosition(Point::ZERO);
	this->addChild(snowsceneButton);

	auto snowNightsceneButton = Menu::create(snowNightscene, NULL);
	snowNightsceneButton->setPosition(Point::ZERO);
	this->addChild(snowNightsceneButton);

	auto overcastsceneButton = Menu::create(overcastscene, NULL);
	overcastsceneButton->setPosition(Point::ZERO);
	this->addChild(overcastsceneButton);

	auto overcastnightsceneButton = Menu::create(overcastnightscene, NULL);
	overcastnightsceneButton->setPosition(Point::ZERO);
	this->addChild(overcastnightsceneButton);

	auto realtimeButton = Menu::create(realtime, NULL);
	realtimeButton->setPosition(Point::ZERO);
	this->addChild(realtimeButton);

	return true;
}

void MainMenuScene::GoToRainDayScene(Ref *sender)//go to rain scene method implementation 
{
	auto scene = RainDayTime::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void MainMenuScene::GoToRainNightScene(Ref *sender)//go to rain night scene method implementation 
{
	auto scene = RainNight::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void MainMenuScene::GoToSunDayScene(Ref *sender)//go to sun scene method implementation 
{
	auto scene = SunnyDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void MainMenuScene::GoToNightScene(Ref *sender)//go to Night scene method implementation 
{
	auto scene = Night::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void MainMenuScene::GoToSnowDayScene(Ref * sender)//go to Snow scene method implementation 
{
	auto scene = SnowDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void MainMenuScene::GoToSnowNightScene(Ref * sender)//go to Snow night scene method implementation 
{
	auto scene = SnowNight::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void MainMenuScene::GoToOvercastScene(Ref * sender)//go to cloudy scene method implementation 
{
	auto scene = CloudyDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void MainMenuScene::GoToOvercastNightScene(Ref * sender)//go to cloudy night scene method implementation 
{
	auto scene = CloudyNight::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void MainMenuScene::GoToFogDayScene(Ref *sender)   //go to fog scene method implementation 
{
	auto scene = FogDayTime::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

}


void MainMenuScene::GoToFogNightScene(Ref *sender)   //go to fog night scene method implementation 
{
	auto scene = FogNights::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

}

void MainMenuScene::GoToRealTimeWeatherScene(Ref *sender)  //go to realTime scene method implementation 
{
	auto scene = RealTime::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));

}

// end of mainmenu scene 