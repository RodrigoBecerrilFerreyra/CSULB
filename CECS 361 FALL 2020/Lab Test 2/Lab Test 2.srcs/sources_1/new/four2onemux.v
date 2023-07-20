`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab Test 2
    Start Date: 03 September 2020
    End Date: 03 September 2020
*/
module four2onemux(
    input a,
    input b,
    input c,
    input d,
    input [1:0] sel,
    output out
);

wire mux0out, mux1out;

two2onemux mux0(.in0(a), .in1(b), .sel(sel[1]), .out(mux0out));
two2onemux mux1(.in0(c), .in1(d), .sel(sel[1]), .out(mux1out));
two2onemux finalmux(.in0(mux0out), .in1(mux1out), .sel(sel[0]), .out(out));

endmodule
