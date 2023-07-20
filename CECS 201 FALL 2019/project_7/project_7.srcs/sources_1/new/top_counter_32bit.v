`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/19/2019 05:15:29 PM
// Design Name: 
// Module Name: top_counter_32bit
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


module top_counter_32bit(
    input count_en_top,
    input clk_top,
    input reset_top,
    input Sel_top,
    output [15:0] Q_top
);

wire [31:0] Q_int;
counter_32bit counter(.clk(clk_top), .reset(reset_top), .count_en(count_en_top), .Q(Q_int));
multiplexor_16bit_2_to_1 mux(.in0(Q_int[15:0]), .in1(Q_int[31:16]), .sel(Sel_top), .out(Q_top));

endmodule
