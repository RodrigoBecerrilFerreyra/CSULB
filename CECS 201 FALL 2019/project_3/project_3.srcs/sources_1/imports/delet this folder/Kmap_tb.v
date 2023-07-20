`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/03/2019 01:42:39 PM
// Design Name: 
// Module Name: Kmap_tb
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

module Kmap_tb();

reg a_tb;
reg b_tb;
reg c_tb;
reg d_tb;
wire K_tb;

Kmap uut(.a(a_tb), .b(b_tb), .c(c_tb), .d(d_tb), .K(K_tb));

initial begin
// K(1) = a'b' + c'd' + a'c' + ad'

a_tb = 0;
b_tb = 0;
c_tb = 0;
d_tb = 0;
#125;

a_tb = 0;
b_tb = 0;
c_tb = 0;
d_tb = 1;
#125;

a_tb = 0;
b_tb = 0;
c_tb = 1;
d_tb = 0;
#125;

a_tb = 0;
b_tb = 0;
c_tb = 1;
d_tb = 1;
#125;

a_tb = 0;
b_tb = 1;
c_tb = 0;
d_tb = 0;
#125;

a_tb = 0;
b_tb = 1;
c_tb = 0;
d_tb = 1;
#125;

a_tb = 0;
b_tb = 1;
c_tb = 1;
d_tb = 0;
#125;

a_tb = 0;
b_tb = 1;
c_tb = 1;
d_tb = 1;
#125;

a_tb = 1;
b_tb = 0;
c_tb = 0;
d_tb = 0;
#125;

a_tb = 1;
b_tb = 0;
c_tb = 0;
d_tb = 1;
#125;

a_tb = 1;
b_tb = 0;
c_tb = 1;
d_tb = 0;
#125;

a_tb = 1;
b_tb = 0;
c_tb = 1;
d_tb = 1;
#125;

a_tb = 1;
b_tb = 1;
c_tb = 0;
d_tb = 0;
#125;

a_tb = 1;
b_tb = 1;
c_tb = 0;
d_tb = 1;
#125;

a_tb = 1;
b_tb = 1;
c_tb = 1;
d_tb = 0;
#125;

a_tb = 1;
b_tb = 1;
c_tb = 1;
d_tb = 1;
#125;

end

endmodule
