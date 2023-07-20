`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 09/19/2019 04:59:48 PM
// Design Name: 
// Module Name: boolean_function
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

module boolean_function(
    input a,
    input b,
    input c,
    output o
    );
    
    //o = ab' + a'c
    
    wire first;
    wire second;
    
    assign first = a && !b;
    assign second = c && !a;
    assign o = first || second;
    
endmodule
