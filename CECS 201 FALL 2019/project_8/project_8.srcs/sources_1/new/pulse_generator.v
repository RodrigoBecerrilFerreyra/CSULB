`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 12/03/2019 01:54:18 PM
// Design Name: 
// Module Name: pulse_generator
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


module pulse_generator(clk,reset,pulse);

input clk, reset;
output pulse;
reg [25:0] count;

assign pulse = (count == 56_250_000);

always@(posedge clk, posedge reset)
    if (reset)
        count <= 26'b0;
    else if(pulse)
        count <= 26'b0;
    else
        count <= count + 26'b1;

endmodule
