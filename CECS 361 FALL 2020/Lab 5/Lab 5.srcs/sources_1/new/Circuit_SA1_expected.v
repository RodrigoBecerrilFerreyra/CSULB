`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module Circuit_SA1_expected(
    input wire A, input wire B, input wire C,
    output wire F1, output wire F0
);

wire L1, L2, L3;
assign L1 = A ^ B;
assign L2 = A & B;
assign L3 = C & L1;
assign F1 = L3 | L2;
assign F0 = L1 ^ C;

endmodule
