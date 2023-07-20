`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: alu.v
// Date: 30 March 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module alu(
    input [2:0] OpcodeSelect,
    input [7:0] OperandA,
    input [7:0] OperandB,
    output [7:0] ALUout,
    output Zero,
    output Carry
    );

reg [8:0] result;

always @(*)
begin
    case(OpcodeSelect)
        3'h0: result = OperandA + OperandB;
        3'h1: result = OperandA - OperandB;
        3'h2: result = OperandA << 1;
        3'h3: result = {1'b0, OperandA[0], OperandA[7:1]};
        3'h4: result = OperandA & OperandB;
        3'h5: result = OperandA | OperandB;
        3'h6: result = OperandA ^ OperandB;
        3'h7: result = ~OperandA;
    endcase
    
    result[8] = (OpcodeSelect == 3'h0) ? result[8] : 0;
end

assign Zero = (result[7:0] == 8'b0);
assign Carry = result[8];
assign ALUout = result[7:0];

endmodule
