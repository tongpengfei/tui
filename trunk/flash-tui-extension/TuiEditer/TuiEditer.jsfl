
/////////////////////////////////////////////////////////////////////
ExportElementXMLErrorStrings = {};
ExportElementXMLErrorStrings.kNoOpenedFla = "no opened fla document!";
ExportElementXMLErrorStrings.kNullDocument = "export error, empty document!";
ExportElementXMLErrorStrings.kNoSetScheme = "export error, no such scheme!";
ExportElementXMLErrorStrings.kCanNotFindLibraryItem = "can not find library item!";
/////////////////////////////////////////////////////////////////////
/*给函数原型增加一个extend函数，实现继承*/  
Function.prototype.extend = function(superClass){  
	if(typeof superClass !== 'function'){  
		throw new Error('fatal error:Function.prototype.extend expects a constructor of class');  
	}  

	var F = function(){}; //创建一个中间函数对象以获取父类的原型对象  
	F.prototype = superClass.prototype; //设置原型对象  
	this.prototype = new F(); //实例化F, 继承父类的原型中的属性和方法，而无需调用父类的构造函数实例化无关的父类成员  
	this.prototype.constructor = this; //设置构造函数指向自己  
	this.superClass = superClass; //同时，添加一个指向父类构造函数的引用，方便调用父类方法或者调用父类构造函数  
          
    return this;  
};

/**
 @brief 打印
 @param str:string 字符串
 */
function trace( str ){
	fl.outputPanel.trace( str );
}

/** 清屏 */
function cls(){
	fl.outputPanel.clear();
}

/** 保留小数 */
function formatNumber( num, retain){
	retain = retain || 100;
	return Math.round(num * retain) / 100;
}

/** 把一个库目录里的资源转换为资源的绝对目录 */
function getFilePathByLibraryPath( path ){
	if( path == null || path == "" || path == undefined ){
		alert( "getFilePathByLibraryPath 无效的参数" );
	}
	var lib = fl.getDocumentDOM().library;
	var item_index = lib.findItemIndex( path );
	if( item_index < 0 ){
		alert( ExportElementXMLErrorStrings.kCanNotFindLibraryItem + ": " + path );
	}
	var item = lib.items[item_index];
	var url = item.sourceFilePath;
	url = url.replace( "file:///", "" );
	url = url.replace( "|", ":" );
	//for ( var i in item ){
	//	trace( "" + i + "" + ":" + item[i] );
	//}
	//trace( "转换路径 " + path + "===>>" + url );
	return url;
}

/**
 @brief 获取当前文档的时间轴
 @return Timeline object
 */
getCurrentTimeline = function(){
	try{
		return fl.getDocumentDOM().getTimeline();
	}catch(e){
		alert( ExportElementXMLErrorStrings.kNoOpenedFla );
	}
	return null;
}

/** 
 @brief 判断一个帧是否是关键帧, 原理是每个关键帧总是一序列帧的第一帧
 @param frame:Frame object 帧对象
 @param frameIndex:int 该帧的索引号
 @return boolean
 */
isKeyFrame = function( frame, frameIndex ){
	if( !frame ) return false;
	if( frame.startFrame == frameIndex ){
		return true;
	}
	return false;
}

/**
 @brief 把某个图层的关键帧枚举出来
 @param layer: Layer object 图层对象
 @param startFrameIndex:int 起始帧数，不一定是从0开始
 @param endFrameIndex:int 结束帧数
 @return vector<int>: 范围[startFrameIndex,endFrameIndex)之间的关键帧索引号数组
 */
getKeyframeIndices = function(layer, startFrameIndex, endFrameIndex){
	if( !layer ) return [];
	var list = [];
	for (var frameIndex=startFrameIndex; frameIndex<endFrameIndex; frameIndex++){
		var frame = layer.frames[frameIndex];
		var isFirstFrame = (frameIndex == startFrameIndex);
		var isKeyframe = (isFirstFrame || frame.startFrame == frameIndex);
	//	if (isKeyframe){
	//		list[frameIndex] = true;
	//	}else{
	//		list[frameIndex] = false;
	//	}
		if( isKeyframe ){
			list.push( frameIndex );
		}
	}
	return list;
}


