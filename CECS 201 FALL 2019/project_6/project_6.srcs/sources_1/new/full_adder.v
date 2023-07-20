`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/31/2019 04:36:52 PM
// Design Name: 
// Module Name: full_adder
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


module full_adder(
    input a,
    input b,
    input cin,
    output s,
    output cout
);

// no delay
assign s = a ^ b ^ cin;
assign cout = (a && b) || (a && cin) || (b && cin);

// 10 ns delay
//assign #10 s = a ^ b ^ cin;
//assign #10 cout = (a && b) || (a && cin) || (b && cin);

endmodule
