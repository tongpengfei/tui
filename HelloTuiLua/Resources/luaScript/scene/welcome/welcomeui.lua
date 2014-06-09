require "extern"
require "tagMap/Tag_welcomeui"

Welcomeui = class("Welcomeui",function()
	return TuiBase:create()
end)

Welcomeui.__index = Welcomeui

function Welcomeui:create()
	local ret = Welcomeui.new()
	TuiManager:sharedManager():parseScene(ret,"panel_welcome",PATH_WELCOMEUI)
	ret:onLoadComplete()
	return ret
end

function Welcomeui:getControl(tagPanel,tagControl)
	local ret = nil
	ret = self:getPanel(tagPanel):getChildByTag(tagControl)
	return ret
end

function Welcomeui:getPanel(tagPanel)
	local ret = nil
	if tagPanel == Tag_welcomeui.PANEL_WELCOME then
		ret = self:getChildByTag(tagPanel)
	end
	return ret
end

---------------logic----------------------------
local animCoin = 		nil
local armatureBoss = 	nil
local armBtnTest = 		nil
local listGoods = 		nil
local tgvOption = 		nil
local munStepTest = 	nil
local ckbTest =			nil

local function event_ctvl_left(p_sender, fx, fy)
	local x, y = animCoin:getPosition()
	animCoin:setPosition(ccp(x + fx, y + fy))
end

local function event_armbtn_test(p_sender)
	print("click!!")
end

local function event_btn_pay(p_sender)
	local btnPlay = tolua.cast(p_sender,"CButton")
	local layout = tolua.cast(btnPlay:getParent(),"CLayout")
	print("pay index:"..layout:getTag())
end

local function event_tgv_option(p_sender, b_checked)
	print("tgvOption "..type(b_checked))
end

local function event_numStep_test(p_sender, n_value)
	print("numStep :"..n_value)
end

local function event_ckb_test(p_sender,b_checked)
	print("ckbTest:"..type(b_checked))
end

function Welcomeui:onLoadComplete()
	--注册事件
	local ctvlLeft = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.CTLV_LEFT),"CControlView")
	ctvlLeft:setOnControlScriptHandler(event_ctvl_left)

 	animCoin = self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.ANIM_COIN)

 	armatureBoss = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.ARMATURE_BOSS1),"CCArmature")
 	armatureBoss:getAnimation():play("live",0,-1,1)

 	armBtnTest = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.ARMBTN_TEST2),"ArmatureBtn")
 	armBtnTest:setOnClickScriptHandler(event_armbtn_test)

 	listGoods = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.LIST_GOODS),"CListView")
 	local cout = listGoods:getNodeCount()
 	for i=0,cout-1 do
 		local item = listGoods:getNodeAtIndex(i)
 		local btnPlay = tolua.cast(item:getChildByTag(Tag_welcomeui.BTN_ITEMPAY),"CButton")
 		btnPlay:setOnClickScriptHandler(event_btn_pay)
 	end

 	tgvOption = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.TGV_OPTION),"CToggleView")
 	tgvOption:setOnCheckScriptHandler(event_tgv_option)

 	munStepTest = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.NUMSTEP_TEST),"NumericStepper")
 	munStepTest:setOnValueChangedScriptHandler(event_numStep_test)

 	ckbTest = tolua.cast(self:getControl(Tag_welcomeui.PANEL_WELCOME,Tag_welcomeui.CKB_TEST),"CCheckBox")
 	ckbTest:setOnCheckScriptHandler(event_ckb_test)
end 

