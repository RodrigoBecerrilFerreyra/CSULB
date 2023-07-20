`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/19/2019 05:19:26 PM
// Design Name: 
// Module Name: multiplexor_16bit_2_to_1_tb
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


module multiplexor_16bit_2_to_1_tb();

reg [15:0] in0_tb;
reg [15:0] in1_tb;
reg sel_tb;
wire [15:0] out_tb;

multiplexor_16bit_2_to_1 uut(.in0(in0_tb), .in1(in1_tb), .sel(sel_tb), .out(out_tb));

initial begin
    in0_tb = 16'hFF00;
    in1_tb = 16'h00FF;
    sel_tb = 0;
    #500;
    
    sel_tb = 1;
    #500;
end
endmodule
