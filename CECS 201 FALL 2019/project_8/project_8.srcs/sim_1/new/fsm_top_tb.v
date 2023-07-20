`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 12/03/2019 04:15:19 PM
// Design Name: 
// Module Name: fsm_top_tb
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


module fsm_top_tb();
reg clk;
reg reset;
reg count_up;
wire [15:0] out;

always begin
    #50 clk = ~clk;
end

fsm_top uut(.clk(clk), .reset(reset), .cnt_up(count_up), .out(out));

initial begin

    clk = 0;
    reset = 1;
    count_up = 0;
    #100;
    reset = 0;
    count_up = 1;

end
endmodule
