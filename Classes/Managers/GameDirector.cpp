#include "GameDirector.h"

_USEC

GameDirector::GameDirector()
{

}

GameDirector* GameDirector::getInstance()
{
	static GameDirector instance;
	return &instance;
}