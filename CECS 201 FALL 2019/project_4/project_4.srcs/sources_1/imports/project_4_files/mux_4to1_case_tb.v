`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/14/2019 11:22:04 AM
// Design Name: 
// Module Name: mux_4to1_case_tb
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

module mux_4to1_case_tb();

reg in0_tb, in1_tb, in2_tb, in3_tb;
reg [1:0] sel_tb;
wire out_tb;

mux_4to1_case uut(.in0(in0_tb), .in1(in1_tb), .in2(in2_tb), .in3(in3_tb), .sel(sel_tb), .out(out_tb));

initial
begin

in0_tb = 0;
in1_tb = 0;
in2_tb = 0;
in3_tb = 0;
sel_tb = 2'b00;
// out = 0;
#100;

in0_tb = 1;
in1_tb = 0;
in2_tb = 0;
in3_tb = 0;
sel_tb = 2'b00;
// out = 1;
#100;

in0_tb = 0;
in1_tb = 0;
in2_tb = 0;
in3_tb = 0;
sel_tb = 2'b01;
// out = 0;
#100;

in0_tb = 0;
in1_tb = 1;
in2_tb = 0;
in3_tb = 0;
sel_tb = 2'b01;
// out = 1;
#100;

in0_tb = 0;
in1_tb = 0;
in2_tb = 0;
in3_tb = 0;
sel_tb = 2'b10;
// out = 0;
#100;

in0_tb = 0;
in1_tb = 0;
in2_tb = 1;
in3_tb = 0;
sel_tb = 2'b10;
// out = 1;
#100;

in0_tb = 0;
in1_tb = 0;
in2_tb = 0;
in3_tb = 0;
sel_tb = 2'b11;
// out = 0;
#100;

in0_tb = 0;
in1_tb = 0;
in2_tb = 0;
in3_tb = 1;
sel_tb = 2'b11;
// out = 1;
#100;

end

endmodule
