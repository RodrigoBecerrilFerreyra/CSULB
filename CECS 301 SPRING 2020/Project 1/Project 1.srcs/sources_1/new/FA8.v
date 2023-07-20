`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: FA8.v
// Date: 04 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module FA8(A, B, Ci, Y, Co);

input [7:0] A, B;
input Ci;
output [7:0] Y;
output Co;

wire int_cout;

FA4 FA4_0(.A(A[3:0]), .B(B[3:0]), .Ci(Ci), .Y(Y[3:0]), .Co(int_cout));
FA4 FA4_1(.A(A[7:4]), .B(B[7:4]), .Ci(int_cout), .Y(Y[7:4]), .Co(Co));

endmodule
