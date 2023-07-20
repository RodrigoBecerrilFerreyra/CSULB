`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/19/2019 05:35:54 PM
// Design Name: 
// Module Name: top_counter_32bit_tb
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


module top_counter_32bit_tb();

reg count;
reg clock;
reg reset;
reg sel;
wire [15:0] Q;

always begin
    #50 clock = ~clock;
end

top_counter_32bit uut(.count_en_top(count), .clk_top(clock), .reset_top(reset), .Sel_top(sel), .Q_top(Q));

initial begin
    clock = 0;
    reset = 1;
    count = 0;
    sel = 0;
    #300;
    reset = 0;
    #200;
    count = 1;
    #20971515;
    sel = 1;
    #1;
end
endmodule
