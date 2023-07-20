`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/11/2019 10:19:55 AM
// Design Name: 
// Module Name: mux_2to1_case_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module mux_2to1_case_tb();

reg in0_tb, in1_tb, sel_tb;
wire out_tb;

mux_2to1_case uut(.in0(in0_tb), .in1(in1_tb), .sel(sel_tb), .out(out_tb));

initial begin

in0_tb = 0;
in1_tb = 0;
sel_tb = 0;
//expecting out = 0
#100;

in0_tb = 1;
in1_tb = 0;
sel_tb = 0;
//expecting out = 1
#100;

in0_tb = 0;
in1_tb = 1;
sel_tb = 0;
//expecting out = 0
#100;

in0_tb = 1;
in1_tb = 1;
sel_tb = 0;
//expecting out = 1
#100;

in0_tb = 0;
in1_tb = 0;
sel_tb = 1;
//expecting out = 0
#100;

in0_tb = 1;
in1_tb = 0;
sel_tb = 1;
//expecting out = 0
#100;

in0_tb = 0;
in1_tb = 1;
sel_tb = 1;
//expecting out = 1
#100;

in0_tb = 1;
in1_tb = 1;
sel_tb = 1;
//expecting out = 1
#100;

end

endmodule
