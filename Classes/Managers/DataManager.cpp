#include "DataManager.h"

_USEC

DataManager::DataManager()
{

}

DataManager* DataManager::getInstance()
{
	static DataManager instance;
	return &instance;
}

void DataManager::setResourcePath(const std::string& resPath)
{
	mResourcePath = resPath;
}

void DataManager::loadMainInfo(const std::string& configPath)
{
	std::string content = FileUtils::getInstance()->getStringFromFile(configPath);

	bool isLoadingCorrect = false;

	if (!content.empty())
	{
		rapidjson::Document document;
		document.Parse<0>(content.c_str());
		if (!document.HasParseError())
		{
			auto docIt = document.FindMember("startup_settings");
			if (docIt != document.MemberEnd())
			{
				isLoadingCorrect = true;
				parseStartupInfo(docIt->value, mMainInfo);
			}
		}
	}
}

void DataManager::parseStartupInfo(const rapidjson::Value& aValue, sMainInfo& aMainInfo)
{
	if (aValue.IsObject())
	{
		for (auto valIt = aValue.MemberBegin(); valIt != aValue.MemberEnd(); ++valIt)
		{
			if (valIt->name == "is_full_screen" && valIt->value.IsBool())
			{
				mMainInfo.isFullScreen = valIt->value.GetBool();
			}
			else if (valIt->name == "screen_size" && valIt->value.IsObject())
			{
				const auto& sizeObject = valIt->value.GetObject();

				auto heightIt = sizeObject.FindMember("height");
				auto widthIt = sizeObject.FindMember("width");

				if ( heightIt != sizeObject.MemberEnd() && heightIt->value.IsInt()
					&& widthIt != sizeObject.MemberEnd() && widthIt->value.IsInt() )
				{
					mMainInfo.screenHeight = heightIt->value.GetInt();
					mMainInfo.screenWidth = widthIt->value.GetInt();
				}
			}
		}
	}
}

sMainInfo& DataManager::getMainInfo()
{
	return mMainInfo;
}