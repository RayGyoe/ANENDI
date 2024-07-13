del Windows-x86\ANENDI.dll
del Windows-x86-64\ANENDI.dll

copy /y %pathtome%..\native\ANENDI\x64\Release\ANENDI\ANENDI.dll "./Windows-x86-64"
copy /y %pathtome%..\native\ANENDI\Release\ANENDI\ANENDI.dll "./Windows-x86"