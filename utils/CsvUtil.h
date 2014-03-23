/*
    文件名：    CsvUtil.h
    描　述：    Csv文件读取工具
    创建人：    笨木头 (博客：http://www.benmutou.com)

    创建日期：   2012.11.22
*/
#ifndef __CSV_H__
#define __CSV_H__

#include "cocos2d.h"

using namespace cocos2d;

class CsvUtil : public CCObject {
public:
    /* 获取工具对象 */
    static CsvUtil* sharedCsvUtil();

    bool init();

    /* 加载配置文件 */
    void loadFile(const char* sPath);

    /* 释放配置文件 */
    void releaseFile(const char* sPath);

    /* 获取某行某列的值 */
    const char* get(int iRow, int iCol, const char* csvFilePath);

	/* 获取某行某列的值，并且转换为整型 */
	const int getInt(int iRow, int iCol, const char* csvFilePath);

	/* 获取某行某列的值，并且转换为浮点型 */
	const float getFloat(int iRow, int iCol, const char* csvFilePath);

    /* 获取配置文件数据的行和列数量 */
    const CCSize getFileRowColNum(const char* csvFilePath);

    /* 根据某个列的值，查找该值所在的行 */
    const int findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath);
private:
    /* 工具对象 */
    static CsvUtil* mCsvUtil;

    /* 
        存放mCsvStrList-filePath的字典。
        这样写注释比较好记忆：CCDictionary<CCArray<CCArray>, const char*>
    */
    CCDictionary* mCsvDict;
};

#endif