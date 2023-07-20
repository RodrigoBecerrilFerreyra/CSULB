`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/24/2019 05:27:25 PM
// Design Name: 
// Module Name: decoder_tb
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


module decoder_tb();

reg [2:0] in_tb;
reg enable_tb;
wire [7:0] out_tb;
integer i;

decoder uut(.in(in_tb), .enable(enable_tb), .out(out_tb));

initial
begin

enable_tb = 1;
for (i=0; i<8; i=i+1)
    begin
    in_tb = i[3:0];
    #100;
    end

enable_tb = 0;
for (i=0; i<8; i=i+1)
    begin
    in_tb = i[3:0];
    #100;
    end

end

endmodule
