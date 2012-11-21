package tcontrol
{
	//控件的对齐方式
	public class TControlAlignment
	{
		/**
		 * 对齐方式,是指定子控件以怎样的方式向父控件对齐
		 * 以水平方向为例:
		 * 当为左对齐时,相对于父控件偏移10时,表示以子控件的左边为准,向右移10
		 * +-------------+
		 * |+-------+    |
		 * +-------------+
		 * 
 		 * 当为中对齐时,相对于父控件偏移10时,表示以子控件宽度的中间为准,向右
		 * 移10,这时如果子控件很宽,子控件有可以左边出了父控件
		 *      +-------------+
		 *  +-------+         |
		 *      +-------------+
		 * 当为右对齐时,相对于父控件偏移10时,表示以子控件的右边为准,从父控件的右边向左移10
		 * +--------------+
		 * |     +-------+|
		 * +--------------+ 
		 */
		
		//无指定,默认为上
		public static const VERTICAL_NONE:int   = 0;	
		
		//竖直方向 上 对齐, 控件的y为准,向父控件或画布对齐
		public static const VERTICAL_TOP:int = VERTICAL_NONE; 
		
		//竖直方向 中间 对齐, 以控件的 y + h/2为准,向父控件或画布对齐
		public static const VERTICAL_CENTER:int = 1; 
		
		//竖直方向 下 对齐, 以控件的 y + h为准,向父控件或画布对齐
		public static const VERTICAL_BOTTOM:int = 2; 
		
		//水平方向, 无指定,默认为左,向父控件或画布对齐
		public static const HORIZON_NONE:int = 3;   
		
		//水平方向 左 对齐, 以控件的 x 为准,向父控件或画布对齐
		public static const HORIZON_LEFT:int = HORIZON_NONE; 
		
		//水平方向 中 对齐, 以控件的 x + w/2为准,向父控件或画布对齐
		public static const HORIZON_CENTER:int = 4; 
		
		//水平方向 右 对齐, 以控件的 x + w为准,向父控件或画布对齐
		public static const HORIZON_RIGHT:int = 5;  
		
		public function TControlAlignment()
		{
		}
	}
}