`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/05/2019 05:38:16 PM
// Design Name: 
// Module Name: mux_2to1_4bit_tb
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


module mux_2to1_4bit_tb();

reg [3:0] in0_tb;
reg [3:0] in1_tb;
reg sel_tb;
wire [3:0] out_tb;

mux_2to1_4bit uut(.in0(in0_tb), .in1(in1_tb), .sel(sel_tb), .out(out_tb));

initial
begin

in0_tb = 4'b0001;
in1_tb = 4'b1000;
sel_tb = 1;
#100;

in0_tb = 4'b0001;
in1_tb = 4'b1000;
sel_tb = 0;
#100;

end
endmodule
