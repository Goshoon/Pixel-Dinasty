@echo off
color 2
setlocal enabledelayedexpansion
set "SOURCES="
set "OBJECTS="
set "INCLUDES="

:: Buscar todos los archivos .cpp en ./Source
for /R ./Source %%f in (*.cpp) do (
    set "SOURCES=!SOURCES! %%f"
    set "OBJECTS=!OBJECTS! %%~nf.o"
)

:: Buscar todas las carpetas de inclusion dentro de ./Headers
for /R ./Headers /D %%d in (*) do (
    set "INCLUDES=!INCLUDES! -I%%d"
)

:: Compilar todos los archivos a un archivo de objeto
for %%f in (%SOURCES%) do (
    g++ -std=c++17 -c %%f -I ./Headers/ %INCLUDES% -I C:/Dependencies/SDL2/include -o %%~nf.o
     if errorlevel 1 (
        echo Error compiling %%f.
        pause
        exit /b 1
    )
)

:: Conectar todos los archivos al ejecutable
g++ %OBJECTS% -L C:/Dependencies/SDL2/lib -o ./Bin/run.exe -static-libgcc -static-libstdc++ -lmingw32 -Wpedantic -Wmaybe-uninitialized -DSDL2_STATIC -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
 if errorlevel 1 (
    echo Linker error compiling %%f.
    pause
    exit /b 1
)

pause

echo Compilation succeeded. Running the app...
start ./Bin/run.exe

endlocal
exit