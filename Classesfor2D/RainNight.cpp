
#include "RainNight.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define TRANSACTION_DURATION 0.8f
#define LAYER_TAG -999
#define BACKGROUND_MOVE_SPEED  5 

Scene* RainNight::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    RainNight *layer = RainNight::create();
    layer->setTag(LAYER_TAG);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RainNight::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 
    
    winSize = Director::sharedDirector()->getWinSize(); 
    //background image
	auto titleSprite = Sprite::create("daynight.png");//image
	titleSprite->setPosition(Point(winSize.width / 2.2 + origin.x, winSize.height / 2.2 + origin.y));
	this->addChild(titleSprite);
   // 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(RainNight::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
    
    scale = winSize.width / 320.0f;
    
    
    return true;
}


void RainNight::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

