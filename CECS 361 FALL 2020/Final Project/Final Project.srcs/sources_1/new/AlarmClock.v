`timescale 1ns / 1ps
`default_nettype none
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
module AlarmClock(clk, rst, en, ctrl, datain, ctdn, done);
input wire clk, rst, en, ctrl, ctdn;
input [15:0] datain;
output reg done;

// main counter (counts down)
reg [15:0] counter_q, counter_d;
always @(posedge clk, posedge rst)
    if(rst) counter_q <= 0;
    else    counter_q <= counter_d;

always @(*) begin
    if(en) begin
        counter_d = ctdn ? counter_q - 1 : counter_q;
        counter_d = (ctrl & ~done) ? datain : counter_d;
    end else
        counter_d = counter_q;
end

// negedge detect
wire negedge_detected;
negedge_detect NED(.clk(clk), .rst(rst), .d(|counter_q), .det(negedge_detected));

// done logic
always@(posedge clk, posedge rst)
    if(rst)              done <= 1'b0;
    else if(ctrl & done) done <= 1'b0;
    else                 done <= negedge_detected;

endmodule
