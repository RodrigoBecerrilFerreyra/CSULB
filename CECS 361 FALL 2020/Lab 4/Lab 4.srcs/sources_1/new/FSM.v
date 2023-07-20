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

reg [2:0] cs, NS; // current state, next state

localparam  reset_state = 3'h0,
            S1 = 3'h1, S2 = 3'h2,
            S3 = 3'h3, S4 = 3'h4,
            S5 = 3'h5, S6 = 3'h6;

// state switching logic
always @(posedge clk, posedge rst)
    if(rst) cs <= reset_state;
    else    cs <= NS;

// next state logic
always @(*)
    case(cs)
        reset_state: NS = S1;
        S1: NS = E ? S2 : S1;
        S2: NS = S3;
        S3: if(cout) NS = S4;
            else NS = zC ? S6 : S5;
        S4: NS = zC ? S6 : S5;
        S5: NS = S3;
        S6: NS = E ? S6 : S1;
        default: NS = cs;
    endcase

// output logic (Moore)
always @(*)
    case(cs)
        reset_state: {LAB, EA, EC, sclrC, sclrR, LR, ER, done} = 8'b0;
        S1: begin
            {LAB, EA, LR, done} = 4'b0;
            {sclrR, ER, EC, sclrC} = 4'b1111;
        end
        S2: begin
            {EC, sclrC, sclrR, LR, ER, done} = 6'b0;
            {LAB, EA} = 2'b11;
        end
        S3: begin
            {LAB, EC, sclrC, sclrR, LR, done} = 6'b0;
            {ER, EA} = 2'b11;
        end
        S4: begin
            {LAB, EA, EC, sclrC, sclrR, ER, done} = 7'b0;
            LR = 1'b1;
        end
        S5: begin
            {LAB, EA, sclrC, sclrR, LR, ER, done} = 7'b0;
            EC = 1'b1;
        end
        S6: begin
            {LAB, EA, EC, sclrC, sclrR, LR, ER} = 7'b0;
            done = 1'b1;
        end
        default: {LAB, EA, EC, sclrC, sclrR, LR, ER, done} = 8'b0;
    endcase

endmodule
