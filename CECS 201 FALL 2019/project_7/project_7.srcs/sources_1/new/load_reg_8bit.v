`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/14/2019 05:32:44 PM
// Design Name: 
// Module Name: load_reg_8bit
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


module load_reg_8bit(
    input [7:0] D,
    input clk,
    input ld,
    input reset,
    output reg [7:0] Q
);

always @(posedge clk or posedge reset) begin

    if (reset) begin
        Q <= 8'h00;
    end else begin
        if (ld) begin
            Q <= D;
        end
    end
    
end
endmodule
