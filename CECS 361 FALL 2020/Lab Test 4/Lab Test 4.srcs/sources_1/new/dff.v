`timescale 1ns / 1ps

/*
    Alex Gonzalez
    Jorge Aguilar
    Jorge Sanchez
    Kenneth Esquivel
    Musa Datti
    Nolan Santellanes
    Ryan Heng
    Rodrigo Becerril Ferreyra
*/

module dff(
    input clk,
    input [15:0] d,
    output reg [15:0] q,
    input rst, input default_value
);

always @(posedge clk, posedge rst)
    if(rst) q <= default_value;
    else q <= d;

endmodule
