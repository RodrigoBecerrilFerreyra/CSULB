`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: Mem_top.v
// Date: 12 May 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module Mem_top(
    input clk,
    input rst,
    input start,
    output finish,
    output error
    );

wire [15:0] rdata, wdata;
wire [14:0] adrs;
wire write, done, loadA, loadD;
wire [1:0] pass;
wire [2:0] state;

memory_controller_state_machine control
(
    .clk(clk), .rst(rst), .start(start), .done(done),
    .finish(finish), .write(write), .loadA(loadA), .loadD(loadD),
    .pass(pass), .state(state)
);

ipmemory memory(.a(adrs), .d(wdata), .we(write), .clk(clk), .spo(rdata));

supplemental_logic misc
(
    .clk(clk), .rst(rst), .pass(pass), .loadA(loadA),
    .loadD(loadD), .wdata(wdata), .state(state), .adrs(adrs),
    .rdata(rdata), .finish(finish), .error(error), .done(done)
);

endmodule
