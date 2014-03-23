package tcontrol
{
	import flash.events.TextEvent;
	import flash.text.TextField;
	import flash.text.engine.TextElement;

	/**
	 * 标题
	 * 可以放在其他控件里当标题用
	 * 主要作用是显示一行文字,不可换行
	 * 
	 * label字体的位置:居中显示
	 * 当Label不加载图片的时候,如果手动设置了label的宽高,那么以手动设置的宽高为label的宽高
	 * 如果没有手动设置宽高,那么以字体的宽高为label的宽高
	 * 如果加载了图片,以图片的宽高为label的宽高
	 */
	public class TLabel extends TText
	{
		public function TLabel()
		{
			super();
	
			text.multiline = false;
			text.wordWrap = false;

			/** 文本框默认大小 **/
			text.width = 100;
			text.height = 20;
		}
		
		public override function getClassName():String
		{
			return "TLabel";
		}
		
		public override function drawControl():void
		{
			super.drawControl();

			if( text )
			{
				showTextByAlignment();
			}
		}

		public override function setText( str:String ):void
		{
			super.setText( str );
			showTextByAlignment();
		}
		
		/** 字体居中 **/
		protected function textAlignmentCenter():void
		{
			if( !text )
				return;

			/** 文本框的宽高自动和字体的宽高相同,不然按钮的大小就不一定为按钮的大小了,可能是文本框的大小 **/
			text.width = text.textWidth + 4;
			text.height = text.textHeight + 4;
			
			/** 如果没有image, 也没有设置宽高,那么,宽高自动高为字体的宽高 **/
			if( !getWidth() || !getHeight() )
				setSize( text.textWidth, text.textHeight );
			
			/** 文字居中 **/
			var txtWidth:Number = text.textWidth;
			var txtHeight:Number = text.textHeight;
			var lw:Number = getWidth();
			var lh:Number = getHeight();
			var diffx:int = (lw - txtWidth) / 2;
			var diffy:Number = (lh - txtHeight) /2;
			text.x = diffx - 2;
			text.y = diffy - 2;
		}
		
		protected function showTextByAlignment():void
		{
			textAlignmentCenter();
		}

		protected function linkListener( e:TextEvent ):void
		{
			trace( "text link" );
		}
		
	}
}