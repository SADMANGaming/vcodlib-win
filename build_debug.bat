@echo off
title [VCODLIB] WINDOWS - DEBUG
cls
echo BUILDING...
md objects


echo ================================================================
echo                  BUILDING VCODLIB_DEBUG.DLL

echo ##### COMPILE CRACKING.CPP #####
g++ -c -g cracking.cpp -o objects/cracking.opp

echo ##### COMPILE FUNCTIONS.CPP #####
g++ -c -g functions.cpp -o objects/functions.opp

echo ##### COMPILE GSC.CPP #####
g++ -c -g gsc.cpp -o objects/gsc.opp

echo ##### COMPILE GSC_PLAYER.CPP #####
g++ -c -g gsc_player.cpp -o objects/gsc_player.opp

echo ##### COMPILE QVSNPRINTF.C #####
g++ -c -g .\lib\qvsnprintf.c -o objects/qvsnprintf.opp

echo ##### COMPILE VCODLIB.CPP #####
g++ -c -g main.cpp -o objects/main.opp

echo ##### LINK vcodlib.dll #####
g++ -m32 -shared -o ..\bin\vcod_lib.dll objects\*.opp

echo                           DONE
echo ================================================================


rd /s /q objects

echo BUILDING DONE!
pause
