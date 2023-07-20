`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab Test 3
    Start Date: 08 September 2020
    End Date: 08 September 2020
*/
module dff(
    input d,
    output reg q,
    output q_not,
    input clk
);

assign q_not = ~q;

always @(posedge clk)
    q <= d;

endmodule
