package{
	
	import flash.display.MovieClip;
	import fl.data.DataProvider; 
	import flash.events.MouseEvent;
	import flash.events.Event;
	import adobe.utils.MMExecute;
	import flash.utils.Dictionary;

	import flash.net.FileFilter;
	import flash.net.FileReference;
	import flash.net.FileReferenceList;
	import flash.events.IOErrorEvent;
	import flash.display.Bitmap;
	import flash.display.Sprite;
	import flash.ui.Mouse;
	import ui.UI;
	import tcontrol.TImage;

	public class TuiEditer extends MovieClip {
		public static const JSFL_URL:String = "WindowSWF/TuiEditer/TuiEditer.jsfl";
		
		private var current_scheme:String = "iphone4";
		
		private var current_xml:String = "";
		
		private var ui_preview:Sprite = null;
		private var tui:UI = null;

		private var list_data:Array = new Array();
		
		//private var file_ref:FileReference = null;
		private var file_ref:FileReference = null;
		private static const kFileFilter:Array = [new FileFilter("save data", "*." + String(["xml", "png"]).replace(/\,/g, ";*."))];

		private var file_cpp:FileReference = null;
		private static const kFileFilterCpp:Array = [new FileFilter("save cpp", "*." + String(["h"]).replace(/\,/g, ";*."))];

		private var control_names:Dictionary = null;
		private var event_cb_table:String = "";

		public function TuiEditer() {
			//scheme combobox
			select_scheme.prompt = "scheme";
			var sfUniversities:Array = new Array( 
			    {label:"iphone4", data:"iphone4"},
				{label:"iphone5", data:"iphone5"},
				{label:"ipad", data:"ipad"}
			);
			select_scheme.dataProvider = new DataProvider(sfUniversities); 
			select_scheme.addEventListener( Event.CHANGE, onSchemeChange );
			
			// constructor code
			btn_export_current_layer.addEventListener( MouseEvent.CLICK, onExprotCurrentLayer );
			btn_export_visible_layer.addEventListener( MouseEvent.CLICK, onExprotVisibleLayer );
			btn_export_all_layer.addEventListener( MouseEvent.CLICK, onExprotAllLayer );
			btn_test_xml_to_ui.addEventListener( MouseEvent.CLICK, onTestXMLToUI );
			btn_debug.addEventListener( MouseEvent.CLICK, onDebugInfo );
			btn_save_xml.addEventListener( MouseEvent.CLICK, onSaveXml );
			
			radio_view_xml.addEventListener( MouseEvent.CLICK, onRadioGroupView );
			radio_view_ui.addEventListener( MouseEvent.CLICK, onRadioGroupView );
			radio_view_cpp.addEventListener( MouseEvent.CLICK, onRadioGroupView );
			//var fuck:Array = new Array( "iphon4", "iphone5", "ipad" );
			//list_all_panels.dataProvider = new DataProvider(sfUniversities); 
			//list_all_panels.addItem( {label:"label", data:"data"} );
			list_all_panels.addEventListener( Event.CHANGE, onPanelList );	
			//填加预览sprite
			ui_preview = new Sprite();
			addChild( ui_preview );
			
			tui = new UI(getResourcePathByLibraryPath, txt_debug );
			ui_preview.addChild( tui );
			
			file_ref = new FileReference();
			file_ref.addEventListener(Event.COMPLETE, onFileSaveComplete);
			
			file_cpp = new FileReference();
			file_cpp.addEventListener( Event.COMPLETE, onFileCppSaveComplete );
		}
		
		public static function isEnableJSFL():Boolean{
			try{
				MMExecute( "'fl;'" );
				return true;
			}catch( e:* ){
			}
			return false;
		}
			
		private static function runJSFL(jsfl:String, code:String):String{
			var ret:String;
			try {
				//ret = MMExecute("fl.runScript(fl.configURI + 'WindowSWF/" + jsfl + "', " + code + ");");
				//var scr:String = "fl.runScript(fl.configURI + '"+ jsfl + "');";
				var scr:String = "fl.runScript(fl.configURI + '"+ jsfl + "', " + code + ");";
				trace( scr );
				ret = MMExecute( scr );
			}catch(_e:Error){
			}
			return ret;
		}
		
		private function onSchemeChange( e:Event ):void{
			current_scheme =  ComboBox(e.target).selectedItem.data;
			trace( "current_scheme: " + current_scheme );
		}
		
		//清空面板list组件
		private function clearPanelList():void{
			for( var i:int = list_all_panels.length -1; i>=0; --i ){
         		list_all_panels.dataProvider.removeItemAt( i ); 
        	} 
		}
		
		public function pushDebugInfo( str:String ):void{
			txt_debug.text += str;
			txt_debug.verticalScrollPosition = txt_debug.maxVerticalScrollPosition;
		}
		
		public function pushCppInfo( str:String ):void{
			txt_result_cpp.text += str;
		}
		
		private function pushPanelNameToList( pname:String ):void{
			list_all_panels.addItem( {label:pname, data:pname} );
		}
				
		private function onExprotCurrentLayer( e:MouseEvent ):void{
			var isportrait:String = radio_portrait.selected ? "1" : "0";
			current_xml = runJSFL( JSFL_URL, "'export_current_layer', 'ui_panel', '" + current_scheme + "', '" + isportrait + "'" );
			//trace( current_xml );
			txt_result_xml.text = current_xml;
			
			refreshPanelList();
		}

		private function onExprotVisibleLayer( e:MouseEvent ):void{
			var isportrait:String = radio_portrait.selected ? "1" : "0";
			current_xml = runJSFL( JSFL_URL, "'export_visible_layer', 'ui_panel', '" + current_scheme + "', '" + isportrait + "'" );
			//trace( current_xml );
			txt_result_xml.text = current_xml;
			
			refreshPanelList();
		}
		
		private function onExprotAllLayer( e:MouseEvent ):void{
			//trace( "fuck" );
			//runJSFL( JSFL_URL, "'trace', 'fuck you'" );
			var isportrait:String = radio_portrait.selected ? "1" : "0";
			current_xml = runJSFL( JSFL_URL, "'export_all_layer', 'ui_panel', '" + current_scheme + "', '" + isportrait + "'" );
			//trace( current_xml );
			txt_result_xml.text = current_xml;
			
			refreshPanelList();
		}
		
		private function refreshPanelList():void{
			//create preview panels
			tui.clear();
			tui.parseXML( XML(txt_result_xml.text) );
			pushDebugInfo( "panels count" + tui.npanels + "\n" );
			convertXMLToCpp( XML(txt_result_xml.text) );
			
			//clear preview list
			clearPanelList();
			for( var i:String in tui.ui_panels ){
				pushDebugInfo( "panel " + i + " " + tui.ui_panels[i] + "\n" );
				pushPanelNameToList( i );
			}
			
			radio_view_ui.selected = true;
			radio_view_ui.dispatchEvent( new MouseEvent( MouseEvent.CLICK ) );			
		}
		
		private function onPreview( e:MouseEvent ):void{
		}
		
		private function getResourcePathByLibraryPath( libpath:String ):String{
			var url:String = runJSFL( JSFL_URL, "'getFilePathByLibraryPath', '"+ libpath + "'" );
			return url;
		}

		private function onRadioGroupView( e:MouseEvent ):void{
			txt_result_xml.visible = radio_view_xml.selected;
			txt_result_cpp.visible = radio_view_cpp.selected;
			ui_preview.visible = radio_view_ui.selected;			
			if( radio_view_ui.selected ){
				pushDebugInfo( "preview" + tui.currentShowPanelName() + "\n" );
				ui_preview.graphics.beginFill( 0x000000 );
				var sw:int = 0;
				var sh:int = 0;
				if( current_scheme == "iphone4" ){
					sw = 320; sh = 480;
				}
				ui_preview.graphics.drawRect( 0, 0, sw, sh );
				ui_preview.graphics.endFill();				
				ui_preview.x = 0;
				ui_preview.y = 0;
				ui_preview.removeChild( tui );
				ui_preview.addChild( tui );
			}
		}
		private function onViewXML( e:MouseEvent ):void{
			txt_result_xml.visible = !txt_result_xml.visible;
		}

		private function onDebugInfo( e:MouseEvent ):void{
			txt_debug.visible = !txt_debug.visible;
		}

		private function onPanelList( e:Event ):void{
			if( list_all_panels.selectedItem != null ){
				pushDebugInfo( "selected " + list_all_panels.selectedItem.data + "\n" );
				tui.showPanel( list_all_panels.selectedItem.data );
			}
		}
		
		private function onSaveXml( e:Event ):void{
			var str:String = txt_result_xml.text;
			str = str.replace( /img_iphone\//g, "" );
			str = str.replace( /img_ipad\//g, "" );
			
			var crlf:String = String.fromCharCode(0x0D, 0x0D);    
			var regEx:RegExp = new RegExp(crlf, "g");    
			str = str.replace(regEx, String.fromCharCode(0x0D, 0x0A)); 
			
			file_ref.save( str, "tui_" + current_scheme + ".xml" );
		}
		
		private function getSavePath( e:Event ):void{
			
		}

		private function onSaveGameUIEvent( e:Event ):void{
			saveGameUIEventCPP( null );
		}

		private function saveGameUIEventCPP( filename:String ):void{
			
		}
		
		private function onFileSaveComplete( e:Event ):void{
			pushDebugInfo( "file xml save complete" );
			
			var str:String = txt_result_cpp.text;
			var crlf:String = String.fromCharCode(0x0D, 0x0D);    
			var regEx:RegExp = new RegExp(crlf, "g");    
			str = str.replace(regEx, String.fromCharCode(0x0D, 0x0A)); 

			file_cpp.save( str, "gameuievent.h" );
		}
		
		private function onFileCppSaveComplete( e:Event ):void{
			pushDebugInfo( "file h save complete" );
		}
		
		private function onFileRefError( e:Event ):void{
			
		}

		private function onTestXMLToUI( e:MouseEvent ):void{
			//txt_result_xml.text = "<ui></ui>";
			//var strxml:XML= new XML( txt_result_xml.text );

			var str:String = "<?xml version='1.0' encoding='utf-8'?>" +
				"<ui version='1.0' name='ui_fuck'>" +
				"<scheme name='iphone4' screen_width='320' screen_height='480'></scheme>" +
				"<control name='panel_fuck' type='panel' x='160' y='240' ox='160' oy='240' width='320' height='480'>" +
				"<control type='image' image='res/menu_background.png' x='-160' y='-240' ox='0' oy='0' width='320' height='480'></control>" +
				"<control name='ok' type='button' image='res/clock-hd.png' click_event='click_ok' x='-77.65' y='208.05' ox='39.65' oy='11.5' width='71' height='24'></control>" +
				"<control name='cancel' type='button' image='res/clock-hd.png' click_event='click_cancel' x='86.4' y='208.05' ox='39.65' oy='11.5' width='71' height='24'></control>" +
				"</control>" +
				"<control type='image' image='res/blank.png' x='147.95' y='43.95' ox='0' oy='0' width='46' height='46'>" + 
				"<control name='panel_level' type='panel' x='160' y='240' ox='160' oy='240' width='320' height='480'>" +
				"<control type='image' image='res/menu_background.png' x='-160' y='-240' ox='0' oy='0' width='320' height='480'></control>" +
				"<control name='help' type='button' image='res/clock-hd.png' click_event='click_help' x='-77.65' y='208.05' ox='39.65' oy='11.5' width='71' height='24'></control>" +
				"</control>" +				
				"</control>" +
				"</ui>";
			var strxml:XML= XML( str );
			txt_debug.text = "";
			convertXMLToCpp( strxml );
		}
		
		private function resetCppText():void{
			txt_result_cpp.text = "";
			control_names = null;
			control_names = new Dictionary();
			event_cb_table = "";			
		}
		
		private function convertXMLToCpp( xml:XML ):void{
			resetCppText();

			getSchemeElement( xml.scheme );
			getControlElement( xml.control, xml );


			pushCppInfo( "/********************************************************************/\r\n" );
			pushCppInfo( "/*      THIS FILE IS GENERATED BY FLASHCS, DO NOT EDIT PLEASE       */\r\n" );
			pushCppInfo( "/********************************************************************/\r\n\r\n" );
			
			pushCppInfo( "#ifndef GAMEUIEVENT_H\r\n" );
			pushCppInfo( "#define GAMEUIEVENT_H\r\n\r\n" );

			pushCppInfo( "/** controls name */\r\n" );
			for each( var v:String in control_names ){
				pushCppInfo( v );
			}
			pushCppInfo( "\r\n" );
			
			pushCppInfo( "/** all tui events defined here */\r\n" );
			pushCppInfo( "static TuiEventCallBackTable tui_event_cb_table[] = { \r\n" );
			
			pushCppInfo( event_cb_table );
			pushCppInfo( "};\r\n" );
			
			pushCppInfo( "#endif//GAMEUIEVENT_H" );
		}
		
		private function getSchemeElement( xml:XMLList ):void{
			pushDebugInfo( "scheme:" + xml.@name + "\n" );
		}
		
		private function getControlElement( xml:XMLList, father:XML ):void {
			if ( xml ) {
				//get current node attribute
				for ( var i:int = 0; i < xml.length(); ++i ) {
					//pushDebugInfo( xml[i].@type + " " + xml[i].@name + "\n" );
					
					if( xml[i].@name != null ){
						var sname:String = xml[i].@name;
						if( sname != "" ){
							control_names[sname] = "#define s_t_" + sname + " " + "\"" + sname + "\"\r\n";
						}
					}
					
					//record events
					if( xml[i].@type == "button" ){
						if( xml[i].@click_event != null ){
							var e:String = father.@name + "_" + xml[i].@click_event;
							//var cb:String = e.split( "_" ).join( "" );
							//pushDebugInfo( ">>>" + father.@name + "\n" );
							var cb:String = e;
							event_cb_table +="\t{ \"" + e + "\", tuievent_cb(GameUIController::on_event_" + cb + ") },\r\n";
						}
					}
					
					//get child element
					getControlElement( xml[i].control, xml[i] );
				}
			}
		}
	}
}
