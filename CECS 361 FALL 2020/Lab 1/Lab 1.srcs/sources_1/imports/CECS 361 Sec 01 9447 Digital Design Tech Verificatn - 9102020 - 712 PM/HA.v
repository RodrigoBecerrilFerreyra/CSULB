`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineers: Jose Aceves & Amin Rezaei 
// Create Date: 08/22/2020 06:59:39 PM
// Design Name: 361_Lab1
// Module Name: HA
// Revision 0.01 - File Created
//////////////////////////////////////////////////////////////////////////////////

module HA(    
    input a, 
    input b,
    output c_out,
    output sum
);

    assign {c_out, sum} = a + b;
endmodule