`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: supplemental_logic.v
// Date: 12 May 2020
// Version: 1.0
//
// Notes:
//////////////////////////////////////////////////////////////////////////////////

module supplemental_logic(
    input clk,
    input rst,
    input loadA,
    input loadD,
    input [1:0] pass,
    input [15:0] rdata,
    input [3:0] state,
    output [15:0] wdata,
    output [14:0] adrs,
    output finish,
    output reg error,
    output done
    );

reg [14:0] adreg;
reg [15:0] dtreg, muxdat;
wire errorD;

assign finish = (pass == 2'b11);
assign done = (adreg == 15'h7fff);
assign adrs = adreg;
assign wdata = dtreg;
assign errorD = ((state == 3'b100) & (dtreg != rdata) & (!done));

always @(posedge clk, posedge rst)
    if(rst)         adreg <= 15'h7fff;
    else if (loadA) adreg <= adreg + 15'b1;

always @(posedge clk, posedge rst)
    if(rst)        dtreg <= 16'b0;
    else if(loadD) dtreg <= muxdat;

always @(*)
    case(pass)
        2'h0: muxdat = ~adreg;
        2'h1: muxdat = {1'b0, adreg[14:1]};
        2'h2: muxdat = 16'h5555;
        2'h3: muxdat = 16'haaaa;
    endcase

always @(posedge clk, posedge rst)
    if(rst) error <= 0;
    else if(errorD) error <= 1;
    else error <= error;

endmodule
