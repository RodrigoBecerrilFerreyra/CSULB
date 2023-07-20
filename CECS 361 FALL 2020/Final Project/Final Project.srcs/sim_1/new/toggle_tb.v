`timescale 1ns / 1ps
`default_nettype none
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
module toggle_tb();
reg clk, rst, in;
wire out;
integer i;

toggle uut(.clk(clk), .rst(rst), .in(in), .out(out));

always #5 clk = ~clk;

initial begin
    clk = 1; rst = 1; in = 0; i = 0;
    #10;
    rst = 0;
    
    for(i = 0; i < 8; i = i + 1) begin
        #10;
        in = ~in;
    end
    $finish;
end
endmodule
