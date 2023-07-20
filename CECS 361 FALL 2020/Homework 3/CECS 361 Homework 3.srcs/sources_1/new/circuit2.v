`timescale 1ns / 1ps

module circuit2(
    input a, b, c,
    output o
);

wire wirebot;
assign wirebot = ~b | c;
assign o = a & wirebot;

endmodule
