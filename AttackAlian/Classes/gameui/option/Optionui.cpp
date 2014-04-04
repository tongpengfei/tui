#include "Optionui.h"
#include "gameui/welcome/Welcomeui.h"

void Optionui::onLoadScene(){
	
	setAutoRemoveUnusedTexture(true);
	TuiManager::sharedManager()->parseScene(this,"panel_option");

	//注册按钮事件
	CButton *pBtnMenu = (CButton*) this->getControl(PANEL_OPTION,BTN_BACK);
	pBtnMenu->setOnClickListener(this,ccw_click_selector(Optionui::event_btn_menu));
	//注册滑动条事件
	CSlider *pSlBgMusic = (CSlider*) this->getControl(PANEL_OPTION,SLIDER_BGMUSIC);
	pSlBgMusic->setOnValueChangedListener(this,ccw_valuechanged_selector(Optionui::event_slider_bgmusic));
	CSlider *pSlMusic = (CSlider *) this->getControl(PANEL_OPTION,SLIDER_MUSIC);
	pSlMusic->setOnValueChangedListener(this,ccw_valuechanged_selector(Optionui::event_slider_music));
	//注册选择框事件
	CCheckBox *pCkbBgMusic = (CCheckBox*) this->getControl(PANEL_OPTION,CKB_BGMUSIC);
	pCkbBgMusic->setOnClickListener(this, ccw_click_selector(Optionui::event_ckb_bgmusic));
	CCheckBox *pCkbMusic = (CCheckBox*) this->getControl(PANEL_OPTION,CKB_MUSIC);
	pCkbMusic->setOnClickListener(this, ccw_click_selector(Optionui::event_ckb_music));
}

void Optionui::event_btn_menu(CCObject* s){
	CCSceneManager::sharedManager()->replaceScene(CCSceneExTransitionFade::create(0.5f,LoadScene("Welcomeui")));
}

void Optionui::event_slider_bgmusic(CCObject* s, int nValue){
	
}

void Optionui::event_slider_music(CCObject* s, int nValue){
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1f);
}

void Optionui::event_ckb_bgmusic(CCObject* s){
	CCheckBox* pCheckBox = (CCheckBox*) s;
	int v = pCheckBox->isChecked() ? 50 : 0;
	CSlider *pSlBgMusic = (CSlider*) this->getControl(PANEL_OPTION,SLIDER_BGMUSIC);
	pSlBgMusic->setValue(v);
}

void Optionui::event_ckb_music(CCObject* s){
	CCheckBox* pCheckBox = (CCheckBox*) s;
	int v = pCheckBox->isChecked() ? 50 : 0;
	CSlider *pBgMusic = (CSlider*) this->getControl(PANEL_OPTION,SLIDER_MUSIC);
	pBgMusic->setValue(v);
	pCheckBox->isChecked() ? SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic() 
		: SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

/************************************************************************/
//	GET/SET/IS
/************************************************************************/
CCNode* Optionui::getPanel(int tagPanel){
	CCNode *panel = NULL;
	switch(tagPanel){
	case PANEL_OPTION:
		panel = this->getChildByTag(PANEL_OPTION);
		break;
	}
	return panel;
}