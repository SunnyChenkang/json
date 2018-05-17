#include "json_base.h"

void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , sint32& val )     { writer.Int( val );    }
void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , uint32& val )     { writer.Uint( val );   }
void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , sint64& val )     { writer.Int64( val );  }
void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , uint64& val )     { writer.Uint64( val ); }
void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , double& val )     { writer.Double( val ); }
void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , bool& val   )     { writer.Bool( val );   }
void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , std::string& val ){ writer.String(  val.data() ); }

void SS::CJsonBase::ToWriterValue( Writer<StringBuffer>& writer , char* val )
{
    if ( NULL == val ) return;
    writer.String( val , strlen( val ) );
}

void SS::CJsonBase::ToParseValue( const Value& value , sint32& t      ) { t = value.GetInt();   }
void SS::CJsonBase::ToParseValue( const Value& value , uint32& t      ) { t = value.GetUint();  }
void SS::CJsonBase::ToParseValue(const Value& value , sint64& t       ) { t = value.GetInt64(); }
void SS::CJsonBase::ToParseValue( const Value& value , uint64& t      ) { t = value.GetUint64();}
void SS::CJsonBase::ToParseValue( const Value& value , double& t      ) { t = value.GetDouble();}
void SS::CJsonBase::ToParseValue( const Value& value , std::string& t ) { t = value.GetString();}

void SS::CJsonBase::ToParseValue(const Value& value , char t[])
{
    int size = sizeof( t ) / sizeof( t[0] );
    const char* s = value.GetString();
    int len = strlen( s );
    strncpy( t , s , std::min( size , len ));
}



void SS::CJsonBase::ToWriterJson( Writer<StringBuffer>& writer )
{
    
}

void SS::CJsonBase::ToParseJson( const Value& val )
{

}

std::string SS::CJsonBase::ToJson( void )
{
    StringBuffer sb;
    Writer<StringBuffer> writer ( sb );
    this->ToWriterJson( writer );
    return sb.GetString();
}

void SS::CJsonBase::FromJson( CJsonBase* pJson , const std::string& json )
{
    Document document;
    document.Parse( json.data() );
    if ( !document.IsArray() )
    {
        const Value& JsonValues = document;
        pJson->ToParseJson( JsonValues );
        return;
    }
    // Êý×é±éÀú;
    GenericValue< UTF8< char > >::Array JsonArray( document.GetArray() );
    for ( int idx = 0; idx < JsonArray.Size(); idx++ )
    {
        const Value& JsonValues = JsonArray[idx];
        pJson->ToParseJson( JsonValues );
    }
}