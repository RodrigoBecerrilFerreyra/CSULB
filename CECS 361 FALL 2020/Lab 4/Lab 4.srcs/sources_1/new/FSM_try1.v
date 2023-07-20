`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module FSM_try1(clk, rst, E, cout, zC, LAB, EA, EC, sclrC, sclrR, LR, ER, done);
input clk, rst, E, cout, zC;
output reg LAB, EA, EC, sclrC, sclrR, LR, ER, done;

localparam reset_state = 0, S1 = 1, S2 = 2, S3 = 3;
reg [1:0] cs, ns; // current state, next state

// state switching logic
always @(posedge clk, posedge rst)
    if(rst) cs <= reset_state;
    else    cs <= ns;

// next state logic
always @(*)
    case(cs)
        reset_state: ns = S1;
        S1: ns = E  ? S2 : S1;
        S2: ns = zC ? S3 : S2;
        S3: ns = E  ? S3 : S1;
    endcase

// output logic (Mealy)
always @(*)
    case(cs)
        reset_state: {LAB, EA, EC, sclrC, sclrR, LR, ER, done} = 8'b0;
        S1: begin
            {LR, done} = 2'b0;
            {sclrR, sclrC, ER, EC} = 4'b1111;
            {LAB, EA} = E ? 2'b11 : 2'b00;
        end
        S2: begin
            {LAB, sclrC, sclrR, done} = 4'b0;
            {ER, EA} = 2'b11;
            LR = cout ? 1'b1 : 1'b0;
            EC = zC ? 1'b0 : 1'b1;
        end
        S3: begin
            {LAB, EA, EC, sclrC, sclrR, LR, ER} = 7'b0;
            done = 1'b1;
        end
    endcase

endmodule
