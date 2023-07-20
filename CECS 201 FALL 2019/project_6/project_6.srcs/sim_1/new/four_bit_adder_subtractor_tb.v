`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/05/2019 05:24:38 PM
// Design Name: 
// Module Name: four_bit_adder_subtractor_tb
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


module four_bit_adder_subtractor_tb();

reg [3:0] A_tb;
reg [3:0] B_tb;
reg M_tb;
wire [3:0] sum_tb;
wire cout_tb;
wire invalid_tb;
integer i;

four_bit_adder_subtractor uut(.a(A_tb), .b(B_tb), .sel(M_tb), .out(sum_tb), .cout(cout_tb), .invalid(invalid_tb));

initial
begin

for(i=0; i<16; i=i+1)
    begin
        M_tb = 0;
        A_tb = i;
        B_tb = i + 3;
        
        if(i==15) begin A_tb = 1; B_tb = 16'hFFFF; end
        #100;
        
        if(sum_tb != A_tb + B_tb) $display("Error: sum=%d cout=%d a=%d b=%d m=%d invalid=%d", sum_tb, cout_tb, A_tb, B_tb, M_tb, invalid_tb);
    end

for(i = -7; i < 7; i = i+1)
    begin
        M_tb = 1;
        A_tb = i;
        B_tb = i+3;
        #100;
        if((16 - sum_tb) != A_tb - B_tb) $display("Error: sum=%d cout=&d a=%d b=%d m=%d invalid=%d", sum_tb, cout_tb, A_tb, B_tb, M_tb, invalid_tb);
    end
end

endmodule
