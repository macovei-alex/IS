@echo off

xcopy "assets" "..\x64\Debug\assets" /e /i /y

REM Copy 1 file
copy "openal32.dll" "..\x64\Debug\openal32.dll"

REM Copy all the mentioned files from source to dest
REM set "source=..\_external\Assimp\bin\x64\"
REM set "dest=..\x64\Debug\"
REM set "files=assimp-vc143-mt.dll"
REM for %%f in (%files%) do (
    REM if not exist "%dest%%%f" (
        REM copy "%source%%%f" "%dest%%%f"
    REM )
REM )