/**
 @brief 获取某个图层的所有关键帧
 @param layer:Layer object 图层对象
 @return vector<Frame object>
 */
getKeyframeObjects = function( layer ){
	if( !layer ) return [];
	var list = [];
	var index = 0;
	for each( frame in layer.frames ){
		if( frame.startFrame == index ){
			list.push( frame );
		}
		index++;
	}
	return list;
}

/**
 @brief 获取一个帧上的所有元素
 @param frame:Frame object 帧对象
 @return vector<Element object> 该帧上的所有元素
 */
getElementObjects = function( frame ){
	if( !frame ) return [];
	return frame.elements;
}

/**
 @brief 获取元素的类型
 @param element:Element object 元素对象
 @return string 类型
 */
getElementType = function(element){
	if (!element) return '';

	var elementType = '';
	var libraryItem = element.libraryItem;
	// element.elementType: "shape", "text", "instance", or "shapeObj"
	// item.itemType: "undefined", "component", "movie clip", "graphic", "button", "folder", "font", "sound", "bitmap", "compiled clip", "screen", and "video".
	switch (element.elementType){
	case 'shape' :
		{
			//NOTE: a drawing object is both a group and a drawing object, so check it first
			elementType = element.isRectangleObject ? 'rectangle object'
						: element.isOvalObject ? 'oval object'
						: element.isDrawingObject ? 'drawing object'
						: element.isGroup ? 'group'
						: 'shape';
		}break;
	case 'shapeObj' :
		{
			elementType = 'shape object'; 
		}break;
	case 'text' :
		{
			elementType = 'text'; 
		}break;
	case 'instance' :
		{
			if (element.symbolType)
				elementType = element.symbolType;
			else if (libraryItem.itemType && libraryItem.itemType != 'undefined')
				elementType = libraryItem.itemType;
		}break;
	}
	return elementType;
}

/** 精减小数 */
roundToTwip = function(value){
	return Math.round(value*20) / 20;
}

/** 获取元素的x坐标 */
getX = function(element){
	return roundToTwip(element.transformX);
}

/** 获取元素的y坐标 */
getY = function(element){
	return roundToTwip(element.transformY);
}

/** 设置元素的x坐标 */
setX = function(element, x){
	element.transformX = x;
}

/** 设置元素的y坐标 */
setY = function(element, y){
	element.transformY = y;
}

/////////////////////////////////////////////////////////////////////
/** 默认的xml 节点名字 */
XMLNode = {};
XMLNode.root = "root";
XMLNode.control = "control";
XMLNode.scheme = "scheme";

/////////////////////////////////////////////////////////////////////
/** xml类 */
TXML = function( nodename ){
	/** 父节点 */
	this.parent = null;
	/** 子节点 */
	this.children = [];
	/** 所有需要输出的属性 */
	this.attributes = {};
	
	this.xml = "";
	this.nodeName = nodename==null ? XMLNode.root : nodename;
	
	this.init();
}

TXML.prototype.init = function(){
}

TXML.prototype.setNodeName = function( name ){
	this.nodeName = name;
}

TXML.prototype.getNodeName = function(){
	return this.nodeName;
}

TXML.prototype.addChild = function( o ){
	if( !o ){
		alert( o );
	}
	o.parent = this;
	this.children.push( o );
}

TXML.prototype.registerAttribute = function( k, v ){
	this.attributes[k] = v;
//	for( i in this.attributes ){
//		trace( "<<< " + i + ":" + this.attributes[i] );
//	}
}

TXML.prototype.setAttribute = function( k, v ){
	if( this.attributes[k] == null ){
		alert( "没有属性: " + k );
	}
	this.attributes[k] = v;
}

TXML.prototype.getAttribute = function( k ){
	if( this.attributes[k] == null ){
		alert( "没有属性: " + k );
	}
	return this.attributes[k];
}

TXML.prototype.getTabCount = function(){
	if( this.parent != null ){
		return this.parent.getTabCount() + 1;
	}
	return 0;
}

