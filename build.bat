@echo off

rem for dynamic linking
set compilerFlags=-nologo -EHsc -fp:fast -O2 -Oi -WX -W4 -wd4100 -wd4244 -wd4458 -wd4996 -FC -Z7 
rem for static linking
rem set compilerFlags=-nologo -MD -nologo -EHsc -fp:fast -O2 -Oi -WX -W4 -wd4100 -wd4244 -wd4458 -wd4996 -FC -Z7 

rem for dynamic linking
set linkerFlags=-incremental:no -opt:ref /LIBPATH:%CD%\"\SFML\lib" sfml-system.lib sfml-window.lib sfml-graphics.lib
rem for static linking
rem set linkerFlags=-incremental:no -opt:ref /LIBPATH:%CD%\"\SFML\lib" sfml-system-s.lib sfml-window-s.lib sfml-graphics-s.lib advapi32.lib user32.lib winmm.lib gdi32.lib opengl32.lib freetype.lib 

mkdir .\build
pushd .\build

rem for dynamic linking
cl /I..\  %compilerFlags% ..\*.cpp /link %linkerFlags% /OUT:untitled-game.exe
rem for static linking
rem cl /I..\ /DSFML_STATIC  %compilerFlags% ..\*.cpp /link %linkerFlags% /OUT:untitled-game.exe

popd
