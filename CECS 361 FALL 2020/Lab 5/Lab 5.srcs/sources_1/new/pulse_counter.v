`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module pulse_counter
#(parameter MAX_COUNT = 26'd49_999_999)
(input wire clk, input wire rst, output wire tick);

reg [25:0] counter, next_value;

assign tick = (counter == MAX_COUNT);

always @(posedge clk, posedge rst)
    if(rst) counter <= 0;
    else    counter <= next_value;

always @(*)
    if(tick) next_value = 0;
    else     next_value = counter + 1;

endmodule
