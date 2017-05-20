// include header files that calls other classes used in this ccp file
#include "RealTime.h"
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
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
//stdio, cstdio, fstream, iosstream, ctime and vector headers included
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
//json parser for c++ lib include used header files
//#include "spine\Json.h" cocos 2d built in jsonparser not used
#include "include\rapidjson\document.h"
#include "include\rapidjson\prettywriter.h"
#include "include\rapidjson\stringbuffer.h"
#include"include\rapidjson\filereadstream.h"
#include"include\rapidjson\istreamwrapper.h"


//using cocos namespace for cocos2d functions/methods
USING_NS_CC;
using namespace std;  //standard namespace
using namespace rapidjson; //rapidjson namespace
using std::string;

// scene creates a new pointer
Scene* RealTime::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RealTime::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance // realtime scene starts
bool RealTime::init()
{
    
    // super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //gets Visiblesie and getsvisibleOrigin
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // menu item with "X" image, which is clicked to quit the program
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(RealTime::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    //  label
    
    //auto label = Label::createWithTTF("Loading weatherdata", "fonts/Marker Felt.ttf", 14);
    //
    //// position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(label, 1);
	auto titleSprite = Sprite::create("title2d.png");//image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(titleSprite);
    

	//cocos2d network class that handles HttpRequests for wunderground weather api call
	//pointer request is used to set Url,setResponseCallback, setRequestType and send request
	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl("http://api.wunderground.com/api/907f0105dc40c3d1/conditions/q/pws:ICOUNTYT2.json");
	request->setResponseCallback(CC_CALLBACK_2(RealTime::onHttpRequestCompleted, this));
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	cocos2d::network::HttpClient::getInstance()->send(request);
	//request is released
	request->release();
    return true;
}
// OnHttpRequestCompleted  gets the responseData using vector char pointer called buffer
void RealTime::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse* response)
{
	std::vector<char> *buffer = response->getResponseData();
	//concatencated merges buffer pointer data and then converts to string
	char * concatencated = (char *)malloc(buffer->size() + 1);
	string convo(buffer->begin(), buffer->end());
	strcpy(concatencated, convo.c_str());
	//rapidjson functions/methods new document created called documentj from rapidjson files,documentj parses the convo.cstr()
	//CCLOG prints the weather value which is nested in the current_observation. documentj contains the apicall from wunderground by getString(), value is sent to cocos log as string 
	Document documentj;
	documentj.Parse(convo.c_str());
	CCLOG("weather = %s\n", documentj["current_observation"]["weather"].GetString());
	// time_t  calls the system time needed for day/night weather effect scenes
	time_t now = time(0);
	//struct tm uses pointer ltm, which gets tm_hour,tm_min,tm_sec and tm_isdst, ints contain the  hour,min,sec system time
	tm *ltm = localtime(&now);
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;
	int second = ltm->tm_sec;
	int saving = ltm->tm_isdst; // hours of daylight savings time
	CCLOG( "Time:%i:%i ",hour,min); // systems time printed to screen
	CCLOG("Time:%i", saving); // is daylight savings used return 1 for yes 0 for no and -1 error.
	int t1 = 07;  // two ints called t1 and t2 which holds two values
	int t2 = 20;//where t1  is estimated sunlight hours begin at 07 and 20 when it ends
	/*TimeSpan daystart = new TimeSpan(07, 0, 0); // t1 and t2 is based upon the timespan function in c#
	TimeSpan dayEnd = new TimeSpan(20, 0, 0);*/

	// if statment checks int hour value from system time against t1 and t2, 
	//if hour is greather than t1 07 day hours then logical AND operator
	//returns the boolean value true if both operands are true and returns false otherwise 
	//if hour from system falls between greather than 07
	//and less than 20 then daylight hours else nightlight hours

	if (( hour>t1) && (hour <t2))
	{
		CCLOG("daytime\n"); //prints to cocos log daytime
		//relvevant weather effects are  checked against the weather tag value
		// so == tag is check for values that appear as value for weather type
		//documentj  search for current_observation , that contains weather tag
		if (documentj["current_observation"]["weather"].GetString() == "Clear")
		{
			// if true cocoslog prints value 
			CCLOG("clear\n");	 
			// scene for weather value replaces	current scene which realtime scene
			auto scene = SunnyDayTime::scene();  
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);  //scene is added to child
		}
		else {  // if not true log prints not weather value
			CCLOG("notclear\n");
		}
		if (documentj["current_observation"]["weather"] == "Rain")
		{
			CCLOG("Rain\n");
			auto scene = RainDayTime::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("notRain\n");
		}
		if (documentj["current_observation"]["weather"] == "Rain Showers")
		{
			CCLOG("Rain showers\n");//Day
			auto scene = RainDayTime::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("not Rain showers\n");
		}
		if (documentj["current_observation"]["weather"]=="Overcast")
		{
			CCLOG("overcast\n");
			auto scene = CloudyDayTime::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
			
		}
		else {
			CCLOG("notOvercast\n");
		}
		if (documentj["current_observation"]["weather"] == "Mostly Cloudy")
		{
			CCLOG("Mostly cloudy\n");
			auto scene = CloudyDayTime::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("notMostlycloudy\n");
		}
		if (documentj["current_observation"]["weather"] == "Snow")
		{
			CCLOG("snowing\n");
			auto scene = SnowDayTime::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		
		else {
			CCLOG("notsnowing\n");
		}
		if (documentj["current_observation"]["weather"] == "Partly Cloudy")
		{
			CCLOG("Partly Cloudy\n");
			auto scene = CloudyDayTime::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
			
		}
		else {
			CCLOG("notPartly Cloudy\n");
		}
		if (documentj["current_observation"]["weather"] == "Fog")
		{
			CCLOG("Foggy\n");
			auto scene = FogDayTime::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("not Foggy\n");
		}

		
		
	}
	else { //night time weather effects ,if t1 and t2 values fall outside then night weather scenes
		CCLOG("nightTime\n");
		if (documentj["current_observation"]["weather"]== "Rain")
		{
			CCLOG("Rain\n");
			auto scene = RainNight::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("notRain\n");
		}
		if (documentj["current_observation"]["weather"] == "Rain Showers")
		{
			CCLOG("Rain showers\n");
			auto scene = RainNight::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);

		}
		else {
			CCLOG("not Rain showers\n");
		}
		if (documentj["current_observation"]["weather"] == "Fog")
		{
			CCLOG("Foggy\n");
			auto scene = FogNights::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("not Foggy\n");
		}
		
		if (documentj["current_observation"]["weather"] == "Partly Cloudy")
		{
			CCLOG("partily cloudy\n");
			//Director::getInstance()->resume();
			auto scene = CloudyNight::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("notclear\n");
		}
		if (documentj["current_observation"]["weather"] == "Overcast")
		{
			CCLOG(" night overcast\n");
			auto scene = CloudyNight::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		

		}
		else {
			CCLOG("notOvercast\n");
		}
		if (documentj["current_observation"]["weather"] == "Mostly Cloudy")
		{
			CCLOG(" Mostly cloudy\n");
			auto scene = CloudyNight::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
			
		
		}
		else {
			CCLOG("not cloudy\n");
		}
		if (documentj["current_observation"]["weather"] == "Snow")
		{
			CCLOG("snowing night\n");
			auto scene = SnowNight::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);

		}
		else {
			CCLOG("notsnowing\n");
		}
		if (documentj["current_observation"]["weather"] == "Clear")
		{
			CCLOG("nighttime\n");
			auto scene = Night::scene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
			this->addChild(scene);
		}
		else {
			CCLOG("not clearnight\n");
		}
	}
	//  http status code, checks  for 200,  will 404 is not found
	CCLOG("Response code:%li\n", response->getResponseCode());
	if (200 == response->getResponseCode())
	{
		CCLOG("successful"); //200 OK || Status Code Definitions for Http
	}
	else {
		CCLOG("failed"); //404 Not found
	}

}

// methods  is called when the  user clicks on the exit button bottom right of cocos scene
void RealTime::menuCloseCallback(Ref* pSender)
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
