/*
    文件名：    StringUtil.h
    描　述：    字符串处理工具
    创建人：    笨木头 (博客：http://www.benmutou.com)

    创建日期：   2012.11.22
*/
#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "cocos2d.h"

using namespace cocos2d;

class StringUtil : public CCObject {
public:
    static StringUtil* sharedStrUtil();

    bool init();

    /** 用分隔符分割字符串，结果存放到一个列表中，列表中的对象为CCString */
    CCArray* split(const char* srcStr, const char* sSep);

private:
    static StringUtil* mStringUtil;
};

#endif