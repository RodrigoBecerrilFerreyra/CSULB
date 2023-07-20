`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 3
    Date: 15 October 2020
*/
module top(
    input A, B, C, D, E,
    output out1, out2, eq
);

lab3    original  (.A(A), .B(B), .C(C), .D(D), .E(E), .Out(out1));
Lab3_eq equivalent(.A(A), .B(B), .C(C), .D(D), .E(E), .Out(out2));

assign eq = out1 ^ out2;

endmodule
