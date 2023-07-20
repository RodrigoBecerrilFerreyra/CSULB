`timescale 1ns / 1ps
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
module negedge_detect_tb();
reg clk, rst, d;
wire det;
negedge_detect uut(.clk(clk), .rst(rst), .d(d), .det(det));
always #5 clk = ~clk;

initial begin
    clk = 1; rst = 1; d = 1;
    #5;
    rst = 0;
    #10;
    d = 0;
    #10;
    d = 1;
    #10;
    $finish;
end
endmodule
