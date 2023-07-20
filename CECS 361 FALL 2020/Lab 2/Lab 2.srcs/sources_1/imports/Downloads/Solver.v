`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineers: Jose Aceves & Amin Rezaei 
// Create Date: 08/30/2020 03:45:30 PM
// Design Name: 361_Lab2
// Module Name: Solver
// Revision 0.01 - File Created
//////////////////////////////////////////////////////////////////////////////////

/*
    Edited by:
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project name: Lab 2
    Date: 03 October 2020
*/

module Solver(
    input clk, 
    input reset,
    input in,
    output reg [2:0] RGB,
    output reg [2:0] solution,
    output reg [2:0] LED
 );

localparam GREEN = 3'b010, RED = 3'b001;

always@(posedge clk, posedge reset) begin
    if(reset) begin
        solution <= 3'b0;
        LED <= 3'b000;
        RGB <= 3'b001;
    end
    else if(in) begin
        LED <= solution;
        RGB <= GREEN;
    end
    else begin 
        solution <= solution + 1;
        LED <= 0;
        RGB <= RED; 
    end      
end
endmodule
