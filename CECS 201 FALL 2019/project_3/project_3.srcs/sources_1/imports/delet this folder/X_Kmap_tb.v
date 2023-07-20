`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 09/19/2019 05:04:36 PM
// Design Name: 
// Module Name: boolean_function_tb
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

module X_Kmap_tb();

reg a_tb;
reg d_tb;
wire K_X_tb;

X_Kmap uut(.a(a_tb), .d(d_tb), .K_X(K_X_tb));

initial begin
//K_X = a' + ad'

a_tb = 0;
d_tb = 0;
//expecting 1 + 01 = 1
#500;

a_tb = 0;
d_tb = 1;
//expecting 1 + 00 = 1
#500;

a_tb = 1;
d_tb = 1;
//expecting 0 + 10 = 0
#500;

a_tb = 1;
d_tb = 0;
//expecting 0 + 11 = 1
#500;

end

endmodule
