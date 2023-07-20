`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineers: Jose Aceves & Amin Rezaei
// Create Date: 08/22/2020 06:59:39 PM
// Design Name: 361_Lab1
// Module Name: Mux2to1
// Revision 0.01 - File Created
//////////////////////////////////////////////////////////////////////////////////

module mux2to1(
    input a, 
    input b, 
    input sel, 
    output out
    );
    
    assign out = (sel) ? a : b;
endmodule