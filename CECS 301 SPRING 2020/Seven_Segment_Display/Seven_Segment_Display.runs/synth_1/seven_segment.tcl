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
set_property webtalk.parent_dir {C:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING 2020/Seven_Segment_Display/Seven_Segment_Display.cache/wt} [current_project]
set_property parent.project_path {C:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING 2020/Seven_Segment_Display/Seven_Segment_Display.xpr} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part digilentinc.com:nexys-a7-100t:part0:1.0 [current_project]
read_verilog -library xil_defaultlib {{C:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING 2020/Seven_Segment_Display/Seven_Segment_Display.srcs/sources_1/new/seven_segment.v}}
foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc {{C:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING 2020/Seven_Segment_Display/Seven_Segment_Display.srcs/constrs_1/imports/new/top_level_seven_segment_Nexys_A7.xdc}}
set_property used_in_implementation false [get_files {{C:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING 2020/Seven_Segment_Display/Seven_Segment_Display.srcs/constrs_1/imports/new/top_level_seven_segment_Nexys_A7.xdc}}]


synth_design -top seven_segment -part xc7a100tcsg324-1


write_checkpoint -force -noxdef seven_segment.dcp

catch { report_utilization -file seven_segment_utilization_synth.rpt -pb seven_segment_utilization_synth.pb }
