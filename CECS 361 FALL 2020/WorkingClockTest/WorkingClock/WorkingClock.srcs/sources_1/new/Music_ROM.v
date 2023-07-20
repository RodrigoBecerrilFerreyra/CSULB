`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineer: Colton Curtis, Rodrigo Becerril Ferreya, Ethan Hua
// 
// Create Date: 12/04/2020 09:44:33 PM
// Design Name: 
// Module Name: Music_ROM
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


module Music_ROM(
    input songChoice,
    input clk,
	input [7:0] address,
	output reg [7:0] note
    );
    
always @(posedge clk)
    begin
    if (songChoice)
        begin
            case(address)
                  0: note<= 8'd29;
                  1: note<= 8'd29;
                  2: note<= 8'd41;
                  3: note<= 8'd24;
                  4: note<= 8'd35;
                  5: note<= 8'd34;
                  6: note<= 8'd32;
                  7: note<= 8'd29;
                  8: note<= 8'd32;
                  9: note<= 8'd34;
                 10: note<= 8'd27;
                 11: note<= 8'd27;
                 12: note<= 8'd41;
                 13: note<= 8'd24;
                 14: note<= 8'd35;
                 15: note<= 8'd34;
                 16: note<= 8'd32;
                 17: note<= 8'd29;
                 18: note<= 8'd32;
                 19: note<= 8'd34;
                 20: note<= 8'd26;
                 21: note<= 8'd26;
                 22: note<= 8'd41;
                 23: note<= 8'd24;
                 24: note<= 8'd35;
                 25: note<= 8'd34;
                 26: note<= 8'd32;
                 27: note<= 8'd29;
                 28: note<= 8'd32;
                 29: note<= 8'd34;
                 30: note<= 8'd25;
                 31: note<= 8'd25;
                 32: note<= 8'd41;
                 33: note<= 8'd24;
                 34: note<= 8'd35;
                 35: note<= 8'd34;
                 36: note<= 8'd32;
                 37: note<= 8'd29;
                 38: note<= 8'd32;
                 39: note<= 8'd34;
                default: note <= 8'd00;
            endcase
        end
    else
        begin // todo, make it so it continues indefinitly
            case(address)
                  0: note<= 8'd25;
                  2: note<= 8'd25;
                  4: note<= 8'd25;
                  6: note<= 8'd25;
                  8: note<= 8'd25;
                 10: note<= 8'd25;
                 12: note<= 8'd25;
                 14: note<= 8'd25;
                 16: note<= 8'd25;
                 18: note<= 8'd25;
                 20: note<= 8'd25;
                 22: note<= 8'd25;
                 24: note<= 8'd25;
                 26: note<= 8'd25;
                 28: note<= 8'd25;
                 30: note<= 8'd25;
                 32: note<= 8'd25;
                 34: note<= 8'd25;
                 36: note<= 8'd25;
                 38: note<= 8'd25;
                 40: note<= 8'd25;
                 42: note<= 8'd25;
                 44: note<= 8'd25;
                 46: note<= 8'd25;
                 48: note<= 8'd25;
                 50: note<= 8'd25;
                 52: note<= 8'd25;
                 54: note<= 8'd25;
                 56: note<= 8'd25;
                 58: note<= 8'd25;
                 60: note<= 8'd25;
                 62: note<= 8'd25;
                default: note <= 8'd00;
            endcase
            end
        end
endmodule
