`timescale 1ns / 1ps

module circuit1(
    input a, b, c,
    output o
);

wire wiretop, wirebot;

assign wiretop = a | ~b;
assign wirebot = a | c;
assign o = wiretop & wirebot;

endmodule
