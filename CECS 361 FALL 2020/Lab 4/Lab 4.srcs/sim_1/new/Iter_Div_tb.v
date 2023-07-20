`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 30 October 2020
*/
module Iter_Div_tb();
reg clk, rst, E;
reg [5:0] A; reg [3:0] B;
wire [5:0] Q; wire [3:0] R;
wire done;
integer i, j;

Iter_Div uut(.clk(clk), .rst(rst), .E(E), .A(A), .B(B), .done(done), .Q(Q), .R(R));

always #5 clk = ~clk;

initial begin

    rst = 1; clk = 1; E = 1; {A, B, i, j} = 0;
    #5;
    rst = 0;

    for(i = 0; i < 64; i = i + 1) begin
        A = i;
        for(j = 0; j < 16; j = j + 1) begin
            B = j;
            E = 1;
            #5;
            while(~done) #5;

            $write("Test: %d = %d*%d + %d ", A, B, Q, R);
            if(Q != A/B || R != A%B) $display("FAILED -------");
            else                     $display("passed");
            
            E = 0;
            rst = 1; #5; rst = 0;

        end
    end

    $finish;

end
endmodule
