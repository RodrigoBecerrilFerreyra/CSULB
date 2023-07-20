`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 3
    Date: 15 October 2020
*/
module top_tb();

reg A, B, C, D, E;
wire o1, o2, eq;
integer i;

top uut(.A(A), .B(B), .C(C), .D(D), .E(E), .out1(o1), .out2(o2), .eq(eq));

initial begin

    for(i = 0; i < 32; i = i + 1) begin
        {A, B, C, D, E} = i;
        #30;
    end

end
endmodule
