CLS

cl.exe /c /EHsc EndCredit.c
rc.exe OGL.rc
link.exe EndCredit.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
EndCredit.exe

