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
	m_isUseSpriteFrame = false;
	return true;
}

void TuiManager::parseScene(TuiBase* pScene ,const char* sceneName){
	//判断是否用SpriteFrame创建控件
	m_isUseSpriteFrame = pScene->getAutoRemoveUnusedSpriteFrame();

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
////////////////////解析组件/////////////////////////////////////////////
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

	}else if(strcmp(e->Attribute("type"),kTuiContainerRelativeLayout) == 0){//relativeLayout
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		RelativeLayout *relLayer = createRelativeLayout(tag,x,y,w,h);
		container->addChild(relLayer);
		//递归
		for( TiXmlNode* iitem = item->FirstChild( kTuiNodeControl );iitem; iitem = iitem->NextSibling(kTuiNodeControl)){
			TiXmlElement* ee = iitem->ToElement();
			parseControl(relLayer,ee,iitem);
		}

	}else if(strcmp(e->Attribute("type"),kTuiContainerLayout) == 0){//layout
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CLayout *playout = createLayout(tag,x,y,w,h);
		playout->ignoreAnchorPointForPosition(true);
		container->addChild(playout);
		//递归
		for( TiXmlNode* iitem = item->FirstChild( kTuiNodeControl );iitem; iitem = iitem->NextSibling(kTuiNodeControl)){
			TiXmlElement* ee = iitem->ToElement();
			parseControl(playout,ee,iitem);
		}

	}else if(strcmp(e->Attribute("type"),kTuiControlImage) == 0){//image
		const char* file = e->Attribute("image");
		CImageView *pImg = createImage(tag,file,x,y);
		container->addChild(pImg);
	
	}else if(strcmp(e->Attribute("type"),kTuiControlImage9) == 0){//image9
		const char* file = e->Attribute("image");
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		float up = atof(e->Attribute("up"));
		float down = atof(e->Attribute("down"));
		float left = atof(e->Attribute("left"));
		float right = atof(e->Attribute("right"));
		CImageViewScale9 *pImg = createImage9(tag,file,x,y,w,h,up,down,left,right);
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
		float num = atof(e->Attribute("num"));
		CListView* pList = createListView(tag,img,x,y,w,h);
		container->addChild(pList);

		for(int i=0; i<num;i++){//添加item
			TiXmlNode* iitem = item->FirstChild( kTuiNodeControl );
			TiXmlElement* layoutElem = iitem->ToElement();
			w = atof(layoutElem->Attribute("width"));
			h = atof(layoutElem->Attribute("height"));

			CLayout *pLayout = createLayout(i,0,0,w,h);
			for( TiXmlNode* iiitem = iitem->FirstChild( kTuiNodeControl );iiitem; iiitem = iiitem->NextSibling(kTuiNodeControl)){
				TiXmlElement* ee = iiitem->ToElement();
				parseControl(pLayout,ee,iiitem);
			}
			CCObject* pObj = NULL;
			CCARRAY_FOREACH(pLayout->getChildren(),pObj){//偏移坐标 因为CLayout的零点在左下角
				CCNode* pChild = (CCNode*)pObj;
				pChild->setPosition(pChild->getPositionX()+w/2,pChild->getPositionY()+h/2);
			}
			pList->insertNodeAtLast(pLayout);
		}
		pList->reloadData();
		
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

	}else if(strcmp(e->Attribute("type"),kTuiControlPaticle) == 0){//Paticle
		const char* plist = e->Attribute("plist");
		CCParticleSystem *pPartical = createParticle(tag,plist,x,y);
		container->addChild(pPartical);

	}else if(strcmp(e->Attribute("type"),kTuiControlTable) == 0){//TableView
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		CTableView *pView = createTableView(tag,x,y,w,h);
		container->addChild(pView);

	}else if(strcmp(e->Attribute("type"),kTuiControlEditBox) == 0){//EditBox
		float w = atof(e->Attribute("width"));
		float h = atof(e->Attribute("height"));
		const char* img = e->Attribute("image");
		CCEditBox *pEdit = createEditBox(tag,img,x,y,w,h);
		container->addChild(pEdit);

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

CLayout *TuiManager::createLayout(float tag,float x,float y,float w,float h){
	CLayout *pLayout = CLayout::create(CCSizeMake(w,h));
	pLayout->setPosition(ccp(x,y));
	pLayout->setTag(tag);
	return pLayout;
}

RelativeLayout *TuiManager::createRelativeLayout(float tag,float x,float y,float w,float h){
	RelativeLayout *pRelLayer = RelativeLayout::create(CCSize(w,h));
	pRelLayer->setPosition(ccp(x,-y));
	pRelLayer->setTag(tag);
	return pRelLayer;
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
	m_isUseSpriteFrame ? pList->setBackgroundSpriteFrameName(img) : pList->setBackgroundImage(img);
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
	CImageView *pSprite = m_isUseSpriteFrame ? CImageView::createWithSpriteFrameName(file) : CImageView::create(file);
	CCSize size = pSprite->getContentSize();
	pSprite->setPosition(ccp(x,-y));
	pSprite->setTag(tag);
	return pSprite;
}

CImageViewScale9 *TuiManager::createImage9(float tag,const char* file,float x,float y,float w,float h,float up,float down,float left, float right){
	CImageViewScale9* pSprite = NULL;
	if(m_isUseSpriteFrame){
		pSprite = CImageViewScale9::createWithSpriteFrameName(file,CCRectMake(up,down,left,right));
	}else{
		CImageView *temp = CImageView::create(file);
		CCSize size = temp->getContentSize();
		pSprite = CImageViewScale9::create(file, CCRectMake(0,0,size.width,size.height),CCRectMake(up,down,left,right));
	}
	pSprite->setContentSize(CCSizeMake(w,h));
	pSprite->setPosition(ccp(x,-y));
	pSprite->setTag(tag);
	return pSprite;
}

CButton* TuiManager::createBtn(float tag, const char* normal,const char* select,const char* disable,float x,float y,float w, float h){
	CButton * pBtn = NULL;
	if(m_isUseSpriteFrame){
		pBtn = CButton::create();
		pBtn->setNormalSpriteFrameName(normal);
		pBtn->setSelectedSpriteFrameName(select);
		pBtn->setDisabledSpriteFrameName(disable);
	}else{
		pBtn = CButton::createWith9Sprite(CCSize(w,h),normal,select,disable);
	}
	pBtn->setPosition(ccp(x,-y));
	pBtn->setTag(tag);
	return pBtn;
}

CToggleView* TuiManager::createToggleView(float tag,int exclusion,const char* normal,const char* select,const char* disable,float x,float y){
	CToggleView *pToggle = NULL;
	if(m_isUseSpriteFrame){
		pToggle = CToggleView::create();
		pToggle->setNormalSpriteFrameName(normal);
		pToggle->setSelectedSpriteFrameName(select);
		pToggle->setDisabledSpriteFrameName(disable);
	}else{
		pToggle = CToggleView::create(normal,select,disable);
	}
	pToggle->setExclusion(exclusion);
	pToggle->setPosition(x,-y);
	pToggle->setTag(tag);
	return pToggle;
}

CSlider* TuiManager::createSlider(float tag, const char* bg,const char* progress,const char* thumb,float x,float y){
	CSlider *pSlider = NULL;
	if(m_isUseSpriteFrame){
		pSlider = CSlider::create();
		pSlider->setBackgroundSpriteFrameName(bg);
		pSlider->setProgressSpriteFrameName(progress);
		pSlider->setSliderSpriteFrameName(thumb);
	}else{
		pSlider = CSlider::create(thumb,progress);
		pSlider->setBackgroundImage(bg);
	}
	pSlider->setPosition(ccp(x,-y));
	pSlider->setMinValue(0);
	pSlider->setMaxValue(100);
	pSlider->setValue(15);
	pSlider->setTag(tag);
	return pSlider;
}

CProgressBar* TuiManager::createProgress(float tag, const char* bg,const char* progress,float x,float y){
	CProgressBar *pProgress = NULL;
	if(m_isUseSpriteFrame){
		pProgress = CProgressBar::create();
		pProgress->setBackgroundSpriteFrameName(bg);
		pProgress->setProgressSpriteFrameName(progress);
	}else{
		pProgress = CProgressBar::create(progress);
		pProgress->setBackgroundImage(bg);
	}
	pProgress->setPosition(ccp(x,-y));
	pProgress->setMaxValue(100);
	pProgress->setMinValue(0);
	pProgress->setValue(15);
	pProgress->setTag(tag);
	return pProgress;
}

CLabel* TuiManager::createLabel(float tag, const char* text ,float fontSize,float x,float y,float w,float h){
	CLabel *pLabel = CLabel::create(text,"",fontSize);
	pLabel->setDimensions(CCSize(w,h));
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
	if(m_isUseSpriteFrame){
		CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile(plist,png,xml);
	}else{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png,plist,xml);
	}
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
	CControlView* pView = NULL;
	if(m_isUseSpriteFrame){
		pView = CControlView::create();
		pView->setBaseBoardSpriteFrameName(baseboard);
		pView->setJoystickSpriteFrameName(joystick);
	}else{
		pView = CControlView::create(baseboard,joystick);
	}
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
	CCheckBox* pCheckBox = NULL;
	if(m_isUseSpriteFrame){
		pCheckBox = CCheckBox::create();
		pCheckBox->setNormalSpriteFrameName(normal1);
		pCheckBox->setNormalPressSpriteFrameName(normal2);
		pCheckBox->setCheckedSpriteFrameName(select1);
		pCheckBox->setCheckedPressSpriteFrameName(select2);
		pCheckBox->setDisabledNormalSpriteFrameName(disable1);
		pCheckBox->setDisabledCheckedSpriteFrameName(disable2);
	}else{
		pCheckBox = CCheckBox::create(); 
		pCheckBox->setNormalImage(normal1); 
		pCheckBox->setNormalPressImage(normal2); 
		pCheckBox->setCheckedImage(select1); 
		pCheckBox->setCheckedPressImage(select2); 
		pCheckBox->setDisabledNormalImage(disable1); 
		pCheckBox->setDisabledCheckedImage(disable2); 
	}
	pCheckBox->setPosition(ccp(x,-y));
	pCheckBox->setTag(tag);
	return pCheckBox;
}

