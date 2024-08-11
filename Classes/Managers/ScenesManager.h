#ifndef __SCENES_MANAGER_H__
#define __SCENES_MANAGER_H__

#include "CommonDefines.h"

#include "Basics/BaseScene.h"

_CSTART

class ScenesManager
{
private:

	ScenesManager();

	std::map<std::string, BaseScene*> mScenes;

public:

	static ScenesManager* getInstance();

	void registerScene(const std::string& aSceneID, BaseScene* aScene);
	void openScene(const std::string& aSceneID);

};

#define SM ScenesManager::getInstance()

_CEND

#endif // __SCENES_MANAGER_H__
