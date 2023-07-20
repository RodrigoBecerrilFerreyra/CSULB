`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: memory_tb.v
// Date: 11 May 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module memory_tb();

reg [14:0] a; //log_2(32 768) = 15
reg [15:0] d;  //16 bits wide
reg clk;
reg we;
wire [15:0] spo; //data out 
integer i;

ipmemory mem(.a(a), .d(d), .clk(clk), .we(we), .spo(spo));
//manual_memory mem(.a(a), .d(d), .clk(clk), .we(we), .spo(spo));

always #5 clk = ~clk;

initial
    begin
    a = 0; d = 0; clk = 0; we = 0;
    
    // write to memory addresses
    #100;
    for(i = 0; i < 16'h8000; i=i+1)
        begin
        @(posedge clk)
        we = 1; a = i; d = i;
        @(posedge clk)
        we = 0;
        repeat(5) @(posedge clk);
        end
    
    // read from memory addresses
    #100;
    for(i = 0; i < 16'h8000; i=i+1)
        begin
        @(posedge clk)
        a = i;
        @(posedge clk)
        #5;
        if(spo != i[15:0])
            $display("Error on i=", i);
        repeat(5) @(posedge clk);
        end
    end
endmodule
