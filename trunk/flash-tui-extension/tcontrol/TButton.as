package tcontrol
{
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Rectangle;
	
	import tevent.TEvent;
	import tevent.TEventController;

	/** 
	 * 按钮
	 * 包括正常,焦点,按下,不可用四个状态
	 * 鼠标不在按钮上时是正常状态
	 * 鼠标在按钮上时是焦点状态
	 * 鼠标点下按钮时时按下状态
	 * 不可用时不接收点击事件
	 * 四个状态可以用四个图片表示
	 * 鼠标点下时,按钮发出被点击事件,此事件归控件事件管理,方便其他模块也触发同样的事件,为的是把行为和动作分开,
	 * 如按下按钮用触发一个事件,按下另一个按钮也会触发该事件,只要发出相同的事件就可以被相同的处理了
	 * 
	 * 使用时需要先设置事件 setEventClick
	 */
	public class TButton extends TLabel
	{
		/** 按钮被点击时发出的事件 **/
		private var eventClick:TEvent = null;
		
		/** 按钮的状态定义 **/
		public static const TBUTTON_STATE_NORMAL:int = 0;
		public static const TBUTTON_STATE_OVER:int = 1;
		public static const TBUTTON_STATE_PUSHDOWN:int = 2;
		public static const TBUTTON_STATE_DISABLE:int = 3;
		public static const TBUTTON_STATE_MAX:int = 4;
		
		/** 按钮当前的状态 **/
		private var currentState:int = TBUTTON_STATE_NORMAL;
		
		public function TButton()
		{
			super();
			buttonMode = true;
			/** 使用手形图标 **/
			useHandCursor = true;
			
			currentState = TBUTTON_STATE_NORMAL;
			
			setSize( 50, 20 );
			
			addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown );
			addEventListener( MouseEvent.MOUSE_UP, onMouseUp );
			addEventListener( MouseEvent.MOUSE_OVER, onMouseOver );
			addEventListener( MouseEvent.MOUSE_OUT, onMouseOut );
			addEventListener( MouseEvent.CLICK, onMouseClick );
		}
		
		public override function getClassName():String
		{
			return "TButton";
		}
		
		/** 图片的宽和高由资源决定 **/
		public override function setSize(vw:Number, vh:Number):void
		{
			/** 按钮的宽为图片宽的1/4,因为每个状态占1/4个图片 **/
			if( img )	
			{
				controlWidth = img.width / 4;
				controlHeight = img.height;
				setButtonState( currentState );
			}
			else
				super.setSize( vw, vh );
		}
		
		public override function drawControl():void
		{
			super.drawControl();
		}

		/** 按钮被禁用后就不能点击了 **/
		public override function setDisable(v:Boolean):void
		{
			super.setDisable( v );
			if( v )
				setButtonState( TBUTTON_STATE_DISABLE );
			else {
				setButtonState( TBUTTON_STATE_NORMAL );
			}
		}
		
		/** 设置按钮被点击时发出的事件 **/
		public function setEventClick( e:TEvent ):void
		{
			eventClick = e;
			eventClick.whosevent = this;
		}
		
		/** 获取按钮被点击时发出的事件 **/
		protected function getEventClick():TEvent
		{
			return eventClick;
		}

		protected function onMouseClick( e:MouseEvent ):void
		{
			/** 停止向上层传递事件 **/
			e.stopPropagation();
			if( TBUTTON_STATE_DISABLE == getButtonState() )
				return;
			/** 发送该事件 **/
			if( eventClick )
			{
				/** 这里拷贝一个事件发送,因为事件发送一次就不能用了 **/
				var te:TEvent = new TEvent( eventClick.type, this, eventClick.eventBody, eventClick.bubbles, eventClick.cancelable );
				te.dispatch();
			}
		}
		
		protected function onMouseDown( e:MouseEvent ):void
		{
			e.stopPropagation();
			if( TBUTTON_STATE_DISABLE == getButtonState() )
				return;
			//trace( "down" );
			setButtonState( TBUTTON_STATE_PUSHDOWN );
//			setBackgroundColor( 0xff0000 );
//			drawControl();
		}
		
		protected function onMouseUp( e:MouseEvent ):void
		{
			e.stopPropagation();
			if( TBUTTON_STATE_DISABLE == getButtonState() )
				return;
			//trace( "up" );
			setButtonState( TBUTTON_STATE_OVER );
//			setBackgroundColor( 0xffff00 );
//			drawControl();
		}
		
		protected function onMouseOver( e:MouseEvent ):void
		{
			e.stopPropagation();
			if( TBUTTON_STATE_DISABLE == getButtonState() )
				return;
			//trace( "over" );
			setButtonState( TBUTTON_STATE_OVER );
//			setBackgroundColor( 0xffff00 );
//			drawControl();
		}
		
		protected function onMouseOut( e:MouseEvent ):void
		{
			e.stopPropagation();
			if( TBUTTON_STATE_DISABLE == getButtonState() )
				return;
			//trace( "out" );
			setButtonState( TBUTTON_STATE_NORMAL );
//			setBackgroundColor( 0x00ff00 );
//			drawControl();
		}
		
		private function getButtonStateOffsetX():Number
		{
			var offset:int = currentState * getWidth(); 
			return 	offset;
		}

		/** 设置按钮的状态,不同的状态显示不同的图片 **/
		protected function setButtonState( state:int ):void
		{
			currentState = state;
			/** 显示图片的哪一个矩形区域 **/
			if( img )
				img.scrollRect = new Rectangle( getButtonStateOffsetX(), 0, getWidth(), getHeight() );
		}
		
		/** 获取按钮当前的状态 **/
		protected function getButtonState():int
		{
			return currentState;	
		}
		
		/** 按钮的宽度需要设置为1/4个图片宽度,因为按钮有四个状态 **/
		protected override function loaderCompleteHandle( e:Event ):void
		{
			img = e.target.content;
			addChild( img );
			
			/** 按钮的宽和高由资源图片决定 **/
			setSize( img.width, img.height );

			/** 设置按钮的状态 **/
			setButtonState( getButtonState() );
			
			/** 如果有背景色,画背景色,因为画背景色时候需要宽和高,这里需要先加载资源才能得到宽和高 **/
			//drawControl();
		}
		
	}
}