`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 12/03/2019 02:18:19 PM
// Design Name: 
// Module Name: pulse_generator_tb
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


module pulse_generator_tb();

reg clock;
reg reset;
wire pulse;

always begin
    #25 clock = ~clock;
end

pulse_generator uut(.clk(clock), .reset(reset), .pulse(pulse));

initial begin

    clock = 0;
    reset = 1;
    #10;
    reset = 0;

end
endmodule
