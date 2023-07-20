`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2020 04:01:54 PM
// Design Name: 
// Module Name: counter8_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module counter8_tb();

reg tick, clk, rst;
wire [2:0] q;

counter8 counter(.tick(tick), .clk(clk), .rst(rst), .q(q));

always #10 clk = ~clk;

initial begin
    clk = 0;
    rst = 1;
    #15;
    rst = 0;
    tick = 1;
    #100;
    tick = 0;
end
endmodule
