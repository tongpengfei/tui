#ifndef __TUIMANAGER_H__
#define __TUIMANAGER_H__

#include "../rapidXml/rapidxml.hpp"  
#include "../rapidXml/rapidxml_utils.hpp"  
#include "../rapidXml/rapidxml_print.hpp"

#include "TuiBase.h"

using namespace rapidxml;
using namespace std;

class TuiManager : public CCObject{
public:
	static TuiManager* sharedManager();
	virtual bool init();

	void parseScene(CCNode* pScene ,const char* sceneName,const char* xmlPath);//��������
	void parseCell(CLayout* pCell, const char* cellName, const char* xmlPath);//��������

	void setUseSpriteFrame(bool b);//�Ƿ�ʹ��SpriteFrame

public:

	CWidgetWindow *createPanel(float tag, float x, float y, int w, int h, float rotation);
	CLayout *createLayout(float tag, float x, float y, float w, float h, float rotation);
	CScrollView *createScrollView(float tag, int direction, float x, float y, float w, float h, float rotation);
	CListView *createListView(float tag, const char* img, float x, float y, float w, float h, float rotation);
	CImageView *createImage(float tag, const char* file, float scaleX, float scaleY, float x, float y, float rotation);
	CImageViewScale9 *createImage9(float tag, const char* file, float x, float y, float w, float h, float up, float down, float left, float right, float rotation);
	CButton *createBtn(float tag, const char* normal, const char* select, const char* disable, float x, float y, float w, float h, float rotation);
	CToggleView *createToggleView(float tag, int exclusion, const char* normal, const char* select, const char* disable, float x, float y, float rotation);
	CSlider *createSlider(float tag, const char* bg, const char* progress, const char* thumb, int dir, float x, float y, float rotation);
	CProgressBar *createProgress(float tag, const char* bg, const char* progress, int dir, float x, float y, float rotation);
	CLabel *createLabel(float tag, const char* text, const char* font, int alignment, float fontSize, int r, int g, int b, float x, float y, float w, float h, int r2, int g2, int b2, float strokeSize, int shadowDistance, float shadowBlur, float rotation);
	CLabelAtlas *createLabelAtlas(float tag, const char* file, float x, float y, float w, float h, float rotation);
	CCArmature *createArmature(float tag, const char* name, const char* png, const char* plist, const char* xml, float x, float y, float rotation);
	CCSprite *createAnim(float tag, const char* name, const char* png, const char* plist, float x, float y, float rotation);
	CControlView *createControl(float tag, const char* baseboard, const char* joystick, float x, float y, float rotation);
	CCheckBox *createCheckBox(float tag, const char* normal1, const char* normal2, const char* select1, const char* select2, const char* disable1, const char* disable2, float x, float y, float rotation);
	ArmatureBtn *createArmatureBtn(float tag, const char* name, const char* png, const char* plist, const char* xml, float x, float y, float rotation);
	NumericStepper *createNumStep(float tag, const char* lnormal, const char* lselect, const char* ldisable, const char* rnormal, const char* rselect, const char* rdisable, const char* stepBg, float x, float y, float rotation);
	CCParticleSystemQuad *createParticle(float tag, const char* plist, float x, float y);
	CTableView *createTableView(float tag, const char* img, int dir, int num, int cellWidth, int cellHeight, float x, float y, float w, float h, float rotation);
	CPageView *createPageView(float tag, const char* img, int dir, int num, float x, float y, float w, float h, float rotation);
	CGridView *createGridView(float tag, const char* img, int column, int num, int cellWidth, int cellHeight, float x, float y, float w, float h, float rotation);
	CGridPageView *createGridPageView(float tag, const char* img, int dir, int column, int row, int num, int cellWidth, int cellHeight, float x, float y, float w, float h, float rotation);
	CCEditBox *createEditBox(float tag, const char* file, int inputMode, int inputFlag, float x, float y, float w, float h, float rotation);
	MovieView *createMovieView(float tag, const char* json, const char* plist, const char* png, float x, float y, float rotation);
	CircleMenu *createCircleMenu(float tag, float x, float y, float w, float h, float rotation);

protected:
	void loadXml(const string& pathXML);	//����xml
	void parseControl(CCNode* container,xml_node<char>*);//�������
private:
	static TuiManager* m_instance;

	map<string,string> m_DataMap;//xmlӳ������
	bool m_isUseSpriteFrame;
};
#endif

