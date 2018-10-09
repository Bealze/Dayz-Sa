@echo off
TITLE DayZ SA Server - Updater / installer
COLOR 0A
mode con:cols=75 lines=3
:: Variables::
::SteamCMD.exe path
set STEAM_CMD_LOCATION="C:\GS\scmd"
set STEAM_USERNAME="######"
SET %STEAM_PASSWORD="######"
::DayZServer_64.exe path
set DAYZ-SA_SERVER_LOCATION="C:\GS\scmd\servers\dayz"

echo Agusanz
goto checksv
pause

:checksv
tasklist /FI "IMAGENAME eq DayZServer_x64.exe" 2>NUL | find /I /N "DayZServer_x64.exe">NUL
if "%ERRORLEVEL%"=="0" goto checkbec
cls
echo Server is not running, taking care of it..
goto killsv


:loopsv
FOR /L %%s IN (30,-1,0) DO (
	cls
	echo Server is running. Checking again in %%s seconds.. 
	timeout 1 >nul
)
goto checksv

:killsv
taskkill /f /im DayZServer_x64.exe
goto updatesv

:updatesv
cls
echo Updating DayZ SA Server.
timeout 1 >nul
cls
echo Updating DayZ SA Server..
timeout 1 >nul
cls
echo Updating DayZ SA Server...
cd "%STEAM_CMD_LOCATION%"
start /wait "" steamcmd.exe +login "%STEAM_USERNAME%" "%STEAM_PASSWORD%" +force_install_dir %~dp0 +app_update 223350 validate +quit