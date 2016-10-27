echo off
set PROGRAM="%~1"

rem check empty file
%PROGRAM% test\empty.txt %TEMP%\empty.txt a ab
if ERRORLEVEL 1 goto err
fc.exe test\empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err

rem check without change
%PROGRAM% test\without_change.txt %TEMP%\without_change.txt a ab
if ERRORLEVEL 1 goto err
fc.exe test\without_change.txt %TEMP%\without_change.txt
if ERRORLEVEL 1 goto err

rem check file with 1 line
%PROGRAM% test\line_in.txt %TEMP%\line.txt a ab
if ERRORLEVEL 1 goto err
fc.exe test\line_out.txt %TEMP%\line.txt
if ERRORLEVEL 1 goto err

rem second check file with 1 line
%PROGRAM% test\line_out.txt %TEMP%\line.txt a ab
if ERRORLEVEL 1 goto err
fc.exe test\line_out2.txt %TEMP%\line.txt
if ERRORLEVEL 1 goto err

rem check for replica in line
%PROGRAM% test\six_a_in.txt %TEMP%\six_a.txt a ab
if ERRORLEVEL 1 goto err
fc.exe test\six_a_out.txt %TEMP%\six_a.txt
if ERRORLEVEL 1 goto err

rem check for replica in several lines
%PROGRAM% test\nine_a_in.txt %TEMP%\nine_a.txt a ab
if ERRORLEVEL 1 goto err
fc.exe test\nine_a_out.txt %TEMP%\nine_a.txt
if ERRORLEVEL 1 goto err

rem check file it doesn't exist
%PROGRAM% test\nofile.txt %TEMP%\nofile.txt a ab
if ERRORLEVEL 2 goto allOK
goto err

:allOK
echo Program testing succcesed
exit 0

:err
echo Program testing failed
exit 1