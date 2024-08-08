#ifndef __GAME_DIRECTOR_H__
#define __GAME_DIRECTOR_H__

#include "CommonDefines.h"

_CSTART

class GameDirector
{
private:

	GameDirector();

public:

	static GameDirector* getInstance();

};

#define GD GameDirector::getInstance()

_CEND

#endif // __GAME_DIRECTOR_H__
