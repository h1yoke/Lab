@echo off

:: Get OS verison & memory
systeminfo > sysinfo.temp
findstr /r /C:"^OS Version:" sysinfo.temp > os_version
findstr /r /C:"Physical Memory:" sysinfo.temp > physical_memory

:: Disk list
echo list disk > diskpart.temp
diskpart /s diskpart.temp > disks

:: Remove temporary files
del sysinfo.temp
del diskpart.temp

:: Copy files
mkdir C:\TEST
copy /y C:\LAB6 C:\TEST > test_files

:: Remove all except latest
for /f "skip=1 delims=" %%i in ('dir /b /o-d') do (
  del %%i
)
