package tcontrol
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.events.TimerEvent;
	import tcontrol.TImage;
	import tcontrol.TPanel;
	
	/**
	 * ...
	 * @author tpf
	 */
	public class TImageNumber extends TImage 
	{
		private var all_number:TImage = null;
		private var imgs:Array = null;
		private var nsplit:int = 0; //img要分成多少份
		private var nbit:int = 0; //最多显示多少位数字
		private var space:Number = 0; //每个数字间隔多少
		private var srcbmp:Bitmap = null;
		private var nnumber:int = 0;
		public function TImageNumber( bmp:Bitmap, nsplit:int, nbit:int, space:Number, initnumber:int ) 
		{
			super();
			this.nsplit = nsplit;
			this.nbit = nbit;
			this.space = space;
			this.nnumber = initnumber;
			srcbmp = bmp;
		}
		public function init():void {
			var fw:Number = getParentControl().getWidth();
			var fh:Number = getParentControl().getHeight();
			var w:Number = srcbmp.width / nsplit;
			var h:Number = srcbmp.height;
			//var aw:Number = w * nbit;
			var aw:Number = w * nbit + space * (nbit-1);
			setImageWithClip( new Bitmap(null), 0, 0, aw, srcbmp.height );
			imgs = new Array();
			for ( var i:int = 0; i < nbit; ++i ) {
				var img:TImage = new TImage();
				img.setImageWithClip( new Bitmap(srcbmp.bitmapData), 0, 0, w, srcbmp.height );
				imgs.push( img );
				addChild( img );
				//var mw:Number = (nbit-1 - i) * (w+space) - space/2;
				var mw:Number = (nbit-1 - i) * (w+space);
				var mh:Number = 0;
				img.setRelationLocation( mw, mh );
			}
			setNumber( nnumber );
		}
		public function setNumber( v:int ):void {
			nnumber = v;
			var num:int = nnumber;
			
			for ( var i:int = 0; i < nbit; ++i ) {
				
				var img:TImage = imgs[i] as TImage;
				var r:int = num % 10;
				num /= 10;
				var w:Number = img.getWidth();
				img.setImageClip( r * w, 0, w, srcbmp.height );
			}
		}
	}

}