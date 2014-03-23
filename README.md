Tui-x
=====

This Tui-x is Tui's updated version,more light,more sample,more flexible

简介：

Tui是一个创建cocos2d-x UI界面的解决方案，而builder用的则是FlashCS，它的前身Github地址https://github.com/tongpengfei/tui
    ，里面有一些说明，原始Tui本身只支持3个控件，button,panel,image。由于控件种类太少，根本不能满足开发需求，后来Tui-x出现了，
完美支持一个第三方组件库cocoswiget上的所有控件，这时候的Tui-x才开始变得强大。而且在事件处理上Tui-x完全改掉Tui之前的做法，
轻量，灵活和可视化是Tui-x最大的优点，而且开源。欢迎大家提供意见和反馈。CocosWidget交流群：261286285

注意：

Tui-x最终所生成的组件全部来自CocosWidget，所以大家一定要下载并配置好依赖库。由于Tui-x是需要用jsfl来导出xml和.h的，所以FlashCS编辑器要CS5.5以上，具体要如何可视化创建组件，大家请看教程word文档，有图有真相。

说明：

Tui-x和Tui的解析库是完全不兼容，在原始的Tui中，按钮发出的事件全部集中在GameUIController里面，需要继承它来实现事件回调来做出响应，显然这种强制UI去继承Controller的做法不太灵活。在Tui-x里，能为每个组件分配一个唯一Tag，并导出一张TuiTagMap.h的映射表，内容如 static const int IMG_BG = 1; （这个映射的名字来自我们在FlashCS里面的影片剪辑的实例名）这样我们就能很容易地
通过getChildByTay来获取该组件，然后你自行setListener就可以监听事件了，是不是很方便呢:) 

配置：

首先要配置在TuiEditer.jsfl里面配置导出xml和.h的路径，请在FlashCS里面导入TuiEditer.jsfl，然后滚到最下面有两个配置路径。
然后配置如何在工程里使用。在AppDelegate.cpp里的applicationDidFinishLaunching中加上

TuiManager::sharedManager()->setPathXml("tui/480x800.xml"); //读取xml文件内容
CCSize screenSize = TuiManager::sharedManager()->getScreen(); //设置屏幕分辨率

CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, kResolutionNoBorder); //无边框

这样配置就完成了。然后我们需要让我们的场景去继承TuiBase。假如我们现在在FlashCS里面创建好一个场景叫panel_ingame，我现在需要创建一个Ingame.cpp然后让它继承TuiBase，在初始化的时候调用
TuiManager::sharedManager()->parseScene(this,"panel_ingame");
就可以自动生成界面了，这跟FlashCS里面设计的UI一模一样:)
