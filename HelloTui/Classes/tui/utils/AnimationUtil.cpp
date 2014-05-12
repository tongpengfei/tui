#include "AnimationUtil.h"
//按名字返回动画帧
CCAnimation* AnimationUtil::createAnimWithName(const char* name,float delay,unsigned int iLoops){

	CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCArray *pArray = CCArray::create();

	CCSpriteFrame *pFrame = NULL;
	int index = 1;
	do 
	{
		pFrame = pCache->spriteFrameByName(CCString::createWithFormat("%s%d.png",name,index++)->getCString());
		if(pFrame == NULL){
			break;
		}
		pArray->addObject(pFrame);
	} while (true);

	CCAnimation *pAnim = CCAnimation::createWithSpriteFrames(pArray);
	pAnim->setLoops(iLoops);
	pAnim->setRestoreOriginalFrame(true);
	pAnim->setDelayPerUnit(delay);

	return pAnim;
}

//按名字和数目返回动画帧
CCAnimation* AnimationUtil::createAnimWithNameAndNum(const char* name,int iNum, float delay,unsigned int iLoops){

	CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCArray *pArray = CCArray::create();

	CCSpriteFrame *pFrame = NULL;
	int index = 1;
	for(int i=1; i<= iNum; i++){
		pFrame = pCache->spriteFrameByName(CCString::createWithFormat("%s%d.png",name,i)->getCString());
		if(pFrame == NULL){
			break;
		}
		pArray->addObject(pFrame);
	}
	
	CCAnimation *pAnim = CCAnimation::createWithSpriteFrames(pArray);
	pAnim->setRestoreOriginalFrame(true);
	pAnim->setLoops(iLoops);

	return pAnim;
}
