#include "TuiManager.h"
#include "tuiconsts.h"

TuiManager* TuiManager::m_instance = NULL;
TuiManager* TuiManager::sharedManager(){
	if(m_instance == NULL){
		m_instance = new TuiManager();
		if(m_instance && m_instance->init()){
			m_instance->retain();
		}else{
			CC_SAFE_DELETE(m_instance);
			m_instance = NULL;
		}
	}
	return m_instance;
}

bool TuiManager::init(){
	m_fileContent = "";

	return true;
}

void TuiManager::parseScene(TuiBase* pScene ,const char* sceneName){
	
	TiXmlDocument doc;
	doc.Parse(m_fileContent, 0, TIXML_ENCODING_UTF8);	
	//真机上不可以用 TiXmlElement doc(m_xmlPath);

	TiXmlElement* root = doc.RootElement(); 

	for( TiXmlNode*  item = root->FirstChild( kTuiNodeControl );  item;  item = item->NextSibling( kTuiNodeControl ) ) {
		
		TiXmlElement* e = item->ToElement();

		if( strcmp(e->Attribute("type"), kTuiContainerPanel) == 0){//panel

			if(strcmp(e->Attribute("name"),sceneName) != 0) continue;//只解析当前场景

			this->parseControl(pScene,e,item);
		}
	}
}
//解析组件//////////////////////////////////////////////////////////////////
void TuiManager::parseControl(CCNode* container,TiXmlElement* e,TiXmlNode* item){

	int tag = atof(e->Attribute("tag"));
	int x = atof(e->Attribute("x"));
	int y = atof(e->Attribute("y"));

	if(strcmp(e->Attribute("type"), kTuiContainerPanel) == 0){//panel
		CWidgetWindow* pPanel = createPanel(tag,x,y);
		container->addChild(pPanel);
		//递归
		for( TiXmlNode* iitem = item->FirstChild( kTuiNodeControl );iitem; iitem = iitem->NextSibling(kTuiNodeControl)){
			TiXmlElement* ee = iitem->ToElement();
			parseControl(pPanel,ee,iitem);
		}

	}else if(strcmp(e->Attribute("type"),kTuiControlImage) == 0){//image
		const char* file = e->Attribute("image");
		CImageView *pImg = createImage(tag,file,x,y);
		container->addChild(pImg);

	}else if(strcmp(e->Attribute("type"),kTuiControlButton) == 0){//button
		const char* normal = e->Attribute("normal");
		const char* select = e->Attribute("select");
		const char* disable = e->Attribute("disable");
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CButton *pBtn = createBtn(tag,normal,select,disable,x,y,w,h);
		container->addChild(pBtn);

	}else if(strcmp(e->Attribute("type"),kTuiControlToggleView) == 0){//toggleView
		const char* normal = e->Attribute("normal");
		const char* select = e->Attribute("select");
		const char* disable = e->Attribute("disable");
		float exclusion = atof(e->Attribute("exclusion"));
		CToggleView* toggle = createToggleView(tag,exclusion,normal,select,disable,x,y);
		container->addChild(toggle);

	}else if(strcmp(e->Attribute("type"),kTuiControlSlider) == 0){//slider
		const char* bg = e->Attribute("bg");
		const char* progress = e->Attribute("progress");
		const char* thumb = e->Attribute("thumb");
		CSlider *pSlider = createSlider(tag,bg,progress,thumb,x,y);
		container->addChild(pSlider);

	}else if(strcmp(e->Attribute("type"),kTuiControlProgress) == 0){//progress
		const char* bg = e->Attribute("bg");
		const char* progress = e->Attribute("progress");
		CProgressBar *pProgress = createProgress(tag,bg,progress,x,y);
		container->addChild(pProgress);

	}else if(strcmp(e->Attribute("type"),kTuiControlLabel) == 0){//label
		float size = atof(e->Attribute("textSize"));
		const char* text = e->Attribute("text");
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CLabel *pLabel = createLabel(tag,text,size,x,y,w,h);
		container->addChild(pLabel);

	}else if(strcmp(e->Attribute("type"),kTuiControlLabelAtlas) == 0){//labelAtlas
		const char* imgPath = e->Attribute("image");
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CLabelAtlas *pLabAtlas = createLabelAtlas(tag,imgPath,x,y,w,h);
		container->addChild(pLabAtlas);

	}else if(strcmp(e->Attribute("type"),kTuiControlArmature) == 0){//armature
		const char* xml = e->Attribute("xml");
		const char* png = e->Attribute("png");
		const char* plist = e->Attribute("plist");
		const char* name = e->Attribute("name");
		CCArmature *pArmature = createArmature(tag,name,png,plist,xml,x,y);
		container->addChild(pArmature);

	}else if(strcmp(e->Attribute("type"),kTuiControlAnim) == 0){//animation
		const char* png = e->Attribute("png");
		const char* plist = e->Attribute("plist");
		const char* name = e->Attribute("name");
		CCSprite *pSprite = createAnim(tag,name,png,plist,x,y);
		container->addChild(pSprite);

	}else if(strcmp(e->Attribute("type"),kTuiControlControl) == 0){//controlView
		const char* baseboard = e->Attribute("baseboard");
		const char* joystick = e->Attribute("joystick");
		CControlView *pControl = createControl(tag,baseboard,joystick,x,y);
		container->addChild(pControl);

	}else if(strcmp(e->Attribute("type"),kTuiContainerScroll) == 0){//scrollView
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CScrollView *pView = createScrollView(tag,x,y,w,h);
		container->addChild(pView);

	}else if(strcmp(e->Attribute("type"),kTuiControlListView) == 0){//listView
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		const char* img = e->Attribute("image");
		CListView* pList = createListView(tag,img,x,y,w,h);
		container->addChild(pList);

	}else if(strcmp(e->Attribute("type"),kTuiControlPageView) == 0){//pageView
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CPageView *pPageView = createPageView(tag,x,y,w,h);
		container->addChild(pPageView);

	}else if(strcmp(e->Attribute("type"),kTuiControlCheckBox) == 0){//checkBox
		const char* normal1 = e->Attribute("normal1");
		const char* normal2 = e->Attribute("normal2");
		const char* select1 = e->Attribute("select1");
		const char* select2 = e->Attribute("select2");
		const char* disable1 = e->Attribute("disable1");
		const char* disable2 = e->Attribute("disable2");
		CCheckBox *pCheckBox = createCheckBox(tag,normal1,normal2,select1,select2,disable1,disable2,x,y);
		container->addChild(pCheckBox);

	}else if(strcmp(e->Attribute("type"),kTuiControlArmatureBtn) == 0){//ArmatureBtn
		const char* png = e->Attribute("png");
		const char* plist = e->Attribute("plist");
		const char* name = e->Attribute("name");
		const char* xml = e->Attribute("xml");
		ArmatureBtn *pArmBtn = createArmatureBtn(tag,name,png,plist,xml,x,y);
		container->addChild(pArmBtn);

	}else if(strcmp(e->Attribute("type"),kTuicontrolNumbericStepper) == 0){//NumbericStepper
		const char* lnormal = e->Attribute("lnormal");
		const char* rnormal = e->Attribute("rnormal");
		const char* lselect = e->Attribute("lselect");
		const char* rselect = e->Attribute("rselect");
		const char* ldisable = e->Attribute("ldisable");
		const char* rdisable = e->Attribute("rdisable");
		const char* stepBg = e->Attribute("stepBg");
		NumericStepper *pNumStep = createNumStep(tag,lnormal,lselect,ldisable,rnormal,rselect,rdisable,stepBg,x,y);
		container->addChild(pNumStep);

	}
}

