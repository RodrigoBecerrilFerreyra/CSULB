`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/14/2019 05:37:49 PM
// Design Name: 
// Module Name: load_reg_8bit_tb
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


module load_reg_8bit_tb();

reg [7:0] D_tb;
reg clock;
reg reset;
reg load;
wire [7:0] Q_tb;

always begin
    #50 clock = ~clock;
end

load_reg_8bit uut(.D(D_tb), .clk(clock), .ld(load), .reset(reset), .Q(Q_tb));

initial begin

    D_tb = 8'hFF;
    clock = 0;
    reset = 1;
    #25;
    reset = 0;
    load = 0;
    #100;
    
    D_tb = 8'h30;
    load = 1;
    #50;
    
    D_tb = 8'h89;
    load = 0;
    #75;
    load = 1;
    #100;
    
    D_tb = 8'h57;
    load = 0;
    #113;
    
    D_tb = 8'h24;
    load = 1;
    #113;
    
    D_tb = 8'hFF;
    #113;
    
    D_tb = 8'h00;
    load = 0;
    #113;
    
    D_tb = 8'h56;
    #113;
    
    D_tb = 8'h66;
    load = 1;
    reset = 1;
    #25;
    reset = 0;
    #88;
    
    D_tb = 8'h91;
    #113;
    
    D_tb = 8'hF0;
    #113;
    
    D_tb = 8'h02;
    #113;
    
    D_tb = 8'hFA;
    #113;

end
endmodule
