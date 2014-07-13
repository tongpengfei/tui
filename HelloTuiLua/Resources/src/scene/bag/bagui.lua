require "extern"
require "tagMap/Tag_bagui"

Bagui = class("Bagui",function()
	return TuiBase:create()
end)

Bagui.__index = Bagui
local __instance = nil

function Bagui:create()
	local ret = Bagui.new()
	__instance = ret
	TuiManager:sharedManager():parseScene(ret,"panel_bag",PATH_BAGUI)
	ret:onLoadComplete()
	return ret
end

function Bagui:getControl(tagPanel,tagControl)
	local ret = nil
	ret = self:getPanel(tagPanel):getChildByTag(tagControl)
	return ret
end

function Bagui:getPanel(tagPanel)
	local ret = nil
	if tagPanel == Tag_bagui.PANEL_BAG then
		ret = self:getChildByTag(tagPanel)
	end
	return ret
end

---------------logic----------------------------

local function event_btn_back(p_sender)
	
	local scene = Welcomeui:create()
	CCDirector:sharedDirector():replaceScene(
		CCTransitionFade:create(0.5, scene, ccc3(0,255,255)))
end

local function event_btn_recombine(p_sender)

	local scene = Recombineui:create()
	CCDirector:sharedDirector():replaceScene(
		CCTransitionFade:create(0.5, scene, ccc3(0,255,255)))
end

local function event_btn_click(p_sender)
	print("tag : "..tolua.cast(p_sender,"CButton"):getUserTag())
end

local function event_adapt_gvbag(p_convertview, idx)
	local pCell = p_convertview
	local btn = nil
	if pCell == nil then
		pCell = CGridViewCell:new()
		pCell:autorelease()
		TuiManager:sharedManager():parseCell(pCell, "cell_grid", PATH_BAGUI)
		btn = tolua.cast(pCell:getChildByTag(Tag_bagui.BTN_GRID),"CButton")
		btn:setOnClickScriptHandler(event_btn_click)
	else
		btn = pCell:getChildByTag(Tag_bagui.BTN_GRID)
	end
	btn:setUserTag(idx)
	return pCell
end

local function event_adapt_tblbag(p_convertview, idx)
	local pCell = p_convertview
	if pCell == nil then
		pCell = CTableViewCell:new()
		pCell:autorelease()
		TuiManager:sharedManager():parseCell(pCell, "cell_grid", PATH_BAGUI)
	else

	end
	return pCell
end

local function event_adapt_pvbag(p_convertview, idx)
	local pCell = p_convertview
	if pCell == nil then
		pCell = CPageViewCell:new()
		pCell:autorelease()
		TuiManager:sharedManager():parseCell(pCell, "cell_page", PATH_BAGUI)
	else

	end
	return pCell
end

function Bagui:onLoadComplete()
	--加载完成
	local btnBack = tolua.cast(self:getControl(Tag_bagui.PANEL_BAG,Tag_bagui.BTN_BACK),"CButton")
	btnBack:setOnClickScriptHandler(event_btn_back)
	
	local btnRecombine = tolua.cast(self:getControl(Tag_bagui.PANEL_BAG,Tag_bagui.BTN_RECOMBINE),"CButton")
	btnRecombine:setOnClickScriptHandler(event_btn_recombine)
	
	local gvBag = tolua.cast(self:getControl(Tag_bagui.PANEL_BAG,Tag_bagui.GV_BAG),"CGridView")
	gvBag:setDataSourceAdapterScriptHandler(event_adapt_gvbag)
	gvBag:reloadData()
	
	local tblBag = tolua.cast(self:getControl(Tag_bagui.PANEL_BAG,Tag_bagui.TBL_BAG),"CTableView")
	tblBag:setDataSourceAdapterScriptHandler(event_adapt_tblbag)
	tblBag:reloadData()
	
	local pvBag = tolua.cast(self:getControl(Tag_bagui.PANEL_BAG,Tag_bagui.PV_BAG),"CPageView")
	pvBag:setDataSourceAdapterScriptHandler(event_adapt_pvbag)
	pvBag:reloadData()
	
end