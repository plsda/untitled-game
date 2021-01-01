@echo off

rem -MTd: use the debug version of static c run-time library	//In debug mode change -O2 to -Od and vice versa
rem Add -FR and run bscmake *.sbr to generate browse info(e.g. able to jump to definition in debugger) 

rem for dynamic linking
set compilerFlags=-nologo -EHsc -fp:fast -Od -Oi -WX -W4 -wd4201 -wd4505 -wd4100 -wd4189 -wd4091 -wd4456 -wd4311 -wd4302 -wd4244 -wd4458 -wd4996 -FC -Z7 
rem for static linking
rem set compilerFlags=-FR -nologo -MD -EHsc -fp:fast -Od -Oi -WX -W4 -wd4201 -wd4505 -wd4100 -wd4189 -wd4091 -wd4456 -wd4311 -wd4302 -wd4244 -wd4458 -wd4996 -FC -Z7 

rem for dynamic linking
set linkerFlags=-incremental:no -opt:ref /LIBPATH:"G:\MyPrograms\C++_Projektit\untitled_game\code\SFML\lib" sfml-system.lib sfml-window.lib sfml-graphics.lib
rem for static linking
rem set linkerFlags=-incremental:no -opt:ref /LIBPATH:"G:\MyPrograms\C++_Projektit\untitled_game\code\SFML\lib" sfml-system-s.lib sfml-window-s.lib sfml-graphics-s.lib advapi32.lib user32.lib winmm.lib gdi32.lib opengl32.lib freetype.lib 

rem IF NOT EXIST .\build mkdir .\build 
mkdir .\build
pushd .\build

rem for dynamic linking
cl /I..\  %compilerFlags% ..\*.cpp /link %linkerFlags% /OUT:untitled-game.exe
rem for static linking
rem cl /I..\ /DSFML_STATIC  %compilerFlags% ..\*.cpp /link %linkerFlags% /OUT:untitled-game.exe
rem cl /I..\ %compilerFlags% ..\Main.cpp ..\Ohjelma.cpp ..\Ammukset.cpp ..\Ase.cpp ..\Aseet.cpp ..\Efektit.cpp ..\Kauppa.cpp ..\TileMappi.cpp ..\VihollistenKaytto.cpp /link %linkerFlags% /OUT:untitled-game

popd
