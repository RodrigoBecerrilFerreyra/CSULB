`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: seven_segment.v
// Date: 21 February 2020
// Version: 3.1
//
// Notes: All previous modules in one file for easy copy-pasting.
//////////////////////////////////////////////////////////////////////////////////

module seven_segment(value, clk, rst, cathode, anode);

// Declaration of variables
input [31:0] value;
input clk, rst;
output reg [7:0] cathode, anode;


// Misc wires/regs
reg [3:0] dec_input; //decoder input
reg [2:0] sel; // mux input
wire pulse; // pulse from pulse gen
wire dp = 0; // TODO: implement this better


// 4-bit 8:1 mux
always @(*)
    case(sel)
        3'd0: dec_input = value[3:0];
        3'd1: dec_input = value[7:4];
        3'd2: dec_input = value[11:8];
        3'd3: dec_input = value[15:12];
        3'd4: dec_input = value[19:16];
        3'd5: dec_input = value[23:20];
        3'd6: dec_input = value[27:24];
        3'd7: dec_input = value[31:28];
    endcase

// decoder
always @(*) begin
    case(dec_input)
        4'h0: cathode[6:0] = 7'h3f;
        4'h1: cathode[6:0] = 7'h06;
        4'h2: cathode[6:0] = 7'h5b;
        4'h3: cathode[6:0] = 7'h4f;
        4'h4: cathode[6:0] = 7'h66;
        4'h5: cathode[6:0] = 7'h6d;
        4'h6: cathode[6:0] = 7'h7d;
        4'h7: cathode[6:0] = 7'h07;
        4'h8: cathode[6:0] = 7'h7f;
        4'h9: cathode[6:0] = 7'h6f;
        4'ha: cathode[6:0] = 7'h77;
        4'hb: cathode[6:0] = 7'h7c;
        4'hc: cathode[6:0] = 7'h39;
        4'hd: cathode[6:0] = 7'h5e;
        4'he: cathode[6:0] = 7'h79;
        4'hf: cathode[6:0] = 7'h71;
    endcase
    cathode[7] = dp;
    cathode = ~cathode;
end


// pulse generator
reg [12:0] q_pulse, d_pulse;
always @(posedge clk, posedge rst)
    if(rst) q_pulse <= 13'b0;
    else    q_pulse <= d_pulse;

assign pulse = (q_pulse == 13'd4_999); //20 kHz

always @(*)
    if(pulse) d_pulse = 13'b0;
    else      d_pulse = q_pulse + 13'b1;


// 3-bit counter (for sel)
reg [2:0] d_count;
always @(posedge clk, posedge rst)
    if(rst) sel <= 3'b0;
    else    sel <= d_count;

always @(*)
    if(pulse) d_count = sel + 1;
    else      d_count = sel;


// (left) shift register (rotate)
reg [7:0] d_shift;
always @(posedge clk, posedge rst)
    if(rst) anode <= 8'b1111_1110;
    else    anode <= d_shift;

always @(*)
    if(pulse) d_shift = {anode[6:0], anode[7]};
    else      d_shift = anode;

endmodule
