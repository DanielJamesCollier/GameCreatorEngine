:: copy all resources from this master locatin into the build folders so all all the same

:: DLL FOLDER
xcopy /v .\dll ..\build\Debug
xcopy /v .\dll ..\build\Release

:: LIB FOLDER dont need multiple copys of this folder

:: LOGS FOLDER dont copy, logs are generated from each build seperatly

:: MODELS FOLDER
xcopy /v .\Models ..\build\Models
xcopy /v .\Models ..\build\Debug\Models
xcopy /v .\Models ..\build\Release\Models

:: SHADERS FOLDER
xcopy /v .\Shaders ..\build\Shaders
xcopy /v .\Shaders ..\build\Debug\Shaders
xcopy /v .\Shaders ..\build\Release\Shaders

:: TEXTURES FOLDER
xcopy /v .\Textures ..\build\Textures
xcopy /v .\Textures ..\build\Debug\Textures
xcopy /v .\Textures ..\build\Release\Textures
