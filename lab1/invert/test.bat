echo on
set PROGRAM="%~1"


rem 
%PROGRAM% test_files\matrix_1_in.txt > %TEMP%\result.txt
if ERRORLEVEL 1 goto err
fc.exe test_files\matrix_1_out.txt %TEMP%\result.txt
if ERRORLEVEL 1 goto err

%PROGRAM% test_files\matrix_3_in.txt > %TEMP%\result.txt
if ERRORLEVEL 1 goto err
fc.exe test_files\matrix_3_out.txt %TEMP%\result.txt
if ERRORLEVEL 1 goto err

%PROGRAM% test_files\matrix_2_in.txt > %TEMP%\result.txt
if ERRORLEVEL 1 goto err
fc.exe test_files\matrix_2_out.txt %TEMP%\result.txt
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
