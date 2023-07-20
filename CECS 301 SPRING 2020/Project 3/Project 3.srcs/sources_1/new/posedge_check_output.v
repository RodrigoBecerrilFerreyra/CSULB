`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: posedge_check_output.v
// Date: 27 February 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module posedge_check_output(
    input clk,
    input rst,
    input signal,
    output [7:0] cathode,
    output [7:0] anode
    );

// Debounce Signal Logic
wire debounced_signal, ped;
debounce_filter dbf(.clk(clk), .rst(rst), .signal(signal), .db(debounced_signal));


// Posedge Detector
reg q1, q2;
always @(posedge clk, posedge rst)
    if(rst) q1 <= 0;
    else    q1 <= debounced_signal;
always @(posedge clk, posedge rst)
    if(rst) q2 <= 0;
    else    q2 <= q1;

assign ped = (q1 && !q2);


// Counter (for output)
reg [31:0] q_count, d_count;
always @(posedge clk, posedge rst)
    if(rst) q_count <= 0;
    else    q_count <= d_count;
always @(*)
    if(ped) d_count = q_count + 1;
    else    d_count = q_count;

seven_segment ssd(.value(q_count), .clk(clk), .rst(rst), .cathode(cathode), .anode(anode));

endmodule
