`timescale 1ns / 1ps
/*
    Reverse Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Engineer: Maurice Komara et al.
    Date: 15 October 2020
*/
module maurice_tb();

reg a, clk;
wire [3:0] q;

maurice uut(.a(a), .q(q), .clk(clk));

always #20 clk = ~clk;

initial begin
    clk = 0; a = 1;
    #50;
    a = 0;
    #150;
    a = 1;
    #50;
    a = 0;
end
endmodule
