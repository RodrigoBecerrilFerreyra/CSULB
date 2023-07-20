`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2020 03:42:55 PM
// Design Name: 
// Module Name: pulse_gen_tb
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


module pulse_gen_tb();

reg clk, rst;
wire tick;

pulse_gen pg(.clk(clk), .rst(rst), .tick(tick));

always #10 clk = ~clk;
    
initial begin

    clk = 0;
    rst = 1;
    #500;
    rst = 0;

end
endmodule
