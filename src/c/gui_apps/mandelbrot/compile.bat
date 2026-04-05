cl.exe /Zi ^
    /I "C:\Custom_ProgramFiles\DeveloperLibraries\SDL2-2.30.6\include" ^
    main.cpp ^
    /link ^
        "C:\Custom_ProgramFiles\DeveloperLibraries\SDL2-2.30.6\lib\x86\SDL2main.lib" ^
        "C:\Custom_ProgramFiles\DeveloperLibraries\SDL2-2.30.6\lib\x86\SDL2.lib" ^
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86\shell32.lib" ^
    /SUBSYSTEM:CONSOLE