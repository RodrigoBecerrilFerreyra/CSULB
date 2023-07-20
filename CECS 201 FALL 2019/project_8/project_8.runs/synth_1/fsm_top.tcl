# 
# Synthesis run script generated by Vivado
# 

set_param xicom.use_bs_reader 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7a100tcsg324-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir {E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.cache/wt} [current_project]
set_property parent.project_path {E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.xpr} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part digilentinc.com:nexys-a7-100t:part0:1.0 [current_project]
read_verilog -library xil_defaultlib {
  {E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.srcs/sources_1/new/pulse_generator.v}
  {E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.srcs/sources_1/new/fsm_w_pulse.v}
  {E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.srcs/sources_1/new/fsm_top.v}
  {E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.srcs/sources_1/new/fsm_no_pulse.v}
}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc {{E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.srcs/constrs_1/new/fsm_top_NexysA7.xdc}}
set_property used_in_implementation false [get_files {{E:/Coding Projects/CECS 201 FALL 2019/project_8/project_8.srcs/constrs_1/new/fsm_top_NexysA7.xdc}}]


synth_design -top fsm_top -part xc7a100tcsg324-1


write_checkpoint -force -noxdef fsm_top.dcp

catch { report_utilization -file fsm_top_utilization_synth.rpt -pb fsm_top_utilization_synth.pb }