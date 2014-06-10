require "src/scene/welcome/Welcomeui"

local function init()
 -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    
	CCEGLView:sharedOpenGLView():setDesignResolutionSize(800,480, kResolutionNoBorder)
end

local function createWelcomeScene()
	local scene = Welcomeui:create()
	return scene
end

------------------------------------------------
function main()

	init()
	CCDirector:sharedDirector():runWithScene(createWelcomeScene())
	
end
------------------------------------------------