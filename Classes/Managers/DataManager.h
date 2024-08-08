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

#include "Helpers/DataHelper.h"
#include "Types/BasicDataTypes.h"

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

public:

	static DataManager* getInstance();

	void setResourcePath(const std::string& resPath);

	void loadMainInfo(const std::string& configPath);
	void loadWindows(const std::string& folderPath);

	const sMainInfo* getMainInfo() const;
	const sWindowInfo* getWindowInfo(const std::string& aWndID) const;

	void saveMainInfo();

	sMainInfo& getMainInfo();


};

#define DM DataManager::getInstance()

_CEND

#endif // __DATA_MANAGER_H__
