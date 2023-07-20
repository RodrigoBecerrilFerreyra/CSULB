`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineers: Jose Aceves & Amin Rezaei 
// Create Date: 10/12/2020 12:07:56 AM
// Design Name: 361_Lab4
// Module Name: LShift_Reg_Clr
// Revision 0.01 - File Created
//////////////////////////////////////////////////////////////////////////////////

module LShift_Reg_Clr(
    input clk,
    input reset,
    input [3:0] D,
    input sclr,
    input s_L,
    input E,
    input w,
    output reg [3:0] Q
    );
    
    // Loadable left Shift Register with Enable and synchronous clear input 
    // sclr = 1, E = 1, clear Q
    // sclr = 0, s_L = 1, E = 1, Load from Data input
    // sclr = 0, s_L = 0, E = 1, shift in w
    // else Q = Q
    always@(posedge clk, posedge reset) begin
        if(reset)
            Q <= 4'b0;
        else if(sclr && E)
            Q <= 4'b0;
        else
            if(s_L && E)
                Q <= D;
            else if(~s_L && E)
                Q <= {Q[3:0], w};                   
    end 
            
endmodule
