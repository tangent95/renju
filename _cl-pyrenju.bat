if exist "D:\Program Files\MinGW64\bin" (
		set GCC_BIN_PATH=D:\Program Files\MinGW64\bin
	) else (
		set GCC_BIN_PATH=C:\w64devkit-1.19.0\x64\w64devkit\bin
	)
path=%GCC_BIN_PATH%;%path%

if exist "D:\Program Files\anaconda3\envs\pytorchcpu" (
		set PYTHON_PATH=D:\Program Files\anaconda3\envs\pytorchcpu
		set CL_LIB=-lpython3 -lpython310
	) else (
		set PYTHON_PATH=D:\ProgramData\Anaconda3\envs\pytorchcpu
		set CL_LIB=-lpython3 -lpython38
	)

set PYBIND11_PATH=%cd%

set CL_INC_PATH=-I"%PYBIND11_PATH%" -I"%PYTHON_PATH%\include"
set CL_LIB_PATH=-L"%PYTHON_PATH%\libs"
set CODEPATH=.\renju
set CL_BIT=-m64
set CL_STD=-std=c++17

cls

del .\renju.pyd

cd %CODEPATH%

g++.exe SuccessionJudge.cpp -c %CL_STD% %CL_BIT%
g++.exe Board.cpp -c %CL_STD% %CL_BIT%
g++.exe Renju.cpp -c %CL_STD% %CL_BIT%
g++.exe MainBind.cpp -c %CL_STD% %CL_BIT% %CL_INC_PATH%

g++.exe SuccessionJudge.o Board.o Renju.o MainBind.o -o ..\renju.pyd -shared -fPIC %CL_BIT% %CL_LIB_PATH% %CL_LIB%

del .\SuccessionJudge.o
del .\Board.o
del .\Renju.o
del .\MainBind.o

cd ..\

pause