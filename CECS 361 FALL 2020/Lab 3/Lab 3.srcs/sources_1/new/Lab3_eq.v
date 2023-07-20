`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 3
    Date: 15 October 2020
*/
module Lab3_eq(
    input A,
    input B,
    input C,
    input D,
    input E,
    output Out
);

assign Out = (~B & ~C & ~E) | (A & B & C & ~E) | (~A & B & C & ~D);

endmodule
