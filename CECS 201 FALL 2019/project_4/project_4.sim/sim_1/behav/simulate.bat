@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xsim mux_4to1_4bit_case_tb_behav -key {Behavioral:sim_1:Functional:mux_4to1_4bit_case_tb} -tclbatch mux_4to1_4bit_case_tb.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
