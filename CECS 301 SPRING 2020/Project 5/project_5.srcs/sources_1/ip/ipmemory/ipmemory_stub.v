// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
// Date        : Tue May 05 10:39:24 2020
// Host        : PC-2 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub {c:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING
//               2020/project_5/project_5.srcs/sources_1/ip/ipmemory/ipmemory_stub.v}
// Design      : ipmemory
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "dist_mem_gen_v8_0_10,Vivado 2016.2" *)
module ipmemory(a, d, clk, we, spo)
/* synthesis syn_black_box black_box_pad_pin="a[14:0],d[15:0],clk,we,spo[15:0]" */;
  input [14:0]a;
  input [15:0]d;
  input clk;
  input we;
  output [15:0]spo;
endmodule
