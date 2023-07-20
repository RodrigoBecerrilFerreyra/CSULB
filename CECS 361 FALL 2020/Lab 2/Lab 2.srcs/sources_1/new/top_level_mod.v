`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: Lab 2
    Date: 03 October 2020
*/

module top_level_mod(
    input clk, input reset,
    input [1:0] sel,
    output [2:0] RGB,
    output [2:0] LED
    //debugging purposes
    //output [7:0] cathode,
    //output [7:0] anode
);

wire CNFout;
wire [2:0] CNFin;

Solver solver(.clk(clk), .reset(reset), .in(CNFout), .RGB(RGB), .solution(CNFin), .LED(LED));
CNF cnf(.A(CNFin[2]), .B(CNFin[1]), .C(CNFin[0]), .sel(sel), .out(CNFout));
//debugging purposes
//seven_segment ssd(.clk(clk), .rst(reset), .value(sel), .cathode(cathode), .anode(anode));

endmodule
