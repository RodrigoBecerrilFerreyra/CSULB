`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/19/2019 05:16:25 PM
// Design Name: 
// Module Name: multiplexor_16bit_2_to_1
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


module multiplexor_16bit_2_to_1(
    input [15:0] in0,
    input [15:0] in1,
    input sel,
    output reg [15:0] out
);

always @(in0 or in1 or sel) begin
    
    case(sel)
        0: out <= in0;
        1: out <= in1;
        default: out <= 16'hFFFF;
    endcase
    
end
endmodule
