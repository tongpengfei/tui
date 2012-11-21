#ifndef MACRO_H
#define MACRO_H

/**
 * @file macro.h
 * @author tpf
 * @brief some usefull macro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sleep
#ifndef WIN32
#include <unistd.h>
#define msleep( x )  usleep( (x) * 1000 )
#else
//#include <WinSock2.h>
#include <windows.h>
#pragma comment( lib, "ws2_32.lib" )
#pragma warning(disable:4273) //dllexport dllimport
#pragma warning(disable:4275) //子类为dllexport父类不是dllexport
#pragma warning(disable:4996) //fopen fcanf
#pragma warning(disable:4251) //依赖项需要dll导出
#pragma warning(disable:4099) //找不到pdb调试符号文件
#define msleep( x ) Sleep( x )
#define snprintf _snprintf
#define strncasecmp strnicmp
#endif//WIN32

#ifndef max
#define max( a, b ) ( (a) > (b) ? (a) : (b) )
#endif//max
#ifndef min
#define min( a, b ) ( (a) < (b) ? (a) : (b) )
#endif//min

//console color
#ifndef WIN32
#define TXTCOLOR_DEFAULT    "\033[0;m"
#define TXTCOLOR_BLACK      "\033[0;30m"
#define TXTCOLOR_RED        "\033[0;31m"
#define TXTCOLOR_GREEN      "\033[0;32m"
#define TXTCOLOR_BROWN      "\033[0;33m"
#define TXTCOLOR_BLUE       "\033[0;34m"
#define TXTCOLOR_MAGENTA    "\033[0;35m"
#define TXTCOLOR_CYAN       "\033[0;36m"
#define TXTCOLOR_LIGHTGRAY  "\033[0;37m"
#else
#define TXTCOLOR_DEFAULT	0x0F
#define TXTCOLOR_BLACK		0x00
#define TXTCOLOR_RED		0x0C
#define TXTCOLOR_GREEN		0x0A
#define TXTCOLOR_BROWN		0x0D
#define TXTCOLOR_BLUE		0x0B
#define TXTCOLOR_MAGENTA	0x0D
#define TXTCOLOR_CYAN		0x0B
#define TXTCOLOR_LIGHTGRAY	0x0F
#endif//WIN32




#ifndef WIN32
#define PATH_SPLIT '/'
#else
#define PATH_SPLIT '\\'
#endif//WIN32


#define __FILENAME__ \
	( strrchr( __FILE__, '/' ) == NULL ? \
	( strrchr( __FILE__, '\\' ) == NULL ? __FILE__: strrchr( __FILE__, '\\' ) + 1 ) : \
	  strrchr( __FILE__, '/' ) + 1 )


#ifndef WIN32
#define __FUN__ __FUNCTION__
#else
#define __FUN__ \
	( ( strrchr( __FUNCTION__, ':' ) == NULL ? __FUNCTION__: strrchr( __FUNCTION__, ':' ) + 1 ) )
#endif//WIN32

#ifndef WIN32
#define tLogError( format, ... ) \
	printf( TXTCOLOR_RED"[ERROR] %s %s %d #"format"#"TXTCOLOR_DEFAULT"\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );

#define tLogWarning( format, ... ) \
	printf( TXTCOLOR_CYAN"[WARNING] %s %s %d #"format"#"TXTCOLOR_DEFAULT"\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );

#define tLogSystem( format, ... ) \
	printf( TXTCOLOR_GREEN"[SYSTEM] %s %s %d #"format"#"TXTCOLOR_DEFAULT"\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );
#else
#define tLogError( format, ... ) \
	do{	\
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_RED ); \
		printf( "[ERROR] %s %s %d #"format"\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_DEFAULT ); \
	}while(0);

#define tLogWarning( format, ... ) \
	do{	\
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_CYAN ); \
		printf( "[WARNING] %s %s %d #"format"\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_DEFAULT ); \
	}while(0);
#define tLogSystem( format, ... ) \
	do{	\
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_GREEN ); \
		printf( "[SYSTEM] %s %s %d #"format"\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_DEFAULT ); \
	}while(0);
#endif//WIN32


//log defines
#ifdef DEBUG
#define tLogDebug( format, ... ) \
	printf( "[DEBUG] %s %s %d ["format"]\n", \
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ ); 
#else
#define tLogDebug( format, ... ) ((void)0)
#endif //DEBUG

#define LOG_TRACE

#ifdef LOG_TRACE
#ifndef WIN32
#define tLogTrace( format, ... ) \
	printf( TXTCOLOR_BROWN"[TRACE] %s %s %d #"format"#"TXTCOLOR_DEFAULT"\n",\
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );
#else
#define tLogTrace( format, ... ) \
	do{	\
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_BROWN ); \
		printf( "[TRACE] %s %s %d #"format"\n",\
			__FILENAME__, __FUN__, __LINE__, ##__VA_ARGS__ );	\
		SetConsoleTextAttribute( hstdout, TXTCOLOR_DEFAULT ); \
	}while(0);
#endif//WIN32
#else
#define tLogTrace( format, ... ) ((void)0)
#endif //LOG_TRACE

#ifdef DEBUG
#define tAssert( exp ) if( !(exp) ) {tLogError( #exp );};
#define tAssertc( exp, cmd ) if(!(exp)) {tLogError( #exp ); cmd;}
#define tAssertm( exp, msg, ... ) if( !(exp) ) { tLogError( #exp msg, ##__VA_ARGS__ ); }
#define tAssertcm( exp, cmd, msg, ... ) if( !(exp) ) { tLogError( #exp msg, ##__VA_ARGS__ ); cmd; }
#else
#define tAssert( exp ) if( !(exp) ) {tLogError( #exp );}
#define tAssertc( exp, cmd ) if(!(exp)) {tLogError( #exp ); cmd;}
#define tAssertm( exp, msg, ... ) if( !(exp) ) {tLogError( #exp msg, ##__VA_ARGS__ );}
#define tAssertcm( exp, cmd, msg, ... ) if( !(exp) ) { tLogError( #exp msg, ##__VA_ARGS__ ); cmd; }
#endif //DEBUG

#if defined(MAKEDLL)
#define MDLLEXPORT __declspec(dllexport)
#elif defined(USEDLL)
#define MDLLEXPORT __declspec(dllimport)
#else
#define MDLLEXPORT
#endif

#endif //MACRO_H
