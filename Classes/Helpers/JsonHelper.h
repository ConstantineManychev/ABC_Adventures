#ifndef __JsonHelper_H__
#define __JsonHelper_H__

#include "CommonDefines.h"
#include "Basics/BValue.h"

#include "cocos2d.h"

//json
#include "external/json/reader.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "external/json/prettywriter.h"

_CSTART

class JsonHelper
{
public:

	static void parseBValueFromJsonConfig(const std::string& aConfigPath, BValue& aBValue);
    static bool saveBValueToJsonValue( rapidjson::Value& jsonValue, const BValue& bValue, rapidjson::Document::AllocatorType& allocator );
    static void parseBValueFromJsonValue( const rapidjson::Value& jsonValue, BValue& bValue );
};

_CEND

#endif __JsonHelper_H__
