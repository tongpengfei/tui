#include <xmlreader.h>
#include <macro.h>


XmlReader::XmlReader()
{
	cur_node = NULL;
}

XmlReader::~XmlReader()
{
}

bool XmlReader::open( const char* file )
{
//	tAssertcm( xml_doc.LoadFile( file ), return false, "[XMLREADER] LoadFile[%s]", file );
	const char* fullpath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath( file );
	tAssertcm( fullpath, return false, "%s", file );
	
	unsigned long filesize = 0;
	unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData( fullpath, "rb", &filesize );
	tAssertcm( pBuffer, return false, "%s", file );
//	tAssertc( xml_doc.Parse( (const char*)pBuffer ), return false );
	xml_doc.Parse( (const char*)pBuffer );
	delete [] pBuffer;
	pBuffer = NULL;
	return true;
}

TiXmlElement* XmlReader::getRoot()
{
	cur_node = xml_doc.RootElement();
	return cur_node;
}

TiXmlElement* XmlReader::getCurNode()
{
	return cur_node;
}

void XmlReader::setCurNode( TiXmlElement* cur )
{
	tAssertc( NULL != cur, return );
	cur_node = cur;
}

TiXmlElement* XmlReader::FirstChildElement( const char* name )
{
	tAssertc( NULL != cur_node, return NULL );
	TiXmlElement* p = cur_node->FirstChildElement( name );
	if( p )
		cur_node = p;
	else
	{
		getRoot();
		if( !cur_node ) return NULL;
		p = cur_node->FirstChildElement( name );
		if( p )
			cur_node = p;
	}

	return p;
}


TiXmlElement* XmlReader::NextSiblingElement( const char* name )
{
	tAssertc( NULL != cur_node, return NULL );
	TiXmlElement* p = cur_node->NextSiblingElement( name );
	if( p )
		cur_node = p;
	return p;
}

bool XmlReader::getString( const TiXmlElement* e, const char* name, char* v, int size )
{
	tAssertc( NULL != cur_node, return false );
	tAssertc( NULL != e, return false );
	tAssertc( NULL != name, return false );
	tAssertc( NULL != v, return false );
	tAssertc( size > 0, return false );

//	const char* s = cur_node->Attribute( name );
	const char* s = e->Attribute( name );
	if( s )
	{
		strncpy( v, s, size );
		return true;
	}

	return false;
}

bool XmlReader::getInt( const TiXmlElement* e, const char* name, int& v )
{
	tAssertc( NULL != cur_node, return false );
	tAssertc( NULL != e, return false );
	tAssertc( NULL != name, return false );

	const char* s = e->Attribute( name );
	if( s )
	{
		v = atoi( s );
		return true;
	}
	return false;
}

bool XmlReader::getFloat( const TiXmlElement* e, const char* name, float& v )
{
	tAssertc( NULL != cur_node, return false );
	tAssertc( NULL != e, return false );
	tAssertc( NULL != name, return false );

	const char* s = e->Attribute( name );
	if( s )
	{
		v = (float)atof( s );
		return true;
	}
	return false;
}
