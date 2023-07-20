`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineer: Colton Curtis, Rodrigo Becerril Ferreya, Ethan Hua
// 
// Create Date: 11/16/2020 07:27:45 PM
// Design Name: 
// Module Name: Divide_by12
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


module Divide_by12(
    input wire [5:0] numer,
    output reg [2:0] quotient,
    output wire [3:0] remain
);
    
reg [3:0] remain_bit3_bit2;
    
assign remain = {remain_bit3_bit2, numer[1:0]}; // the first bits are copied through
    
always @(numer[5:2]) // and just do a divide by "3" on the remaining bits
    case(numer[5:2])
       0: begin quotient=0; remain_bit3_bit2=0; end
       1: begin quotient=0; remain_bit3_bit2=1; end
       2: begin quotient=0; remain_bit3_bit2=2; end
       3: begin quotient=1; remain_bit3_bit2=0; end
       4: begin quotient=1; remain_bit3_bit2=1; end
       5: begin quotient=1; remain_bit3_bit2=2; end
       6: begin quotient=2; remain_bit3_bit2=0; end
       7: begin quotient=2; remain_bit3_bit2=1; end
       8: begin quotient=2; remain_bit3_bit2=2; end
       9: begin quotient=3; remain_bit3_bit2=0; end
       10: begin quotient=3; remain_bit3_bit2=1; end
       11: begin quotient=3; remain_bit3_bit2=2; end
       12: begin quotient=4; remain_bit3_bit2=0; end
       13: begin quotient=4; remain_bit3_bit2=1; end
       14: begin quotient=4; remain_bit3_bit2=2; end
       15: begin quotient=5; remain_bit3_bit2=0; end
    endcase
endmodule

