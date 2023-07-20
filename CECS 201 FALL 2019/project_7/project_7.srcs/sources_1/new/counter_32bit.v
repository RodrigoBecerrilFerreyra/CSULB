`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/19/2019 04:55:10 PM
// Design Name: 
// Module Name: counter_32bit
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


module counter_32bit(
    input clk,
    input reset,
    input count_en,
    output reg [31:0] Q
);

always @(posedge clk or posedge reset) begin

    if(reset) Q <= 32'h00000000;
    else if (count_en) Q <= Q + 1;

end
endmodule
