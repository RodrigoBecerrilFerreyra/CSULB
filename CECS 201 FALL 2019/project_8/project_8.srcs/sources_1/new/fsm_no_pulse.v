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


module fsm_no_pulse(
    input clk,
    input reset,
    input cnt_up,
    output reg [15:0] out
);

reg [3:0]  state;
reg [3:0] nstate;

//state encoding
localparam S0 = 4'b0000, S1 = 4'b0001,
           S2 = 4'b0011, S3 = 4'b0010,
           S4 = 4'b0110, S5 = 4'b0111,
           S6 = 4'b0101, S7 = 4'b0100,
           S8 = 4'b1100;
           
//state register
always @(posedge clk or posedge reset) begin
    if (reset) state <= 4'h0;
    else state <= nstate;
end

//state transitioning logic
always @(*) begin
    nstate = 4'h0;
    
        case(state)
            S0: nstate <= (cnt_up) ? S1:S8;
            S1: nstate <= (cnt_up) ? S2:S0;
            S2: nstate <= (cnt_up) ? S3:S1;
            S3: nstate <= (cnt_up) ? S4:S2;
            S4: nstate <= (cnt_up) ? S5:S3;
            S5: nstate <= (cnt_up) ? S6:S4;
            S6: nstate <= (cnt_up) ? S7:S5;
            S7: nstate <= (cnt_up) ? S8:S6;
            S8: nstate <= (cnt_up) ? S0:S7;
            default: nstate <= 4'h0;
        endcase

end

//output logic
always @(*) begin
    case(state)
        S0: out <= 16'h0000;
        S1: out <= 16'h0003;
        S2: out <= 16'h000F;
        S3: out <= 16'h003F;
        S4: out <= 16'h00FF;
        S5: out <= 16'h03FF;
        S6: out <= 16'h0FFF;
        S7: out <= 16'h3FFF;
        S8: out <= 16'hFFFF;
        default: out <= 16'h8000;
    endcase
end
endmodule
