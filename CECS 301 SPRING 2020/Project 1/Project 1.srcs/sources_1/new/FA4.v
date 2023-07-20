`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: FA4.v
// Date: 04 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module FA4(A, B, Ci, Y, Co);

input [3:0] A, B;
input Ci;
output [3:0] Y;
output Co;

wire cout0, cout1, cout2;

FA FA0(.A(A[0]), .B(B[0]), .Ci(Ci), .Y(Y[0]), .Co(cout0));
FA FA1(.A(A[1]), .B(B[1]), .Ci(cout0), .Y(Y[1]), .Co(cout1));
FA FA2(.A(A[2]), .B(B[2]), .Ci(cout1), .Y(Y[2]), .Co(cout2));
FA FA3(.A(A[3]), .B(B[3]), .Ci(cout2), .Y(Y[3]), .Co(Co));

endmodule
