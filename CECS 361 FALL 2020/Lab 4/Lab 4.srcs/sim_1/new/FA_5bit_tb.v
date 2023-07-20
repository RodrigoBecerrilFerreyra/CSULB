`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module FA_5bit_tb();

reg [4:0] A, B; reg cin;
wire [4:0] Sum; wire cout;
//wire[4:0] testsum; wire testcout;
integer i;

FA_5bit uut(.A(A), .B(B), .cin(cin), .Sum(Sum), .cout(cout));

//assign {testcout, testsum} = A + B + cin;

initial begin
    for(i = 0; i < 1024 /*2^12*/; i = i + 1) begin
        {A, B, cin} = i; // {A, B, cin} is 5+5+1 = 11 bits long
        #5;
        if({cout, Sum} != A + B + cin)
            $display("Error: %d + %d + %d != {%d, %d}", A, B, cin, cout, Sum);
    end
    $finish;
end
endmodule
