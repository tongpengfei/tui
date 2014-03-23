package tcontrol
{
	import flash.display.DisplayObject;
	import flash.display.Sprite;
	import flash.geom.PerspectiveProjection;
	
	public class TControl extends Sprite
	{
		/** 屏幕的宽和高 **/
		/** 当父控件为空的时候,以程序屏幕为标准 **/
		public static var SCREEN_WIDTH:Number = 0; 
		public static var SCREEN_HEIGHT:Number= 0;
	
		/** 标识符 **/
		public var tag:int = 0;
		
		/** 对齐方式 **/
		private var verticalAlignment:int = TControlAlignment.VERTICAL_NONE;
		private var horizonAlignment:int = TControlAlignment.HORIZON_NONE;
		
		/** 控件的宽,高, sprite里的width,height不靠谱,空容器时候无论如何都是0 **/
		protected var controlWidth:Number = 0;
		protected var controlHeight:Number = 0;
		
		/** 背景颜色 **/
		private var backgroundColor:int = 0xAAAAAA;
		
		/** 禁用 **/
		private var disable:Boolean = false;
		
		public function TControl()
		{
			super();
			buttonMode=false;
			/** 不使用手形指针 **/
			useHandCursor = false; 
		}
		
		/** 检查控件是否准备好,主要是检查必要的变量是否已经设置 **/
		public static function isAlready():Boolean
		{
			if( 0 == SCREEN_WIDTH )
			{
				trace( "[ERROR] has to set screen_width" );
				return false;
			}
			if( 0 == SCREEN_HEIGHT )
			{
				trace( "[ERROR] has no set screen_height" );
				return false;
			}
			
			return true;
		}
		
		/** 获取类的名字 **/
		public function getClassName():String
		{
			throw( "[ERROR] this function need to override" );
			return "??";
		}

		/** 获取父控件 **/
		public function getParentControl():TControl
		{
			if( parent && (parent as TControl) )
				return TControl(parent);
			return null;
		}
		
		/**
		 * 绘制该控件, 如果一个控件有图片,就不要在外部再调用该方法了,内部会自己处理
		 */
		public function drawControl():void
		{
			//	this.graphics.clear();
			this.graphics.beginFill(getBackgroundColor());
			this.graphics.drawRect(0,0,getWidth(),getHeight());
			this.graphics.endFill();
					
		}

		/** 设置是否禁用 **/
		public function setDisable( v:Boolean ):void
		{
			disable = v;
		}
		
		/** 获取是否禁用 **/
		public function getDisable():Boolean
		{
			return disable;
		}
		
		public function setSize( vw:Number, vh:Number ):void
		{
			controlWidth = vw;
			controlHeight = vh;
		}
		
		public function getWidth():Number
		{
			return controlWidth; 
		}
		
		public function getHeight():Number
		{
			return controlHeight;
		}
		
		/***********************************颜色相关**************************************/
		/**
		 * 设置背景色
		 */
		public function setBackgroundColor( color:int ):void
		{
			backgroundColor = color;
		}
		public function getBackgroundColor():int
		{
			return backgroundColor;
		}
		
		/***********************************位置相关**************************************/
		/**
		 * 设置绝对坐标,相对于画布左上角(0,0)点
		 */
		public function setAbsoluteLocation( vx:Number, vy:Number ):void
		{
			x = vx;
			y = vy;
		}
		
		/**
		 * 获取绝对x坐标
		 */
		public function getAbsoluteX():Number
		{
			var parentx:Number = 0;
			var pc:TControl = getParentControl(); 
			if( pc )
				parentx = pc.getAbsoluteX();
			return x + parentx;
		}
		
		/**
		 * 获取绝对y坐标
		 */
		public function getAbsoluteY():Number
		{
			var parenty:Number = 0;
			var pc:TControl = getParentControl(); 
			if( pc )
				parenty = pc.getAbsoluteY();				
			return y + parenty;
		}
		
		/**
		 * 设置相对坐标,相对于父控件左上角(0,0)点
		 */
		public function setRelationLocation( relatex:Number, relatey:Number ):void
		{
			setAbsoluteLocationByAlignment( relatex, relatey );
		}

		/**
		 * 获取相对x坐标
		 */
		public function getRelationX():Number
		{
			var pc:TControl = getParentControl(); 
			if( !pc )
				return x;
			var rx:Number = getAbsoluteX() - pc.getAbsoluteX();
			return rx;
		}
		
		/**
		 * 获取相对y坐标
		 */
		public function getRelationY():Number
		{
			var pc:TControl = getParentControl(); 
			if( !pc )
				return y;
			var ry:Number = getAbsoluteY() - pc.getAbsoluteY();
			return ry;
		}

		/**
		 * 设置相对于父控件的百分比位移,范围为[0.0,1.0] 
		 */
		public function setRelatePercentLocation( percentx:Number, percenty:Number ):void
		{
//			percentx = Math.max( 0, percentx );
//			percentx = Math.min( 1, percentx );
//			percenty = Math.max( 0, percenty );
//			percenty = Math.min( 1, percenty );
			
			/** 设置位置 **/
			var relatex:Number = relatePercentToIntX( percentx );
			var relatey:Number = relatePercentToIntY( percenty );
			setAbsoluteLocationByAlignment( relatex, relatey );
		}
		
		/**
		 * 获取相对于父控件的百分比位移,范围为[0,1]
		 */
		public function getRelatePercentLocationX():Number
		{
			var rx:Number = getRelationX();
			var percent:Number = relateIntToPercentX( rx );
			return percent;
		}
		
		public function getRelatePercentLocationY():Number
		{
			var ry:Number = getRelationY();
			var percent:Number = relateIntToPercentY( ry );
			return percent;
		}
		
		/**
		 * 设置对齐方式,竖直方向,水平方向
		 */
		public function setControlAlignment( vertical:int, horizon:int ):void
		{
			verticalAlignment = vertical;
			horizonAlignment = horizon;
		}
		
		/*******************************************************************************/
		/**
		 * 根据相对位移和对齐方式设置绝对坐标
		 */
		protected function setAbsoluteLocationByAlignment( relatex:Number, relatey:Number ):void
		{
			var pc:TControl = getParentControl(); 
			var pw:Number = 0;
			var ph:Number = 0;
			if( pc )
			{
				pw = pc.getWidth();
				ph = pc.getHeight();
			}
			else 
			{
				pw = SCREEN_WIDTH;
				ph = SCREEN_HEIGHT;
			}
			
			/** 水平 **/
			if( TControlAlignment.HORIZON_LEFT == horizonAlignment ){
				x = relatex;
			}else if( TControlAlignment.HORIZON_CENTER == horizonAlignment ){
				x = relatex - getWidth()/2;				
			}else if( TControlAlignment.HORIZON_RIGHT == horizonAlignment ){
				x = pw - relatex - getWidth();
			}
			
			/** 竖直 **/
			if( TControlAlignment.VERTICAL_TOP == verticalAlignment ){
				y = relatey;				
			}else if( TControlAlignment.VERTICAL_CENTER == verticalAlignment ){
				y = relatey - getHeight()/2;
			}else if( TControlAlignment.VERTICAL_BOTTOM == verticalAlignment ){
				y = ph - relatey - getHeight();
			}
		}
		
		/**
		 * 把相对浮点位移转为相对数值位移,就是把[0,1]转为以父宽度为准的[0,父宽];
		 */
		protected function relatePercentToIntX( percent:Number ):Number
		{
			/** TODO 得到场景的宽 **/
			var pc:TControl = getParentControl(); 
			var pw:Number = 0;
			if( pc )
				pw = pc.getWidth();
			else 
				pw = SCREEN_WIDTH;
			
			var offx:Number = pw * percent - this.getWidth()*0.5;
			return offx;
		}
		protected function relateIntToPercentX( relate:Number ):Number
		{
			/** TODO 得到场景的宽 **/
			var pc:TControl = getParentControl(); 
			var pw:Number = 0;
			if( pc )
				pw = pc.getWidth();
			else 
				pw = SCREEN_WIDTH;
			var percent:Number = relate / pw + this.getWidth()*0.5;
			return percent;
		}
		
		/**
		 * 把相对浮点位移转为相对数值位移,就是把[0,1]转为以父宽度为准的[0,父高];
		 */
		protected function relatePercentToIntY( percent:Number ):Number
		{
			/** TODO 得到场景的高 **/
			var pc:TControl = getParentControl(); 
			var ph:Number = 0;
			if( pc )
				ph = pc.getHeight();
			else
				ph = SCREEN_HEIGHT;
			var offy:Number = ph * percent - this.getHeight()*0.5;
			return offy;
		}
		protected function relateIntToPercentY( relate:int ):Number
		{
			/** TODO 得到场景的高 **/
			var pc:TControl = getParentControl(); 
			var ph:int = 0;
			if( pc )
				ph = pc.getHeight();
			else
				ph = SCREEN_HEIGHT;
			var percent:Number = relate / ph + this.getHeight()*0.5;
			return percent;
		}
		/////////////////////////////////////////////////////////////////////////////////
	}
}













