`timescale 1ns / 1ps

module ben(
    input clk, Jim, a,
    output reg [2:0] q
);

always @(posedge clk, posedge Jim)
    if(Jim) q <= 0;
    else case (a)
        0: q <= q - 1;
        1: q <= q + 1;
    endcase

endmodule
