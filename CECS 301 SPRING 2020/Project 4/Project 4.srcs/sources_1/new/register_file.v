`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: register_file.v
// Date: 30 March 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module register_file(
    input write,
    input [2:0] wAdrs,
    input [7:0] wData,
    input [2:0] rAdrsA,
    input [2:0] rAdrsB,
    output [7:0] rDataA,
    output [7:0] rDataB,
    input clk,
    input rst
    );

reg [7:0] reg_array [0:7];
integer i;

always @(posedge clk, posedge rst)
    if(rst)
        for(i = 0; i < 8; i = i + 1)
            reg_array[i] <= 0;
    else if(write)
        reg_array[wAdrs] <= wData;
//    else
//        reg_array[wAdrs] <= reg_array[wAdrs];

assign rDataA = reg_array[rAdrsA];
assign rDataB = reg_array[rAdrsB];

endmodule
