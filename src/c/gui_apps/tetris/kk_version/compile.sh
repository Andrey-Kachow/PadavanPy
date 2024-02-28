cl.exe \
    /Zi \
    /I "D:\CDevLibraries\SDL2-2.28.5\include" \
    /I "D:\CDevLibraries\SDL2_ttf-2.22.0\include" \
    main.c \
    /link \
        "D:\CDevLibraries\SDL2-2.28.5\lib\x86\SDL2main.lib" \
        "D:\CDevLibraries\SDL2-2.28.5\lib\x86\SDL2.lib" \
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x86\shell32.lib" \
        "D:\CDevLibraries\SDL2_ttf-2.22.0\lib\x86\SDL2_ttf.lib"\
    /SUBSYSTEM:WINDOWS

pause


cl.exe /Zi /I "D:\CDevLibraries\SDL2-2.28.5\include" /I "D:\CDevLibraries\SDL2_ttf-2.22.0\include" main.c  /link "D:\CDevLibraries\SDL2-2.28.5\lib\x86\SDL2main.lib" "D:\CDevLibraries\SDL2-2.28.5\lib\x86\SDL2.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x86\shell32.lib" "D:\CDevLibraries\SDL2_ttf-2.22.0\lib\x86\SDL2_ttf.lib" /SUBSYSTEM:WINDOWS
