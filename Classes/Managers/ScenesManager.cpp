#include "ScenesManager.h"

#include "DataManager.h"

_USEC

ScenesManager::ScenesManager()
	: mCurrentScene(nullptr)
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
		mCurrentScene = sceneIt->second;

		Director::getInstance()->runWithScene(mCurrentScene);

		mCurrentScene->useDefaultView();
	}
	else
	{

	}
}

void ScenesManager::registerScene(const std::string& aSceneID, BaseScene* aScene)
{
	mScenes[aSceneID] = aScene;
}

BaseScene* ScenesManager::getCurrentScene()
{
	return mCurrentScene;
}