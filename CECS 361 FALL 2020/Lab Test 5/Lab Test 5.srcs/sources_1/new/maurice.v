`timescale 1ns / 1ps
/*
    Reverse Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Engineer: Maurice Komara et al.
    Date: 15 October 2020
*/
module maurice(
    input clk, a,
    output reg [3:0] q
);

initial q = 0;

always @(posedge clk) begin
    if(a) q <= 7;
    else if (q == 0) q <= 4'he;
    else q = q - 1;
end
endmodule
