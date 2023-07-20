`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: California State University, Long Beach
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 09/12/2019 04:58:36 PM
// Design Name: 
// Module Name: add_behavioral_testbench
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

module add_behavioral_testbench();
    
    reg [2:0] in0_tb;
    reg [2:0] in1_tb;
    wire [2:0] out_tb;
    wire carry_tb;
    
    
    add_behavioral uut(.in0(in0_tb), .in1(in1_tb), .out(out_tb), .carry(carry_tb));
    
    initial begin
    
    in0_tb = 3'b001;
    in1_tb = 3'b001;
    #500;
    
    in0_tb = 3'b111;
    in1_tb = 3'b111;
    #500;
    
    in0_tb = 3'b111;
    in1_tb = 3'b110;
    #500
    
    in0_tb = 3'b000;
    in1_tb = 3'b000;
    #500;
    
    in0_tb = 3'b011;
    in1_tb = 3'b101;
    #500;
    
    end
    
endmodule
