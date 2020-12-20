@echo off

:: Get hostname and start copying
for /f %%i in ('hostname') do set host_name=%%i
net use x: \\%host_name%\SharedDocs
mkdir X:\temp
call copy.bat
pause

:: Compare original file and copyied
fc /a C:\Windows\file.txt X:\temp\file.txt
:: Schedule copying script
schtasks /create /tn "copying" /tr copy.bat /sc minute /mo 1
pause

:: Remove script from schedule
schtasks /delete /tn "copying"
pause

:: Print all current services
net start > services_1
