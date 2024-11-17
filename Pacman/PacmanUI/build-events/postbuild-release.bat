@echo off

xcopy "assets" "..\x64\Release\assets" /e /i /y

REM Copy 1 file
REM copy "..\_external\Assimp\bin\x64\assimp-vc143-mt.dll" "..\x64\Debug\assimp-vc143-mt.dll"

REM Copy all the mentioned files from source to dest
REM set "source=..\_external\Assimp\bin\x64\"
REM set "dest=..\x64\Debug\"
REM set "files=assimp-vc143-mt.dll"
REM for %%f in (%files%) do (
    REM if not exist "%dest%%%f" (
        REM copy "%source%%%f" "%dest%%%f"
    REM )
REM )

