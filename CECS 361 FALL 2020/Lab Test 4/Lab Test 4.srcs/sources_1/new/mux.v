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

module mux(
    input [15:0] in1,
    input [15:0] in0,
    input sel,
    output [15:0] out
);

assign out = sel ? in1 : in0;

endmodule
