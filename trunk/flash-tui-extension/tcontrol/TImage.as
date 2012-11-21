package tcontrol
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.geom.Rectangle;
	import flash.net.URLLoader;
	import flash.net.URLRequest;

	/** 
	 * 图片控件,显示一张图形,所有需要显示图片的控件都从这里继承
	 * 如果有图片,那么图片的宽和高由资源决定,否则可以手动设置一个宽高值
	 * 有图片的控件,不用在外部显示调用drawControl,如果设置
	 */
	
	public class TImage extends TControl
	{
		protected var img:Bitmap = null;
		public function TImage()
		{
			super();
		}
		
		public override function getClassName():String
		{
			return "TImage";
		}
		
		public override function drawControl():void
		{
			super.drawControl();
		}
	
		/** 图片的宽和高由资源决定 **/
		public override function setSize(vw:Number, vh:Number):void
		{
			if( img )	
				super.setSize( img.width, img.height );
			else
				super.setSize( vw, vh );
		}

		/** 设置图片, 这里最终可以由统一的资源管理 **/
		public function setImage( url:String ):void
		{
			var loader:Loader = new Loader();
			loader.load( new URLRequest( url ) );
			loader.contentLoaderInfo.addEventListener( Event.COMPLETE, loaderCompleteHandle );
		}
		
		/** 通过bitmap设置图片 **/
		public function setImageWithBitmap( bmp:Bitmap ):void {
			img = bmp;
			addChild( img );
			/** 图片的宽和高由资源图片决定 **/
			setSize( img.width, img.height );
			/** 如果有背景色,画背景色,因为画背景色时候需要宽和高,这里需要先加载资源才能得到宽和高 **/
			if( !img )
				drawControl();
		}
		
		/** 设置图片为bmp的某一个矩形区域 **/
		public function setImageWithClip( bmp:Bitmap, cx:int, cy:int, cw:int, ch:int ):void {
			img = bmp;
			addChild( img );
			img.scrollRect = new Rectangle( cx, cy, cw, ch );
			//setSize( cw, ch );
			super.setSize( cw, ch )
		}
		
		public function setImageClip( cx:int, cy:int, cw:int, ch:int ):void {
			if( img ){
				img.scrollRect = new Rectangle( cx, cy, cw, ch );
				//setSize( cw, ch );
				super.setSize( cw, ch )
			}
		}
		
		protected function loaderCompleteHandle( e:Event ):void
		{
			img = e.target.content;
			addChild( img );
			//setChildIndex( img, 0 );
			trace( e.target.content.bitmapData );
			img.smoothing = true;
			/** 图片的宽和高由资源图片决定 **/
			setSize( img.width, img.height );
			
			/** 如果有背景色,画背景色,因为画背景色时候需要宽和高,这里需要先加载资源才能得到宽和高 **/
			//drawControl();
		}
	}
}