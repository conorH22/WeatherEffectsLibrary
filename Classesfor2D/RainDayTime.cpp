
// include header files simpleaudioengine, realtime, parallaxNodeExtra, raindaytime and level2story
#include "RainDayTime.h"
#include "RealTime.h"
#include "ParallaxNodeExtras.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#define TRANSACTION_DURATION 1.0f
#define LAYER_TAG -999
#define BACKGROUND_MOVE_SPEED  5 
USING_NS_CC;
#define COCOS2D_DEBUG 1 //used for CCLOG for debugging/testing
using namespace CocosDenshion;// for the in house cocos audio engine
							  // scene audio
#define GAME_AUDIO "Far_The_Days_Come.mp3"
#define EXPLOSION_LARGE "explosion_large.wav"
#define BULLET "Emergency_Siren_Short_Burst.mp3"
#define ENEMY_BULLET "Crash.mp3"
int Score2;
Scene* RainDayTime::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RainDayTime::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool RainDayTime::init()
{
	// super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(RainDayTime::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	scaleRD = visibleSize.width / 320.0f;

	//rain weather particle effect
	ParticleSystemQuad* RainEffect = ParticleSystemQuad::create("Particle_texture_raincy.plist");
	RainEffect->setPosition(Point(visibleSize.width / 2 - 30, visibleSize.height)); //position in screen
	RainEffect->setScale(scaleRD); //set scale for rain particle
	this->addChild(RainEffect);

	
	//player ship created using sprite, position and added to scene 
	player = Sprite::create("Player1.png");
	player->setPosition(Vec2(visibleSize.width / 2.4f, visibleSize.height / 2.2f));

	this->addChild(player);

	// Create the ParallaxNode
	_backgroundNode = ParallaxNodeExtras::create();
	this->addChild(_backgroundNode, -1);

	// Create the sprites will be added to the ParallaxNode
	_spaceDust1 = Sprite::create("landscape.png");
	_spaceDust2 = Sprite::create("landscape.png");


	//Determine relative movement speeds for space dust and background
	auto dustSpeed = Point(0.1F, 0.1F);
	auto bgSpeed = Point(0.05F, 0.05F);

	// Add children to ParallaxNode
	_backgroundNode->addChild(_spaceDust1, 0, dustSpeed, Point(0, visibleSize.height / 2));
	_backgroundNode->addChild(_spaceDust2, 0, dustSpeed, Point(_spaceDust1->getContentSize().width, visibleSize.height / 2));



	// timer label 

	const float timerFontSize = 2;
	const float timerPostitionX = 24;
	const float timerPostitionY = 12;
	CountDown = 120;
	String * temptimer = String::createWithFormat("Time Remaining:%i", CountDown);

	TimerLabel = Label::create(temptimer->getCString(), "fonts/Marker felt.tff", visibleSize.height * 0.1);
	TimerLabel->setColor(Color3B::RED);
	TimerLabel->setAnchorPoint(Vec2(0, 1));
	TimerLabel->setPosition(visibleSize.width * 0.3, visibleSize.height* 1.0);
	TimerLabel->setScale(0.5f);

	this->addChild(TimerLabel, 1);
	this->schedule(schedule_selector(RainDayTime::UpdateTimer), 1); //added to scene/schedule_selector
	this->scheduleUpdate();


	// enemy vector that loads enemy image for  enemy sprite
#define ENEMYARMYNUM 20
	_enemies = new Vector<Sprite*>(ENEMYARMYNUM);
	for (int i = 0; i < ENEMYARMYNUM; ++i) {
		auto *enemy2 = Sprite::create("Boss2.png");
		enemy2->setVisible(false);
		this->addChild(enemy2);
		_enemies->pushBack(enemy2);
	}
	/*this->schedule(schedule_selector(Level1::addEnemy), 1);
	this->scheduleUpdate();*/
	// player laser bullets, using green laser image
#define LASERSNUM 10
	_shipLasers = new Vector<Sprite*>(LASERSNUM);
	for (int i = 0; i < LASERSNUM; ++i) {
		auto shipLaser = Sprite::create("GreenLaser.png");
		shipLaser->setVisible(false);
		this->addChild(shipLaser);
		_shipLasers->pushBack(shipLaser);
	}
	//enemy lasers using redbeam laser image
	_EnemyLasers = new Vector<Sprite*>(LASERSNUM);
	for (int i = 0; i < LASERSNUM; ++i) {
		auto EnemyLaser = Sprite::create("RedBeam.png");
		EnemyLaser->setVisible(false);

		this->addChild(EnemyLaser);
		_EnemyLasers->pushBack(EnemyLaser);
	}
	// device sets acceleromterEnabled to true, with new Event listenerAccleration added
	Device::setAccelerometerEnabled(true);
	auto accelerationListener = EventListenerAcceleration::create(CC_CALLBACK_2(RainDayTime::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(accelerationListener, this);
	// new touch listener for player bullets/lasers
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(RainDayTime::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// keyboard listener for keyboard input switch statement is used for w,s,up and down keys
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
			/*case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
			event->getCurrentTarget()->setPosition(--loc.x-=12, loc.y);
			break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
			event->getCurrentTarget()->setPosition(++loc.x+=12, loc.y);
			break;*/
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			event->getCurrentTarget()->setPosition(loc.x, ++loc.y += 52);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			event->getCurrentTarget()->setPosition(loc.x, --loc.y -= 52);
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, player);

	//lives label
	_lives = 6;
	String * tempLives = String::createWithFormat("Lives:%d", _lives);
	LivesLabel = Label::create(tempLives->getCString(), "fonts/Marker felt.tff", visibleSize.height* 0.1);
	LivesLabel->setColor(Color3B::RED);
	LivesLabel->setAnchorPoint(Vec2(0, 1));
	LivesLabel->setPosition(visibleSize.width / 12.3 + origin.x, visibleSize.height * 1.0);
	LivesLabel->setScale(0.5f);
	this->addChild(LivesLabel, 1000);
	double curTime = getTimeTick();
	_gameOverTime = curTime + 200000;

	// score label
	const float ScoreFontSize = 2;
	const float ScorePositionX = 24;
	const float ScorepositionY = 12;
	Score2 = 0;
	String * tempScore = String::createWithFormat("Score:%i", Score2);
	ScoreLabel = Label::create(tempScore->getCString(), "fonts/Marker felt.tff", visibleSize.height* 0.1);
	ScoreLabel->setColor(Color3B::RED);
	ScoreLabel->setAnchorPoint(Vec2(0, 1));
	ScoreLabel->setPosition(visibleSize.width / 1.2 + origin.x, visibleSize.height * 1.0);
	ScoreLabel->setScale(0.5f);
	this->addChild(ScoreLabel, 1000);

	this->scheduleUpdate();
	this->schedule(schedule_selector(RainDayTime::enemybullets), 2.0f);

	//this->schedule(schedule_selector(HelloWorld::UpdateTimer), 1.0f);
	//  game audio 
	SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_AUDIO, true);
	SimpleAudioEngine::getInstance()->preloadEffect(EXPLOSION_LARGE);
	SimpleAudioEngine::getInstance()->preloadEffect(BULLET);
	SimpleAudioEngine::getInstance()->preloadEffect(ENEMY_BULLET);

	return true;
}
// timer method 
void RainDayTime::UpdateTimer(float dt)
{
	CountDown--;
	String * tempTimer = String::createWithFormat("Time Remaining:%i", CountDown);
	TimerLabel->setString(tempTimer->getCString());
	TimerLabel->setScale(0.5f);
	//if  timer reaches zero new level
	if (CountDown <= 0)
	{
		RainDayTime::endScene(LOSERD);
		this->unscheduleUpdate();
	}
}

// key board press  message in CCLOG
void RainDayTime::onkeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	CCLOG("Key with keycode %d released", keyCode);

}
// key board release  message in CCLOG
void RainDayTime::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	CCLOG("Key with keycode %d released", keyCode);

}

