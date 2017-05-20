
#include "Night.h"
USING_NS_CC;

Scene* Night::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    Night *layer = Night::create();
    layer->setTag(LAYER_TAG);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Night::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    winSize = Director::sharedDirector()->getWinSize(); 
	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 
    //background image

	auto titleSprite = Sprite::create("daynight.png");//image
	titleSprite->setPosition(Point(winSize.width / 2.2 + origin.x, winSize.height / 2.2 + origin.y));
	this->addChild(titleSprite);
	
	// add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

   // add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Night::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
    
    
    float scale = winSize.width / 320.0f;
    
    
    //Moon
    Sprite *MoonSprite = Sprite::create("Moon.png");
    MoonSprite->setPosition(ccp(winSize.width-MoonSprite->getContentSize().width, winSize.height - MoonSprite->getContentSize().height/1));
   
    this->addChild(MoonSprite);
    
   
    return true;
}

void Night::menuCloseCallback(Ref* pSender)
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
