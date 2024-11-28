if exist "D:\Program Files\anaconda3\envs\pytorchcpu" (
		set PYTHON_PATH=D:\Program Files\anaconda3\envs\pytorchcpu
		set CONDA_BIN=D:\Program Files\anaconda3\condabin
	) else (
		set PYTHON_PATH=D:\ProgramData\Anaconda3\envs\pytorchcpu
		set CONDA_BIN=D:\ProgramData\Anaconda3\condabin
	)

path=%CONDA_BIN%;path

call conda.bat activate pytorchcpu
python test.py

pause