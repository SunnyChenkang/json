#include "json_base.h"

// get string key cell;
template< typename T >
T* SS::CJsonBase::GetCell(std::string name)
{
    JSON_STRING_KEY_TABLE::iterator it = m_string_key_tables.find( name );
    if ( it == m_string_key_tables.end() ) return NULL;
    return dynamic_cast<T*>( it->second );
}



template< typename T >
void SS::CJsonArray<T>::ToWriterJson(Writer<StringBuffer> & writer)
{
    JsonWriterBegin( writer );
    for each ( T en in m_Array )
    {
        ToWriterValue( writer , en );
    }
    JsonWriterEnd();
}

template< typename T >
void SS::CJsonArray<T>::ToParseJson(const Value& value)
{
    for ( size_t idx = 0; idx < value.Size(); idx++ )
    {
        const Value& val = value[ idx ];
        T t;
        ToParseValue( val , t );
        m_Array.push_back( t );
    }
}

