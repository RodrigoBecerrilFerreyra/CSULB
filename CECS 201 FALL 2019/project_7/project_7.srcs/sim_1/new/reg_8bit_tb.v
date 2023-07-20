`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/14/2019 04:36:36 PM
// Design Name: 
// Module Name: reg_8bit_tb
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


module reg_8bit_tb();

reg [7:0] D_tb;
reg clock;
reg reset;
wire [7:0] Q_tb;

always begin
    #50 clock = ~clock;
end

reg_8bit uut (.D(D_tb), .clk(clock), .reset(reset), .Q(Q_tb));

initial begin
    
    D_tb = 8'hFF;
    clock = 0;
    reset = 1;
    #25;
    reset = 0;
    #75;

    D_tb = 8'hA1;
    #325;
    
    D_tb = 8'h09;
    #130;
    
    D_tb = 8'hFF;
    reset = 1;
    #392;
    reset = 0;
    #175;

    D_tb = 8'h01;
    #20;
    D_tb = 8'h8F;
    #100;
    
    D_tb = 8'h78;
    #1000;

end
endmodule
