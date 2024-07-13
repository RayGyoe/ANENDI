package com.vsdevelop.air.extension.ndi
{
	import flash.events.ErrorEvent;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.StatusEvent;
	import flash.external.ExtensionContext;
	import com.vsdevelop.air.extension.ndi.NDIlib;
	
	public class ANENDI extends EventDispatcher
	{
		private static var _instance:ANENDI;
		private var _extCtx:ExtensionContext;
		private var _isSupported:Boolean;
		
		private var _actionScriptData:Object = {};
		
		public function ANENDI()
		{
			if (!_instance)
			{
				_extCtx = ExtensionContext.createExtensionContext("com.vsdevelop.air.extension.ndi", null);
				
				if (_extCtx != null)
				{
					
					_isSupported = _extCtx.call("isSupported") as Boolean;
					
					if(_isSupported)
					{
						_extCtx.actionScriptData = actionScriptData;
					}
					
					_extCtx.addEventListener(StatusEvent.STATUS, onStatus);
				} else
				{
					trace('extCtx is null.'); 
				}
				_instance = this;
			}
			else
			{
				throw Error( 'This is a singleton, use getInstance, do not call the constructor directly');
			}
		}

		public function get actionScriptData():Object
		{
			return _actionScriptData;
		}
		
		public static function getInstance() : ANENDI
		{
			return _instance ? _instance : new ANENDI();
		}
		
		public function get isSupported():Boolean
		{
			return _isSupported;
		}

		
		
		public function get context():ExtensionContext{
			
			if(_isSupported)return _extCtx;
			return null;
		}
		
		/**
		 * 事件 
		 * @param event
		 * 
		 */		
		protected function onStatus(event:StatusEvent):void
		{
			if (event.level == "d3derror"){
				
			}
		}
		
		
		public function debug(value:Boolean = false):void
		{
			if (isSupported){
				_extCtx.call("isDeBug",value);
			}
		}

		
		/**
		 * 
		 * @param	name
		 * @param	groups
		 * @param	is_video
		 * @param	is_audio
		 * @return NDIlib
		 */
		public function create_NDI(name:String="", groups:String = "", is_video:Boolean = true, is_audio:Boolean = true) :NDIlib
		{
			if (isSupported){
				var intptr:Number = _extCtx.call("ANE_NDIlib_send_create", name, groups, is_video, is_audio) as Number;
				if (intptr){
					return new NDIlib(_extCtx, intptr, name, groups, is_video, is_audio);
				}
			}
			return null;
		}
		
		
	}
}