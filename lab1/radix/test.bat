set PROGRAM="%~1"

%PROGRAM% 255 10 16 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test255_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 256 10 16 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test256_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 0 10 16 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test0_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% -255 10 16 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test-255_10_16.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% FF 16 10 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\testFF_16_10.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% -100 16 10 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test-100_16_10.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% 2147483647 10 2 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test2147483647_10_2.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err

%PROGRAM% -2147483648 10 2 > %TEMP%\test.txt
if ERRORLEVEL 1 goto errRun
fc.exe test\test-2147483648_10_2.txt %TEMP%\test.txt
if ERRORLEVEL 1 goto err


echo Program testing succcesed
exit 0

:errRun
echo echo Program testing failed : Program exit with error
exit 1

:err
echo Program testing failed : Incorrect result
exit 1