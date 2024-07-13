package com.vsdevelop.air.extension.ndi 
{
	import flash.external.ExtensionContext;
	import flash.utils.ByteArray;
	/**
	 * ...
	 * @author Ray.lei
	 */
	public class NDIlib 
	{
		private var _extCtx:ExtensionContext;
		private var _name:String;
		private var _intptr:Number;
		private var _is_video:Boolean;
		private var _is_audio:Boolean;
		private var _groups:String;
		
		
		public function get name():String 
		{
			return _name;
		}
		
		public function get groups():String 
		{
			return _groups;
		}
		
		public function get is_video():Boolean 
		{
			return _is_video;
		}
		
		public function get intptr():Number 
		{
			return _intptr;
		}
		
		public function get is_audio():Boolean 
		{
			return _is_audio;
		}
		
		public function NDIlib(_extCtx:ExtensionContext, _intptr:Number, _name:String, _groups:String, _is_video:Boolean, _is_audio:Boolean) 
		{
			this._extCtx = _extCtx;
			this._intptr = _intptr;
			this._name = _name;
			this._groups = _groups;
			this._is_video = _is_video;
			this._is_audio = _is_audio;
		}
		
		
		
		public function sendByteArray(byteArray:ByteArray, width:int, height:int):Boolean{
			
			if (_extCtx && _intptr){
				if (byteArray.length == width * height * 4){
					
					return _extCtx.call("ANE_NDIlib_send_send_video_v2",_intptr,width,height,byteArray) as Boolean;
				}
			}
			return false;
		}
		
		
		public function destroy():void{
			if (_extCtx && _intptr)
			{
				if (_extCtx.call("ANE_NDIlib_send_destroy", _intptr) as Boolean){
					trace("NDIlib_send_destroy Ok");
				}else{
					trace("NDIlib_send_destroy Error");
				}
				_intptr = 0;
			}
			
		}
	}

}