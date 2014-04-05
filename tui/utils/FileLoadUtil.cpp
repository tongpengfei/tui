#include "FileLoadUtil.h"
#include "StringUtil.h"

FileLoadUtil* FileLoadUtil::mFileLoadUtil = NULL;

FileLoadUtil* FileLoadUtil::sharedFileLoadUtil() {
    if(mFileLoadUtil == NULL) {
        mFileLoadUtil = new FileLoadUtil();
        if(mFileLoadUtil && mFileLoadUtil->init()) {
            mFileLoadUtil->autorelease();
        }
        else {
            CC_SAFE_DELETE(mFileLoadUtil);
            mFileLoadUtil = NULL;
        }
    }

    return mFileLoadUtil;
}

bool FileLoadUtil::init() {
    return true;
}

CCArray* FileLoadUtil::getDataLines( const char* sFilePath ) {
    CCArray* linesList = CCArray::create();

	/* 读取文本数据 */
    unsigned long pSize = 0;
    unsigned char* chDatas = CCFileUtils::sharedFileUtils()->getFileData(sFilePath, "r", &pSize);

    /* 将数据转换为字符串对象 */
    CCString* str = CCString::createWithData(chDatas, pSize);

	/* 使用split函数按行分隔字符串 */
    linesList = StringUtil::sharedStrUtil()->split(str->getCString(), "\n");
    
    return linesList;
}
