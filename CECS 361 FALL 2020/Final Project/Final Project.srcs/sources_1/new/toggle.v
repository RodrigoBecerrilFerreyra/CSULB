`timescale 1ns / 1ps
`default_nettype none
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
module toggle(clk, rst, in, out);
input wire clk, rst, in;
output wire out;

// state transition logic
reg [1:0] cs, ns;
always @(posedge clk, posedge rst)
    if(rst) cs <= 2'b00;
    else    cs <= ns;

// next state logic
always @(*)
    case({cs, in})
    3'h0: ns = 2'b00;
    3'h1: ns = 2'b01;
    3'h2: ns = 2'b11;
    3'h3: ns = 2'b01;
    3'h4: ns = 2'b00;
    3'h5: ns = 2'b10;
    3'h6: ns = 2'b11;
    3'h7: ns = 2'b10;
    endcase

// output logic
assign out = cs[1];

endmodule
