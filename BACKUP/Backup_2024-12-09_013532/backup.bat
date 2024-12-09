@echo off
:: Definir las rutas de los archivos y la carpeta de backup (sin comillas extra)
set source=C:\Users\DELL\Documents\KERLLY\PROYECTO_PRIMER_PARCIAL\CODIGO
:: Cambia esta ruta a la ubicación de tus archivos importantes
set backupDir=C:\Users\DELL\Documents\KERLLY\PROYECTO_PRIMER_PARCIAL\BACKUP

:: Obtener la fecha y hora en formato válido para Windows
for /f "tokens=2 delims==" %%I in ('"wmic os get localdatetime /value"') do set datetime=%%I
set timestamp=%datetime:~0,4%-%datetime:~4,2%-%datetime:~6,2%_%datetime:~8,2%%datetime:~10,2%%datetime:~12,2%

:: Crear el directorio de backup si no existe
if not exist "%backupDir%" mkdir "%backupDir%"

:: Copiar los archivos al directorio de backup con un timestamp
xcopy /E /I /H /Y "%source%" "%backupDir%\Backup_%timestamp%"

:: Mensaje de éxito
echo Backup completado exitosamente: "%backupDir%\Backup_%timestamp%"
pause