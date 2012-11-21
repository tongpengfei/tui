package tcontrol
{
	import flash.display.BitmapData;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	/**
	 * 面板,是所有控件依附的容器,一个UI可以由一个单独的面板组成 
	 * 面板可以托动,所有需要托动的控件都要依附于一个面板
	 * 面板不接受点击事件,面板主要作用是其他控件的容器,其他所有控件都不可以托动
	 * 可以有背景图
	 */
	public class TPanel extends TImage
	{
		/** 是否可托动 **/
		private var dragEnable:Boolean = false;
		
		public function TPanel()
		{
			super();
			
			/** 设置初始大小 **/
			setSize( 100, 50 );
			
			/** 这里每个面板都需要立刻监听鼠标事件,如果子控件不监听鼠标事件,
			 * 假如鼠标点在子控件上,事件就会往上传到父控件,引起父控件托动 
			 */
			addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown );
			addEventListener( MouseEvent.MOUSE_UP, onMouseUp );
		}
		
		public override function getClassName():String
		{
			return "TPanel";
		}

		public override function drawControl():void
		{
			super.drawControl();
		}

		/** 设置是否可以托动 **/
		public function setDragEnable( enable:Boolean ):void
		{
			dragEnable = enable;
		}
		
		/** 获取是否可以托动 **/
		public function getDragEnable():Boolean
		{
			return dragEnable;
		}
		
		/** 默认的鼠标按下是托动 **/
		protected function onMouseDown( e:MouseEvent ):void
		{
			/** 停止继续向上层传递事件,否则在托子控件的时候,父控件会跟着动 **/
			e.stopPropagation();
			if( dragEnable )
				startDrag();
		}
		
		/** 默认的鼠标抬起是停止托动 **/
		protected function onMouseUp( e:MouseEvent ):void
		{
			/** 停止继续向上层传递事件 **/
			e.stopPropagation();
			if( dragEnable )
				stopDrag();
		}
		
//		/** 默认的鼠标点击事件,什么也不做,只是不让事件继续往上传 **/
//		protected function onMouseClick( e:MouseEvent ):void
//		{
//			/** 停止继续向上层传递事件 **/
//			e.stopPropagation();
//			trace( "[DEBUG] TPanel click" );
//		}
	}
}