#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
// game over class method and variables declaration
class GameOver: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

private:
	
	void GoToGameScene(cocos2d::Ref *sender);
	void GoToMainMenuScene(cocos2d::Ref *sender);
	//	void GoToLeaderBoard(cocos2d::Ref *sender);

};

#endif // _GAME_OVER_H__