********************************************************************************
** Tui user manual

  FAQ:
* What is Tui?
  Tui is a game ui editer. It is a FlashCS6 extension, writen in jsfl and as3.
  You can edit game ui in FlashCS6 with real-time preview. The editer outputs
  a xml file. The current version( v1.0 ) supports 2 schemes: iphone(320*480 or 480*320)
  and ipad(1024*768 or 768*1024).
    Below are the features of Tui:
    * Tui is "what you seen is what you get".
    * Seperate the work of artists, designers and programmers.
    * Easy to learn and easy to use.
    * Stable.
    * As long as your working environment supports Flash, it will work.
    * One of the best feature is the support for event! For example, you may test a button click 
  event in Tui's preview panel, and see debug log like "receive button click event ***" in debug panel,
 (if the event is currectly configured.)

* What can it do?
  * You may edit game ui visually in FlashCS.
  * Export a xml file that describes the UI layout.
  * Test a button click in real time.
  * Parse a xml file and generate the UI in game.
  * Just check out the codes below:
    You may show a ui panel via 
    GameUIController::sharedGameUIController()->showTui( "panel_name" );
    or hide a panel via
    GameUIController::sharedGameUIController()->hideTui( "panel_name" );
  * You may access a child ui control in a panel via
    Tui* panel = GameUIController::sharedGameUIController()->getTui( "panel_name" );
    CCNode* control = panel->getControl( "control_name" );
    ...now you get the child control.

* How it works?
  * Edit ui in FlashCS, a panel is a movieclip, a panel could include multiple images,
    buttons or panels.
  * Preview your work in the preview panel
  * Use Tui export Flash layer data to xml via jsfl.
  * Import xml file and generate ui panel in game programm.

* How it support multiple schemes?
  * In Flash: you create multiple folders in library, like img_iphone, img_ipad that 
    include corresponding image resource.
  * NOTICE: the folder MUST be img_iphone for iphone or img_ipad for ipad. Other target platforms are not supported for now.
  * In game: Tui distinguishes the different schemes by directory name, for example: iphone 
    resource placed in Resource/ui_iphone, iphonehd resource placed in Resource/ui_iphonehd,
    ipad resource placed in Resource/ui_ipad.
  * You may output two xml files: tui_iphone.xml, tui_ipad.xml
  * Just simply load tui_iphone.xml for iphone or tui_ipad.xml for ipad.

* How do I make an iphone HD scheme?
  * In tui xml there is a node named "scheme" which has a attribute named "is_retina", you can
    access it via your game, it will be HD mode if it is "1" other wise it is "0".
  * NOTICE: In Tui extension, is_retina is "0" by default, you just need edit standard definition
    version in Tui, then change is_retina to "0" or "1" if it is a HD version.

* How can I handle a button event?
  * Tui will generate a gameuievent.h file that includes all controls and panels name, all
    used events in this scheme. It looks like:
    static TuiEventCallBackTable tui_event_cb_table[] = { 
        { "panel_menu_click_btn_start", tuievent_cb(GameUIController::on_event_panel_menu_click_btn_start) },
        ...
    };

    You just need to add a class named GameUIController extending from TuiManager and implementing the callback:
    class GameUIController : public TuiManager{
    public:
        void on_event_panel_menu_click_btn_start( void* o, TEvent* e ){
             //TODO add your code here
        }
    };

* Where can I get it?
  download: https://github.com/tongpengfei/tui/archive/master.zip
  source:   https://github.com/tongpengfei/tui.git

* Author
  pengfei tong     27001909#qq.com ( replace # to @ please )

* License
  MIT license
  Yes! It's all FREE! Just do what you like!

* Requirements
  FlashCS6
  AdobeExtensionManager6.0All
  cocos2d-x-2.0.3

* Have fun~

* NOTICE:
  * Every button or panel you make is REQUIRES a name, you need it to access that control in your game.
  * In flash library, iphone image MUST be placed in img_iphone forder and ipad image MUST
    be placed in img_ipad forder.
  * DO NOT forget to set "portrait" or "landscape" mode in Tui extension.
  * DO NOT forget to choose the scheme when exporting, the default scheme is iphone4.


********************************************************************************
** Tui 用户手册

  FAQ:
