#ifndef XMLREADER_H
#define XMLREADER_H

#include <tinyxml.h>
#include <macro.h>

/**
 * @file xmlreader.h
 * @class XmlReader
 * @author tpf
 * @brief reader xml file
 *
 *  Example:
 *	XmlReader reader;
 *	tAssertc( reader.open( "xml.xml" ), return -1 );
 *  TiXmlElement* root = NULL;
 *  tAssertc( NULL != (root = reader.getRoot()), return false );
 *  TiXmlElement* pElement = NULL;
 *  pElement = reader.FirstChildElement( "testgroup" );
 *  if( !pElement )
 *      return 0;
 *  int a = 0;
 *  pElement = reader.FirstChildElement( "test" );
 *  for( ; pElement != NULL; pElement = reader.NextSiblingElement("test") )
 *  {
 *      tAssertc( reader.getInt( pElement, "a", a ), return -1 );
 *      TiXmlElement* pMapElement = NULL;
 *      pMapElement = reader.FirstChildElement( "map" );
 * 		for( ; pMapElement != NULL; pMapElement = reader.NextSiblingElement("map") )
 * 		{
 * 			int nmap = map_num[game_num];
 * 			char* mname = game_map[game_num][nmap];
 * 			tAssertc( reader.getString( pMapElement, "name", mname ), return -1 );
 * 			map_num[game_num]++;
 * 		}
 * 		reader.setCurNode( pElement ); // NOTICE!!!
 * 		game_num++;
 *	}
 * 
 *
 * @see Message
 * @see IModuleManager
 * @see IController
 */

class MDLLEXPORT XmlReader
{
public:
	XmlReader();
	~XmlReader();

	//! 打开一个xml文件
	bool open( const char* file );
	//! 检查是否有node节点
    bool hasNode(const char* node ) const;
	//! 获取根节点
	TiXmlElement* getRoot();
	//! 获取当前节点
	TiXmlElement* getCurNode();
	//! 设置当前节点
	void setCurNode( TiXmlElement* cur );
	//! 获取一个子节点
	TiXmlElement* FirstChildElement( const char* name );
	//! 获取一个兄弟节点
	TiXmlElement* NextSiblingElement( const char* name );

	//! 获取字符串型值
	bool getString( const TiXmlElement* e, const char* name, char* v, int size );
	//! 获取整型值
	bool getInt( const TiXmlElement* e, const char* name, int& v );
	//! 获取浮点型值
	bool getFloat( const TiXmlElement* e, const char* name, float& v );

private:
	TiXmlDocument xml_doc;
	TiXmlElement* cur_node;
};

#endif //XMLREADER_H
