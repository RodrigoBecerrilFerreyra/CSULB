`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/31/2019 04:40:14 PM
// Design Name: 
// Module Name: full_adder_tb
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


module full_adder_tb();

reg a_tb, b_tb, cin_tb;
wire s_tb, cout_tb;

full_adder uut(.a(a_tb), .b(b_tb), .cin(cin_tb), .s(s_tb), .cout(cout_tb));

initial
begin

a_tb   = 0;
b_tb   = 0;
cin_tb = 0;
#200; //s = 0, cout = 0

a_tb   = 0;
b_tb   = 0;
cin_tb = 1;
#200; //s = 1, cout = 0

a_tb   = 0;
b_tb   = 1;
cin_tb = 0;
#200; //s = 1, cout = 0

a_tb   = 0;
b_tb   = 1;
cin_tb = 1;
#200; //s = 0, cout = 1

a_tb   = 1;
b_tb   = 0;
cin_tb = 0;
#200; //s = 1, cout = 0

a_tb   = 1;
b_tb   = 0;
cin_tb = 1;
#200; //s = 0, cout = 1

a_tb   = 1;
b_tb   = 1;
cin_tb = 0;
#200; //s = 0, cout = 1

a_tb   = 1;
b_tb   = 1;
cin_tb = 1;
#200; //s = 1, cout = 1

end

endmodule
