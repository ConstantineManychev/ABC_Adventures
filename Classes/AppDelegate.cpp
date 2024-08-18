#include "AppDelegate.h"

#include "Managers/DataManager.h"
#include "Managers/GameDirector.h"
#include "Types/BasicDataTypes.h"

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

_USEC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#endif
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; //flag for packages manager
}


void AppDelegate::onInit()
{
	DM->loadMainInfo("configs/main_config.json");
}

bool AppDelegate::applicationDidFinishLaunching() {

	onInit();

	auto& mainInfo = DM->getMainInfo();

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

		if (mainInfo.isFullScreen)
		{
			glview = GLViewImpl::createWithFullScreen("ABC_Adventures");
		}
		else
		{
			glview = GLViewImpl::createWithRect("ABC_Adventures", cocos2d::Rect(0, 0, mainInfo.screenWidth, mainInfo.screenHeight));
		}
#else
        glview = GLViewImpl::create("ABC_Adventures");
#endif
        director->setOpenGLView(glview);
    }


	DM->calcScale();

    const auto& glviewFrameSize = glview->getFrameSize();

    register_all_packages();

	GD->startGame();

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}
