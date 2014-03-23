package tcontrol 
{
	import flash.events.MouseEvent;
	import tevent.TEvent;
	/**
	 * ...
	 * @author tpf
	 */
	public class TSimpleButton extends TLabel
	{
		/** 按钮被点击时发出的事件 **/
		private var eventClick:TEvent = null;
		
		public function TSimpleButton() 
		{
			super();
			buttonMode = true;
			/** 使用手形图标 **/
			useHandCursor = true;
			setSize( 50, 20 );
			
			addEventListener( MouseEvent.CLICK, onMouseClick );
		}
		
		public override function getClassName():String
		{
			return "TSimpleButton";
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
			if ( getDisable() )
				return;
			/** 发送该事件 **/
			if( eventClick )
			{
				/** 这里拷贝一个事件发送,因为事件发送一次就不能用了 **/
				var te:TEvent = new TEvent( eventClick.type, this, eventClick.eventBody, eventClick.bubbles, eventClick.cancelable );
				te.dispatch();
			}
		}
	}

}