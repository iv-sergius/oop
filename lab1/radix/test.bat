set PROGRAM="%~1"

%PROGRAM% 10 16 255 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test255_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 10 16 +256 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test256_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 10 16 +0> %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test0_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 10 16 -255 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test-255_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 +fF > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\testFF_16_10.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 -100 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test-100_16_10.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 10 2 2147483647 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test2147483647_10_2.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 10 2 -2147483648 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test-2147483648_10_2.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% -10 2 2147483649 > %TEMP%\test.txt
if not ERRORLEVEL 1 goto errRun

%PROGRAM% 10 2 -214748A > %TEMP%\test.txt
if not ERRORLEVEL 1 goto errRun

%PROGRAM% 1 2 -214748A > %TEMP%\test.txt
if not ERRORLEVEL 1 goto errRun


echo Program testing succcesed
exit 0

:errRun
echo echo Program testing failed : Program exit with error
exit 1

:err
echo Program testing failed : Incorrect result
exit 1