// update method for background movement/parallax scrolling, collison detection for player, enemies, laser bullets
void RainDayTime::update(float dt)
{
	auto backgroundScrollVert = Point(-500, 0);
	_backgroundNode->setPosition(_backgroundNode->getPosition() + (backgroundScrollVert * dt));



	//Parallax
	auto spaceDusts = new Vector<Sprite*>(2);
	spaceDusts->pushBack(_spaceDust1);
	spaceDusts->pushBack(_spaceDust2);
	for (auto spaceDust : *spaceDusts) {
		float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
		float size = spaceDust->getContentSize().width;
		if (xPosition < -size / 2) {
			_backgroundNode->incrementOffset(Point(spaceDust->getContentSize().width * 2, 0), spaceDust);
		}
	}


	//Acceleration
	Size winSize = Director::getInstance()->getWinSize();
	float maxY = winSize.height - player->getContentSize().height / 2;
	float minY = player->getContentSize().height / 2;
	float diff = (_shipPointsPerSecY * dt);
	float newY = player->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	player->setPosition(player->getPosition().x, newY);

	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextEnemySpawn) {

		float randMillisecs = randomValueBetween(0.20F, 0.9F) * 1000;
		_nextEnemySpawn = randMillisecs + curTimeMillis;

		float randY = randomValueBetween(0.0F, winSize.height);
		float randDuration = randomValueBetween(3.0F, 5.0F);

		enemy2 = _enemies->at(_nextEnemy);
		_nextEnemy++;

		if (_nextEnemy >= _enemies->size())
			_nextEnemy = 0;

		enemy2->stopAllActions();
		enemy2->setPosition(winSize.width + enemy2->getContentSize().width / 2, randY);
		enemy2->setVisible(true);
		enemy2->runAction(
			Sequence::create(
				MoveBy::create(randDuration, Point(-winSize.width - enemy2->getContentSize().width, 0)),
				MoveBy::create(randDuration, Point(winSize.width - enemy2->getContentSize().width, 0)),
				CallFuncN::create(CC_CALLBACK_1(RainDayTime::setInvisible, this)),
				NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
		);
	}
	// Enemies type level 1
	for (auto enemy2 : *_enemies) {
		if (!(enemy2->isVisible()))
			continue;
		for (auto shipLaser : *_shipLasers) {
			if (!(shipLaser->isVisible()))
				continue;
			if (shipLaser->getBoundingBox().intersectsRect(enemy2->getBoundingBox())) {
				ParticleSystemQuad*particleEnemyCollision = CCParticleSystemQuad::create("particle_textureEnemydeath.plist");
				particleEnemyCollision->setPosition(enemy2->getPosition());
				particleEnemyCollision->setAutoRemoveOnFinish(true);
				this->addChild(particleEnemyCollision);
				SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_LARGE);
				shipLaser->setVisible(false);
				enemy2->setVisible(false);
				Score2++;

				String * tempScore = String::createWithFormat("Score:%i", Score2);
				ScoreLabel->setString(tempScore->getCString());
				ScoreLabel->setScale(0.5f);
				if (Score2 == 5)
				{
					auto scene = MainMenuScene::createScene();
					Director::getInstance()->replaceScene(TransitionPageTurn::create(1, scene, true));
				}
			}
		}
		for (auto EnemyLaser : *_EnemyLasers) {
			if (!(EnemyLaser->isVisible()))
				continue;
			if (EnemyLaser->getBoundingBox().intersectsRect(player->getBoundingBox())) {
				ParticleSystemQuad*particleEnemyCollision = ParticleSystemQuad::create("particle_textureEnemydeath.plist");
				particleEnemyCollision->setPosition(player->getPosition());
				particleEnemyCollision->setAutoRemoveOnFinish(true);
				this->addChild(particleEnemyCollision);
				SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_LARGE);
				EnemyLaser->setVisible(false);
				//player->setVisible(false);
				player->runAction(Blink::create(1.0F, 4));
				_lives--;
				String * tempLives = String::createWithFormat("Lives:%d", _lives);
				LivesLabel->setString(tempLives->getCString());
				LivesLabel->setScale(0.5f);
			}
		}

		if (player->getBoundingBox().intersectsRect(enemy2->getBoundingBox())) {
			enemy2->setVisible(false);
			//player->runAction(Blink::create(1.0F, 4));
			_lives--;
			String * tempLives = String::createWithFormat("Lives:%d", _lives);
			LivesLabel->setString(tempLives->getCString());
			LivesLabel->setScale(0.5f);
		}
	}

	if (_lives <= 0) {
		player->stopAllActions();
		player->setVisible(false);
		this->endScene(LOSERD);
	}
	else if (curTimeMillis >= _gameOverTime) {
		this->endScene(WINRD);
	}
}
// acceleration method for android tilt controls
void RainDayTime::onAcceleration(Acceleration* acc, Event* event) {
#define FILTERINGFACTOR 0.1
#define RESTACCELX -0.6
#define SHIPMAXPOINTSPERSEC (winSize.height*0.5)        
#define MAXDIFFX 0.2

	double rollingX;

	// Cocos2DX inverts X and Y accelerometer depending on device orientation
	// in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
	acc->x = acc->y;
	rollingX = (acc->x * FILTERINGFACTOR) + (rollingX * (1.0 - FILTERINGFACTOR));
	float accelX = acc->x - rollingX;
	Size winSize = Director::getInstance()->getWinSize();
	float accelDiff = accelX - RESTACCELX;
	float accelFraction = accelDiff / MAXDIFFX;
	_shipPointsPerSecY = SHIPMAXPOINTSPERSEC * accelFraction;
}
// random  method for scene
float RainDayTime::randomValueBetween(float low, float high) {
	// from http://stackoverflow.com/questions/686353/c-random-float-number-generation
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
}
// get time for update method and timed events
float RainDayTime::getTimeTick() {
	timeval time;
	gettimeofday(&time, NULL);
	unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (float)millisecs;
}
// set invisible  method when objects have been collided with
void RainDayTime::setInvisible(Node * node) {
	node->setVisible(false);
}
// enemy bullets methods (AI) what happens to enemy bullets
void RainDayTime::enemybullets(float dt)
{

	SimpleAudioEngine::getInstance()->playEffect(ENEMY_BULLET);
	auto winSize = Director::getInstance()->getWinSize();
	auto EnemyLaserz = _EnemyLasers->at(_nextEnemyLaser++);
	if (_nextEnemyLaser >= _EnemyLasers->size())
		_nextEnemyLaser = 0;
	EnemyLaserz->setPosition(enemy2->getPosition() + Point(EnemyLaserz->getContentSize().width / 2, 0));
	EnemyLaserz->setVisible(true);
	EnemyLaserz->stopAllActions();
	EnemyLaserz->runAction(
		Sequence::create(
			MoveBy::create(1, Point(-winSize.width, 0)),  // enemy bullets move from right to left towards player
			CallFuncN::create(CC_CALLBACK_1(RainDayTime::setInvisible, this)),
			NULL));
}