ArmatureBtn* TuiManager::createArmatureBtn(float tag,const char* name,const char* png,const char* plist,const char* xml,float x,float y){
	if(m_isUseSpriteFrame){
		CCArmatureDataManager::sharedArmatureDataManager()->addSpriteFrameFromFile(plist,png,xml);
	}else{
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(png,plist,xml);
	}
	ArmatureBtn *pArmBtn = ArmatureBtn::create(name);
	CCSize size = pArmBtn->getContentSize();
	pArmBtn->setPosition(ccp(x - size.width/2,-y - size.height/2));
	pArmBtn->setTag(tag);
	return pArmBtn;
}

NumericStepper* TuiManager::createNumStep(float tag,const char* lnormal,const char* lselect,const char* ldisable,const char* rnormal,const char* rselect,const char* rdisable,const char* stepBg,float x,float y){
	NumericStepper* pNumStep = NULL;
	if(m_isUseSpriteFrame){
		pNumStep = NumericStepper::create();
		pNumStep->setlNormalSpriteFrameName(lnormal);
		pNumStep->setlSelectedSpriteFrameName(lselect);
		pNumStep->setlDisabledSpriteFrameName(ldisable);
		pNumStep->setrNormalSpriteFrameName(rnormal);
		pNumStep->setrSelectedSpriteFrameName(rselect);
		pNumStep->setrDisabledSpriteFrameName(rdisable);
		pNumStep->setStepBgSpriteFrameName(stepBg);
	}else{
		pNumStep = NumericStepper::create(lnormal,lselect,ldisable,rnormal,rselect,rdisable,stepBg);
	}
	CCSize size = pNumStep->getContentSize();
	pNumStep->setPosition(ccp(x - size.width/2,-y - size.height/2));
	pNumStep->setTag(tag);
	return pNumStep;
}

