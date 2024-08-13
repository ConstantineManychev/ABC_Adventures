#ifndef __NODE_HELPER_H__
#define __NODE_HELPER_H__

#include "cocos2d.h"

#include "CommonDefines.h"

_CSTART

class NodeHelper
{
public:

	static Node* createNodeForType(const std::string& aType);

};

_CEND

#endif // __NODE_HELPER_H__
