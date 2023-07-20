`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/22/2019 05:13:00 PM
// Design Name: 
// Module Name: encoder_tb
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


module encoder_tb();

reg [7:0] in_tb;
wire [2:0] out_tb;
wire valid_tb;

encoder uut(.in(in_tb), .out(out_tb), .valid(valid_tb));

initial
begin
//    in_tb = 8'b00000000;
//    #100;
//    in_tb = 8'b00000001;
//    #100;
//    in_tb = 8'b00000010;
//    #100;
//    in_tb = 8'b00000100;
//    #100;
//    in_tb = 8'b00001000;
//    #100;
//    in_tb = 8'b00010000;
//    #100;
//    in_tb = 8'b00100000;
//    #100;
//    in_tb = 8'b01000000;
//    #100;
//    in_tb = 8'b10000000;
//    #100;

in_tb = 8'b0000001;


for (real i = 0; i < 9; i = i + 1)
    #100 in_tb = in_tb << 1;

end

endmodule
