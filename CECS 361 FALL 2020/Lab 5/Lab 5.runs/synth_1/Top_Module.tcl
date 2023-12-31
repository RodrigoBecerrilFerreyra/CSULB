# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000
create_project -in_memory -part xc7a100tcsg324-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.cache/wt} [current_project]
set_property parent.project_path {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.xpr} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part digilentinc.com:nexys-a7-100t:part0:1.0 [current_project]
read_verilog -library xil_defaultlib {
  {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/sources_1/new/RGBflash.v}
  {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/sources_1/new/pulse_counter.v}
  {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/sources_1/imports/Downloads/Circuit_SA1.v}
  {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/sources_1/new/Circuit_SA1_expected.v}
  {C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/sources_1/new/Top_Module.v}
}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc {{C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/constrs_1/imports/CECS 361 FALL 2020/Nexys-A7-100T-Master.xdc}}
set_property used_in_implementation false [get_files {{C:/Users/oscar/Coding Projects/CSULB/CECS 361 FALL 2020/Lab 5/Lab 5.srcs/constrs_1/imports/CECS 361 FALL 2020/Nexys-A7-100T-Master.xdc}}]


synth_design -top Top_Module -part xc7a100tcsg324-1


write_checkpoint -force -noxdef Top_Module.dcp

catch { report_utilization -file Top_Module_utilization_synth.rpt -pb Top_Module_utilization_synth.pb }
