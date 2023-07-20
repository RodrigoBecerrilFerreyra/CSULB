`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: memory_controller_state_machine.v
// Date: 11 May 2020
// Version: 1.0
//
// Notes: Modified-Moore State Machine
//////////////////////////////////////////////////////////////////////////////////

module memory_controller_state_machine(
    input start,
    input done,
    input finish,
    input clk, input rst,
    output write,
    output loadA,
    output loadD,
    output [1:0] pass,
    output reg [2:0] state
    );

//state encoding
localparam S0 = 3'h0,
           S1 = 3'h1,
           S2 = 3'h2,
           S3 = 3'h3,
           S4 = 3'h4,
           S5 = 3'h5,
           S6 = 3'h6,
           S7 = 3'h7;
reg [2:0] next_state;
reg [4:0] out, next_out;

assign {write, loadA, loadD, pass} = out;

always @(posedge clk, posedge rst)
    if(rst)
    begin
        state <= S0;
        out <= 0;
    end
    else
    begin
        state <= next_state;
        out <= next_out;
    end

always @(*)
    if(pass != 2'b11)
        case(state)
            S0: {next_state, next_out} = start ? {S1, 3'b010, out[1:0]} : {S0, 3'b000, out[1:0]};
            S1: {next_state, next_out} = {S2, 3'b001, out[1:0]};
            S2: {next_state, next_out} = {S3, 3'b100, out[1:0]};
            S3: {next_state, next_out} = done ? {S4, 3'b010, out[1:0]} : {S1, 3'b010, out[1:0]};
            S4: {next_state, next_out} = {S5, 3'b001, out[1:0]};
            S5: {next_state, next_out} = {S6, out};
            S6: {next_state, next_out} = done ? {S7, 3'b000, out[1:0] + 1} : {S4, 3'b010, out[1:0]};
            S7: {next_state, next_out} = finish ? {S1, 5'b01000} : {S1, 3'b010, out[1:0]};
        endcase
endmodule
