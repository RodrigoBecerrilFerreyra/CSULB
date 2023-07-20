`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: manual_memory.v
// Date: 05 May 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module manual_memory(
    input [14:0] a, //log_2(32 768) = 15
    input [15:0] d,  //16 bits wide
    input clk,
    input we,
    output reg [15:0] spo //data out 
);

reg [15:0] memory [0:32_767];

always @(*)
    spo = memory[a];
always @(posedge clk)
    if(we) memory[a] <= d;

endmodule
