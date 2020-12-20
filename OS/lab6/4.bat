@echo off

:: Save all drivers
driverquery > query.temp
findstr /v "Module Name  Display Name Driver Type   Link Date ============ ====================== ============= ======================" query.temp > driver.temp
:: Sort drivers list
sort /r driver.temp > drivers
:: Remove temporary files
del query.temp
del driver.temp
