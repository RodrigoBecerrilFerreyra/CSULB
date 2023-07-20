`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// WHEN SUBMITTING THIS WORK I ATTEST THAT THIS IS MY WORK PRODUCT
// I will give credit to any other source that may have contributed.
//
// Author: Rodrigo Becerril Ferreyra
// Email: rodrigo.becerrilferreyra@student.csulb.edu
// Filename: Processor_Components_Top.v
// Date: 30 March 2020
// Version: 1.0
//
// Notes: 
//////////////////////////////////////////////////////////////////////////////////

module Processor_Components_Top(
    input [3:0] btn,
    input [15:0] switches,
    output [2:0] LED,
    output [7:0] cathode, output [7:0] anode,
    input clk
    );

wire rst; assign rst = btn[0];

// debounce btn 1-3
wire ldsw, wtrg, doop;
DB_PED db1(.clk(clk), .rst(rst), .signal(btn[1]), .ped(ldsw));
DB_PED db2(.clk(clk), .rst(rst), .signal(btn[2]), .ped(wtrg));
DB_PED db3(.clk(clk), .rst(rst), .signal(btn[3]), .ped(doop));


// load register
// loads value from switches when ldsw is high
reg [15:0] q_ldreg, d_ldreg;
always @(posedge clk, posedge rst)
    if(rst) q_ldreg <= 0;
    else    q_ldreg <= d_ldreg;
always @(*)
    if(ldsw) d_ldreg = switches;
    else     d_ldreg = q_ldreg;
//ldreg ldreg(.D(switches), .Q(q_ldreg), .ld(ldsw), .clk(clk), .rst(rst));


// register file
// array of 8 registers for storing values
wire [7:0] write_data, ALU_out;
assign write_data = wtrg ? q_ldreg[7:0] : ALU_out;
wire [7:0] A, B;
register_file regfile(.write(doop | wtrg), .wAdrs(q_ldreg[15:13]), .wData(write_data), .rAdrsA(q_ldreg[12:10]), .rAdrsB(q_ldreg[9:7]), .rDataA(A), .rDataB(B), .clk(clk), .rst(rst));


// ALU
// performs predetermined mathematical operations
alu alu(.OpcodeSelect(q_ldreg[2:0]), .OperandA(A), .OperandB(B), .ALUout(ALU_out), .Zero(LED[0]), .Carry(LED[1]));


// Seven-Segment Display
// Displays certain values
seven_segment ssg(.value({q_ldreg[7:0], A, B, ALU_out}), .clk(clk), .rst(rst), .cathode(cathode), .anode(anode));

assign LED[2] = rst;

endmodule
