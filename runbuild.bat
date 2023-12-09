@echo off
setlocal

mkdir build
cd build

git submodule update --init --recursive

REM Step 3: Configure the Build
cmake -DGFX_BUILD_EXAMPLES=ON -DGFX_ENABLE_GUI=ON -DGFX_ENABLE_SCENE=ON ..

pause
endlocal
