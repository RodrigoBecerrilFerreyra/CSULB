`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineers: Jose Aceves & Amin Rezaei 
// Create Date: 10/11/2020 11:39:21 PM
// Design Name: 361_Lab4
// Module Name: LShift_Reg
//////////////////////////////////////////////////////////////////////////////////

module LShift_Reg(
    input clk,
    input reset,
    input [5:0] D,
    input s_L,
    input E,
    input w,
    output reg [5:0] Q
    );
    
    // Loadable left Shift Register with Enable 
    // s_L = 1, E = 1, Load from Data input
    // s_L = 0, E = 1, shift in w
    // else Q = Q
    always@(posedge clk, posedge reset) begin
        if(reset)
            Q <= 6'b0;
        else begin
            if(s_L && E)
                Q <= D;
            else if(~s_L && E)
                Q <= {Q[4:0],w};     
        end              
    end
endmodule
