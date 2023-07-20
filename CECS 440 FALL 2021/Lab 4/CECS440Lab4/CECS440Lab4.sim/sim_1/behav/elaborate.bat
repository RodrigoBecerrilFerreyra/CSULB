@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xelab  -wto 73e8a523aebf4c2da7ed36aad2377209 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot ALU16bit_tb_behav xil_defaultlib.ALU16bit_tb -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
