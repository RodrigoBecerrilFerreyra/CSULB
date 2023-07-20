`timescale 1ns / 1ps

module ben_tb();

reg clk, rst, a;
wire [2:0] q;

ben uut(.clk(clk), .Jim(rst), .a(a), .q(q));

always #5 clk = ~clk;

initial begin
    clk = 1; rst = 1; a = 1;
    #5;
    rst = 0;
    #120;
    a = 0;
    #80;
    a = 1;
    #40;
    a = 0;
end
endmodule
