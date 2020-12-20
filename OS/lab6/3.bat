@echo off

:: Stop dns service
net stop dnscache
:: Wait 10 seconds
ping localhost -n 10 >NUL
:: Print current services
net start > services_2
:: Compare active services
fc /w services_1 services_2