TXML.prototype.pushXMLAttribution = function( key, value ){
	if( value == null ) return;
	var str = value.toString();
	if( str=="" ) return;
	this.xml += " " + key + "=" + "\"" + value + "\"";
}


TXML.prototype.pushXML = function( str ){
	this.xml += str;
}

TXML.prototype.outputControlXML = function(){
	//trace( "{" + "name" + ":" + this.attributes["name"] + "}" );
	for( k in this.attributes ){
		this.pushXMLAttribution( k, this.attributes[k] );
	}
}

TXML.prototype.outputChildrenXML = function(){
	for each( c in this.children ){
		//trace( "child: " + c.getAttribute( UIControlAttribute.kName ) + " parent: " + c.parent.getAttribute( UIControlAttribute.kName ) );
		c.outputXML();
		//trace( "child2: " + c.getAttribute( UIControlAttribute.kName ) + " parent: " + c.parent.getAttribute( UIControlAttribute.kName ) );
	}
}

TXML.prototype.outputTabXML = function(){
	var n = this.getTabCount();
	for( var i = 0; i<n; ++i ){
		this.pushXML( "\t" );
	}
}

TXML.prototype.outputXML = function(){
	//trace( "{" + "name" + ":" + this.attributes["name"] + "}" );
	//this.xml = "";
	this.outputTabXML(); this.pushXML( "<" + this.nodeName ); this.outputControlXML(); this.pushXML( ">" );
	if( this.children.length > 0 ){
		this.pushXML( "\n" );
	}
	this.outputChildrenXML();
	if( this.children.length > 0 ){
		this.outputTabXML(); 
	}
	this.pushXML( "</" + this.nodeName + ">\n" );
	if( this.parent ){
		this.parent.pushXML( this.xml );
	}
	//trace( "{" + "name" + ":" + this.attributes["name"] + "}" );
	return this.xml;
}

UIXML = function(uiname){
	UIXML.superClass.call( this, "ui" );
	
	this.registerAttribute( "name", (uiname == null ? "uipanel" : uiname) );
}

UIXML.extend( TXML );
UIXML.prototype.init = function(){
	UIXML.superClass.prototype.init.call(this);

	this.registerAttribute( "version", "1.0" );
}


/////////////////////////////////////////////////////////////////////
/** ui主题的属性 */
SchemeAttribute = {};
/** 主题的名字, 如: iphone4, iphone5, ipad */
SchemeAttribute.kName = "name";
SchemeAttribute.kIsRetina = "is_retina";
SchemeAttribute.kScreenWidth = "screen_width";
SchemeAttribute.kScreenHeight= "screen_height";

/** 支持的控件类型 */
UIControlType = {};
UIControlType.kPanel = "panel";
UIControlType.kImage = "image";
UIControlType.kButton = "button";

/////////////////////////////////////////////////////////////////////
/** 控件的属性 */
UIControlAttribute = {};
/** 控件的名字,在程序中控制用 */
UIControlAttribute.kName = "name";
/** 控件的类型 */
UIControlAttribute.kType = "type";
/** 是否可托动 */
UIControlAttribute.kEnableDrag = "enable_drag";
/** 用到的图片 */
UIControlAttribute.kImage = "image";
/** 点击事件 */
UIControlAttribute.kClickEvent = "click_event";
/** 坐标 */
UIControlAttribute.kX = "x";
UIControlAttribute.kY = "y";
/** 图层决定zorder */
UIControlAttribute.kZ = "z";
/** 中心点坐标 */
UIControlAttribute.kOriginX = "ox";
UIControlAttribute.kOriginY = "oy";
/** 宽高 */
UIControlAttribute.kWidth = "width";
UIControlAttribute.kHeight = "height";
/** 缩放 */
UIControlAttribute.kScaleX = "scalex";
UIControlAttribute.kScaleY = "scaley";
/** 角度 */
UIControlAttribute.kAngle = "angle";

/**
 @brief 控件基类
 */
UIControl = function(){
	UIControl.superClass.call(this, XMLNode.control );
}

