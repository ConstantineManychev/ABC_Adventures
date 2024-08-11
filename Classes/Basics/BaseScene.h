#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "CommonDefines.h"

_CSTART

class BaseScene : public Scene
{
	typedef Scene Parent;

public:

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void useDefaultView() = 0;
};

_CEND

#endif // __BASE_SCENE_H__
