#include "MovieView.h"

#include "../../extensions/CocoStudio/Json/rapidjson/document.h"
#include "Ease.h"
#include "../../extensions/CocoStudio/Json/DictionaryHelper.h"

using namespace rapidjson;
using namespace cocos2d::extension;

NS_CC_WIDGET_BEGIN

MovieView::MovieView()
{
}

MovieView* MovieView::create(const string& json)
{
	MovieView *ret = new MovieView();
	if (ret && ret->init(json))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

bool MovieView::init(const string& json)
{
	string jsonPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(json.c_str());
	unsigned long size;
	string fileContent = (const char*)CCFileUtils::sharedFileUtils()->getFileData( jsonPath.c_str() , "r", &size);
	
	Document doc;
	doc.Parse<0>(fileContent.c_str());

	m_frameRate = DICTOOL->getIntValue_json(doc, "frameRate");
	vector<vector<FrameInfo*>> vetLayers;
	for (unsigned int i = 0; i < doc["layers"].Size(); i++)
	{
		vector<FrameInfo*> vetLayer;
		rapidjson::Value& layerItem = doc["layers"][i];
		for (unsigned int j = 0; j <layerItem.Size(); j++)
		{
			rapidjson::Value& jsonItem = layerItem[j];
			FrameInfo *info = FrameInfo::create();
			info->x = DICTOOL->getIntValue_json(jsonItem, "x");
			info->y = (-1)*DICTOOL->getIntValue_json(jsonItem, "y");
			info->alpha = DICTOOL->getFloatValue_json(jsonItem, "alpha");
			info->index = DICTOOL->getIntValue_json(jsonItem, "index");
			info->rotate = DICTOOL->getFloatValue_json(jsonItem, "rotate");
			info->scaleY = DICTOOL->getFloatValue_json(jsonItem, "scaleY");
			info->scaleX = DICTOOL->getFloatValue_json(jsonItem, "scaleX");
			info->tween = DICTOOL->getIntValue_json(jsonItem, "tween");
			info->url = DICTOOL->getStringValue_json(jsonItem, "url");
			info->key = DICTOOL->getStringValue_json(jsonItem, "key");
			vetLayer.push_back(info);
		}
		vetLayers.push_back(vetLayer);
	}

	createFrames(vetLayers);
	return true;
}

void MovieView::play(bool isLoop /*= true*/)
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MovieView::doFrame),this);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
		schedule_selector(MovieView::doFrame), this, (float) 1 / m_frameRate, false);
	m_isLoop = isLoop;
}

void MovieView::stop()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MovieView::doFrame),this);
}

void MovieView::rePlay()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(MovieView::doFrame),this);
	this->m_currFrame = 0;
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
		schedule_selector(MovieView::doFrame), this, (float) 1 / m_frameRate, false);
	this->doFrame(0);
}

void MovieView::createFrames(vector<vector<FrameInfo*>>& layers)
{
	this->m_maxFrame = 0;
	this->m_currFrame = 0;
	this->m_layerFrames.clear();

	for (vector<FrameInfo*> layer : layers)
	{
		vector<FrameInfo*> frames;
		FrameInfo* from = NULL;
		for (FrameInfo* frame : layer)
		{
			for(FrameInfo* item : this->getFrames(from, frame)){
				frames.push_back(item);
			}
			from = frame;
			this->m_maxFrame = max(this->m_maxFrame, frame->index);
			if (frame->key.compare("") != 0){
				this->m_keys[frame->index] = frame->key;
			}
		}
		this->m_layerFrames.push_back(frames);
	}
	this->m_maxFrame = this->m_maxFrame + 1;
}

void MovieView::doFrame(float dt)
{
	this->playFrame(this->m_currFrame);
	auto it = this->m_keys.find(this->m_currFrame);
	if (it != this->m_keys.end()){
		function<void()> func = this->m_keyHandlers.at(it->second);
		if (func != NULL) {
			func();
		}
	}

	this->m_currFrame = this->m_currFrame + 1;
	if (this->m_currFrame >= this->m_maxFrame) {
		if (this->m_isLoop) {
			this->m_currFrame = 0;
		}
		else {
			this->unschedule(schedule_selector(MovieView::doFrame));
		}
	}
}

