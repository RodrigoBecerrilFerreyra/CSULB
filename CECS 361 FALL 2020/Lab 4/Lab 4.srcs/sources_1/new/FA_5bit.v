`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module FA_5bit(A, B, cin, Sum, cout);
input [4:0] A, B; input cin;
output [4:0] Sum; output cout;

assign {cout, Sum} = A + B + cin;

endmodule
