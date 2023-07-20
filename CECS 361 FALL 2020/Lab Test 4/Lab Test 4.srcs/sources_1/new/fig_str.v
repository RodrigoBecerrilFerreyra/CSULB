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

module fig_str(
    input en, input clk, input rst,
    output [15:0] out
);

// registers
wire [15:0] dr1, dr0;
wire [15:0] qr1, qr0;
dff reg1(.d(dr1), .q(qr1), .clk(clk), .rst(rst), .default_value(1));
dff reg0(.d(dr0), .q(qr0), .clk(clk), .rst(rst), .default_value(0));

// muxes
mux mux1(.in0(qr1), .in1(out), .sel(en), .out(dr1));
mux mux0(.in0(qr0), .in1(qr1), .sel(en), .out(dr0));

// summing
assign out = qr1 + qr0;

endmodule
