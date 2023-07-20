`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: DB_PED.v
// Date: 30 March 2020
// Version: 1.0
//
// Notes: Compressed into one file.
//////////////////////////////////////////////////////////////////////////////////

module DB_PED
#(
parameter POSEDGEDETECT = 1
)
(
    input clk, input rst,
    input signal,
    output out
    );

//pulse generator
wire pulse;
reg [16:0] q_pulse, d_pulse;
always @(posedge clk, posedge rst)
    if(rst) q_pulse <= 0;
    else    q_pulse <= d_pulse;
always @(*)
    if(pulse) d_pulse = 0;
    else      d_pulse = q_pulse + 1;
assign pulse = (q_pulse == 17'd100_000); //1 ms at 100 MHz


//debounce
//shift register
wire db;
reg [9:0] q_reg, d_reg;
always @(posedge clk, posedge rst)
    if(rst) q_reg <= 0;
    else    q_reg <= d_reg;
always @(*)
    if(pulse) d_reg = {signal, q_reg[9:1]};
    else      d_reg = q_reg;
assign db = &q_reg;


//posedge detect
reg q1, q2;
always @(posedge clk, posedge rst)
    if(rst) q1 <= 0;
    else    q1 <= db;
always @(posedge clk, posedge rst)
    if(rst) q2 <= 0;
    else    q2 <= q1;
wire ped; assign ped = (q1 && !q2);

assign out = POSEDGEDETECT ? ped : db; 

endmodule
