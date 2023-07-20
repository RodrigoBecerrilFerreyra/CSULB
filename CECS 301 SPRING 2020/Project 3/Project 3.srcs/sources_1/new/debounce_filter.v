`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: debounce_filter.v
// Date: 27 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module debounce_filter(
    input clk,
    input rst,
    input signal,
    output db
    );

//pulse generator
reg [16:0] q_pulse, d_pulse;
always @(posedge clk, posedge rst)
    if(rst) q_pulse <= 0;
    else    q_pulse <= d_pulse;

wire pulse;
assign pulse = (q_pulse == 17'd100_000); //1 ms = 1 kHz

always @(*)
    if(pulse) d_pulse = 0;
    else      d_pulse = q_pulse + 17'b1;


//shift register
reg [9:0] q_shift, d_shift;
always @(posedge clk, posedge rst)
    if(rst) q_shift <= 0;
    else    q_shift <= d_shift;

always @(*)
    if(pulse) d_shift = {signal, q_shift[9:1]};
    else d_shift = q_shift;


//db output
assign db = &q_shift; 

endmodule