UIControl.extend( TXML );
UIControl.prototype.init = function(){
	for( k in UIControlAttribute ){
		this.registerAttribute( UIControlAttribute[k], "" );
	}
//	this.setNodeName( "control" );
}

/////////////////////////////////////////////////////////////////////
/**
 @brief 面板,所有UI都得放在面板里
 */
UIPanel = function(){
	UIPanel.superClass.call(this);
}

UIPanel.extend( UIControl );
UIPanel.prototype.init = function(){
	UIPanel.superClass.prototype.init.call(this);
	this.setAttribute( UIControlAttribute.kType, UIControlType.kPanel );
	//this.setAttribute( UIControlAttribute.kEnableDrag, 0 );
}

/////////////////////////////////////////////////////////////////////
/**
 @brief 图片,只显示一个图片
 */
UIImage = function(){
	UIImage.superClass.call(this);
}

UIImage.extend( UIControl );
UIImage.prototype.init = function(){
	UIImage.superClass.prototype.init.call(this);
	this.setAttribute( UIControlAttribute.kType, UIControlType.kImage );
}

/**
 @brief 按钮
 */
UIButton = function(){
	UIButton.superClass.call(this);
}
UIButton.extend( UIControl );
UIButton.prototype.init = function(){
	UIButton.superClass.prototype.init.call(this);
	this.setAttribute( UIControlAttribute.kType, UIControlType.kButton );
}

/////////////////////////////////////////////////////////////////////
kSchemeIPhone4 = "iphone4";
kSchemeIPhone5 = "iphone5";
kSchemeIPad = "ipad";

Scheme = function(){
	Scheme.superClass.call(this, XMLNode.scheme );
}

Scheme.extend( TXML );
Scheme.prototype.init = function(){
	Scheme.superClass.prototype.init.call(this);
	for( k in SchemeAttribute ){
		this.registerAttribute( SchemeAttribute[k], "" );
	}
//	this.setNodeName( "scheme" );
}

/** 横向 */
Scheme.prototype.setModeToLandscape = function(){
}

/** 纵向 */
Scheme.prototype.setModeToPortrait = function(){
}

SchemeIPhone4 = function(){
	SchemeIPhone4.superClass.call(this);
}
SchemeIPhone4.extend( Scheme );
SchemeIPhone4.prototype.init = function(){
	SchemeIPhone4.superClass.prototype.init.call(this);
	this.setAttribute( SchemeAttribute.kName, kSchemeIPhone4 );
	this.setAttribute( SchemeAttribute.kIsRetina, 0 );
	this.setModeToPortrait();
}

/** 横向 */
SchemeIPhone4.prototype.setModeToLandscape = function(){
	this.setAttribute( SchemeAttribute.kScreenWidth, 480);
	this.setAttribute( SchemeAttribute.kScreenHeight, 320);
}

/** 纵向 */
SchemeIPhone4.prototype.setModeToPortrait = function(){
	this.setAttribute( SchemeAttribute.kScreenWidth, 320);
	this.setAttribute( SchemeAttribute.kScreenHeight, 480);
}

SchemeIPad = function(){
	SchemeIPad.superClass.call(this);
}
SchemeIPad.extend( Scheme );
SchemeIPad.prototype.init = function(){
	SchemeIPad.superClass.prototype.init.call(this);
	this.setAttribute( SchemeAttribute.kName, kSchemeIPad );
	this.setAttribute( SchemeAttribute.kIsRetina, 0 );
	this.setModeToLandscape();
}

/** 横向 */
SchemeIPad.prototype.setModeToLandscape = function(){
	this.setAttribute( SchemeAttribute.kScreenWidth, 1024);
	this.setAttribute( SchemeAttribute.kScreenHeight, 768);
}

/** 纵向 */
SchemeIPad.prototype.setModeToPortrait = function(){
	this.setAttribute( SchemeAttribute.kScreenWidth, 768);
	this.setAttribute( SchemeAttribute.kScreenHeight, 1024);
}

/////////////////////////////////////////////////////////////////////
ExportUITool = function(){
	this.xml = null;
}

