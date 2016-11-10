echo on
set PROGRAM="%~1"

rem 
%PROGRAM% test_files\matrix_identity.txt > %TEMP%\result.txt
if ERRORLEVEL 1 goto err
fc.exe test_files\matrix_identity.txt %TEMP%\result.txt
if ERRORLEVEL 1 goto err

%PROGRAM% test_files\matrix_without_zero_in.txt > %TEMP%\result.txt
if ERRORLEVEL 1 goto err
fc.exe test_files\matrix_without_zero_out.txt %TEMP%\result.txt
if ERRORLEVEL 1 goto err

%PROGRAM% test_files\matrix_adverse_diagonal.txt > %TEMP%\result.txt
if ERRORLEVEL 1 goto err
fc.exe test_files\matrix_adverse_diagonal.txt %TEMP%\result.txt
if ERRORLEVEL 1 goto err

%PROGRAM% test_files\matrix_singular.txt > %TEMP%\result.txt
if not ERRORLEVEL 1 goto err



:allOK
echo Program testing succcesed
exit 0

:err
echo Program testing failed
exit 1
