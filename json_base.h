#ifndef SERVICE_SHARED_JSON_H_
#define SERVICE_SHARED_JSON_H_

#include "../common.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define JsonWriterBegin( writer )   { writer.StartObject();
#define JsonWriterEnd()               writer.EndObject(); }

#define JsonWriterToString( param ) writer.Key( #param ); writer.String( param.data() );
#define JsonWriterToChar( param )   writer.Key( #param ); writer.String( param , strlen(param) );
#define JsonWriterToInt( param )    writer.Key( #param ); writer.Int( param );
#define JsonWriterToUint( param )   writer.Key( #param ); writer.Uint( param );
#define JsonWriterToInt64( param )  writer.Key( #param ); writer.Int64( param );
#define JsonWriterToUint64( param ) writer.Key( #param ); writer.Uint64( param );
#define JsonWriterToDouble( param ) writer.Key( #param ); writer.Double( param );
#define JsonWriterToClass( param )  writer.Key( #param ); ((JsonBase*)(&param)->ToWriterJson(writer);

#define JsonParseBegin( val ) for( Value::ConstMemberIterator it = val.MemberBegin(); it != val.MemberEnd(); ++it ) {
#define JsonParseEnd() }

#define JsonParseToString(param)    if (strcmp( it->name.GetString() , #param ) == 0 ) param = it->value.GetString();
#define JsonParseToInt(param)       if (strcmp( it->name.GetString() , #param ) == 0 ) param = it->value.GetInt();
#define JsonParseToUint(param)      if (strcmp( it->name.GetString() , #param ) == 0 ) param = it->value.GetUint();
#define JsonParseToInt64(param)     if (strcmp( it->name.GetString() , #param ) == 0 ) param = it->value.GetInt64();
#define JsonParseToUint64(param)    if (strcmp( it->name.GetString() , #param ) == 0 ) param = it->value.GetUint64();
#define JsonParseToDouble(param)    if (strcmp( it->name.GetString() , #param ) == 0 ) param = it->value.GetDouble();
#define JsonParseToClass(param)     if (strcmp( it->name.GetString() , #param ) == 0 ) ((CJsonBase*)(&param))->ToParseJson(it->value);
#define JsonParseToChar(param)      if (strcmp( it->name.GetString() , #param ) == 0 ) \
{ \
    int size = array_size( param ); \
    const char *s = it->value.GetString(); \
    int len = strlen( s ); \
    strncpy( param , s , std::min(size , len)); \
} \

using namespace rapidjson;

SS_NAMESPACE_BEGIN_DECL

class CJsonBase
{
public:
    CJsonBase( void ) { }
    virtual ~CJsonBase( void ) { }

protected:

    // writer template;
    template< typename T >
    static void ToWriter( Writer<StringBuffer>& writer , T& val )
    {
        CJsonBase* pJson = &val;
        pJson->ToWriter( writer );
    }
    // writer int32;
    static void ToWriterValue( Writer<StringBuffer>& , sint32& );
    static void ToWriterValue( Writer<StringBuffer>& , uint32& );
    // writer int64;
    static void ToWriterValue( Writer<StringBuffer>& , sint64& );
    static void ToWriterValue( Writer<StringBuffer>& , uint64& );
    // writer double;
    static void ToWriterValue( Writer<StringBuffer>& , double& );
    // writer bool;
    static void ToWriterValue( Writer<StringBuffer>& , bool&   );
    // writer char*
    static void ToWriterValue( Writer<StringBuffer>& , char*   );
    // writer string;
    static void ToWriterValue( Writer<StringBuffer>& , std::string& );

    // parse template;
    template< typename T >
    static void ToParse( const Value& val , T& t )
    {
        CJsonBase* pJson = &t;
        pJson->ToParseJson( val );
    }
    // parse int32;
    static void ToParseValue( const Value& , sint32& );
    static void ToParseValue( const Value& , uint32& );
    // parse int64;
    static void ToParseValue( const Value& , sint64& );
    static void ToParseValue( const Value& , uint64& );
    // parse double;
    static void ToParseValue( const Value& , double& );
    // parse char[];
    static void ToParseValue( const Value& , char [] );
    // parse string;
    static void ToParseValue( const Value& , std::string& );

public:
    // to writer;
    virtual void ToWriterJson( Writer<StringBuffer>& );
    virtual void ToParseJson( const Value& );

    // to json;
    std::string ToJson( void );
    static void FromJson( CJsonBase* , const std::string& );
};


// JSON ARRAY;
template< typename T >
class CJsonArray : public CJsonBase
{
public:
    CJsonArray( void ) { };
   ~CJsonArray( void ) { };

    std::list< T > m_Array;

public:
    virtual void ToWriterJson( Writer<StringBuffer> & writer )
    {
        writer.StartArray();
        for each ( T en in m_Array )
        {
            ToWriterValue( writer , en );
        }
        writer.EndArray();
    }

    virtual void ToParseJson( const Value& value )
    {
        for ( size_t idx = 0; idx < value.Size(); idx++ )
        {
            const Value& val = value[ idx ];
            T t;
            ToParseValue( val , t );
            m_Array.push_back( t );
        }
    }
};

SS_NAMESPACE_END_DECL

#endif // SERVICE_SHARED_JSON_H_;