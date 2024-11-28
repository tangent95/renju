if exist "D:\Program Files\MinGW64\bin" (
		set GCC_BIN_PATH=D:\Program Files\MinGW64\bin
	) else (
		set GCC_BIN_PATH=C:\w64devkit-1.19.0\x64\w64devkit\bin
	)
path=%GCC_BIN_PATH%;%path%

set QT_PATH=%cd%\qtlib
set RESULT_PATH=%cd%\run_space
set RENJU_PATH=%cd%\renju
set QTRENJU_PATH=%cd%\qtrenju
set MCTS_PATH=%cd%\MCTS
set BOOST_PATH=%cd%
set CL_BIT=-m64
set CL_STD=-std=c++17 -O2

@REM cls

@REM moc.exe MainWindow.hpp -o MainWindow.moc

del "%RESULT_PATH%\qtrenju.exe"

@REM 编译窗口部分
cd %QTRENJU_PATH%
g++.exe -c main.cpp -o "%RESULT_PATH%\main.o" -std=c++17 -I"%QT_PATH%\include" -I"%RENJU_PATH%\.." %CL_BIT% %CL_STD% -I"%RENJU_PATH%"
g++.exe -c PlayWindow.cpp -o "%RESULT_PATH%\PlayWindow.o" -std=c++17 -I"%QT_PATH%\include" -I"%RENJU_PATH%\.." %CL_BIT% %CL_STD%  -I"%BOOST_PATH%"
g++.exe -c BoardWindow.cpp -o "%RESULT_PATH%\BoardWindow.o" -std=c++17 -I"%QT_PATH%\include" -I"%RENJU_PATH%\.." %CL_BIT% %CL_STD%
g++.exe -c MainBoard.cpp -o "%RESULT_PATH%\MainBoard.o" -std=c++17 -I"%RENJU_PATH%\.." %CL_BIT% %CL_STD%

@REM 编译五子棋逻辑部分
cd %RENJU_PATH%
g++.exe -c SuccessionJudge.cpp -o "%RESULT_PATH%\SuccessionJudge.o" %CL_BIT% %CL_STD%
g++.exe -c Board.cpp -o "%RESULT_PATH%\Board.o" %CL_BIT% %CL_STD%
g++.exe -c Renju.cpp -o "%RESULT_PATH%\Renju.o" %CL_BIT% %CL_STD%

@REM 编译MCTS部分
cd %MCTS_PATH%
g++.exe -c RolloutMCTS.cpp -o "%RESULT_PATH%\RolloutMCTS.o" -std=c++17 -I"%RENJU_PATH%\.." %CL_BIT% %CL_STD% -I"%QT_PATH%\include" -I"%BOOST_PATH%"

@REM 链接汇总
cd %RESULT_PATH%
g++.exe main.o PlayWindow.o BoardWindow.o MainBoard.o RolloutMCTS.o SuccessionJudge.o Board.o Renju.o -o .\qtrenju.exe  -L"%QT_PATH%\lib" -lQt5Core -lQt5Widgets -lQt5Gui %CL_BIT% %CL_STD%

del .\main.o
del .\PlayWindow.o
del .\BoardWindow.o
del .\MainBoard.o
del .\RolloutMCTS.o
del .\SuccessionJudge.o
del .\Board.o
del .\Renju.o

pause