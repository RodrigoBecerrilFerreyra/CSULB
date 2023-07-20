`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab Test 2
    Start Date: 08 September 2020
    End Date: 08 September 2020
*/
module dff_d_latch_tb();

reg d, clk;
wire q_dff, q_latch;//, q_not_dff, q_not_latch;
reg [15:0] data; integer index;

dff uut1(.d(d), .q(q_dff), .clk(clk));
d_latch uut(.d(d), .q(q_latch), .en(clk));

always #20 clk = ~clk;

always @(posedge clk)
begin
    #10;
    d = data >> index;
    index = index + 1;
    #10;
    d = data >> index;
    index = index + 1;
end

initial
begin
    clk = 0; index = 0; data = 16'h45e9; d = 0;
end
endmodule
