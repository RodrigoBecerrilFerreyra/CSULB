`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module RGBflash_tb();
reg clk, rst, en; wire tick;
wire r, g, b;

pulse_counter #(.MAX_COUNT(3)) timer (.clk(clk), .rst(rst), .tick(tick));
RGBflash uut(.clk(clk), .rst(rst), .enable(en), .tick(tick), .red_on(r), .green_on(g), .blue_on(b));

always #5 clk = ~clk;

initial begin

rst = 1; clk = 1; en = 0;
#5;
rst = 0;

// test if properly switches state
en = 1;
#40; if({r, g, b} != 3'b100) $display("Error, should be red.");
#40; if({r, g, b} != 3'b010) $display("Error, should be green.");
#40; if({r, g, b} != 3'b001) $display("Error, should be blue.");
#40; en = 0;
$finish;

end
endmodule
