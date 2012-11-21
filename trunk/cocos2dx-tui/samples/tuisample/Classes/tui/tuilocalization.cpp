#include <tuilocalization.h>
#include <macro.h>

struct TuiLocalizationTable{
	char localization[32];
	char prefix[32];
};

// supported localization
TuiLocalizationTable s_localization_code[] = {
	{ "default", "" },     //default, do not need prefix
	{ "zh-Hans", "cn_" },  //simplified chinese
	{ "zh-Hant", "cnt_" }, //traditional chinese
};

TuiLocalization* TuiLocalization::s_instance = NULL;
TuiLocalization* TuiLocalization::I()
{
	if( NULL == s_instance ){
		s_instance = new TuiLocalization();
	}
	return s_instance;
}

TuiLocalization::TuiLocalization()
{
	memset( str_prefix, 0x00, sizeof(str_prefix) );
}

void TuiLocalization::setLocalization( const char* v )
{
	tAssertc( v, return );
	size_t nsize = sizeof(s_localization_code)/sizeof(s_localization_code[0]);
	for( size_t i=0; i<nsize; ++i ){
		TuiLocalizationTable& code = s_localization_code[i];
		if( strncmp( code.localization, v, sizeof(code.localization) ) == 0 ){
			strncpy( str_prefix, code.prefix, sizeof(str_prefix) );
			return;
		}
	}
	tLogError( "can not find localization: %s", v );
}
