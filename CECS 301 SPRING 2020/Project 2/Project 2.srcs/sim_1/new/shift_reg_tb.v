`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2020 04:19:54 PM
// Design Name: 
// Module Name: shift_reg_tb
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


module shift_reg_tb();

reg clk, rst, ls;
wire [7:0] q;

shift_reg sh(.clk(clk), .rst(rst), .ls(ls), .q(q));

always #10 clk = ~clk;

initial begin

clk = 0;
rst = 1;
#15;
rst = 0;
ls = 1;

end
endmodule
