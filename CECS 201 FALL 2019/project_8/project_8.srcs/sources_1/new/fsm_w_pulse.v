`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CECS 201 - Fall 2019
// Engineer: Rodrigo Becerril Ferreyra
// 
// Create Date: 11/26/2019 04:52:08 PM
// Design Name: 
// Module Name: fsm_w_pulse
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

module fsm_w_pulse(
    input clk,
    input reset,
    input cnt_up,
    input pulse,
    output reg [15:0] out
);

reg [3:0] state;
reg [3:0] nstate;

//state encoding
localparam s0 = 4'b0000,
           s1 = 4'b0001,
           s2 = 4'b0011,
           s3 = 4'b0010,
           s4 = 4'b0110,
           s5 = 4'b0111,
           s6 = 4'b0101,
           s7 = 4'b0100,
           s8 = 4'b1100;
           
//state register
always @(posedge clk, posedge reset)
    if (reset) state <= 4'b0;
    else state <= nstate;

//next state logic
always @(*) begin
    nstate = state;
    if(pulse)
        case(state)
            s0: nstate = (cnt_up) ? s1:s8;
            s1: nstate = (cnt_up) ? s2:s0;
            s2: nstate = (cnt_up) ? s3:s1;
            s3: nstate = (cnt_up) ? s4:s2;
            s4: nstate = (cnt_up) ? s5:s3;
            s5: nstate = (cnt_up) ? s6:s4;
            s6: nstate = (cnt_up) ? s7:s5;
            s7: nstate = (cnt_up) ? s8:s6;
            s8: nstate = (cnt_up) ? s0:s7;
       default: nstate = 4'h8;
        endcase
end

//output logic
always@(*) begin
    out = 16'h5555;
    case(state)
        s0: out = 16'h0000;
        s1: out = 16'h0003;
        s2: out = 16'h000F;
        s3: out = 16'h003F;
        s4: out = 16'h00FF;
        s5: out = 16'h03FF;
        s6: out = 16'h0FFF;
        s7: out = 16'h3FFF;
        s8: out = 16'hFFFF;
    default:out = 16'h8000;
    endcase
end
endmodule
