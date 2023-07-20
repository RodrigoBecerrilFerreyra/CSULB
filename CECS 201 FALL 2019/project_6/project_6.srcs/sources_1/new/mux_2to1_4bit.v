`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/05/2019 04:48:04 PM
// Design Name: 
// Module Name: mux_2to1_4bit
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


module mux_2to1_4bit(
    input [3:0] in0,
    input [3:0] in1,
    input sel,
    output reg [3:0] out
);

always @(in0 or in1 or sel)
begin
    case(sel)
        
        0:       out <= in0;
        1:       out <= in1;
        default: out <= 4'bZZZZ;
        
    endcase
end
endmodule