///创建组件 ////////////////////////////////////////////////////////////////
CWidgetWindow *TuiManager::createPanel(float tag,float x,float y){
	CWidgetWindow *pSprite = CWidgetWindow::create();
	pSprite->setPosition(ccp(x,y));
	pSprite->setTag(tag);
	pSprite->setZOrder(INT_MAX);
	return pSprite;
}

CScrollView *TuiManager::createScrollView(float tag,float x,float y,float w,float h){
	CScrollView *pView = CScrollView::create(CCSize(ccp(w,h)));
	pView->setPosition(ccp(x,-y));
	pView->setContainerSize(CCSize(w,h));
	pView->setDirection(eScrollViewDirectionBoth);
	pView->setTag(tag);
	return pView;
}

CListView *TuiManager::createListView(float tag,const char* img,float x,float y,float w,float h){
	CListView *pList = CListView::create(CCSize(w,h));
	pList->setBackgroundImage(img);
	pList->setDirection(eScrollViewDirectionVertical);
	pList->setPosition(ccp(x,-y));
	pList->setTag(tag);
	return pList;
}

CPageView *TuiManager::createPageView(float tag,float x,float y,float w,float h){
	CPageView *pPage = CPageView::create(CCSize(w,h));
	pPage->setSizeOfCell(CCSize(w,h));
	pPage->setPosition(ccp(x,-y));
	pPage->setTag(tag);
	return pPage;
}

CImageView *TuiManager::createImage(float tag, const char* file,float x,float y){
	CImageView *pSprite = CImageView::create(file);
	CCSize size = pSprite->getContentSize();
	pSprite->setPosition(ccp(x,-y));
	pSprite->setTag(tag);
	return pSprite;
}

CButton* TuiManager::createBtn(float tag, const char* normal,const char* select,const char* disable,float x,float y,float w, float h){
	CButton *pBtn = CButton::createWith9Sprite(CCSize(w,h),normal,select,disable);
	pBtn->setPosition(ccp(x,-y));
	pBtn->setTag(tag);
	return pBtn;
}

CToggleView* TuiManager::createToggleView(float tag,int exclusion,const char* normal,const char* select,const char* disable,float x,float y){
	CToggleView *toggle = CToggleView::create(normal,select,disable);
	toggle->setExclusion(exclusion);
	toggle->setPosition(x,-y);
	toggle->setTag(tag);
	return toggle;
}

