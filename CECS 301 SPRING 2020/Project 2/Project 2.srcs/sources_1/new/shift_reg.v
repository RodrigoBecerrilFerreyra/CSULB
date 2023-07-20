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

module shift_reg(
    input clk,
    input rst,
    input ls,
    output reg [7:0] q
    );

reg [7:0] d;

always @(posedge clk, posedge rst)
    if(rst) q <= 8'b1111_1110;
    else q <= d;

always @(*)
    if(ls) d = {q[6:0], q[7]};
    else d = q;

endmodule
