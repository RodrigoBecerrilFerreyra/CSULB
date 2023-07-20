`timescale 1ns / 1ps
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
module posedge_detect(clk, rst, d, det);
input wire clk, rst, d;
output wire det;

reg q;
always @(posedge clk, posedge rst)
    if(rst) q <= 1'b0;
    else    q <= d;
assign det = d & ~q;

endmodule
