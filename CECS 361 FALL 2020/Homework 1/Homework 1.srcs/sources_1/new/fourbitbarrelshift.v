`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: California State University, Long Beach
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 08/27/2020 06:07:46 PM
// Design Name: Four-Bit Barrel Shift
// Module Name: fourbitbarrelshift
// Project Name: Homework 1
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


module fourbitbarrelshift(
    input [1:0] shift,
    input [3:0] in,
    output reg [3:0] out
);

always @(*)
    case(shift)
        2'd0: out = in;
        2'd1: out = {in[2:0], in[3]};
        2'd2: out = {in[1:0], in[3:2]};
        2'd3: out = {in[0], in[3:1]};
    endcase

endmodule
