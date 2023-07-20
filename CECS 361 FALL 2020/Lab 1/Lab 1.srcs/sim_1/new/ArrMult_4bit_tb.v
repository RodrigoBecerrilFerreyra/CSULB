`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab 1
    Date: 10 September 2020
*/
module ArrMult_4bit_tb();

reg [3:0] a, b;
wire [7:0] prod;
ArrMult_4bit uut(.a(a), .b(b), .prod(prod));

integer i, j;
reg [7:0] expected_product;

initial
begin
    a = 4'b1101; b = 4'b1001;
    #10;
    
    for(i = 0; i < 16; i = i + 1)
    begin
        for(j = 0; j < 16; j = j + 1)
        begin
            a = i; b = j;
            expected_product = a*b;
            #1;
            if(expected_product != prod)
                $display("%d * %d = %d, not %d", a, b, expected_product, prod);
            else
                $display("Test passed: %d * %d = %d", a, b, prod);
        end
    end
end
endmodule
