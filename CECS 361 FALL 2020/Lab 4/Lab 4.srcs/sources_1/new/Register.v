`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module Register(clk, rst, E, D, Q);
input clk, rst, E;
input [3:0] D;
output reg [3:0] Q;

always @(posedge clk, posedge rst)
    if(rst) Q <= 0;
    else if(E) Q <= D;

endmodule
