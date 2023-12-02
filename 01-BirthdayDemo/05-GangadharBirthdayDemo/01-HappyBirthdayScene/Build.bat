CLS

cl.exe /c /EHsc BirthdayScene.c
rc.exe OGL.rc
link.exe BirthdayScene.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
BirthdayScene.exe

