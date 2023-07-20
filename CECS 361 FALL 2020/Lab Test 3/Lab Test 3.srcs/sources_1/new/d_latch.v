`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab Test 2
    Start Date: 08 September 2020
    End Date: 08 September 2020
*/
module d_latch(
    input d,
    input en,
    output reg q,
    output q_not
);

assign q_not = ~q;

always @(*)
    if(en) q = d;

endmodule
