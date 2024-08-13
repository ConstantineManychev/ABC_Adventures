#include "JsonHelper.h"

_USEC

bool JsonHelper::saveBValueToJsonValue( rapidjson::Value& aJSONValue, const BValue& aBValue, rapidjson::Document::AllocatorType& aAllocator )
{
    bool result = false;
    auto valueType = aBValue.getType();
    
    if ( valueType != BValue::Type::NONE )
    {
        switch( valueType )
        {
            case BValue::Type::BYTE:
            case BValue::Type::INTEGER:
            {
                aJSONValue = rapidjson::Value( rapidjson::kNumberType );
                aJSONValue.SetInt( aBValue.getInt() );
                
                result = true;
            }
                break;
            case BValue::Type::DOUBLE:
            case BValue::Type::FLOAT:
            {
                aJSONValue = rapidjson::Value( rapidjson::kNumberType );
                aJSONValue.SetDouble( aBValue.getDouble() );
                
                result = true;
            }
                break;
                
            case BValue::Type::BOOLEAN:
            {
                aJSONValue = rapidjson::Value( aBValue.getBool() ? rapidjson::kTrueType : rapidjson::kFalseType );
                
                result = true;
            }
                break;
                
            case BValue::Type::STRING:
            {
                aJSONValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = aBValue.getString();
                aJSONValue.SetString(saveStr.c_str(), (rapidjson::SizeType)saveStr.size(), aAllocator);
                
                result = true;
            }
                break;
			case BValue::Type::VEC2:
			{
				aJSONValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = aBValue.getString();
				saveStr = "?" + saveStr;
				aJSONValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), aAllocator);

				result = true;
			}
			break;
			case BValue::Type::SIZE:
			{
				aJSONValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = aBValue.getString();
				saveStr = "!" + saveStr;
				aJSONValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), aAllocator);

				result = true;
			}
			break;
			case BValue::Type::COLOR3B:
			{
				aJSONValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = aBValue.getString();
				saveStr = "<" + saveStr;
				aJSONValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), aAllocator);

				result = true;
			}
			break;
			case BValue::Type::COLOR4F:
			{
				aJSONValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = aBValue.getString();
				saveStr = ">" + saveStr;
				aJSONValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), aAllocator);

				result = true;
			}
			break;
            case BValue::Type::VECTOR:
            {
                aJSONValue = rapidjson::Value( rapidjson::kArrayType );
                
                const BValueVector& valueVector = aBValue.getValueVector();
                
                for ( unsigned i = 0; i < valueVector.size(); ++i)
                {
                    rapidjson::Value val;
                    if ( saveBValueToJsonValue( val, valueVector[ i ], aAllocator) )
                    {
                        aJSONValue.PushBack( val, aAllocator);
                    }
                }
                
                result = true;
            }
                break;
                
            case BValue::Type::MAP:
            {
                aJSONValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueMap& valueMap = aBValue.getValueMap();
                
                for ( auto mapIt : valueMap )
                {
                    std::string mapKey = mapIt.first;
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, aAllocator) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), aAllocator);
                        
                        aJSONValue.AddMember( jsonMapKey, jsonMapValue, aAllocator);
                    }
                    
                }

				result = true;
            }
                break;
            case BValue::Type::UN_MAP:
            {
                aJSONValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueUnMap& valueMap = aBValue.getValueUnMap();
                
                for ( auto mapIt : valueMap )
                {
                    std::string mapKey = mapIt.first;
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, aAllocator) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), aAllocator);
                        
                        aJSONValue.AddMember( jsonMapKey, jsonMapValue, aAllocator);
                    }
                    
                }
				result = true;
            }
                break;
            case BValue::Type::INT_MAP:
            {
                aJSONValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueIntMap& valueMap = aBValue.getValueIntMap();
                
                for ( auto mapIt : valueMap )
                {
                    BValue bMapKey( mapIt.first );
                    std::string mapKey = bMapKey.getString();
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, aAllocator ) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), aAllocator);
                        
                        aJSONValue.AddMember( jsonMapKey, jsonMapValue, aAllocator);
                    }
                    
                }
				result = true;
            }
                break;
            case BValue::Type::INT_UN_MAP:
            {
                aJSONValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueIntUnMap& valueMap = aBValue.getValueIntUnMap();
                
                for ( auto mapIt : valueMap )
                {
                    BValue bMapKey( mapIt.first );
                    std::string mapKey = bMapKey.getString();
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, aAllocator) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), aAllocator);
                        
                        aJSONValue.AddMember( jsonMapKey, jsonMapValue, aAllocator);
                    }
                    
                }
				result = true;
            }
                break;
        };

    }
    
    return result;
}

void JsonHelper::parseBValueFromJsonValue( const rapidjson::Value& aJSONValue, BValue& aBValue)
{
    if (aJSONValue.IsObject() )
    {
        //parse map
		aBValue.clearWithType( BValue::Type::MAP );
        BValueMap& valueMap = aBValue.getValueMap();
        
        for ( auto it = aJSONValue.MemberBegin(); it != aJSONValue.MemberEnd(); ++it )
        {
            BValue& fillValue = valueMap[ (*it).name.GetString() ];
            parseBValueFromJsonValue( (*it).value, fillValue );
        }
        
    }
    else if (aJSONValue.IsArray() )
    {
        //parse array
		aBValue.clearWithType( BValue::Type::VECTOR );
        BValueVector& valueVec = aBValue.getValueVector();
        
        for ( int i = 0; i != aJSONValue.Size() ; ++i )
        {
            BValue fillValue;
            parseBValueFromJsonValue(aJSONValue[ i ], fillValue );
            valueVec.push_back( fillValue );
        }
    }
    else if (aJSONValue.IsFloat() || aJSONValue.IsDouble() )
    {
		aBValue = aJSONValue.GetDouble();
    }
    else if (aJSONValue.IsBool() )
    {
		aBValue = aJSONValue.GetBool();
    }
    else if (aJSONValue.IsString() )
    {
		std::string jsonStr = aJSONValue.GetString();
		aBValue = jsonStr;

		if ( !jsonStr.empty() )
		{
			const char checkSym = jsonStr[0];

			switch ( checkSym )
			{

				case '?' :
				{
					BValue tmpVal( jsonStr.substr( 1, jsonStr.size() - 1 ) );
					aBValue = tmpVal.getVec2();
				}
				break;

				case '!':
				{
					BValue tmpVal( jsonStr.substr( 1, jsonStr.size() - 1) );
					aBValue = tmpVal.getSize();
				}
				break;

				case '<':
				{
					BValue tmpVal( jsonStr.substr( 1, jsonStr.size() - 1) );
					aBValue = tmpVal.getColor3B();
				}
				break;

				case '>':
				{
					BValue tmpVal( jsonStr.substr(1, jsonStr.size() - 1) );
					aBValue = tmpVal.getColor4F();
				}
				break;

				default:
					break;
			}
		}
    }
    else if (aJSONValue.IsNumber() )
    {
		aBValue = aJSONValue.GetInt();
    }
    
}

void JsonHelper::parseBValueFromJsonConfig(const std::string& aConfigPath, BValue& aBValue)
{
	std::string content = FileUtils::getInstance()->getStringFromFile(aConfigPath);

	bool isLoadingCorrect = false;

	if (!content.empty())
	{
		rapidjson::Document document;
		document.Parse<0>(content.c_str());
		if (!document.HasParseError())
		{
			parseBValueFromJsonValue(document, aBValue);
		}
	}
}