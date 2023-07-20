`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module Circuit_SA1_tb();
reg a, b, c;
wire f0_expected, f1_expected;
wire f0_actual, f1_actual;
integer i;

Circuit_SA1 uut(.A(a), .B(b), .C(c), .F0(f0_actual), .F1(f1_actual));
Circuit_SA1_expected expected_result(.A(a), .B(b), .C(c), .F0(f0_expected), .F1(f1_expected));

initial begin

    for(i = 0; i < 8; i = i + 1)
    begin
        {a, b, c} = i;
        #10;
    end
    
    $finish;
 
end
endmodule
