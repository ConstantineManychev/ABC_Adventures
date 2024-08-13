#include "ScenesManager.h"

#include "DataManager.h"

_USEC

ScenesManager::ScenesManager()
{

}

ScenesManager* ScenesManager::getInstance()
{
	static ScenesManager instance;
	return &instance;
}

void ScenesManager::openScene(const std::string& aSceneID)
{
	auto sceneIt = mScenes.find(aSceneID);

	if (sceneIt != mScenes.end())
	{
		auto scene = sceneIt->second;

		Director::getInstance()->runWithScene(scene);

		scene->useDefaultView();
	}
	else
	{

	}
}

void ScenesManager::registerScene(const std::string& aSceneID, BaseScene* aScene)
{
	mScenes[aSceneID] = aScene;
}