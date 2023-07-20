`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/20/2020 07:02:09 PM
// Design Name: 
// Module Name: FA8_tb
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


module FA_tb();

reg  [0:0] A;
reg  [0:0] B;
reg       Ci;
wire [0:0] Y;
wire       Co;

integer    i;
  
  //instantiate the device under test;  
  FA FA(
          .A(A), 
          .B(B), 
          .Ci(Ci), 
          .Y(Y), 
          .Co(Co)
          );

//generate the stimulus

initial begin
   A  = 0;
   B  = 0;
   Ci = 0;
   i  = 0;
   
   for (i=0; i<16; i = i + 1)
      begin
      #50 
      A  = $random;
      B  = $random;
      Ci = $random;
      
      #50
      if (Y != A+B+Ci) $display("Error!");
      end
   end
   
endmodule
