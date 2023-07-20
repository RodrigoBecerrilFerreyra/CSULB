`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module FSM(clk, rst, E, cout, zC, LAB, EA, EC, sclrC, sclrR, LR, ER, done);
input clk, rst, E, cout, zC;
output reg LAB, EA, EC, sclrC, sclrR, LR, ER, done;

localparam S1 = 0, S2 = 1, S3 = 2;
reg [1:0] cs, ns; // current state, next state

// state switching logic
always @(posedge clk, posedge rst)
    if(rst) cs <= S1;
    else    cs <= ns;

// next state logic
always @(*)
    casez({cs, E, cout, zC}) // {2'b, 1'b, 1'b, 1'b}
        {S1, 3'b1??}: ns = S2;
        {S1, 3'b0??}: ns = S1;
        {S2, 3'b??1}: ns = S2;
        {S2, 3'b??0}: ns = S3;
        {S3, 3'b1??}: ns = S3;
        {S3, 3'b0??}: ns = S1;
        default: ns = cs;
    endcase

// output logic
always @(*)
    casez({cs, E, cout, zC}) // {2'b, 1'b, 1'b, 1'b}
        {S1, 3'b1??}: begin
            sclrR = 1; ER = 1;
            EC = 1; sclrC = 1;
            LAB = 1; EA = 1;
        end
        {S1, 3'b1??}: begin
            sclrR = 1; ER = 1;
            EC = 1; sclrC = 1;
        end
    endcase
endmodule
