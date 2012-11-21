package tevent
{
	import flash.events.EventDispatcher;

	public class TEventController
	{
		private static var controller:TEventController;
		
		public var dispater:EventDispatcher;

		public function TEventController()
		{
			dispater = new EventDispatcher();
		}
		public static function I():TEventController
		{
			if( controller )
				return controller;
			else
				return controller = new TEventController();
		}
		public static function AddEventListener( type:String, fun:Function ):void
		{
			I().dispater.addEventListener( type, fun );
		}
		public static function RemoveEventListener( type:String, fun:Function ):void
		{
			I().dispater.removeEventListener( type, fun );
		}
		
	}
}