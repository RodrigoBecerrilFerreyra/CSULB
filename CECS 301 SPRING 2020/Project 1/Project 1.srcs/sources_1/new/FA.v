`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: FA.v
// Date: 04 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module FA(A, B, Ci, Co, Y);

input A, B, Ci;
output Co, Y;

assign Y = A ^ B ^ Ci;
assign Co = (A&&B) || (A&&Ci) || (B&&Ci);

endmodule
