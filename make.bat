cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra ^
 ^
 ToolWindow.cpp ^
 ^
 RegistryKeyClass.cpp ^
 ^
 Resource.o ^
 ^
 -o ToolWindow.exe
