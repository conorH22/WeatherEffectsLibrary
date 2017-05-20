//weather effect for cloudy (day) scene cpp file
#include "CloudyDayTime.h"

//cocos namespace
USING_NS_CC;

Scene* CloudyDayTime::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    CloudyDayTime *layer = CloudyDayTime::create();
    layer->setTag(LAYER_TAG);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CloudyDayTime::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
 
    
    winSize = Director::sharedDirector()->getWinSize(); 
	//Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CloudyDayTime::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + winSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
    //background image
	auto titleSprite = Sprite::create("dayovercast.png");// 
	titleSprite->setPosition(Point(winSize.width/2.2 + origin.x, winSize.height / 2.2 + origin.y));
	this->addChild(titleSprite);
    
	auto Cloud = Sprite::create("cloud4.png");// cloud images 1- 3
	Cloud->setPosition(Point(winSize.width / 1 + origin.x, winSize.height + origin.y));
	this->addChild(Cloud);
	auto Cloud2 = Sprite::create("cloud4.png");//image
	Cloud2->setPosition(Point(winSize.width / 5 + origin.x, winSize.height + origin.y));
	this->addChild(Cloud2);
	auto cloud3 = Sprite::create("cloud4.png");//image
	cloud3->setPosition(Point(winSize.width / 10 + origin.x, winSize.height + origin.y));
	this->addChild(cloud3);
    scale = winSize.width / 320.0f;
	 return true;
}
// this method exits out of application with  Director::getInstance()->end();
void CloudyDayTime::menuCloseCallback(Ref* pSender)
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
