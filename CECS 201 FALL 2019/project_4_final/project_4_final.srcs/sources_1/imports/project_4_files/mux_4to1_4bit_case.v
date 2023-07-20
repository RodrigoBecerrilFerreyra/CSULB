`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/14/2019 01:37:42 PM
// Design Name: 
// Module Name: mux_4to1_4bit_case
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

module mux_4to1_4bit_case(
    input [3:0] in0,
    input [3:0] in1,
    input [3:0] in2,
    input [3:0] in3,
    input [1:0] sel,
    output reg [3:0] out
    );
    
    always @(in0 or in1 or in2 or in3 or sel)
    begin
        case(sel)
            0:       out <= in0;
            1:       out <= in1;
            2:       out <= in2;
            3:       out <= in3;
            default: out <= 4'bZZZZ;
        endcase
    end

endmodule
