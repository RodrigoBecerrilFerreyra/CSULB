`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 30 October 2020
*/
module Iter_Div(clk, rst, E, A, B, done, Q, R);
input clk, rst, E;
input [5:0] A; input [3:0] B;
output [5:0] Q; output [3:0] R;
output done;

wire cout, zC, LAB, EA, EC, sclrC, sclrR, LR, ER;
wire [3:0] q_thereg, addersum;

FSM_try1 Statemachine(.clk(clk), .rst(rst), .E(E), .cout(cout), .zC(zC), .LAB(LAB), .EA(EA), .EC(EC), .sclrC(sclrC), .sclrR(sclrR), .LR(LR), .ER(ER), .done(done));
Counter Count(.clk(clk), .rst(rst), .E(EC), .sclr(sclrC), .zC(zC));
LShift_Reg LSR(.clk(clk), .reset(rst), .D(A), .s_L(LAB), .E(EA), .w(cout), .Q(Q));
Register TheRegister(.clk(clk), .rst(rst), .E(LAB), .D(B), .Q(q_thereg));
FA_5bit Adder(.A({R, Q[5]}), .B(~{0, q_thereg}), .cin(1), .Sum(addersum), .cout(cout));
LShift_Reg_Clr LSRC(.clk(clk), .reset(rst), .D(addersum), .sclr(sclrR), .s_L(LR), .E(ER), .w(Q[5]), .Q(R));

endmodule
