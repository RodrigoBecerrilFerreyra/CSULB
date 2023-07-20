`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineer: Colton Curtis, Rodrigo Becerril Ferreya, Ethan Hua
// 
// Create Date: 11/16/2020 04:03:29 PM
// Design Name: 
// Module Name: ThreeSecondTimer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ThreeSecondTimer(clk, rst, btn, mode, tst);
input clk, rst, btn;
input [1:0] mode;
reg [28:0] tcount;
wire tick;
output reg tst;

    // Tick Generator (Tick every 3s)
    assign tick = tcount == 29'd299999999;
    always @(posedge clk, posedge rst) begin
        if (rst || !btn) begin
            tcount <= 29'b0;
            tst <= 1'b0;
        end else if (btn)
            tcount <= tcount + 17'b1;        
    end
    
    always @(posedge clk) begin
        if (mode == 2'b00 && tick) tst <= 1'b1;
        else if (btn && !tst) tcount <= tcount + 17'b1;
        if (tst && !btn) tst <= 1'b0;
    end
endmodule

