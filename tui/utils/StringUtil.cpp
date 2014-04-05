#include "StringUtil.h"

StringUtil* StringUtil::mStringUtil = NULL;

StringUtil* StringUtil::sharedStrUtil(){
    if(mStringUtil == NULL) {
        mStringUtil = new StringUtil();
        if(mStringUtil && mStringUtil->init()) {
            mStringUtil->autorelease();
        }
        else {
            CC_SAFE_DELETE(mStringUtil);
            mStringUtil = NULL;
        }
    }

    return mStringUtil;
}

bool StringUtil::init(){

    return true;
}

CCArray* StringUtil::split( const char* srcStr, const char* sSep ){
    CCArray* stringList = CCArray::create();

    int size = strlen(srcStr);

    /* 将数据转换为Cocos2d-x字符串对象 */
    CCString* str = CCString::create(srcStr);

    int startIndex = 0;
    int endIndex = 0;
    endIndex = str->m_sString.find(sSep);

    CCString* spliStr = NULL;

    /* 根据分隔符拆分字符串，并添加到列表中 */
    while(endIndex > 0) {
        spliStr = CCString::create("");

        /* 截取字符串 */
        spliStr->m_sString = str->m_sString.substr(startIndex, endIndex);

        /* 添加字符串到列表 */
        stringList->addObject(spliStr);

        /* 截取剩下的字符串 */
        str->m_sString = str->m_sString.substr(endIndex + 1, size);

		/* 查找下一个分隔符所在下标 */
        endIndex = str->m_sString.find(sSep);
    }

    /* 剩下的字符串也添加进列表 */
    if(str->m_sString.compare("") != 0) {
        stringList->addObject(CCString::create(str->m_sString));
    }

    return stringList;
}