/** 导出UI数据 */
ExportUITool.prototype.exportUIXML = function( doc ){
	if( !doc ){
		alert( ExportElementXMLErrorStrings.kNullDocument );
		return null;
	}

	//取得时间轴,遍历图层
	var timeline = doc.getTimeline();
	var layerindex = 0;
	for each( layer in timeline ){
		this.exportLayer( layer, layerindex++ );
	}

	//trace( this.xml );
	//trace( this.xml.outputXML() );
}

/** 导出一个图层的数据 */
ExportUITool.prototype.exportLayer = function( layer, layerIndex ){
	var frameindex = 0;
	for each( frame in layer ){
		this.exportFrame( frame, frameindex++ );
	}
}

/** 导出一帧的数据 */
ExportUITool.prototype.exportFrame = function( frame, frameIndex ){
	var elementindex = 0;
	for each( element in frame ){
		this.exportElement( element, elementindex );
	}
}

/** 导出一帧的元素 */
ExportUITool.prototype.exportElement = function( element ){
	//判断是什么类型的元素，导出相应元素	
}

/** 导出一个MovieClip的数据 */
ExportUITool.prototype.exprotMovieClip = function( mc ){

}

/////////////////////////////////////////////////////////////////////
/** 
 @brief 把fla文件转换为xml
  		flash里的 element.libraryItem.itemType有类型映射:
		panel: movie clip, 
		image: graphic
		button:button
 */
kExportLayerCurrent = 0; //导出当前层
kExportLayerVisible = 1; //导出可见层
kExportLayerAll = 2;	 //导出所有层

FlaToXML = function(){
	/** TXML,保存xml */
	this.txml = null;
	/** 当前处理的fla文件, Document Object */
	this.obj_fla = null;
	
	/** 导出哪些层,默认为导出所有层 */
	this.export_layer_type = kExportLayerAll;
	
	this.init();
}

FlaToXML.prototype.init = function(){
}

/**
 @brief 设置导出哪些层
 @param v{ kExportLayerCurrent, kExportLayerVisible, kExportLayerAll }
 */
FlaToXML.prototype.setExportLayerType = function( v ){
	this.export_layer_type = v;
}

FlaToXML.prototype.isExportLayerCurrent = function(){
	return this.export_layer_type == kExportLayerCurrent;
}

FlaToXML.prototype.isExportLayerVisible = function(){
	return this.export_layer_type == kExportLayerVisible;
}

FlaToXML.prototype.isExportLayerAll = function(){
	return this.export_layer_type == kExportLayerAll;
}

/** 判断element是否为panel */
FlaToXML.prototype.elementIsPanel = function( element ){
	var type = element.libraryItem.itemType;
	if( "movie clip" == type ) return true;
	if( "graphic" == type ) return true;
	return false;
}

/** 判断element是否为image */
FlaToXML.prototype.elementIsImage = function( element ){
	var type = element.libraryItem.itemType;
	if( "bitmap" == type ) return true;
	return false;
}

/** 判断element是否为button */
FlaToXML.prototype.elementIsButton = function( element ){
	var type = element.libraryItem.itemType;
	if( "button" == type ) return true;
	return false;
}

/** 获取element的xml类型 */
FlaToXML.prototype.getElementUIType = function( element ){
	if( this.elementIsPanel( element ) ) return UIControlType.kPanel;
	if( this.elementIsImage( element ) ) return UIControlType.kImage;
	if( this.elementIsButton( element ) ) return UIControlType.kButton;
	return "undfine";
}

/** 
 @brief 把objfla:Document Object转换为xmlfile:string xml文件 
 @param objfla:Document Object
 @param xmlfile:string 目标文件名
 @param uiname:string UI名字
 @param scheme:Scheme 布局类型new SchemeIPone4(), new SchemeIPhone5()等等
 */
