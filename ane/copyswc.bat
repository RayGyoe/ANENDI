rd /s /q swc
del ANENDI.swc

copy /y %pathtome%..\swc\lib\ANENDI.swc .

unzip.exe ANENDI.swc -d swc

copy /y swc\library.swf .
copy /y library.swf default
copy /y library.swf Windows-x86
copy /y library.swf Windows-x86-64

rd /s /q swc