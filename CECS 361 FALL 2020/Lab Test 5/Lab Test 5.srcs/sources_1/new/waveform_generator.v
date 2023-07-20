`timescale 1ns / 1ps

module waveform_generator(
    input clk, a,
    output reg [2:0] q
);

initial q = 0;

always @(posedge clk)
    if(a) q = 4;
    else if (q < 6)  q = q + 1;
    else q = 0;

endmodule