// on touch began for player bullets
void RainDayTime::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) {
	SimpleAudioEngine::getInstance()->playEffect(BULLET);
	auto winSize = Director::getInstance()->getWinSize();
	auto shipLaser = _shipLasers->at(_nextShipLaser++);
	if (_nextShipLaser >= _shipLasers->size())
		_nextShipLaser = 0;
	shipLaser->setPosition(player->getPosition() + Point(shipLaser->getContentSize().width / 2, 0));
	//shipLaser->setPosition(player->getPosition() + Point(shipLaser->getContentSize().width / 3, 0));
	shipLaser->setVisible(true);
	shipLaser->stopAllActions();
	shipLaser->runAction(
		Sequence::create(
			MoveBy::create(0.5, Point(winSize.width, 0)),
			//MoveBy::create(0.5, Point(-winSize.width, 0)),
			CallFuncN::create(CC_CALLBACK_1(RainDayTime::setInvisible, this)),
			NULL));
}
// when player select restart , this is method is called
void RainDayTime::restartTapped(Ref* pSender) {
	Director::getInstance()->replaceScene
	(TransitionZoomFlipX::create(0.5, this->createScene()));
	// reschedule
	this->scheduleUpdate();
}
// end game for level2 when timer goes to zero or lives go to zero
void RainDayTime::endScene(EndReasonRD endReason2) {
	if (_gameOver)
		return;
	_gameOver = true;

	auto winSize = Director::getInstance()->getWinSize();
	char message[10] = "You Win";
	if (endReason2 == LOSERD)
		strcpy(message, "You Lose");
	auto label = Label::createWithBMFont("Arial.fnt", message);
	label->setScale(0.1F);
	label->setColor(Color3B::RED);
	label->setPosition(winSize.width / 2, winSize.height*0.6F);
	this->addChild(label);

	strcpy(message, "Restart");
	auto restartLabel = Label::createWithBMFont("Arial.fnt", message);
	restartLabel->setColor(Color3B::RED);
	auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(RainDayTime::restartTapped, this));
	restartItem->setScale(0.1F);
	restartItem->setPosition(winSize.width / 2, winSize.height*0.4);

	auto *menu = Menu::create(restartItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	// clear label and menu
	restartItem->runAction(ScaleTo::create(0.5F, 1.0F));
	label->runAction(ScaleTo::create(0.5F, 1.0F));

	// Terminate update callback
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(RainDayTime::UpdateTimer));
}
// score methods to set score, getis score and get score
void RainDayTime::SetIsScored()
{
	scored = true;
}

bool RainDayTime::GetIsScored()
{
	return scored;
}

int RainDayTime::GetScore()
{
	CCLOG("Score %d", Score2);
	return Score2;
}

// this make x button close game
void RainDayTime::menuCloseCallback(Ref* pSender)
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