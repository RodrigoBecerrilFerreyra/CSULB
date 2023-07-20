`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineers: Jose Aceves & Amin Rezaei
// Create Date: 08/30/2020 03:37:49 PM
// Design Name: 361_Lab2
// Module Name: CNF
// Revision 0.01 - File Created
//////////////////////////////////////////////////////////////////////////////////

module CNF(
    input A,
    input B,
    input C,
    input [1:0] sel,
    output reg out
    );
 
    always@(*) begin
        case(sel)
            2'b00: out = (A|B|C) & (!A|B|!C) & (A|!B|!C) & (!A|!B|!C) & (!A|!B|C); 
            2'b01: out = (A|B|C) & (A|B|!C) & (A|!B|C) & (A|!B|!C) & (!A|B|C) & (!A|!B|!C);
            2'b10: out = (A|B|C) & (A|B|!C) & (A|!B|C) & (A|!B|!C) & (!A|B|C) & (!A|B|!C) & (!A|!B|C) & (!A|!B|!C);
            2'b11: out = (!A|!B|!C);
            default : out = 1'b0;
        endcase
    end
        
endmodule
