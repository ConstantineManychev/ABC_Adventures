#include "BaseScene.h"

_USEC

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BaseScene::init()
{
    return true;
}


void BaseScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
