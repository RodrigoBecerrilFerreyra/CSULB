@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xelab  -wto cbe8386f748d4fa78795b93fa8dfe218 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot Lab5Top_tb_behav xil_defaultlib.Lab5Top_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