FlaToXML.prototype.convert = function( objfla, xmlfile, uiname, scheme ){
	if( objfla == null ){
		alert( ExportElementXMLErrorStrings.kNoOpenedFla );
	}
	if( scheme == null ){
		alert( ExportElementXMLErrorStrings.kNoSetScheme );
	}

	this.obj_fla = objfla;
	this.txml = new UIXML( uiname );
	this.txml.addChild( scheme );
	
	if( xmlfile == "" || xmlfile == null ){
		xmlfile = objfla.name.split(".")[0] + ".xml";
	}
	
	var flaname = this.obj_fla.name;
	trace( "FlaToXML: 开始转换fla[" + flaname + "]文件为xml:[" + xmlfile + "] ui文件" );
	
	if( this.isExportLayerCurrent() ){
		//导出当前层
		var timeline = objfla.getTimeline();
		if( timeline.currentLayer < 0 || timeline.currentLayer == undefined ){
			//alert( "当前没有选中的图层!" );
			return;
		}
		var current_layer_index = timeline.currentLayer;
		trace( "当前选中的是第" + timeline.currentLayer + "层" );
		var layer = timeline.layers[current_layer_index];
		this.fetchElementFromLayer( layer, current_layer_index, this.txml );

	}else if( this.isExportLayerVisible() ){
		//导出可见层
		var nlayer = objfla.getTimeline().layerCount;
		for( var layer_index = nlayer-1; layer_index >= 0; --layer_index ){
			var layer = objfla.getTimeline().layers[layer_index];
			if( layer.visible ){
				this.fetchElementFromLayer( layer, layer_index, this.txml );
			}
		}
		
	}else{
		//导出全部
		this.fetchElement( objfla.getTimeline(), this.txml );		
	}
	this.outputXML();
}

/** 转换元素为UICnotrol */
FlaToXML.prototype.convertElement = function( element ){
	var e_xml = null;
	if( this.elementIsPanel( element ) ){
		e_xml = this.convertMC( element );
	}else if( this.elementIsImage( element ) ){
		e_xml = this.convertImage( element );
	}else if( this.elementIsButton( element ) ){
		e_xml = this.convertButton( element );
	}else{
		alert( "未知的类型: " + element.instanceType + " " + element.libraryItem.itemType );
	}
	return e_xml;
}

/** 填充一般属性 */
FlaToXML.prototype.fullNormalAttirbute = function( xml, element ){	
	xml.setAttribute( UIControlAttribute.kX, formatNumber( element.x ) );
	xml.setAttribute( UIControlAttribute.kY, formatNumber( element.y ) );
	
	var ox = element.x - element.left;
	var oy = element.y - element.top;
	xml.setAttribute( UIControlAttribute.kOriginX, formatNumber(ox) );
	xml.setAttribute( UIControlAttribute.kOriginY, formatNumber(oy) );
	
	xml.setAttribute( UIControlAttribute.kWidth, formatNumber(element.width) );
	xml.setAttribute( UIControlAttribute.kHeight, formatNumber(element.height) );
}

/** 转换movie clip */
FlaToXML.prototype.convertMC = function( mc ){
	var panel_xml = new UIPanel();
	//trace( "把" + mc.libraryItem.name + "转换为panel" );
	
	panel_xml.setAttribute( UIControlAttribute.kName, mc.name );
	this.fullNormalAttirbute( panel_xml, mc );
	//获取mc的timeline
	var timeline = mc.libraryItem.timeline;
	this.fetchElement( timeline, panel_xml );
	return panel_xml;
}

/** 转换image */
FlaToXML.prototype.convertImage = function( image ){
	var xml_img = new UIImage();
	//trace( "把" + image.libraryItem.name + "转换为image" );
	xml_img.setAttribute( UIControlAttribute.kImage, image.libraryItem.name );
	this.fullNormalAttirbute( xml_img, image );
	return xml_img;
}

/** 转换button */
FlaToXML.prototype.convertButton = function( button ){
	var xml_btn = new UIButton();
//	trace( "把" + button.libraryItem.name + "转换为button" );
	
//	button.libraryItem.addData( UIControlAttribute.kClickEvent, "string", "s_click_event_" + button.libraryItem.name );
//	trace( "按钮事件: " + button.libraryItem.getData( UIControlAttribute.kClickEvent ) );
//	xml_btn.setAttribute( UIControlAttribute.kClickEvent, button.libraryItem.getData( UIControlAttribute.kClickEvent ) );
	
//	trace( "实例名: " + button.name + "item.name: " + button.libraryItem.name );
	
	xml_btn.setAttribute( UIControlAttribute.kName, button.name );
	xml_btn.setAttribute( UIControlAttribute.kClickEvent, "click_" + button.name );
	
	this.fullNormalAttirbute( xml_btn, button );

	//trace( ">>>按钮有 " + timeline.layerCount + "层,有" + layer.frameCount + "帧");
	var image = button.libraryItem.timeline.layers[0].frames[0].elements[0];
	xml_btn.setAttribute( UIControlAttribute.kImage, image.libraryItem.name );
	return xml_btn;
}

