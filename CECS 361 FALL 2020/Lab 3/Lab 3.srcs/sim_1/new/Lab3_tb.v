`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 3
    Date: 15 October 2020
*/
module Lab3_tb();

reg a, b, c, d, e;
wire o;
integer i;

lab3 uut(.A(a), .B(b), .C(c), .D(d), .E(e), .Out(o));

initial begin

    for(i = 0; i < 32; i = i + 1) begin
        {a, b, c, d, e} = i;
        #30;
    end

end
endmodule
