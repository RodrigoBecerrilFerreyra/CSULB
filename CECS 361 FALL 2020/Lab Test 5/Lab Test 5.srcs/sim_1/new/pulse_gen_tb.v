`timescale 1ns / 1ps

/*
    Gita Temelkova
    Alexander Valladarez
    Barbara Reveles
    Don Li
    Len Quach
    Mackenzee Gormican-Navarro
    Zane Navarro
    Rodrigo Becerril Ferreyra
*/

module pulse_gen_tb();

reg clk, rst;
wire pulse;

pulse_gen uut(.clk(clk), .rst(rst), .pulse(pulse));

always #20 clk = ~clk;

initial begin

    rst = 1; clk = 0;
    #20;
    rst = 0;

end
endmodule
