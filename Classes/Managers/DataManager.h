#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "cocos2d.h"

//json
#include "external/json/reader.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
#include "external/json/prettywriter.h"

#include "CommonDefines.h"

#include "Helpers/JsonHelper.h"
#include "Types/BasicDataTypes.h"
#include "Basics/BValue.h"

#include <map>

_CSTART

class DataManager
{
private:

	DataManager();

	void parseStartupInfo(const rapidjson::Value& aValue, sMainInfo& aMainInfo);

	std::string mResourcePath;

 	sMainInfo mMainInfo;

	std::map< std::string, sWindowInfo > mWindowsInfos;
	std::map< std::string, BValue > mViewsInfos;

	void parseViewConfig(const std::string& aConfigPath);

public:

	static DataManager* getInstance();

	void setResourcePath(const std::string& resPath);

	void loadMainInfo(const std::string& configPath);
	void loadWindows(const std::string& folderPath);

	void parseViewConfigs();

	const sMainInfo& getMainInfo() const;
	const sWindowInfo* getWindowInfo(const std::string& aWndID) const;

	const BValue& getViewInfoByID(const std::string& aID) const;

	void saveMainInfo();

	float getScaleY();


};

#define DM DataManager::getInstance()

_CEND

#endif // __DATA_MANAGER_H__
