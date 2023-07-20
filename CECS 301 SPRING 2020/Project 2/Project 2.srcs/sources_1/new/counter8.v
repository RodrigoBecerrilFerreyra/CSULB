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

module counter8(
    input tick,
    input clk,
    input rst,
    output reg [2:0] q
    );

reg [2:0] d;

always @(posedge clk, posedge rst)
    if(rst) q <= 0;
    else q <= d;

always @(*)
    if(tick) d = q + 1;
    else d = q;

endmodule
