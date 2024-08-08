#include "AppDelegate.h"
#include "Scenes/MainMenuScene.h"
#include "Managers/DataManager.h"
#include "Types/BasicDataTypes.h"

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

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
			glview = GLViewImpl::createWithFullScreen("ABC_Adventure");
		}
		else
		{
			glview = GLViewImpl::createWithRect("ABC_Adventure", cocos2d::Rect(0, 0, mainInfo.screenWidth, mainInfo.screenHeight));
		}
#else
        glview = GLViewImpl::create("ABC_Adventure");
#endif
        director->setOpenGLView(glview);
    }

    const auto& glviewFrameSize = glview->getFrameSize();

    register_all_packages();

    auto scene = MainMenuScene::createScene();

    director->runWithScene(scene);

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
