`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: California State University, Long Beach
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 09/12/2019 04:46:59 PM
// Design Name: 
// Module Name: add_behavioral
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


module add_behavioral(
    input [2:0] in0,
    input [2:0] in1,
    output [2:0] out,
    output carry
    );
    
    wire [3:0] tempout;
    
    assign tempout = in0 + in1;
    assign out = tempout[2:0];
    assign carry = tempout[3];
    
endmodule
