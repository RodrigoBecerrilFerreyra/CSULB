`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 12/03/2019 01:34:17 PM
// Design Name: 
// Module Name: fsm_w_pulse
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


module fsm_w_pulse_tb();

reg clk;
reg reset;
reg count_up;
reg pulse;
wire [15:0] out;

always begin
    #50 clk = ~clk;
end

fsm_w_pulse uut(.clk(clk), .reset(reset), .cnt_up(count_up), .pulse(pulse), .out(out));

initial begin

    clk = 0;
    pulse = 1;
    reset = 1;
    count_up = 0;
    #100;
    reset = 0;
    count_up = 1;
    #1000;
    count_up = 0;

end
endmodule
