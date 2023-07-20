`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: Lab 2
    Date: 03 October 2020
*/

module top_level_mod_tb();

reg clk, rst;
reg [1:0] sel;
wire [2:0] RGB, LED;

top_level_mod uut(.clk(clk), .reset(rst), .sel(sel), .RGB(RGB), .LED(LED));

always #10 clk = ~clk;

integer i;

initial begin

    clk = 0; rst = 1;
    #20;
    rst = 0;
    for(i = 0; i < 4; i = i + 1) begin
        sel = i;
        rst = 1;
        #20;
        rst = 0;
        #180;
    end
end
endmodule
