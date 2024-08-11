#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "Basics/BaseScene.h"
#include "CommonDefines.h"

_CSTART

class MainGameScene : public BaseScene
{
	typedef BaseScene Parent;

public:

	virtual void useDefaultView() override;

    CREATE_FUNC(MainGameScene);
};

_CEND

#endif // __MAIN_GAME_SCENE_H__
