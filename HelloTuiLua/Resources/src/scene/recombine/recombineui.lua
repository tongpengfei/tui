require "extern"
require "tagMap/Tag_recombineui"

Recombineui = class("Recombineui",function()
	return TuiBase:create()
end)

Recombineui.__index = Recombineui
local __instance = nil

function Recombineui:create()
	local ret = Recombineui.new()
	__instance = ret
	TuiManager:sharedManager():parseScene(ret,"panel_recombine",PATH_RECOMBINEUI)
	ret:onLoadComplete()
	return ret
end

function Recombineui:getControl(tagPanel,tagControl)
	local ret = nil
	ret = self:getPanel(tagPanel):getChildByTag(tagControl)
	return ret
end

function Recombineui:getPanel(tagPanel)
	local ret = nil
	if tagPanel == Tag_recombineui.PANEL_RECOMBINE then
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

local function event_btn_click(p_sender)
	print("tag : "..tolua.cast(p_sender,"CButton"):getUserTag())
end

local function event_adapt_gpvbag(p_convertview, idx)
	local pCell = p_convertview
	local btn = nil
	if pCell == nil then
		pCell = CGridPageViewCell:new()

		TuiManager:sharedManager():parseCell(pCell, "cell_grid", PATH_RECOMBINEUI)
		btn = tolua.cast(pCell:getChildByTag(Tag_recombineui.BTN_GRID),"CButton")
		btn:setOnClickScriptHandler(event_btn_click)
	else
		btn = pCell:getChildByTag(Tag_recombineui.BTN_GRID)
	end
	btn:setUserTag(idx)
	return pCell
end

function Recombineui:onLoadComplete()
	--º”‘ÿÕÍ≥…
	local btnBack = tolua.cast(self:getControl(Tag_recombineui.PANEL_RECOMBINE,Tag_recombineui.BTN_BACK),"CButton")
	btnBack:setOnClickScriptHandler(event_btn_back)
	
	local gpvBag = tolua.cast(self:getControl(Tag_recombineui.PANEL_RECOMBINE,Tag_recombineui.GPV_BAG),"CGridPageView")
	gpvBag:setDataSourceAdapterScriptHandler(event_adapt_gpvbag)
	gpvBag:reloadData()
	
end