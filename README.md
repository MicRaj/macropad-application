# macropad-application
Macropad desktop application for programming of macros

# Linux
- ```cd build```
- ```cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ ..```
- ```make -j4```
- ```cd ..```
- ```sudo build/macropad-application```
    
# Windows
- ```cd build```
- ```cmake -G "MinGW Makefiles" ..```
- ```cmake --build .```
- ```cd ..```
- ```.\build\macropad-application.exe```

