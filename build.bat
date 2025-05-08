@echo off
title [VCODLIB] WINDOWS
cls
echo BUILDING...
md objects


echo ================================================================
echo                     BUILDING VCODLIB.DLL

echo ##### COMPILE CRACKING.CPP #####
g++ -c cracking.cpp -o objects/cracking.opp

echo ##### COMPILE FUNCTIONS.CPP #####
g++ -c functions.cpp -o objects/functions.opp

echo ##### COMPILE GSC.CPP #####
g++ -c gsc.cpp -o objects/gsc.opp

echo ##### COMPILE GSC_PLAYER.CPP #####
g++ -c gsc_player.cpp -o objects/gsc_player.opp

echo ##### COMPILE QVSNPRINTF.C #####
g++ -c .\lib\qvsnprintf.c -o objects/qvsnprintf.opp

echo ##### COMPILE VCODLIB.CPP #####
g++ -c main.cpp -o objects/main.opp

echo ##### LINK vcodlib.dll #####
g++ -m32 -shared -o ..\bin\vcod_lib.dll objects\*.opp

echo                           DONE
echo ================================================================


rd /s /q objects

echo BUILDING DONE!
pause
