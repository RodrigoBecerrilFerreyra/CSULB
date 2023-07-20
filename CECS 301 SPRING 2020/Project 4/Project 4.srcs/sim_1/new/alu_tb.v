`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: alu_tb.v
// Date: 30 March 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module alu_tb();

reg [2:0] opsel;
reg [7:0] A, B;
wire [7:0] out;
wire zero, carry;

alu dut(.OpcodeSelect(opsel), .OperandA(A), .OperandB(B), .ALUout(out), .Zero(zero), .Carry(carry));

initial
begin

A = 8'h00; opsel = 3'h0; B = 8'h00; //Zero test
#50;
A = 8'hff; opsel = 3'h0; B = 8'hff; //Carry test
#50;
A = 8'h83; opsel = 3'h1; B = 8'h0a; //Overflow test
#50;
A = 8'b0011_0101; opsel = 3'h2; B = 8'hff; //lshift test
#50;
A = 8'b1000_0000; opsel = 3'h2; B = 8'hff; //lshift test (zero test)
#50;
A = 8'b1010_1010; opsel = 3'h3; B = 8'hff; //rotate shift test
#50;
A = 8'b0000_1100; opsel = 3'h4; B = 8'b1110_0100; //and test
#50;
A = 8'b0000_1100; opsel = 3'h5; B = 8'b1110_0100; //or test
#50;
A = 8'b0000_1100; opsel = 3'h6; B = 8'b1110_0100; //xor test
#50;
A = 8'b1010_1010; opsel = 3'h7; B = 8'hff; //not test

end
endmodule