CSlider* TuiManager::createSlider(float tag, const char* bg,const char* progress,const char* thumb,float x,float y){
	CSlider *pSlider = CSlider::create(thumb,progress);
	pSlider->setBackgroundImage(bg);
	pSlider->setPosition(ccp(x,-y));
	pSlider->setMinValue(0);
	pSlider->setMaxValue(100);
	pSlider->setValue(15);
	pSlider->setTag(tag);
	return pSlider;
}

CProgressBar* TuiManager::createProgress(float tag, const char* bg,const char* progress,float x,float y){
	CProgressBar *pProgress = CProgressBar::create(progress);
	pProgress->setBackgroundImage(bg);
	pProgress->setPosition(ccp(x,-y));
	pProgress->setMaxValue(100);
	pProgress->setMinValue(0);
	pProgress->setValue(15);
	pProgress->setTag(tag);
	return pProgress;
}

CLabel* TuiManager::createLabel(float tag, const char* text ,float size,float x,float y,float w,float h){
	CLabel *pLabel = CLabel::create(text,"",size);
	pLabel->setPosition(ccp(x+w/2,-(y + h/2)));
	pLabel->setTag(tag);
	return pLabel;
}

CLabelAtlas* TuiManager::createLabelAtlas(float tag,const char* imgPath,float x,float y,float w,float h){
	
	CLabelAtlas *pLabAtlas = CLabelAtlas::create("123456",imgPath,w/12,h,48);
	pLabAtlas->setPosition(ccp(x,-y));
	pLabAtlas->setTag(tag);
	return pLabAtlas;
}

CCArmature* TuiManager::createArmature(float tag,const char* name,const char* png,const char* plist,const char* xml,float x,float y){
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png,plist,xml);
	CCArmature *pArmature = CCArmature::create(name);
	pArmature->setPosition(ccp(x,-y));
	pArmature->setTag(tag);
	return pArmature;
}

CCSprite* TuiManager::createAnim(float tag,const char* name,const char* png,const char* plist,float x,float y){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist,png);
	CCAnimation* pAnim = AnimationUtil::createAnimWithName(name,0.05f,-1);
	CCSprite* pSprite = CCSprite::create();
	pSprite->runAction(CCAnimate::create(pAnim));
	pSprite->setPosition(ccp(x,-y));
	pSprite->setTag(tag);
	return pSprite;
}

CControlView* TuiManager::createControl(float tag,const char* baseboard,const char* joystick,float x,float y){
	CControlView* pView = CControlView::create(baseboard,joystick);
	pView->setPosition(ccp(x, -y));
	pView->setRadius(pView->getContentSize().width / 2);
	//pView->setAnchorPoint(CCPointZero);
	pView->setScale(1.5f);
	pView->setOpacity(200);
	pView->setTag(tag);
	return pView;
}

CCheckBox* TuiManager::createCheckBox(float tag,const char* normal1,const char* normal2,const char* select1,
	const char* select2,const char* disable1,const char* disable2,float x,float y){
	CCheckBox* pCheckBox = CCheckBox::create(); 
	pCheckBox->setNormalImage(normal1); 
	pCheckBox->setNormalPressImage(normal2); 
	pCheckBox->setCheckedImage(select1); 
	pCheckBox->setCheckedPressImage(select2); 
	pCheckBox->setDisabledNormalImage(disable1); 
	pCheckBox->setDisabledCheckedImage(disable2); 
	pCheckBox->setPosition(ccp(x,-y));
	pCheckBox->setTag(tag);
	return pCheckBox;
}

ArmatureBtn* TuiManager::createArmatureBtn(float tag,const char* name,const char* png,const char* plist,const char* xml,float x,float y){
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png,plist,xml);
	ArmatureBtn *pArmBtn = ArmatureBtn::create(name);
	CCSize size = pArmBtn->getContentSize();
	pArmBtn->setPosition(ccp(x - size.width/2,-y - size.height/2));
	pArmBtn->setTag(tag);
	return pArmBtn;
}

NumericStepper* TuiManager::createNumStep(float tag,const char* lnormal,const char* lselect,const char* ldisable,const char* rnormal,const char* rselect,const char* rdisable,const char* stepBg,float x,float y){
	NumericStepper* pNumStep = NumericStepper::create(lnormal,lselect,ldisable,rnormal,rselect,rdisable,stepBg);
	CCSize size = pNumStep->getContentSize();
	pNumStep->setPosition(ccp(x - size.width/2,-y - size.height/2));
	pNumStep->setTag(tag);
	return pNumStep;
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void TuiManager::setPathXml(const char* xml){
	m_xmlPath = xml;

	if(strlen(m_fileContent) == 0){//简单地缓存下xml
		unsigned long size;
		m_fileContent = (const char*)CCFileUtils::sharedFileUtils()->getFileData( m_xmlPath , "r", &size);
	}
}

CCSize TuiManager::getScreen(){
	TiXmlDocument doc;
	doc.Parse(m_fileContent, 0, TIXML_ENCODING_UTF8);
	TiXmlElement* root = doc.RootElement(); 
	float screenX = atof(root->FirstChildElement(kTuiNodeScheme)->Attribute("screen_width"));
	float screenY = atof(root->FirstChildElement(kTuiNodeScheme)->Attribute("screen_height"));
	return CCSize(screenX,screenY);
}
