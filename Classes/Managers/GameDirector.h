#ifndef __GAME_DIRECTOR_H__
#define __GAME_DIRECTOR_H__

#include "CommonDefines.h"

#include "Basics/BaseLocation.h"
#include "Basics/Player.h"

_CSTART

class GameDirector
{
private:

	BaseLocation* mCurrentLocation;
	Player* mCurrentPlayer;

	GameDirector();

public:

	static GameDirector* getInstance();

	void startGame();

	void setLocation(BaseLocation* aLocation);
	void setPlayer(Player* aPlayer);


	BaseLocation* getCurrentLocation();
	Player* getCurrentPlayer();

};

#define GD GameDirector::getInstance()

_CEND

#endif // __GAME_DIRECTOR_H__
