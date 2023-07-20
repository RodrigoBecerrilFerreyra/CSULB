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

module X_Kmap(
    input a,
    input d,
    output K_X
    );
    
    //K_X = a' + ad'
    
    assign K_X = !a || (a && !d);
    
endmodule
