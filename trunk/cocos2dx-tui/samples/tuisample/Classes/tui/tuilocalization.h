#ifndef TUILOCALIZATION_H
#define TUILOCALIZATION_H

/**
 @class TuiLocalization
 @brief Tui is support localization file path, the 
		default localization is "", if you want to show a 
		simplified chinese image, you need to add a prefix "cn_" to
		the image file, for example: default background.png,
		simplified chinese: cn_background.png. 
		NOTE: before support localization, you should set the current
		tui localization by 
		TuiLocalization::I()->setLocalization( localizationcode );
		for example: I want to set localization to simplified chinese,
		TuiLocalization::I()->setLocalization( "zh-Hans" );
		you can use IOS API [NSLocale preferredLanguages] to get the 
		current localization code and set TuiLocalization localization.
 */
class TuiLocalization
{
	TuiLocalization();
public:
	static TuiLocalization* I();
	void setLocalization( const char* v );

	/** localization prefix, default is en*/
	const char* prefix() { return str_prefix; }

private:
	static TuiLocalization* s_instance;
	char str_prefix[32];
};

#endif//TUILOCALIZATION_H
