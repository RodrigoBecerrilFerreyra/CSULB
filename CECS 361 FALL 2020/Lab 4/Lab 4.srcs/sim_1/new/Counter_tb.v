`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module Counter_tb();

reg clk, rst, E, sclr;
wire [2:0] Q; wire zC;

Counter uut(.clk(clk), .rst(rst), .E(E), .sclr(sclr), .Q(Q), .zC(zC));

always #5 clk = ~clk;

initial begin

    rst = 1; clk = 1; E = 0; sclr = 0;
    #5;
    rst = 0;
    
    // test count up
    E = 1;
    #70;
    
    // test clear
    sclr = 1;
    #10;
    sclr = 0;
    
    // test count up
    E = 1;
    #70;
    
    // stop counting
    E = 0;
    #70;
    $finish;

end
endmodule
