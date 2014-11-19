

:: Build the project folders
mkdir build\Shaders
mkdir build\Logs
mkdir build\Textures
mkdir build\Models
xcopy /v res\Shaders build\Shaders
xcopy /v res\Textures build\Textures
xcopy /v res\Models build\Models


:: Build the debug Folder
:: - create the directories if not there
mkdir build\Debug
mkdir build\Debug\Shaders
mkdir build\Debug\Textures
mkdir build\Debug\Logs
mkdir build\Debug\Models
:: - copy over required files
xcopy /v res\OS-Windows\dll build\Debug
xcopy /v res\Logs build\Debug\Logs
xcopy /v res\Shaders build\Debug\Shaders
xcopy /v res\Textures build\Debug\Textures
xcopy /v res\Models build\Debug\Models


:: Build the Release Folder
:: - create the directories if not there
mkdir build\Release
mkdir build\Release\Shaders
mkdir build\Release\Logs
mkdir build\Release\Textures
mkdir build\Release\Models
:: - copy over required files
xcopy /v res\OS-Windows\dll build\Release
xcopy /v res\Shaders build\Release\Shaders
xcopy /v res\Logs build\Release\Logs
xcopy /v res\Textures build\Release\Textures
xcopy /v res\Models build\Release\Models

:: Add a .gitignore file to the build folder
echo # Ignore everything in this directory > build\.gitignore
echo * >> build\.gitignore
echo # Except this file >> build\.gitignore
echo !.gitignore >> build\.gitignore

PAUSE 