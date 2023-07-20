`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/27/2020 09:49:22 AM
// Design Name: 
// Module Name: debounce_filter_tb
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

module debounce_filter_tb();

reg clk, rst, signal;
wire db;

debounce_filter dbf(.clk(clk), .rst(rst), .signal(signal), .db(db));

always #10 clk = ~clk;

initial begin

clk = 0;
rst = 1;
signal = 0;
#10;
rst = 0;
signal = 1;
#10000000; //10 ms
signal = 0;
#10000000;
signal = 1;

end
endmodule
