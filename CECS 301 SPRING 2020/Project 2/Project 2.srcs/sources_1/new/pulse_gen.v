`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: decoder.v
// Date: 11 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module pulse_gen(
    input clk,
    input rst,
    output tick
    );

reg [18:0] q, d;

always @(posedge clk, posedge rst)
    if(rst) q <= 0;
    else q <= d;
    
assign tick = (q == 19'd4_999); //20 kHz

always @(*)
    if(tick) d = 0;
    else d = q + 1;

endmodule