void MovieView::playFrame(int index)
{
	for (CCSprite *s : this->m_sprites){
		s->setVisible(false);
	}
	for (auto i = 0; i < this->m_layerFrames.size(); i++) {
		CCSprite *sprite = NULL;
		if (this->m_sprites.size() > i) {
			sprite = this->m_sprites.at(i);
		}
		else {
			sprite = CCSprite::create();
			this->addChild(sprite);
			this->m_sprites.push_back(sprite);
		}

		vector<FrameInfo*> frames = this->m_layerFrames.at(i);
		FrameInfo* frameInfo;
		if (frames.size() > index) {
			frameInfo = frames.at(index);
			if (frameInfo != 0 && frameInfo->url != "") 
			{
				CCSpriteFrame* sf = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameInfo->url.c_str());
				sprite->setDisplayFrame(sf);
				sprite->setVisible(true);
				sprite->setPosition(CCPoint(frameInfo->x, frameInfo->y));
				sprite->setScaleX(frameInfo->scaleX);
				sprite->setScaleY(frameInfo->scaleY);
				sprite->setOpacity((GLubyte)255 * frameInfo->alpha);
				sprite->setRotation(frameInfo->rotate);
			}
			else {
				sprite->setVisible(false);
			}
		}
		else {
			sprite->setVisible(false);
		}
	}
}

vector<FrameInfo*> MovieView::getFrames(FrameInfo* from, FrameInfo* to)
{
	int count = to->index;
	if (from != NULL) {
		count = count - from->index;
	}
	else {
		count = count + 1;
	}

	vector<FrameInfo*> arr;
	for (int i = 0; i < count; i++) 
	{
		if (i == count - 1) {
			arr.push_back(to);
		}
		else if (from) {
			if (from->tween == 0) {
				arr.push_back(from);
			}
			else {
				arr.push_back(this->getTweenFrame(i + 1, count, from, to, from->tween));
			}
		}
		else {
			arr.push_back(NULL);
		}
	}
	return arr;
}

FrameInfo* MovieView::getTweenFrame(int curr, int count, FrameInfo* from, FrameInfo* to, int tween)
{
	FrameInfo* temp = FrameInfo::create();
	temp->url = from->url;
	for (int key = 0; key < PropSize; key++){
		eProp prop = (eProp)key;
		float fromValue = from->getValueByName(prop);
		float toValue = to->getValueByName(prop);

		if (fromValue != toValue) {
			float ratio = Ease::none(curr, 0, 1, count);
			float v = fromValue + ratio * (toValue - fromValue);
			temp->setValueByName(prop, v);
		}
		else {
			temp->setValueByName(prop,from->getValueByName(prop));
		}
	}
	return temp;
}

void MovieView::setCallBack(map<string, function<void()>>& m)
{
	m_keyHandlers = m;
}

MovieView::~MovieView()
{
	this->unschedule(schedule_selector(MovieView::doFrame));
}


///////////////////////FrameInfo//////////////////////////////////////////
float FrameInfo::getValueByName(eProp prop)
{
	float ret = -1;
	switch (prop)
	{
	case kX:		ret = this->x;			break;
	case kY:		ret = this->y;			break;
	case kAlpha:	ret = this->alpha;		break;
	case kScaleX:	ret = this->scaleX;		break;
	case kScaleY:	ret = this->scaleY;		break;
	case kRotate:	ret = this->rotate;		break;
	}
	return ret;
}

void FrameInfo::setValueByName(eProp prop, float v)
{
	switch (prop)
	{
	case kX:		this->x = v;			break;
	case kY:		this->y = v;			break;
	case kAlpha:	this->alpha = v;		break;
	case kScaleX:	this->scaleX = v;		break;
	case kScaleY:	this->scaleY = v;		break;
	case kRotate:	this->rotate = v;		break;
	}
}


NS_CC_WIDGET_END