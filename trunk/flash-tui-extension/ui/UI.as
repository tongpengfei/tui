package ui 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.utils.Dictionary;
	import tcontrol.TButton;
	import tcontrol.TControl;
	import tcontrol.TControlAlignment;
	import tcontrol.TImage;
	import tcontrol.TPanel;
	import tcontrol.TSimpleButton;	
	import tevent.TEvent;
	import tevent.TEventController;

	/**
	 * ...
	 * @author tpf
	 */
	public class UI extends Sprite 
	{
		//所有的面板,{ 面板的名字:面板数据 }
		public var ui_panels:Dictionary = null;
		//当前显示的面板名字
		private var current_show_panel:String = "";
		//一共有多少个面板
		public var npanels:int = 0;
		//jsfl库目录转换为资源目录的回调
		private var cbGetResourcePath:Function = null;
		//debug信息面板
		private var txt_debug_panel:* = null;
		//当前监听的事件
		private var btn_events:Array = new Array();
		
		//每个面板里的button和button的事件
		//{面板: PanelEvent, PanelEvent };
		private var panel_events:Dictionary = null;
		//当前解析到哪个panel
		private var current_parse_panel:String = "";
		/**
		 @param getResourcePathByLibraryPath 把库路径换为资源路径
		 @param debugpanel debug面板,是个textfield
		 */
		public function UI( getResourcePathByLibraryPath:Function = null, debugpanel:* = null ) {
			cbGetResourcePath = getResourcePathByLibraryPath;
			setTextDebugPanel( debugpanel );
		}
		
		public function setTextDebugPanel( v:* ):void{
			txt_debug_panel = v;
		}
		
		public function pushDebugInfo( str:String ):void{
			txt_debug_panel.text += str;
			txt_debug_panel.verticalScrollPosition = txt_debug_panel.maxVerticalScrollPosition;
		}
		
		public function currentShowPanelName():String{
			return current_show_panel;
		}
		
		public function clear():void{
			npanels = 0;
			for( var up in ui_panels ){
				ui_panels[up] = null;
			}
			ui_panels = null;
			//panel_events = null;
			for( var pe in panel_events ){
				panel_events[pe].splice();
				panel_events[pe] = null;
			}
			panel_events = null;
			
			clearChildren();
			clearEvent();
		}

		private function clearChildren():void{
			var n:int = this.numChildren;
			var i:int = 0;
			for ( i = n - 1; i >= 0; --i ) {
				removeChildAt( i );
			}			
		}

		private function clearEvent():void{
			for( var i:int = 0; i < btn_events.length; ++i ){
				pushDebugInfo( "删除事件监听:" + btn_events[i] + "\n" );
				TEventController.RemoveEventListener( btn_events[i], onTestEvent );
			}
			btn_events.splice();
		}
		
		public function loadXML( file:String ):void {
			var loadurl:URLLoader = new URLLoader( new URLRequest(file) );
			loadurl.addEventListener( Event.COMPLETE, onLoaderComplete );
		}
		
		private function onLoaderComplete( e:Event ):void {
			var xml:XML = XML((e.target as URLLoader).data);
			parseXML( xml );
		}
		
		//显示一个panel
		public function showPanel( panelname:String ):void{
			clearEvent();
			clearChildren();
			
			var panel:TControl = ui_panels[panelname];
			if( panel != null ){
				addChild( panel );
				pushDebugInfo( "显示" + panelname + "\n" );
				current_show_panel = panelname;

				if( panel.getWidth() > 515 ){
					panel.scaleX = 0.5;
					panel.scaleY = 0.5;
					panel.x /= 2.0;
					panel.y /= 2.0;
					panel.setSize( panel.getWidth()/2, panel.getHeight()/2 );
				}else{
					//panel.scaleX = 1.0;
					//panel.scaleY = 1.0;
				}
			}
			
			//填加当前显示的panel的事件
			for each( var pe:PanelEvent in panel_events[current_show_panel] ){
				TEventController.AddEventListener( pe.event_type, onTestEvent );
				pushDebugInfo( "监听按键消息: " + pe.event_type + "\n" );
			}
		}
		
		public function parseXML( xml:XML ):void {
			//清除所有数据
			this.clear();
			
			ui_panels = new Dictionary();
			panel_events = new Dictionary();
			
			getSchemeElement( xml.scheme );
			getControlElement( xml.control, null );	

			for each( var c:TControl in ui_panels ) {
				addChild( c );
				npanels++;
				//这里居中放panel
				//c.x += c.getWidth() / 2;
				//c.y += c.getHeight() / 2;
			}
			
			//显示第一个panel
			if( npanels > 0 ){
				for( var panelname:String in ui_panels ){
					showPanel( panelname );
					break;
				}
			}
		}
		
		private function getSchemeElement( xml:XMLList ):void {
			trace( xml.@scheme );
		}
		
		private function getControlElement( xml:XMLList, father:TControl ):void {
			if ( xml ) {
				//获取当前属性
				for ( var i:int = 0; i < xml.length(); ++i ) {
					trace( xml[i].@type + " " + xml[i].@name);
					var c:TControl = createControlByXML( xml[i], father );
					
					//取得子属性
					getControlElement( xml[i].control, c );
				}
			}
		}
		private function createControlByXML( xml:XML, father:TControl ):TControl {
			var control:TControl = null;
			var xml_type:String = xml.@type;
			var xml_name:String = xml.@name;
			var xml_x:Number = Number( xml.@x );
			var xml_y:Number = Number( xml.@y );
			var xml_ox:Number = Number( xml.@ox );
			var xml_oy:Number = Number( xml.@oy );
			var xml_width:Number = Number( xml.@width );
			var xml_height:Number = Number( xml.@height );
			var xml_event:String = xml.@click_event;
			var xml_img:String = xml.@image;
			//需要把资源的库路径转为资源路径
			var url_img:String = xml_img;
			if( xml_img != null && xml_img != "" ){
				url_img = cbGetResourcePath == null ? xml_img : cbGetResourcePath( xml_img );
			}
			
			if ( xml_type == "panel" ) {
				control = new TPanel();
				control.setSize( xml_width, xml_height );
			}else if ( xml_type == "image" ) {
				control = new TImage();
				var img:TImage = control as TImage;
				img.setImage( url_img );				
			}else if ( xml_type == "button" ) {
				control = new TButton();
				var btn:TButton = control as TButton;
				//control = new TSimpleButton();
				//var btn:TSimpleButton = control as TSimpleButton;
				btn.setImage( url_img );
				
				btn.setEventClick( new TEvent( xml_event, btn ) );
				//TEventController.AddEventListener( xml_event, onTestEvent );
				
				//btn_events.push( xml_event );
				//pushDebugInfo( "监听按键消息: " + xml_event + "\n" );
				
				//保存下当前解析面板的事件
				panel_events[current_parse_panel].push( new PanelEvent( btn, xml_event ) );				
			}

			if ( !father ) {
				ui_panels[xml_name] = control;
				current_parse_panel = xml_name;
				
				panel_events[current_parse_panel] = new Array();
				//this.addChild( control );
			}else {
				father.addChild( control );
			}
			//control.setBackgroundColor( 0x000000 );
			control.setControlAlignment( TControlAlignment.VERTICAL_TOP, TControlAlignment.HORIZON_LEFT );
			if ( xml_type == "panel" ) {
				//因为panel是有中点的
				control.setRelationLocation( xml_x, xml_y );
			}else{
				control.setRelationLocation( xml_x - xml_ox, xml_y - xml_oy );
			}
			return control;
		}
		
		private function onTestEvent( e:TEvent ):void{
			var ev:String = e.type;
			var who:TControl = e.whosevent as TControl;
			pushDebugInfo( "收到事件: " + ev + " " + who + "\n" );
		}
	}

}

import tcontrol.TButton;
class PanelEvent{
	public var button:TButton = null;
	public var event_type:String = "";
	
	function PanelEvent( o:TButton, e:String ){
		button = o;
		event_type = e;
	}
}
