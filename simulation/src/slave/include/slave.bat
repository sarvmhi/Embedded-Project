cd .

if "%1"=="" ("E:\Polyspace\R2020a\bin\win64\gmake"  -f wrapper.mk all) else ("E:\Polyspace\R2020a\bin\win64\gmake"  -f wrapper.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1
