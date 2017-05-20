// game over includes files listed below
#include "GameOver.h"
#include "Level1.h"
#include "MainMenu.h"
//#include "LeaderBoard.h"
//#include "Database.h"
#include "Level2.h"
#include "ui/CocosGUI.h"
#include <iostream>

#include "SimpleAudioEngine.h" // cocos2d audio sys


// game over audio
#define BACKGROUND_AUDIO "Drizzle_to_Downpour.mp3"



using namespace CocosDenshion;// for the in house cocos audio engine

int Level1score;
int Level2score;
int TScore;
//
//std::string name = "Please enter your Name:";
//ui::EditBox* Box;
// cocos namespace 
USING_NS_CC;
// scene pointer to create scene
Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// Init method for sprites and methods are called using schedule selector
bool GameOver::init()
{
	//super init first
	if (!Layer::init())
	{
		return false;
	}

	Level1 Level1;
	Level1score = Level1.getScore();
	CCLOG("Score: init: %i", Level1score);

	Level2 Level2;
	Level2score = Level2.GetScore();
	CCLOG("Score: init: %i", Level2score);

	GameOver Total;
	TScore = Level1score + Level2score;
	CCLOG("Score: init: %i", TScore);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameOver::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	/*
	Add a label that says Game Over
	Create and initialize the Game Over label
	Position the Game Over label in the center of the screen
	Add the Game Over label as a child to this layer
	*/

	auto label = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 40);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2.2 - label->getContentSize().height));

	this->addChild(label, 1);

	auto MainMenu = MenuItemImage::create("Mainmenu.png", "Mainmenu.png", CC_CALLBACK_1(GameOver::GoToMainMenuScene, this));
	MainMenu->setPosition(Vec2(visibleSize.width / 5, origin.y + visibleSize.height / 4.0));

	auto menu1 = Menu::create(MainMenu, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	auto TryAgain = MenuItemImage::create("TryAgain.png", "TryAgain.png", CC_CALLBACK_1(GameOver::GoToGameScene, this));
	TryAgain->setPosition(Vec2(visibleSize.width / 1.3, origin.y + visibleSize.height / 4.0));

	auto menu2 = Menu::create(TryAgain, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);

	/*// LeaderBoard
	auto Leaderboard = MenuItemImage::create("leaderboard1.png", "leaderboard1.png", CC_CALLBACK_1(GameOverScene::GoToLeaderBoard, this));
	Leaderboard->setPosition(Point(visibleSize.width / 2.5 + origin.x, visibleSize.height / 5 + origin.y));

	auto menu4 = Menu::create(Leaderboard, NULL);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4, 1);
	*/
	/*	auto Submit = MenuItemImage::create("Submit.png", "Submit.png", CC_CALLBACK_1(GameOverScene::GoToLeaderBoard, this));
	Submit->setPosition(Vec2(origin.x + visibleSize.width / 2, 70));
	auto menu3 = Menu::create(Submit, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);
	*/
	//This adds a background to the screen
	auto sprite = Sprite::create("Flag of xexes.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	/*auto EBox = ui::EditBox::create(Size(200, 40), ".png");
	EBox->setPlaceHolder("Enter Name:");
	EBox->setFontSize(20);
	EBox->setMaxLength(10);
	EBox->setPosition(Vec2(origin.x + visibleSize.width / 2, 150));
	this->addChild(EBox, 1);

	Box = EBox;*/
/*
	CCLOG("Score: %d", TScore);
	auto nameLabel = Label::createWithTTF("Your Score: " + std::to_string(TScore), "fonts/Marker Felt.ttf", 24);
	nameLabel->setColor(Color3B::RED);
	nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, 200));

	this->addChild(nameLabel, 1);*/

	return true;
}
// method for label new game goes to level1
void GameOver::GoToGameScene(Ref* psender)
{
	auto scene = Level1::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
// method for label go to main menu
void GameOver::GoToMainMenuScene(Ref* psender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
/*
void GameOverScene::GoToLeaderBoard(Ref* psender)
{
Database d;
d.write(Box->getText(), Pscore);
auto scene = LeaderBoard::createScene();
Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}
*/
// closes application safely and for x button
void GameOver::menuCloseCallback(Ref* pSender)
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