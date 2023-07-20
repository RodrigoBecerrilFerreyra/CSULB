`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/14/2019 04:32:49 PM
// Design Name: 
// Module Name: reg_8bit
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


module reg_8bit(
    input [7:0] D,
    input clk,
    input reset,
    output reg [7:0] Q
);

always @(posedge clk or posedge reset) begin
    if (reset) begin
        Q <= 8'H00;
    end else begin
        Q <= D;
    end
end

endmodule