CCParticleSystemQuad* TuiManager::createParticle(float tag,const char* plist,float x,float y){
	CCParticleSystemQuad *pPartical = CCParticleSystemQuad::create(plist);
	pPartical->setPosition(x,-y);
	pPartical->setTag(tag);
	return pPartical;
}

CTableView* TuiManager::createTableView(float tag,float x,float y,float w,float h){
	CTableView *pView = CTableView::create(CCSize(w,h));
	pView->setPosition(x,-y);
	pView->setTag(tag);
	return pView;
}

CCEditBox* TuiManager::createEditBox(float tag,const char* file,float x,float y,float w,float h){
	CCEditBox *pEditBox = NULL;
	if(m_isUseSpriteFrame){
		pEditBox = CCEditBox::create(CCSize(w,h),CCScale9Sprite::createWithSpriteFrameName(file));
	}else{
		pEditBox = CCEditBox::create(CCSize(w,h),CCScale9Sprite::create(file));
	}
	pEditBox->setPosition(ccp(x,-y));
	pEditBox->setTag(tag);
	return pEditBox;
}



void TuiManager::loadXml(const char* xml){

	if(strlen(m_fileContent) == 0){//简单地缓存下xml
		unsigned long size;
		m_fileContent = (const char*)CCFileUtils::sharedFileUtils()->getFileData( xml , "r", &size);
	}else{
		std::string s = m_fileContent;
		s.clear();
		loadXml(xml);
	}
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
void TuiManager::setUseSpriteFrame(bool b){
	m_isUseSpriteFrame = b;
}

CCSize TuiManager::getScreen(){
	TiXmlDocument doc;
	doc.Parse(m_fileContent, 0, TIXML_ENCODING_UTF8);
	TiXmlElement* root = doc.RootElement(); 
	float screenX = atof(root->FirstChildElement(kTuiNodeScheme)->Attribute("screen_width"));
	float screenY = atof(root->FirstChildElement(kTuiNodeScheme)->Attribute("screen_height"));
	return CCSize(screenX,screenY);
}