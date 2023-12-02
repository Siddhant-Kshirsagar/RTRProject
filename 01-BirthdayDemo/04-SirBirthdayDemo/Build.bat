CLS

cl.exe /c /EHsc OGL.cpp SGK_Demo.cpp hrishikeshScene.cpp
rc.exe OGL.rc
link.exe OGL.obj SGK_Demo.obj hrishikeshScene.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
OGL.exe

