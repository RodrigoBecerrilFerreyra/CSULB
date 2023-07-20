`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: debounce_filter_counter.v
// Date: 27 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module debounce_filter_counter(
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


//counter
reg [3:0] q_count, d_count;
always @(posedge clk, posedge rst)
    if(rst) q_count <= 0;
    else    q_count <= d_count;

assign db = (q_count == 4'b1010);

always @(*) begin
    if(pulse)
        case({signal, db})
            2'b10: d_count = q_count + 1;
            2'b11: d_count = q_count;
            2'b00: d_count = 0;
            2'b01: d_count = 0;
        endcase
end
endmodule
