`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/31/2019 05:08:47 PM
// Design Name: 
// Module Name: four_bit_adder_tb
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


module four_bit_adder_tb();

reg [3:0] A_tb;
reg [3:0] B_tb;
reg cin_tb;
wire [3:0] sum_tb;
wire cout_tb;
wire invalid_tb;

four_bit_adder uut(.a(A_tb), .b(B_tb), .cin(cin_tb), .sum(sum_tb), .cout(cout_tb), .invalid(invalid_tb));

integer i;

initial
begin

for(i = 0; i < 16; i = i + 1)
begin
    if (i%4) cin_tb = 1; else cin_tb = 0;
    A_tb = i;
    B_tb = i+10;
    
    if(i == 15) begin A_tb = 1; B_tb = 16'hFFFF; end
    
    #100;
    
    if(sum_tb != A_tb + B_tb + cin_tb) $display("Error: sum=%d cout=&d a=%d b=%d cin=%d", sum_tb, cout_tb, A_tb, B_tb, cin_tb);
    
end

end

endmodule
