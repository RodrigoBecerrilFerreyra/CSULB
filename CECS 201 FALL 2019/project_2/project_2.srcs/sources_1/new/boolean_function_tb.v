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

module boolean_function_tb();

reg a_tb;
reg b_tb;
reg c_tb;
wire o_tb;

boolean_function uut(.a(a_tb), .b(b_tb), .c(c_tb), .o(o_tb));

initial begin
//o = ab' + a'c

a_tb = 0;
b_tb = 0;
c_tb = 0;
//expecting o = 01 + 10 = 0 + 0 = 0
#500;

a_tb = 0;
b_tb = 0;
c_tb = 1;
//expecting o = 01 + 11 = 0 + 1 = 1
#500;

a_tb = 0;
b_tb = 1;
c_tb = 1;
//expecting o = 00 + 11 = 0 + 1 = 1
#500;

a_tb = 0;
b_tb = 1;
c_tb = 0;
//expecting o = 00 + 10 = 0 + 0 = 0
#500;

a_tb = 1;
b_tb = 1;
c_tb = 0;
//expecting o = 10 + 00 = 0 + 0 = 0
#500;

a_tb = 1;
b_tb = 1;
c_tb = 1;
//expecting o = 10 + 01 = 0 + 0 = 0
#500;

a_tb = 1;
b_tb = 1;
c_tb = 0;
//expecting o = 10 + 00 = 0 + 0 = 0
#500;

a_tb = 1;
b_tb = 0;
c_tb = 0;
//expecting o = 11 + 00 = 1 + 0 = 1
#500;

end

endmodule
