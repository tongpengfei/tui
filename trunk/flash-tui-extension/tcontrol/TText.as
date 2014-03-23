package tcontrol
{
	import flash.events.TextEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextFormat;
	
	import tevent.TEventController;

	/**
	 * TText文本框,显示多行文字,行太多的时候有滚动条
	 */
	public class TText extends TImage
	{
		protected var text:TextField = null;
		/** 链接的监听函数 **/
		protected var callback_link:Function = null;
//		protected var format:TextFormat = null;
		
		public function TText()
		{
			super();
			
			text = new TextField();
			text.multiline = true;
			text.wordWrap = true;
			text.border = false;
			text.alwaysShowSelection = false;
			text.mouseEnabled = true;
			text.selectable = false;
			text.mouseWheelEnabled = false;
//			text.autoSize = TextFieldAutoSize.LEFT;

		//	text.background = true;
		//	text.backgroundColor = 0x0000ff;
			
			/** 文本框默认大小 **/
			text.width = 100;
			text.height = 50;
			addChild( text );
			
//			format = new TextFormat();
//			format.bold = false;
//			format.color = 0x000000;
//			format.align = "left";
//			format.leading = 0;
		}
		
		public override function getClassName():String
		{
			return "TText";
		}
		
		public override function setSize(vw:Number, vh:Number):void
		{
			if( img )	
			{
				controlWidth = img.width;
				controlHeight= img.height;
			}
			else
			{
				controlWidth = vw;
				controlHeight = vh;
			}
			
			text.width = getWidth();
			text.height = getHeight();
		}
		
		public override function drawControl():void
		{
			super.drawControl();
			/** 把文字放在最上层 **/
			if( text )
			{
				if( img )
					setChildIndex( img, 0 );
			}
		}
		
		public function setText( str:String ):void
		{
			clear();
			addText( str );
		}
		
		public function getText():String
		{
			if( !text )
				return "";
			return text.htmlText;
		}
		
		/** 清空文本 **/
		public function clear():void
		{
			if( text )
				text.htmlText = "";
			return;
			/** 清空链接事件 **/
			if( callback_link )
				text.removeEventListener( TextEvent.LINK, callback_link );	
		}
		
		public function setSelectable( v:Boolean ):void {
			text.selectable = v;
		}
		
		public function getSelectable():Boolean {
			return text.selectable;
		}
		
		/*********************************文本内容相关************************************/
		/**
		 * 填加文本
		 */
		public function addText( str:String ):void
		{
			text.htmlText += str;
//			text.setTextFormat( format );
		}
		
		/**
		 * 填加link文本
		 * @param event:String 点击文本后触发的事件
		 * @param str:String 文本
		 * @color:String 文本的颜色,默认为绿色
		 */
		public function addLinkString( event:String, str:String, color:String="#00ff00" ):void
		{
			text.htmlText += "<a href='event:" + event + "'><u><font size='12' color='" + color + "'>"
							+ str + "</font></u></a>";
//			text.setTextFormat( format );
		}
		
		public function setLinkCallBack( cb:Function ):void
		{
			if( null != callback_link )
				text.removeEventListener( TextEvent.LINK, callback_link );
			callback_link = cb;
			text.addEventListener( TextEvent.LINK, callback_link );
		}
		
		/**
		 * 填加一个图片
		 */
		public function addImage( url:String, vwidth:int, vheight:int ):void
		{
			text.htmlText += "a<img	align='left' hspace='0' vspace='0' width='" + vwidth + "' height='" + vheight + "' src='" + url + "'></img><br>s";
		//	text.setTextFormat( format );
		}
	}
}