`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS-201 Fall 2019
// Engineer: Dr. Jelena Trajkovic
// 
// Create Date: 10/07/2019 11:17:08 AM
// Design Name: 
// Module Name: mux_4to1_4bit_case_tb
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


module mux_4to1_4bit_case_tb();

    reg [3:0] in0_tb;
    reg [3:0] in1_tb;
    reg [3:0] in2_tb;
    reg [3:0] in3_tb;
    reg [2:0] sel_tb;
    
    wire [3:0] out_tb;

mux_4to1_4bit_case uut(
    .in0(in0_tb),
    .in1(in1_tb),
    .in2(in2_tb),
    .in3(in3_tb),
    .sel(sel_tb),
    .out(out_tb)
    );
    
 initial begin
       
       in0_tb = 4'b0000;
       in1_tb = 4'b0000;
       in2_tb = 4'b0000;
       in3_tb = 4'b0000;
       sel_tb = 2'b00;
       #100;
       
       in0_tb = 4'b0001;
       in1_tb = 4'b0000;
       in2_tb = 4'b0000;
       in3_tb = 4'b0000;
       sel_tb = 2'b00;
       #100;
       
       in0_tb = 4'b0000;
       in1_tb = 4'b0010;
       in2_tb = 4'b0000;
       in3_tb = 4'b0000;
       sel_tb = 2'b01;
       #100;
           
       in0_tb = 4'b0000;
       in1_tb = 4'b0011;
       in2_tb = 4'b0000;
       in3_tb = 4'b0000;
       sel_tb = 2'b01;
       #100;
       
       in0_tb = 4'b0000;
       in1_tb = 4'b0000;
       in2_tb = 4'b0100;
       in3_tb = 4'b0000;
       sel_tb = 2'b10;
       #100;
               
       in0_tb = 4'b0000;
       in1_tb = 4'b0000;
       in2_tb = 4'b0101;
       in3_tb = 4'b0000;
       sel_tb = 2'b10;
       #100;
           
       in0_tb = 4'b0000;
       in1_tb = 4'b0000;
       in2_tb = 4'b000;
       in3_tb = 04'b0110;
       sel_tb = 2'b11;
       #100;
        
        in0_tb = 4'b0000;
        in1_tb = 4'b0000;
        in2_tb = 4'b0000;
        in3_tb = 4'b0111;
        sel_tb = 2'b11;
        #100;                                  
       end
       
endmodule
