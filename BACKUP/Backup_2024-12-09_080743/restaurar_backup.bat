@echo off
:: Definir las rutas de los archivos y la carpeta de backup
set backupDir=C:\Users\DELL\Documents\KERLLY\PROYECTO_PRIMER_PARCIAL\BACKUP
set restoreDir=C:\Users\DELL\Documents\KERLLY\PROYECTO_PRIMER_PARCIAL\CODIGO
:: Cambia esta ruta a la ubicación de tus archivos importantes

:: Mostrar los backups disponibles
echo Selecciona el backup a restaurar:
dir /b "%backupDir%\Backup_*.*"
echo.

:: Leer la entrada del usuario
set /p backupFile="Escribe el nombre del archivo de backup (ej. Backup_2024-12-09_011055): "

:: Verificar si el archivo existe
if not exist "%backupDir%\%backupFile%" (
    echo Error: El backup especificado no existe en "%backupDir%".
    pause
    exit /b
)

:: Restaurar el archivo
xcopy /E /I /H /Y "%backupDir%\%backupFile%" "%restoreDir%"

:: Mensaje de éxito
echo Backup restaurado exitosamente en: "%restoreDir%"
pause