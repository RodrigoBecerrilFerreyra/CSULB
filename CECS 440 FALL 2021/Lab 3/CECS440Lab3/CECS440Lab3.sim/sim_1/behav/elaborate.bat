@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xelab  -wto 7dbc0a46970942f8b490e823f39f131a -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot full_adder_tb_behav xil_defaultlib.full_adder_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
