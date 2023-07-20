@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xelab  -wto d41a27fad041418b80b62c2e181f3af3 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot signextend_tb_behav xil_defaultlib.signextend_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
