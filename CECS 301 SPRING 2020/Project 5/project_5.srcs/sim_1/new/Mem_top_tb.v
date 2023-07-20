`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: Mem_top_tb.v
// Date: 12 May 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module Mem_top_tb();

reg clk, rst, start;
wire finish, error;

Mem_top uut(.clk(clk), .rst(rst), .start(start), .finish(finish), .error(error));

always #5 clk = ~clk;

initial
begin
    clk = 0; rst = 1; start = 0;
    #100;
    rst = 0;
    #100;
    start = 1;
end

always @(posedge finish)
begin
    $display("Finished.");
    $finish;
end
endmodule
