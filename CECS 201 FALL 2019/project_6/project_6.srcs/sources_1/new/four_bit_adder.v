`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/31/2019 04:55:05 PM
// Design Name: 
// Module Name: four_bit_adder
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


module four_bit_adder(
input [3:0] a,
input [3:0] b,
input cin,
output [3:0] sum,
output cout,
output invalid
);

wire cout0, cout1, cout2, cout3;

full_adder fa0(.a(a[0]), .b(b[0]), .cin(cin), .s(sum[0]), .cout(cout0));
full_adder fa1(.a(a[1]), .b(b[1]), .cin(cout0), .s(sum[1]), .cout(cout1));
full_adder fa2(.a(a[2]), .b(b[2]), .cin(cout1), .s(sum[2]), .cout(cout2));
full_adder fa3(.a(a[3]), .b(b[3]), .cin(cout2), .s(sum[3]), .cout(cout3));

assign cout = cout3;
assign invalid = cout3 ^ cout2;

endmodule
