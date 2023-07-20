`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module pulse_counter_tb();
reg clk, rst;
wire tick;

pulse_counter #(.MAX_COUNT(3)) timekeeper (.clk(clk), .rst(rst), .tick(tick));

always #5 clk = ~clk;

initial begin
    clk = 1; rst = 1;
    #5;
    rst = 0;
    #100000000;
    $finish;
end
endmodule
