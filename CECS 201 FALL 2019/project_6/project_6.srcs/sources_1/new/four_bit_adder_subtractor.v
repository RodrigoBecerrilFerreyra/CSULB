`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/05/2019 04:52:57 PM
// Design Name: 
// Module Name: four_bit_adder_subtractor
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


module four_bit_adder_subtractor(
    input [3:0] a,
    input [3:0] b,
    input sel,
    output [3:0] out,
    output cout,
    output invalid
);

wire [3:0] mux_output;
mux_2to1_4bit mux(.in0(b), .in1(~b), .sel(sel), .out(mux_output));
four_bit_adder adder(.a(a), .b(mux_output), .cin(sel), .sum(out), .cout(cout), .invalid(invalid));

endmodule
