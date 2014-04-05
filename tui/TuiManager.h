#ifndef __TUIMANAGER_H__
#define __TUIMANAGER_H__

#include "../../../tinyxml/tinyxml.h"
#include "tui/utils/AnimationUtil.h"
#include "tui/TuiBase.h"

class TuiManager : public CCObject{
public:
	static TuiManager* sharedManager();
	bool virtual init();

	void parseScene(TuiBase* pScene ,const char* sceneName);//解析场景

	void loadXml(const char*);
	void setUseSpriteFrame(bool b);//是否使用SpriteFrame

	CCSize getScreen();

public:

	CWidgetWindow *createPanel(float tag,float x,float y);
	RelativeLayout *createRelativeLayout(float tag,float x,float y,float w,float h);
	CScrollView *createScrollView(float tag,float x,float y,float w,float h);
	CListView *createListView(float tag,const char* img,float x,float y,float w,float h);
	CPageView *createPageView(float tag,float x,float y,float w,float h);
	CImageView *createImage(float tag,const char* file,float x,float y);
	CImageViewScale9 *createImage9(float tag,const char* file,float x,float y,float w,float h,float up,float down,float left, float right);
	CButton *createBtn(float tag,const char* normal,const char* select,const char* disable,float x,float y, float w,float h);
	CToggleView *createToggleView(float tag,int exclusion,const char* normal,const char* select,const char* disable,float x,float y);
	CSlider *createSlider(float tag, const char* bg,const char* progress,const char* thumb,float x,float y);
	CProgressBar *createProgress(float tag, const char* bg,const char* progress,float x,float y);
	CLabel *createLabel(float tag, const char* text ,float size,float x,float y,float w,float h);
	CLabelAtlas *createLabelAtlas(float tag,const char* file,float x,float y,float w,float h);
	CCArmature *createArmature(float tag,const char* name,const char* png,const char* plist,const char* xml,float x,float y);
	CCSprite *createAnim(float tag,const char* name,const char* png,const char* plist,float x,float y);
	CControlView *createControl(float tag,const char* baseboard,const char* joystick,float x,float y);
	CCheckBox *createCheckBox(float tag,const char* normal1,const char* normal2,const char* select1,const char* select2,const char* disable1,const char* disable2,float x,float y);
	ArmatureBtn *createArmatureBtn(float tag,const char* name,const char* png,const char* plist,const char* xml,float x,float y);
	NumericStepper *createNumStep(float tag,const char* lnormal,const char* lselect,const char* ldisable,const char* rnormal,const char* rselect,const char* rdisable,const char* stepBg,float x,float y);
	CCParticleSystemQuad *createParticle(float tag,const char* plist,float x,float y);
	CTableView *createTableView(float tag,float x,float y,float w,float h);
	CCEditBox *createEditBox(float tag,const char* file,float x,float y,float w,float h);

protected:
	void parseControl(CCNode* container,TiXmlElement* e,TiXmlNode* item);//解析组件
private:
	static TuiManager* m_instance;

	const char* m_xmlPath;
	const char* m_fileContent;//xml解析后的字符数组
	bool m_isUseSpriteFrame;
};
#endif

