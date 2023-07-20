`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module Counter(clk, rst, E, sclr, Q, zC);
input clk, rst, E, sclr;
output reg [2:0] Q; output zC;

assign zC = (Q == 5);

reg [2:0] d;

// sequential block
always @(posedge clk, posedge rst)
    if(rst) Q <= 0;
    else    Q <= d;

// combinatorial block
always @(*) begin
    case({E, sclr})
        2'b10: d = Q + 1;
        2'b11: d = 0;
        default: d = Q;
    endcase
    if(zC) d = 0;
end
endmodule
