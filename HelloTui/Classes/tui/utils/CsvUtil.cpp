#include "CsvUtil.h"
#include "FileLoadUtil.h"
#include "StringUtil.h"

CsvUtil* CsvUtil::mCsvUtil = NULL;

CsvUtil* CsvUtil::sharedCsvUtil(){
    if(mCsvUtil == NULL) {
        mCsvUtil = new CsvUtil();
        if(mCsvUtil && mCsvUtil->init()) {
            mCsvUtil->autorelease();
        }
        else {
            CC_SAFE_DELETE(mCsvUtil);
            mCsvUtil = NULL;
        }
    }

    return mCsvUtil;
}

bool CsvUtil::init(){

    /* 初始化成员变量 */
    mCsvDict = CCDictionary::create();
    mCsvDict->retain();

    
    return true;
}

void CsvUtil::loadFile( const char* sPath ){

    /* 
        存放一个csv文件的字符串组的列表，每个子对象为一行字符串组。
        这样写可能比较好记忆：CCArray<CCArray>
    */
    CCArray* csvStrList = CCArray::create();

    /* 读取每一行的数据，保存到字符串数组，添加到列表里 */
    /* 读取数据，按行保存到列表中 */
    CCArray* linesList = FileLoadUtil::sharedFileLoadUtil()->getDataLines(sPath);

    /* 把每一行的字符串拆分出来（按逗号分隔） */
    CCObject* obj;
    CCString* tString = NULL;
    CCARRAY_FOREACH(linesList, obj) {
        /* 取出一行字符串 */
        tString = (CCString *) obj;

        if(tString) {
            /* 
                将一行的字符串按逗号分隔，然后存放到列表中。
                换句话说，csvStrList将成为一个二维表格，记录了配置文件行和列的字符串
            */
            CCArray* tArr = StringUtil::sharedStrUtil()->split(tString->getCString(), ",");
            csvStrList->addObject(tArr);
        }
    }

    /* 添加列表到字典里 */
    mCsvDict->setObject(csvStrList, sPath);
}

void CsvUtil::releaseFile( const char* sPath ){
	mCsvDict->removeObjectForKey(sPath);
}

const char* CsvUtil::get( int iRow, int iCol, const char* csvFilePath ) {
    /* 取出配置文件的二维表格 */
    CCObject* csvObj = mCsvDict->objectForKey(csvFilePath);

    /* 如果配置文件的数据不存在，则加载配置文件 */
    if(csvObj == NULL) {
        loadFile(csvFilePath);
    }
    CCArray* csvStrList = (CCArray *) mCsvDict->objectForKey(csvFilePath);

    CCSize size = getFileRowColNum(csvFilePath);

    /* 数据行数 */
    int iRowNum = size.width;
    int iColNum = size.height;

    /* 下标越界 */
    if(iRow >= iRowNum || iCol >= iColNum) {
        return "";
    }

    /* 获取第iRow行数据 */
    CCObject* rowObj = csvStrList->objectAtIndex(iRow);

    if(rowObj != NULL) {
        CCArray* rowArr = (CCArray *) rowObj;

        /* 获取第iCol列数据 */
        CCObject* colObj = rowArr->objectAtIndex(iCol);

        if(colObj != NULL) {
            CCString* colStr = (CCString *) colObj;
            return colStr->getCString();
        }
    }

    return "";
}

const CCSize CsvUtil::getFileRowColNum( const char* csvFilePath )
{

    /* 取出配置文件的二维表格 */
    CCObject* csvObj = mCsvDict->objectForKey(csvFilePath);

    /* 如果配置文件的数据不存在，则加载配置文件 */
    if(csvObj == NULL) {
        loadFile(csvFilePath);
    }

    CCArray* csvStrList = (CCArray *) mCsvDict->objectForKey(csvFilePath);

    /* 数据行数 */
    int iRowNum = csvStrList->count();
    int iColNum = 0;
    if(iRowNum > 0) {
        /* 获取第0行数据 */
        CCObject* rowObj = csvStrList->objectAtIndex(0);

        if(rowObj != NULL) {
            CCArray* rowArr = (CCArray *) rowObj;

            /* 数据列数 */
            iColNum = rowArr->count();
        }
    }
    CCSize size = CCSize(iRowNum, iColNum);
    return size;
}

const int CsvUtil::getInt( int iRow, int iCol, const char* csvFilePath ) {
	const char* chData = get(iRow, iCol, csvFilePath);

	return atoi(chData);
}

const float CsvUtil::getFloat( int iRow, int iCol, const char* csvFilePath ) {
	const char* chData = get(iRow, iCol, csvFilePath);

	return atof(chData);
}

const int CsvUtil::findValueInWithLine( const char* chValue, int iValueCol, const char* csvFilePath ) {
    CCSize csvSize = getFileRowColNum(csvFilePath);

    int iLine = -1;
    for(int i = 0; i < csvSize.width; i++) {
        const char* ID = get(i, iValueCol, csvFilePath);
        CCString* IDStr = CCString::createWithFormat(ID);
        if(IDStr->m_sString.compare(chValue) == 0) {
            iLine = i;
            break;
        }
    }

    return iLine;
}