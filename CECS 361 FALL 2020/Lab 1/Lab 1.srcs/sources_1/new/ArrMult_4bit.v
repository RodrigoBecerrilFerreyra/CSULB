`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab 1
    Date: 10 September 2020
*/
module ArrMult_4bit(
    input [3:0] a,
    input [3:0] b,
    output [7:0] prod
);

wire [3:0] partial [0:3]; //partial products

// Partial Product Tree
mux2to1 mux00(.a(a[0]), .b(0), .sel(b[0]), .out(partial[0][0]));
mux2to1 mux01(.a(a[1]), .b(0), .sel(b[0]), .out(partial[0][1]));
mux2to1 mux02(.a(a[2]), .b(0), .sel(b[0]), .out(partial[0][2]));
mux2to1 mux03(.a(a[3]), .b(0), .sel(b[0]), .out(partial[0][3]));

mux2to1 mux10(.a(a[0]), .b(0), .sel(b[1]), .out(partial[1][0]));
mux2to1 mux11(.a(a[1]), .b(0), .sel(b[1]), .out(partial[1][1]));
mux2to1 mux12(.a(a[2]), .b(0), .sel(b[1]), .out(partial[1][2]));
mux2to1 mux13(.a(a[3]), .b(0), .sel(b[1]), .out(partial[1][3]));

mux2to1 mux20(.a(a[0]), .b(0), .sel(b[2]), .out(partial[2][0]));
mux2to1 mux21(.a(a[1]), .b(0), .sel(b[2]), .out(partial[2][1]));
mux2to1 mux22(.a(a[2]), .b(0), .sel(b[2]), .out(partial[2][2]));
mux2to1 mux23(.a(a[3]), .b(0), .sel(b[2]), .out(partial[2][3]));

mux2to1 mux30(.a(a[0]), .b(0), .sel(b[3]), .out(partial[3][0]));
mux2to1 mux31(.a(a[1]), .b(0), .sel(b[3]), .out(partial[3][1]));
mux2to1 mux32(.a(a[2]), .b(0), .sel(b[3]), .out(partial[3][2]));
mux2to1 mux33(.a(a[3]), .b(0), .sel(b[3]), .out(partial[3][3]));

// Array Multiplier Adder
assign prod[0] = partial[0][0];

wire prod1_ha0_c_out;
HA prod1_ha0(.a(partial[0][1]), .b(partial[1][0]), .c_out(prod1_ha0_c_out), .sum(prod[1]));

wire prod2_fa0_sum, prod2_fa0_c_out;
wire prod2_ha0_c_out;
FA prod2_fa0(.a(partial[0][2]), .b(partial[1][1]), .c_in(prod1_ha0_c_out), .sum(prod2_fa0_sum), .c_out(prod2_fa0_c_out));
HA prod2_ha0(.a(prod2_fa0_sum), .b(partial[2][0]), .sum(prod[2]), .c_out(prod2_ha0_c_out));

wire prod3_ha0_sum, prod3_ha0_c_out;
wire prod3_fa0_sum, prod3_fa0_c_out;
wire prod3_fa1_sum;
HA prod3_ha0(.a(prod2_fa0_c_out), .b(prod2_ha0_c_out), .c_out(prod3_ha0_c_out), .sum(prod3_ha0_sum));
FA prod3_fa0(.a(partial[0][3]), .b(partial[1][2]), .c_in(prod3_ha0_sum), .sum(prod3_fa0_sum), .c_out(prod3_fa0_c_out));
FA prod3_fa1(.a(partial[2][1]), .b(partial[3][0]), .c_in(prod3_fa0_sum), .sum(prod[3]), .c_out(prod3_fa1_c_out));

wire prod4_fa0_sum, prod4_fa0_c_out;
wire prod4_fa1_sum, prod4_fa1_c_out;
wire prod4_ha0_c_out;
FA prod4_fa0(.a(prod3_fa0_c_out), .b(prod3_ha0_c_out), .c_in(prod3_fa1_c_out), .sum(prod4_fa0_sum), .c_out(prod4_fa0_c_out));
FA prod4_fa1(.a(partial[1][3]), .b(partial[2][2]), .c_in(prod4_fa0_sum), .sum(prod4_fa1_sum), .c_out(prod4_fa1_c_out));
HA prod4_ha0(.a(prod4_fa1_sum), .b(partial[3][1]), .sum(prod[4]), .c_out(prod4_ha0_c_out));

wire prod5_fa0_sum, prod5_fa0_c_out;
wire prod5_fa1_c_out;
FA prod5_fa0(.a(prod4_fa1_c_out), .b(prod4_fa0_c_out), .c_in(prod4_ha0_c_out), .sum(prod5_fa0_sum), .c_out(prod5_fa0_c_out));
FA prod5_fa1(.a(partial[2][3]), .b(partial[3][2]), .c_in(prod5_fa0_sum), .sum(prod[5]), .c_out(prod5_fa1_c_out));

FA prod6_fa0(.a(prod5_fa0_c_out), .b(partial[3][3]), .c_in(prod5_fa1_c_out), .sum(prod[6]), .c_out(prod[7]));

endmodule
