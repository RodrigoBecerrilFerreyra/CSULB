`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/19/2019 04:59:48 PM
// Design Name: 
// Module Name: counter_32bit_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module counter_32bit_tb();

reg clock;
reg reset;
reg count;
wire [31:0] Q;

always begin
    #50 clock = ~clock;
end

counter_32bit uut(.clk(clock), .reset(reset), .count_en(count), .Q(Q));

initial begin

    clock = 0;
    reset = 1;
    #25;
    reset = 0;
    #275;
    
    count = 0;
    #150;
    count = 1;
    
    #75;
    reset = 1;
    #50;
    reset = 0;
    
    #600;
    count = 0;

end
endmodule
