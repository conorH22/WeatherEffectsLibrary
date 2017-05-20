
#include "CloudyNight.h"
USING_NS_CC;

Scene* CloudyNight::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    CloudyNight *layer = CloudyNight::create();
    layer->setTag(LAYER_TAG);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CloudyNight::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    winSize = Director::sharedDirector()->getWinSize(); 
    //background image
	auto titleSprite = Sprite::create("daynight.png");
	titleSprite->setPosition(Point(winSize.width / 2.2 + origin.x, winSize.height / 2.2 + origin.y));
	this->addChild(titleSprite);
	// add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CloudyNight::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto CloudSprite = Sprite::create("cloud3.png");//cloud type 1  using png image
	CloudSprite->setPosition(Point(winSize.width /2.2 + origin.x, winSize.height/1.5 + origin.y));
	this->addChild(CloudSprite);
	auto Cloud2Sprite = Sprite::create("cloudy2.png");//cloud type 2  using png image
	Cloud2Sprite->setPosition(Point(winSize.width / 4 + origin.x, winSize.height/1.5+ origin.y));
	this->addChild(Cloud2Sprite);
	auto cloud3Sprite = Sprite::create("cloud4.png");//cloud type 3  using png image
	cloud3Sprite->setPosition(Point(winSize.width / 1 + origin.x, winSize.height/1.8+ origin.y));
	this->addChild(cloud3Sprite);
    
    scale = winSize.width / 320.0f;    
    
    return true;
}

// this method exits out of application with  Director::getInstance()->end();
void CloudyNight::menuCloseCallback(Ref* pSender)
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


