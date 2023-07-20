`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: Lab 2
    Date: 03 October 2020
*/

module Solver_tb();

reg clk, rst, in;
wire [2:0] RGB, solution, LED;

Solver uut(.clk(clk), .reset(rst), .in(in), .RGB(RGB), .solution(solution), .LED(LED));

always #20 clk = ~clk;

initial begin

    clk = 0; rst = 1; in = 0;
    #15;
    rst = 0;
    #800;
    in = 1;

end
endmodule