* Tui是什么?
    Tui是一个游戏UI编辑器,是FlashCS6的扩展插件。开发者可以使用FlashCS6编辑游戏UI,
  然后通过Tui插扩展预览最终的UI效果，并生成相应的xml文件。当前版本(v1.0)支持iphone
  (320*480或480*320)与ipad(1024*768或768*1024)尺寸。
    Tui的特点包括:
    * Tui的最主要特点是所见即所得。
    * 把美术工作,策划工作与程序的工作区分开来。
    * 学习成本极低，只要会用简单操作Flash就可以。
    * 稳定性好。
    * 只要可以运行FlashCS的平台就可以使用。
    * 其中一个非常实用的功能工具对事件的支持，开发者可以测试一个按钮是否正常设置，
      当预览该UI时，可以在工具里点击按钮，如果设置正常，可以在Tui的调试面板里看到
      类似收到了***事件的调试信息。

* Tui可以做什么?
  * 在FlashCS6里可视化编辑UI
  * 生成xml格式UI描述文件
  * 实时测试按钮等是否配置正确
  * 在游戏里解析xml生成UI
  * 亲,看到下面的用法,不心动么
    显示一个UI面板:
    GameUIController::sharedGameUIController()->showTui( "panel_name" );
    隐藏一个UI面板:
    GameUIController::sharedGameUIController()->hideTui( "panel_name" );
  * 还可以获取面板中的子控件:
    Tui* panel = GameUIController::sharedGameUIController()->getTui( "panel_name" );
    CCNode* control = panel->getControl( "control_name" );
    ...ok，控件交给你了，随你处置吧。

* Tui是怎么工作的?
  * 在FlashCS6里创建UI面板影片剪辑(mc),一个mc可以包含多个子mc，图片或按钮控件。
  * 通过jsfl导出Flash的layer数据，生成xml。
  * 工具里通过as3解析xml数据，生成ui预览，并处理相应的事件。
  * 程序通过tui库导入xml文件生成游戏UI。

* Tui是如何支持多个主题的?
  * 在flash里: 你需要为每个主题创建一个资源文件夹，如img_iphone和img_ipad分别包含iphone和ipad的图片资源。
  * 注意: 在flash库里的资源目录必须为img_iphone或img_ipad,否则导出的图片会找不到资源。
  * 在游戏里: Tui通过文件夹来区分不同主题下的资源, 例如iphone的资源放在Resources/ui_iphone目录下，ipad的
    资源放在Resources/ui_ipad目录下, iphonehd的资源放在Resources/ui_iphonehd目录下。
  * 每个主题对应一个xml配置文件，如tui_iphone.xml, tui_ipad.xml。
  * 在程序里判断不同的设备加载相应的xml配置文件就可以了。

* HD版本的UI怎么搞?
  * 在Tui生成的配置文件里有个叫scheme的节点，它有个属性是is_retina, 当值为1时，表示HD版，反之为标清版，默认
    是标清版。可以在程序里读取该值判断是否是HD版，是则把资源的根目录设置到hd版资源目录下。
  * 注意:在编辑器里只需要编辑标清版。需要用到hd版时候，在Resources下加上hd版资源目录并把配置文件改为is_retina。

* 如何处理一个按钮事件?
  * Tui会生成一个gameuievent.h的文件,其中包括所有控件和面板的名字,还有所有用到的事件与相应的回调函数对应表,
    回调函数对应表的格式为:
    static TuiEventCallBackTable tui_event_cb_table[] = { 
        { "panel_menu_click_btn_start", tuievent_cb(GameUIController::on_event_panel_menu_click_btn_start) },
        ...
    };

    开发者仅需要填加一个继承自TuiManager的类GameUIController然后实现对应表中的回调函数即可:
    class GameUIController : public TuiManager{
    public:
        void on_event_panel_menu_click_btn_start( void* o, TEvent* e ){
             //TODO add your code here
        }
    };

* Tui在哪里下载?
  download: https://github.com/tongpengfei/tui/archive/master.zip
  source:   https://github.com/tongpengfei/tui.git

* 作者
  仝鹏飞   27001909#qq.com ( 请把#替换为@ )

* 许可
  MIT license
  亲,免费哦~ 随便你搞!

* 环境需求
  FlashCS6
  AdobeExtensionManager6.0All
  cocos2d-x-2.0.3

* 容易出错的地方
  * 每个控件或面板即只要是mc类型的控件就需要设置名字，否则在程序中就不能找到该控件。
  * 一定要注意在flash的库里资源目录名字只能为img_iphone或img_ipad。
  * 导出的时候别忘了选择正确的横竖屏模式。
  * 导出的时候别忘了选择正确的主题。

* 最后,祝各位同学发大财，闯出属于自己的天空~
