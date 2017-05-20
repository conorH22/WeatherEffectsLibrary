

#ifndef SunnyDayTime_h
#define SunnyDayTime_h

#include "cocos2d.h"
#include "ParallaxNodeExtras.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1

// win/lose enums
typedef enum {
	WINSND,
	LOSESND
} EndReasonSND;

class SunnyDayTime : public Layer
{
public:

    Size winSize;
 
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
   
	void menuCloseCallback(Ref* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SunnyDayTime);
	//virtual void onAcceleration(Acceleration* acc, Event* event);
	/*float randomValueBetween(float low, float high);
	void setInvisible(Node * node);
	float getTimeTick();
	float scale;
	void addEnemy(float dt);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	virtual void onkeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);*/
	bool scored;
	/*void SetIsScored();
	bool GetIsScored();
	int GetScore();*/
	int CountDown;
    
private:
    
	Sprite* player;
	Sprite* enemy2;
	unsigned int Score2;
	//cocos2d labels in game scene for score, health and timer
	Label * ScoreLabel;
	Label * HealthLabel;
	Label * TimerLabel;
	Label * LivesLabel;

	ParallaxNodeExtras *_backgroundNode;
	Sprite *_spaceDust1, *_spaceDust2;
	float _shipPointsPerSecY;
	Vector<Sprite*> *_enemies;
	int _nextEnemy = 0;
	float _nextEnemySpawn = 0;
	Vector<Sprite*> *_shipLasers;
	Vector<Sprite*>*_EnemyLasers;
	int _nextShipLaser = 0;
	int _nextEnemyLaser = 0;
	int _lives = 0;
	double _gameOverTime;
	bool _gameOver = false;

	/*void update(float dt);
	void UpdateTimer(float dt);
	void endScene(EndReasonSND endReasonSND);
	void enemybullets(float dt);
	void restartTapped(Ref* pSender);*/
    
    
};

#endif