/**
 @brief 从某个layer里提取元素
 */
FlaToXML.prototype.fetchElementFromLayer = function( layer, layer_index, parentxml ){
	var nframe = layer.frameCount;
	for( var frame_index = 0; frame_index < nframe; ++frame_index ){
		var frame = layer.frames[frame_index];
			
		var nelement = frame.elements.length;
		for( var element_index = 0; element_index < nelement; ++element_index ){
			var element = frame.elements[element_index];
			trace( "第" + layer_index + "层" + layer.name + ",第" + frame_index + "帧,第" + element_index + "个元素是:" + element.name
					  + "类型[" + element.libraryItem.itemType + "]将被转换成"
					  + this.getElementUIType( element ) + "实例名" + element.libraryItem.name );
			var exml = this.convertElement( element );
			parentxml.addChild( exml );
		}
	}
}

/**
 @brief 从timeline里提取element,并填加到父节点 
 @param parentxml:TXML 父节点
 */
FlaToXML.prototype.fetchElement = function( timeline, parentxml ){
	//trace( "FlaToXML: 提取fla里的元素" );
	//获取时间轴
	//var time_line = this.obj_fla.getTimeline();
	var time_line = timeline;
	var nlayer = time_line.layerCount;
	
//	for( var layer_index = 0; layer_index < nlayer; ++layer_index ){
	for( var layer_index = nlayer-1; layer_index >= 0; --layer_index ){
		var layer = time_line.layers[layer_index];

		var nframe = layer.frameCount;
		
		for( var frame_index = 0; frame_index < nframe; ++frame_index ){
			var frame = layer.frames[frame_index];
			
			var nelement = frame.elements.length;
			for( var element_index = 0; element_index < nelement; ++element_index ){
				var element = frame.elements[element_index];
				if( element.libraryItem == null ){
					continue;
				}
				trace( "第" + layer_index + "层" + layer.name + ",第" + frame_index + "帧,第" + element_index + "个元素是:" + element.name
					  + "类型[" + element.libraryItem.itemType + "]将被转换成"
					  + this.getElementUIType( element ) + "实例名" + element.libraryItem.name );
				//trace( "类型是:[" + element.libraryItem.itemType +"]将被转换成" + this.getElementUIType( element ) );
				//trace( "实例名:" + element.libraryItem.name );
				var exml = this.convertElement( element );
				parentxml.addChild( exml );
			}
		}
	}
}

FlaToXML.prototype.outputXML = function(){
	//trace( "FlaToXML: 输出xml文件" );
	this.txml.outputXML();
	//trace( this.txml.xml );
}

/**
 @brief 导出当前打开的fla文件xml
 @param uiname:string uiname
 @param schemename:string 主题名
 @param isportrait:bool 是否竖屏
 */
export_current_layer = function( uiname, schemename, isportrait ){
	var scheme = null;
	if( schemename == kSchemeIPhone4 ){
		scheme = new SchemeIPhone4();
	}else if( schemename == kSchemeIPad ){
		scheme = new SchemeIPad();
	}else{
		alert( "未设定主题" );
		return;
	}

	if( isportrait == "1" ){
		scheme.setModeToPortrait();
	}else{
		scheme.setModeToLandscape();
	}

	var convert = new FlaToXML();
	convert.setExportLayerType( kExportLayerCurrent );
	convert.convert( fl.getDocumentDOM(), null, uiname, scheme );
	return convert.txml.xml;
}

/**
 @brief 导出所有可见的图层
 @param uiname:string uiname
 @param schemename:string 主题名
 */
