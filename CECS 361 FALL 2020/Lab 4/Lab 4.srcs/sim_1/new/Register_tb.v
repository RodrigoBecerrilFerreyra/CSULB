`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module Register_tb();
reg clk, rst, E;
reg [3:0] D;
wire [3:0] Q;
integer i = 0;

Register uut(.clk(clk), .rst(rst), .E(E), .D(D), .Q(Q));

always #5 clk = ~clk; // 10 ns clock cycle

initial begin

    clk = 0; rst = 1; E = 1; D = 0;
    #5;
    rst = 0;
    
    // testing E = 1
    for(i = 0; i < 16; i = i + 1) begin
        D = i;
        #10;
    end

    // testing E = 0
    E = 0;
    for(i = 0; i < 16; i = i + 1) begin
        D = i;
        #10;
    end
    $finish;

end
endmodule
