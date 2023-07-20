`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: decoder.v
// Date: 06 February 2020
// Version: 2.0
//
// Notes: Cathode[7:0] is actually {hgfedcba}.
//////////////////////////////////////////////////////////////////////////////////

module decoder(
    input [3:0] in,
    input dp,
    output reg [7:0] cathode
    );

always @(*) begin
    case(in)
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

endmodule
