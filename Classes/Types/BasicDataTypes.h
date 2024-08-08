#ifndef __BASIC_DATA_TYPES_H__
#define __BASIC_DATA_TYPES_H__

#include "CommonDefines.h"
#include "Basics/BValue.h"

_CSTART

struct sMainInfo
{
	bool isFullScreen;

	int screenHeight;
	int screenWidth;

	sMainInfo()
		: isFullScreen(false)
		, screenHeight(600)
		, screenWidth(800)
	{}
};

struct sWindowInfo
{
	std::string windowID;

	Value params;

	sWindowInfo()
	{}
};

_CEND

#endif // __BASIC_DATA_TYPES_H__
