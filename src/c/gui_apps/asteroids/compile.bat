cl.exe /Zi ^
    /I "D:\____Developer_Libraries\SDL2-2.30.3\include" ^
    main.c ^
    asteroids.c ^
    /link ^
        "D:\____Developer_Libraries\SDL2-2.30.3\lib\x86\SDL2main.lib" ^
        "D:\____Developer_Libraries\SDL2-2.30.3\lib\x86\SDL2.lib" ^
        "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86\shell32.lib" ^
    /SUBSYSTEM:CONSOLE
    
    @REM /SUBSYSTEM:WINDOWS

    @REM cl.exe /Zi ^
    @REM     /I "D:\____Developer_Libraries\SDL2-2.30.3\include" ^
    @REM     main.c ^
    @REM     example_extra_file.c ^
    @REM     /link ^
    @REM         "D:\____Developer_Libraries\SDL2-2.30.3\lib\x86\SDL2main.lib" ^
    @REM         "D:\____Developer_Libraries\SDL2-2.30.3\lib\x86\SDL2.lib" ^
    @REM         "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x86\shell32.lib" ^
    @REM     /SUBSYSTEM:CONSOLE