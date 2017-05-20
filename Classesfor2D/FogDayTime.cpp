//
//  FogDayTime.cpp
//  weatherEffects2D application
// Conor Holmes
#include "FogDayTime.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define TRANSACTION_DURATION 0.8f
#define LAYER_TAG -999
#define BACKGROUND_MOVE_SPEED  5 

Scene* FogDayTime::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	FogDayTime *layer = FogDayTime::create();
	layer->setTag(LAYER_TAG);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool FogDayTime::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 
	winSize = Director::sharedDirector()->getWinSize(); 

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(FogDayTime::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + winSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
				//background image										
	auto titleSprite = Sprite::create("dayOvercast.png");
	titleSprite->setPosition(Point(winSize.width / 2.2 + origin.x, winSize.height / 2.2 + origin.y));
	this->addChild(titleSprite);

	scale = winSize.width / 320.0f;
	ParticleSystemQuad *fogEffect = ParticleSystemQuad::create("particle_textureFoglight1.plist");
	fogEffect->setPosition(ccp(winSize.width / 2 - 30, winSize.height));
	fogEffect->setScale(scale);
	this->addChild(fogEffect);

	return true;
}

// this method exits out of application with  Director::getInstance()->end();
void FogDayTime::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}