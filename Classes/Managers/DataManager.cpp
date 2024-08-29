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

void DataManager::setResourcePath(const std::string& aResPath)
{
	mResourcePath = aResPath;
}

void DataManager::loadMainInfo(const std::string& aConfigPath)
{
	std::string content = FileUtils::getInstance()->getStringFromFile(aConfigPath);

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

			docIt = document.FindMember("global_values");
			if (docIt != document.MemberEnd() )
			{
				BValue data = BValue();
				JsonHelper::parseBValueFromJsonValue(docIt->value, data);

				if (data.isMap())
				{
					mGlobalValues = data.getValueMap();
				}
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

				if ( heightIt != sizeObject.MemberEnd()
					&& widthIt != sizeObject.MemberEnd())
				{
					if (heightIt->value.IsInt())
					{
						mMainInfo.screenHeight = static_cast<float>(heightIt->value.GetInt());
					}
					else if (heightIt->value.IsDouble() || heightIt->value.IsFloat())
					{
						mMainInfo.screenHeight = heightIt->value.GetFloat();
					}

					if (widthIt->value.IsInt())
					{
						mMainInfo.screenWidth = static_cast<float>(widthIt->value.GetInt());
					}
					else if (widthIt->value.IsDouble() || widthIt->value.IsFloat())
					{
						mMainInfo.screenWidth = widthIt->value.GetFloat();
					}
				}
			}
			else if (valIt->name == "sprites_size" && valIt->value.IsObject())
			{
				const auto& sizeObject = valIt->value.GetObject();

				auto heightIt = sizeObject.FindMember("height");
				auto widthIt = sizeObject.FindMember("width");

				if (heightIt != sizeObject.MemberEnd()
					&& widthIt != sizeObject.MemberEnd())
				{
					if (heightIt->value.IsInt())
					{
						mMainInfo.spritesHeight = static_cast<float>(heightIt->value.GetInt());
					}
					else if (heightIt->value.IsDouble() || heightIt->value.IsFloat())
					{
						mMainInfo.spritesHeight = heightIt->value.GetFloat();
					}

					if (widthIt->value.IsInt())
					{
						mMainInfo.spritesWidth = static_cast<float>(widthIt->value.GetInt());
					}
					else if (widthIt->value.IsDouble() || widthIt->value.IsFloat())
					{
						mMainInfo.spritesWidth = widthIt->value.GetFloat();
					}
				}
			}
			else if (valIt->name == "keys" && valIt->value.IsObject())
			{
				const auto& keysObject = valIt->value.GetObject();

				auto setupKey = [this, keysObject](const std::string& aID)
				{
					auto it = keysObject.FindMember(aID.c_str());
					if (it != keysObject.MemberEnd() && it->value.IsString())
					{
						mKeys[it->name.GetString()] = convertStringToKeyCode(it->value.GetString());
					}
				};

				setupKey("left");
				setupKey("right");
				
			}
		}
	}
}

void DataManager::parseViewConfigs()
{
	BValue values;
	JsonHelper::parseBValueFromJsonConfig("configs/views/views_list.json", values);

	if (values.isVector())
	{
		auto valVec = values.getValueVector();
		for (auto val : valVec)
		{
			if (val.isString())
			{
				parseViewConfig(val.getString());
			}
		}
	}
}

void DataManager::parseViewConfig(const std::string& aConfigPath)
{
	BValue values;
	JsonHelper::parseBValueFromJsonConfig(aConfigPath, values);
	if (values.isMap())
	{
		auto valMap = values.getValueMap();

		auto itID = valMap.find("id");
		if (itID != valMap.end() && itID->second.isString())
		{
			mViewsInfos[itID->second.getString()] = values;
		}
	}

}

const sMainInfo& DataManager::getMainInfo() const
{
	return mMainInfo;
}

float DataManager::getScaleY()
{
	return mMainInfo.scaleY > mMainInfo.scaleX ? mMainInfo.scaleY : mMainInfo.scaleX;
}

void DataManager::setScale(float aX, float aY)
{
	setScaleX(aX);
	setScaleY(aY);
}

void DataManager::setScaleY(float aY)
{
	mMainInfo.scaleY = aY;
}

void DataManager::setScaleX(float aX)
{
	mMainInfo.scaleX = aX;
}

void DataManager::calcScale()
{
	auto screenSize = Director::getInstance()->getWinSize();

	setScale(screenSize.width / mMainInfo.spritesWidth, screenSize.height / mMainInfo.spritesHeight);
}

const BValue& DataManager::getViewInfoByID(const std::string& aID) const
{
	auto it = mViewsInfos.find(aID);
	if (it != mViewsInfos.end())
	{
		return it->second;
	}

	return BValue::Null;
}

const BValue& DataManager::getGlobalValue(const std::string& aID)
{
	auto it = mGlobalValues.find(aID);
	if (it != mGlobalValues.end())
	{
		return it->second;
	}

	return BValue::Null;
}

EventKeyboard::KeyCode DataManager::getKey(const std::string& aID)
{
	EventKeyboard::KeyCode result = EventKeyboard::KeyCode::KEY_NONE;
	auto it = mKeys.find(aID);
	if (it != mKeys.end())
	{
		result = it->second;
	}

	return result;
}

EventKeyboard::KeyCode DataManager::convertStringToKeyCode(const std::string& aID)
{
	EventKeyboard::KeyCode result = EventKeyboard::KeyCode::KEY_NONE;
	
	if (aID == "A")
	{
		result = EventKeyboard::KeyCode::KEY_A;
	}
	else if (aID == "D")
	{
		result = EventKeyboard::KeyCode::KEY_D;
	}

	return result;
}