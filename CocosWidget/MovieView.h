#ifndef __MOVICE_VIEW__
#define __MOVICE_VIEW__

#include "cocos2d.h"
#include "WidgetMacros.h"
using namespace std;

NS_CC_WIDGET_BEGIN

enum eProp
{
	kX,
	kY,
	kAlpha,
	kIndex,
	kRotate,
	kScaleY,
	kScaleX,
	PropSize
};
//////////////////FrameInfo//////////////////////////////////////////////////
class FrameInfo :public CCObject
{
public:
	CREATE_FUNC(FrameInfo);
	virtual bool init(){ return true; };
	friend class MovieView;

	float getValueByName(eProp prop);
	void setValueByName(eProp prop, float v);
protected:
	int x;
	int y;
	float alpha;
	int index;
	float rotate;
	float scaleX;
	float scaleY;
	int tween;
	string url;
	string key;
};
////////////////MovieView///////////////////////////////////////////////
class MovieView : public CCNode
{
public:
	MovieView();
	~MovieView();
	static MovieView* create(const string& json);
	virtual bool init(const string& json);

	void play(bool isLoop = true);
	void stop();
	void rePlay();
	void setCallBack(map<string, function<void()>>& m);

	CC_SYNTHESIZE_READONLY(bool, m_isLoop, IsLoop);
	CC_SYNTHESIZE_READONLY(int, m_frameRate, FrameRate);
	CC_SYNTHESIZE_READONLY(int, m_maxFrame, MaxFrame);
	CC_SYNTHESIZE_READONLY(int, m_currFrame, CurrFrame);
	CC_SYNTHESIZE_READONLY(vector<vector<FrameInfo*>>, m_layerFrames, LayerFrames);
	CC_SYNTHESIZE_READONLY(vector<CCSprite*>, m_sprites, Sprites);
	
protected:
	void createFrames(vector<vector<FrameInfo*>>& layers);
	void doFrame(float dt);
	void playFrame(int index);
	vector<FrameInfo*> getFrames(FrameInfo* from, FrameInfo* to);
	FrameInfo* getTweenFrame(int param1, int count, FrameInfo* from, FrameInfo* to, int tween);
private:
	map<int, string> m_keys;
	map<string, function<void()>> m_keyHandlers;
};


NS_CC_WIDGET_END
#endif