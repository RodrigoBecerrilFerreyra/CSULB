`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: decoder.v
// Date: 11 February 2020
// Version: 2.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module top_level_seven_segment(
    input [15:0] value,
    input clk,
    input rst,
    output [7:0] cathode,
    output [7:0] anode
    );

reg [3:0] dec_input;
wire [2:0] sel;
wire tick;

always @(*) // 8:1 4-bit mux
    case(sel)
        3'd0: dec_input = value[3:0];
        3'd1: dec_input = value[7:4];
        3'd2: dec_input = value[11:8];
        3'd3: dec_input = value[15:12];
        3'd4: dec_input = value[3:0];
        3'd5: dec_input = value[7:4];
        3'd6: dec_input = value[11:8];
        3'd7: dec_input = value[15:12];
    endcase

decoder dec(.in(dec_input), .dp(0), .cathode(cathode));
pulse_gen pulse(.clk(clk), .rst(rst), .tick(tick));
counter8 counter(.clk(clk), .rst(rst), .tick(tick), .q(sel));
shift_reg shift(.clk(clk), .rst(rst), .ls(tick), .q(anode));

endmodule
