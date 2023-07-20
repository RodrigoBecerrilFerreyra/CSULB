`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 12/03/2019 01:59:48 PM
// Design Name: 
// Module Name: fsm_top
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


module fsm_top(clk , reset, out, in);

input in, clk, reset;
output [15:0] out;
wire pulseConnect;

pulse_generator pulse_gen(.clk(clk),.reset(reset),.pulse(pulseConnect));
fsm_w_pulse fsm(.clk(clk),.reset(reset),.pulse(pulseConnect),.cnt_up(in),.out(out));

endmodule
