package tevent
{
	import flash.events.Event;
	
	import tcontrol.TControl;
	
	public class TEvent extends Event
	{
		/** 谁发的事件 **/
		public var whosevent:*;
		/** 消息体 **/
		public var eventBody:*;
		
		public function TEvent(type:String, who:*, body:*=null, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
			whosevent = who; 
			eventBody = body;
		}
		
		public function dispatch():void
		{
			/** 注意这里事件只能发送一次,发完就不能发了,如果想重复发事件,就得拷贝一个副本,用副本发送 **/
			TEventController.I().dispater.dispatchEvent( this );
		}
	}
}