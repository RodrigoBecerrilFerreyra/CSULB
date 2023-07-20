`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: register_file_tb.v
// Date: 30 March 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module register_file_tb();

reg write;
reg [2:0] wAdrs, rAdrsA, rAdrsB;
reg [7:0] wData;
reg clk, rst;
wire [7:0] rDataA, rDataB;

register_file dut(.write(write), .wAdrs(wAdrs), .wData(wData), .rAdrsA(rAdrsA), .rAdrsB(rAdrsB), .rDataA(rDataA), .rDataB(rDataB), .clk(clk), .rst(rst)); 

always #25 clk = ~clk;

initial
begin

    clk = 0;
    rst = 1; #25; rst = 0;
    write = 1;
    wAdrs = 3'h0; wData = 8'hff;
    rAdrsA = 3'h0; rAdrsB = 3'h1;
    #50
    write = 0;
    wAdrs = 3'h1; wData = 8'h69;
    #25
    write = 1;
    #50;
    wAdrs = 3'h7;
    rAdrsA = 3'h7; rAdrsB = 3'h0;
    #50;
    wAdrs = 3'h4; wData = 8'h96;
    rAdrsA = 3'h1; rAdrsB = 3'h4;
    #50;
    rAdrsA = 3'h6; rAdrsB = 3'h6;

end
endmodule
