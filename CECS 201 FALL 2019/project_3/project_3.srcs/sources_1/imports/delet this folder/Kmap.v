`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/03/2019 01:42:39 PM
// Design Name: 
// Module Name: Kmap
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

module Kmap(
    input a,
    input b,
    input c,
    input d,
    output K
    );
    
    //K(1) = a'b' + c'd' + a'c' + ad'
    
    
    assign K = (!a && !b) || (!c && !d) || (!a && !c) || (a && !d);
    
endmodule
