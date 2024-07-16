## ANENDI

Let AdobeAIR screen/image pass to OBS via NDI（https://ndi.video/for-developers/ndi-sdk/）

##### example:

```
if (ANENDI.getInstance().isSupported)
{
	if (ndi)
	{
		ndi.destroy();
		ndiTimer.stop();
		ndiTimer.removeEventListener(TimerEvent.TIMER, ndiAppendFrame);
		ndiTimer = null;
		ndi = null;
		return;
	}
	ndi = ANENDI.getInstance().create_NDI("air_test1" + Math.random());
	if (ndi)
	{
		trace(ndi.intptr, ndi.name);
		
		if (!ndiTimer)
		{
			ndiTimer = new Timer(1000 / 24);
			ndiTimer.addEventListener(TimerEvent.TIMER, ndiAppendFrame);
			ndiTimer.start();
		}
	}
}
else
{
	trace("不支持ndi");
}

private function ndiAppendFrame(e:TimerEvent):void
{
	var byte:ByteArray = new ByteArray();
	var bitemapdata:BitmapData = new BitmapData(stage.stageWidth, stage.stageHeight, false);
	bitemapdata.draw(stage, null, null, null, null, true);
	byte.endian = Endian.LITTLE_ENDIAN;
	bitemapdata.copyPixelsToByteArray(bitemapdata.rect, byte);
	
	ndi.sendByteArray(byte, bitemapdata.width, bitemapdata.height);
	
	byte.clear();
}
```



##### Notice：

**Don't forget to copy "runtime-dll/x86" (according to the architecture) to the application runtime directory**

Debug：Please copy it to the AIRSDK/bin directory when debugging.
