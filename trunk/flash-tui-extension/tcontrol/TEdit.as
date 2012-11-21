package tcontrol
{
	import flash.display.BlendMode;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFieldType;
	import flash.ui.Mouse;
	
	import tevent.TEvent;

	/**
	 * 输入框,可以输入文字,没啥特殊的
	 */
	public class TEdit extends TControl
	{
		/** 输入框可以输入的字符类型 **/
		public static const INPUT_TYPE_NUMBER:int = 0; /** 只能输入数字 **/
		public static const INPUT_TYPE_CHAR:int = 1;   /** 只能输入字符 **/
		public static const INPUT_TYPE_NUMBER_CHAR:int = 2; /** 只能输入数字和字符 **/
		public static const INPUT_TYPE_NUMBER_CHAR_SCORE:int = 3; /** 只能输入数字,字符和下划线 **/
		public static const INPUT_TYPE_NO_SPECIAL_SIGN:int = 4; /** 不允许特殊符号, !@#$%^&* **/
		
		/** 输入框 **/
		private var edit:TextField = null;
		
		/** 输入框的类型 **/
		private var inputType:int = INPUT_TYPE_NO_SPECIAL_SIGN;
		
		/** 按下回车后发送的事件 **/
		private var eventEndInput:TEvent = null;
		
		public function TEdit()
		{
			super();
			
			edit = new TextField();
			addChild( edit );
			edit.border = true;
			edit.borderColor = 0xffff00;
			edit.multiline = true;
			edit.wordWrap = true;
//			edit.background = true;
//			edit.backgroundColor = 0x00ff00;
			edit.type = TextFieldType.INPUT;
			/** 默认大小 **/
			setSize( 100, 20 );
			setInputType( INPUT_TYPE_NO_SPECIAL_SIGN );
			
			addEventListener( KeyboardEvent.KEY_UP, onKeyUp );
			addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown );
		}
		
		public override function getClassName():String
		{
			return "TEdit";
		}
		
		public override function drawControl():void
		{
			super.drawControl();
		}
		
		/** 图片的宽和高由资源决定 **/
		public override function setSize(vw:Number, vh:Number):void
		{
			super.setSize( vw, vh );
			edit.width = getWidth();
			edit.height = getHeight();
		}
		
		public override function setDisable(v:Boolean):void
		{
			super.setDisable( v );
			edit.mouseEnabled = !v;
		}
		
		/** 获取输入框的内容 **/
		public function getText():String
		{
			return edit.text;
		}
		
		public function setText( v:String ):void {
			edit.text = v;
		}
		
		/** 设置输入框的类型,数字或者字符 **/
		public function setInputType( v:int ):void
		{
			/**
			 * 除了数字其他都允许
			 * edit.restrict = "^0-9";
			 */

			inputType = v;
			switch( v )
			{
			case INPUT_TYPE_NUMBER:
				{
					/** 只允许输入数字 **/
					edit.restrict = "0-9";
				}break;
			case INPUT_TYPE_CHAR:
				{
					/** 只允许输入字母 **/
					edit.restrict = "a-zA-Z";
				}break;
			case INPUT_TYPE_NUMBER_CHAR:
				{
					/** 只允许输入数字,字母 **/
					edit.restrict = "0-9a-zA-Z";
				}break;
			case INPUT_TYPE_NUMBER_CHAR_SCORE:
				{
					/** 只允许输入数字,字母和下划线 **/
					edit.restrict = "0-9a-zA-Z_";
				}break;
			case INPUT_TYPE_NO_SPECIAL_SIGN:
				{
					/** 不能输入特殊字符, \\表示转译字符 **/
					edit.restrict = "^!@#$%\\^&*";
				}break;
			default:
				{
					trace( "[ERROR] TEdit unknown input type:" + v );
				}break;
			}
		}
		
		/** 获取输入框的类型 **/
		public function getInputType():int
		{
			return inputType;
		}
		
		/** 清空编辑框 **/
		public function clear():void
		{
			edit.text = "";
		}
		
		/** 设置结束输入时发送的事件,这里不加入callback,以防一个事件对应多个处理函数 **/
		public function setEventEndInput( e:TEvent ):void
		{
			eventEndInput = e;
			eventEndInput.whoevent = this;
		}

		protected function getEventEndInput():TEvent
		{
			return eventEndInput;
		}
		
		protected function onKeyUp( e:KeyboardEvent ):void
		{
			e.stopPropagation();
			/** 输入回车,就处理数据 **/
			if( e.keyCode == 13 && getEventEndInput() )
			{
				//edit.text = "";
				var te:TEvent = new TEvent( eventEndInput.type, this, edit.text, eventEndInput.bubbles, eventEndInput.cancelable );
				te.dispatch();
			}
		}

		protected function onMouseDown( e:MouseEvent ):void
		{
			e.stopPropagation();
		}
	}
}