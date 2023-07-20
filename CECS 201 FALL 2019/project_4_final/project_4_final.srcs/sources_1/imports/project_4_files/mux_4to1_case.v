`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201- Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 10/11/2019 09:01:30 AM
// Design Name: 
// Module Name: mux_4to1_case
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

module mux_4to1_case(
    input in0,
    input in1,
    input in2,
    input in3,
    input [1:0] sel,
    output reg out
    );
    
    always @(in0 or in1 or in2 or in3 or sel)
    begin
        case(sel)
            0:       out <= in0;
            1:       out <= in1;
            2:       out <= in2;
            3:       out <= in3;
            default: out <= 1'bZ;
        endcase
    end

endmodule