export_visible_layer = function( uiname, schemename, isportrait ){
	var scheme = null;
	if( schemename == kSchemeIPhone4 ){
		scheme = new SchemeIPhone4();
	}else if( schemename == kSchemeIPad ){
		scheme = new SchemeIPad();
	}else{
		alert( "未设定主题" );
		return;
	}
	
	if( isportrait == "1" ){
		scheme.setModeToPortrait();
	}else{
		scheme.setModeToLandscape();
	}
	
	var convert = new FlaToXML();
	convert.setExportLayerType( kExportLayerVisible );
	convert.convert( fl.getDocumentDOM(), null, uiname, scheme );
	return convert.txml.xml;
}

/**
 @brief 导出所有图层
 @param uiname:string uiname
 @param schemename:string 主题名
 */
export_all_layer = function( uiname, schemename, isportrait ){
	var scheme = null;
	if( schemename == kSchemeIPhone4 ){
		scheme = new SchemeIPhone4();
	}else if( schemename == kSchemeIPad ){
		scheme = new SchemeIPad();
	}else{
		alert( "未设定主题" );
		return;
	}

	if( isportrait == "1" ){
		scheme.setModeToPortrait();
	}else{
		scheme.setModeToLandscape();
	}

	var convert = new FlaToXML();
	convert.setExportLayerType( kExportLayerAll );
	convert.convert( fl.getDocumentDOM(), null, uiname, scheme );
	return convert.txml.xml;
}

//cls();
//trace( export_current_layer( "testui", "iphone4", "1" ) );
//trace( export_visible_layer( "testui", "iphone4" ) );
//trace( export_all_layer( "testui", "iphone4" ) );

//trace( getFilePathByLibraryPath( "res/img/blank.png" ) );

/** 测试FlaToXML */
//var convert = new FlaToXML();
//convert.convert( fl.getDocumentDOM(), "aaa.xml", "testui", new SchemeIPhone4() );
//convert.convert( fl.getDocumentDOM(), null, "testui", new SchemeIPhone4() );

/**
 @brief 打印一个图层的数据
 @param layer:Layer object 图层
 @return xml </layer>
 */

/**
 @brief 测试输出UI数据
 */
/*
var control = new UIPanel();
control.setAttribute( UIControlAttribute.kName, "rootpanel" );
control.setAttribute( UIControlAttribute.kImage, "background.png" );
control.setAttribute( UIControlAttribute.kX, 0 );
//control.outputXML();
//trace( control.xml );

var son = new UIImage();
son.setAttribute( UIControlAttribute.kName, "son_image" );
son.setAttribute( UIControlAttribute.kX, 10 );

var son2 = new UIImage();
son2.setAttribute( UIControlAttribute.kName, "son_image2" );
son2.setAttribute( UIControlAttribute.kX, 20 );

var son3 = new UIButton();
son3.setAttribute( UIControlAttribute.kName, "son_image3" );
son3.setAttribute( UIControlAttribute.kX, 30 );
son2.addChild( son3 );

son.addChild( son2 );

control.addChild( son );


var scheme = new SchemeIPhone4();
var xml = new UIXML( "ui_hello" );
xml.addChild( scheme );
xml.addChild( control );
trace( xml.outputXML() );
//var tool = new ExportUITool(xml);
//tool.setScheme( scheme );
//tool.setRootControl( control );
//tool.exportUIXML( fl.getDocumentDOM() );
*/


//继承的实现
/*
Base = function(){
	this.init();
}

Base.prototype.getName = function(){
	return this.name;
}

Base.prototype.init = function(){
	trace( "call base init" );
	this.name = "base";
}

Sub = function(){
	Sub.superClass.call(this);	//这里必须调用一下你类的构造
}

Sub.extend( Base ); //要先写继承，再定义函数
Sub.prototype.init = function(){
	Sub.superClass.prototype.init.call(this);	//调用父类的init
	trace( "call sub init" );
	this.name = "sub" + Sub.superClass.prototype.getName.call(this);
}

var base = new Base();
trace( base.getName() );
var sub = new Sub();
trace( sub.getName() );
*/