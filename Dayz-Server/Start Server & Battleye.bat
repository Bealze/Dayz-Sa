@echo off
TITLE DayZ SA Server - Status
COLOR 0A
mode con:cols=75 lines=3
::DayZServer_64.exe path
set DAYZ-SA_SERVER_LOCATION="Dayz-Sa/Dayz-Server/"
::Bec.exe path
set BEC_LOCATION="Dayz-Sa/Dayz-Server/battleye/"
::IMPORTANT: Modify line 70 to your correct parameters
::::::::::::::

echo Agusanz
goto checksv
pause

:checksv
tasklist /FI "IMAGENAME eq DayZServer_x64.exe" 2>NUL | find /I /N "DayZServer_x64.exe">NUL
if "%ERRORLEVEL%"=="0" goto checkbec
cls
echo Server is not running, taking care of it..
goto killsv

:checkbec
tasklist /FI "IMAGENAME eq Bec.exe" 2>NUL | find /I /N "Bec.exe">NUL
if "%ERRORLEVEL%"=="0" goto loopsv
cls
echo Bec is not running, taking care of it..
goto startbec

:loopsv
FOR /L %%s IN (30,-1,0) DO (
	cls
	echo Server is running. Checking again in %%s seconds.. 
	timeout 1 >nul
)
goto checksv

:killsv
taskkill /f /im Bec.exe
taskkill /f /im DayZServer_x64.exe
goto startsv

:startsv
cls
echo Starting DayZ SA Server.
timeout 1 >nul
cls
echo Starting DayZ SA Server..
timeout 1 >nul
cls
echo Starting DayZ SA Server...
cd "%DAYZ-SA_SERVER_LOCATION%"
start DayZServer_x64.exe -config=serverDZ.cfg -port=2302 -profiles=C:Dayz-Sa/Dayz-Server/server_spam -dologs -adminlog -netlog -freezecheck -noFilePatching -BEpath=C:Dayz-Sa/Dayz-Server/battleye/
FOR /L %%s IN (30,-1,0) DO (
	cls
	echo Initializing server, wait %%s seconds to initialize Bec.. 
	timeout 1 >nul
)
goto startbec

:startbec
cls
echo Starting Bec.
timeout 1 >nul
cls
echo Starting Bec..
timeout 1 >nul
cls
echo Starting Bec...
timeout 1 >nul
cd "%BEC_LOCATION%"
start Bec.exe -f Config.cfg --dsc
goto checksv
