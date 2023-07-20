@echo off
set xv_path=C:\\Xilinx\\Vivado\\2016.2\\bin
call %xv_path%/xsim SevenSegmentDisplay_tf_behav -key {Behavioral:sim_1:Functional:SevenSegmentDisplay_tf} -tclbatch SevenSegmentDisplay_tf.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
