#include "JsonHelper.h"

_USEC

/*
enum class Type
{
    /// no value is wrapped, an empty BValue
    NONE = 0,
    /// wrap byte
    BYTE,
    /// wrap integer
    INTEGER,
    /// wrap float
    FLOAT,
    /// wrap double
    DOUBLE,
    /// wrap bool
    BOOLEAN,
    /// wrap string
    STRING,
    /// wrap vector
    VECTOR,
    /// wrap BValueMap
    MAP,
    /// wrap BValueUnMap
    UN_MAP,
    /// wrap BValueIntMap
    INT_MAP,
    /// wrap BValueIntUnMap
    INT_UN_MAP
};
*/
bool JsonHelper::saveBValueToJsonValue( rapidjson::Value& jsonValue, const BValue& bValue, rapidjson::Document::AllocatorType& allocator )
{
    bool result = false;
    auto valueType = bValue.getType();
    
    if ( valueType != BValue::Type::NONE )
    {
        switch( valueType )
        {
            case BValue::Type::BYTE:
            case BValue::Type::INTEGER:
            {
                jsonValue = rapidjson::Value( rapidjson::kNumberType );
                jsonValue.SetInt( bValue.getInt() );
                
                result = true;
            }
                break;
            case BValue::Type::DOUBLE:
            case BValue::Type::FLOAT:
            {
                jsonValue = rapidjson::Value( rapidjson::kNumberType );
                jsonValue.SetDouble( bValue.getDouble() );
                
                result = true;
            }
                break;
                
            case BValue::Type::BOOLEAN:
            {
                jsonValue = rapidjson::Value( bValue.getBool() ? rapidjson::kTrueType : rapidjson::kFalseType );
                
                result = true;
            }
                break;
                
            case BValue::Type::STRING:
            {
                jsonValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = bValue.getString();
                jsonValue.SetString(saveStr.c_str(), (rapidjson::SizeType)saveStr.size(), allocator );
                
                result = true;
            }
                break;
			case BValue::Type::VEC2:
			{
				jsonValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = bValue.getString();
				saveStr = "?" + saveStr;
				jsonValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), allocator );

				result = true;
			}
			break;
			case BValue::Type::SIZE:
			{
				jsonValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = bValue.getString();
				saveStr = "!" + saveStr;
				jsonValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), allocator );

				result = true;
			}
			break;
			case BValue::Type::COLOR3B:
			{
				jsonValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = bValue.getString();
				saveStr = "<" + saveStr;
				jsonValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), allocator );

				result = true;
			}
			break;
			case BValue::Type::COLOR4F:
			{
				jsonValue = rapidjson::Value( rapidjson::kStringType );

				std::string saveStr = bValue.getString();
				saveStr = ">" + saveStr;
				jsonValue.SetString( saveStr.c_str(), ( rapidjson::SizeType )saveStr.size(), allocator );

				result = true;
			}
			break;
            case BValue::Type::VECTOR:
            {
                jsonValue = rapidjson::Value( rapidjson::kArrayType );
                
                const BValueVector& valueVector = bValue.getValueVector();
                
                for ( unsigned i = 0; i < valueVector.size(); ++i)
                {
                    rapidjson::Value val;
                    if ( saveBValueToJsonValue( val, valueVector[ i ], allocator ) )
                    {
                        jsonValue.PushBack( val, allocator );
                    }
                }
                
                result = true;
            }
                break;
                
            case BValue::Type::MAP:
            {
                jsonValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueMap& valueMap = bValue.getValueMap();
                
                for ( auto mapIt : valueMap )
                {
                    std::string mapKey = mapIt.first;
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, allocator ) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), allocator );
                        
                        jsonValue.AddMember( jsonMapKey, jsonMapValue, allocator );
                    }
                    
                }

				result = true;
            }
                break;
            case BValue::Type::UN_MAP:
            {
                jsonValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueUnMap& valueMap = bValue.getValueUnMap();
                
                for ( auto mapIt : valueMap )
                {
                    std::string mapKey = mapIt.first;
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, allocator ) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), allocator );
                        
                        jsonValue.AddMember( jsonMapKey, jsonMapValue, allocator );
                    }
                    
                }
				result = true;
            }
                break;
            case BValue::Type::INT_MAP:
            {
                jsonValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueIntMap& valueMap = bValue.getValueIntMap();
                
                for ( auto mapIt : valueMap )
                {
                    BValue bMapKey( mapIt.first );
                    std::string mapKey = bMapKey.getString();
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, allocator ) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), allocator );
                        
                        jsonValue.AddMember( jsonMapKey, jsonMapValue, allocator );
                    }
                    
                }
				result = true;
            }
                break;
            case BValue::Type::INT_UN_MAP:
            {
                jsonValue = rapidjson::Value( rapidjson::kObjectType );
                
                const BValueIntUnMap& valueMap = bValue.getValueIntUnMap();
                
                for ( auto mapIt : valueMap )
                {
                    BValue bMapKey( mapIt.first );
                    std::string mapKey = bMapKey.getString();
                    
                    rapidjson::Value jsonMapValue;
                    if ( saveBValueToJsonValue( jsonMapValue, mapIt.second, allocator ) )
                    {
                        rapidjson::Value jsonMapKey( rapidjson::kStringType );
                        jsonMapKey.SetString( mapKey.c_str(), (rapidjson::SizeType)mapKey.size(), allocator );
                        
                        jsonValue.AddMember( jsonMapKey, jsonMapValue, allocator );
                    }
                    
                }
				result = true;
            }
                break;
        };

    }
    
    return result;
}
void JsonHelper::parseBValueFromJsonValue( const rapidjson::Value& jsonValue, BValue& bValue )
{
    if ( jsonValue.IsObject() )
    {
        //parse map
        bValue.clearWithType( BValue::Type::MAP );
        BValueMap& valueMap = bValue.getValueMap();
        
        for ( auto it = jsonValue.MemberBegin(); it != jsonValue.MemberEnd(); ++it )
        {
            BValue& fillValue = valueMap[ (*it).name.GetString() ];
            parseBValueFromJsonValue( (*it).value, fillValue );
        }
        
    }
    else if ( jsonValue.IsArray() )
    {
        //parse array
        bValue.clearWithType( BValue::Type::VECTOR );
        BValueVector& valueVec = bValue.getValueVector();
        
        for ( int i = 0; i != jsonValue.Size() ; ++i )
        {
            BValue fillValue;
            parseBValueFromJsonValue( jsonValue[ i ], fillValue );
            valueVec.push_back( fillValue );
        }
    }
    else if ( jsonValue.IsFloat() || jsonValue.IsDouble() )
    {
        bValue = jsonValue.GetDouble();
    }
    else if ( jsonValue.IsBool() )
    {
        bValue = jsonValue.GetBool();
    }
    else if ( jsonValue.IsString() )
    {
		std::string jsonStr = jsonValue.GetString();
		bValue = jsonStr;

		if ( !jsonStr.empty() )
		{
			const char checkSym = jsonStr[0];

			switch ( checkSym )
			{

				case '?' :
				{
					BValue tmpVal( jsonStr.substr( 1, jsonStr.size() - 1 ) );
					bValue = tmpVal.getVec2();
				}
				break;

				case '!':
				{
					BValue tmpVal( jsonStr.substr( 1, jsonStr.size() - 1) );
					bValue = tmpVal.getSize();
				}
				break;

				case '<':
				{
					BValue tmpVal( jsonStr.substr( 1, jsonStr.size() - 1) );
					bValue = tmpVal.getColor3B();
				}
				break;

				case '>':
				{
					BValue tmpVal( jsonStr.substr(1, jsonStr.size() - 1) );
					bValue = tmpVal.getColor4F();
				}
				break;

				default:
					break;
			}
		}
    }
    else if ( jsonValue.IsNumber() )
    {
        bValue = jsonValue.GetInt();
    }
    
}
