cl.exe /Zi ^
    /I "D:\____Developer_Libraries\SDL2-2.30.3\include" ^
    main.c ^
    /link ^
        "D:\____Developer_Libraries\SDL2-2.30.3\lib\x86\SDL2main.lib" ^
        "D:\____Developer_Libraries\SDL2-2.30.3\lib\x86\SDL2.lib" ^
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86\shell32.lib" ^
    /SUBSYSTEM:WINDOWS