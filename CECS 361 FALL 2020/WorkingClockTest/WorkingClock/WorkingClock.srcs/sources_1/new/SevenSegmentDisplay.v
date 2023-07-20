`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/13/2020 07:47:31 PM
// Design Name: 
// Module Name: SevenSegmentDisplay
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


module SevenSegmentDisplay(clk, rst, inVal, cathode, anode);
    input clk, rst;    
    input [31:0] inVal;    
    output reg [7:0] cathode, anode;
    
    reg [14:0] count;
    reg [2:0] sel;
    reg [3:0] hexVal;
    wire tick;
    
    // Tick Generator
    assign tick = (count == 15'd32000);
    always @(posedge clk, posedge rst)
        if (rst || tick)
            count <= 15'b0;
        else
            count <= count + 15'b1;
    
    // Counter
    always @(posedge clk, posedge rst)
        if (rst) sel <= 3'h0; else    
        if (tick) sel <= (sel + 3'h1)%8;
        
    // selector (mux)
    always @(*)
    begin
        case(sel)
            3'h0:  hexVal = inVal[3:0];
            3'h1:  hexVal = inVal[7:4];
            3'h2:  hexVal = inVal[11:8];
            3'h3:  hexVal = inVal[15:12];
            3'h4:  hexVal = inVal[19:16];
            3'h5:  hexVal = inVal[23:20];
            3'h6:  hexVal = inVal[27:24];
            3'h7:  hexVal = inVal[31:28];
        endcase
    end
    
    // Decoder (4:8)
    always @(*)
    begin     
        case(hexVal)
            4'h0:  cathode = 8'hC0;
            4'h1:  cathode = 8'hF9;
            4'h2:  cathode = 8'hA4;
            4'h3:  cathode = 8'hB0;
            4'h4:  cathode = 8'h99;
            4'h5:  cathode = 8'h92;
            4'h6:  cathode = 8'h82;
            4'h7:  cathode = 8'hF8;
            4'h8:  cathode = 8'h80;
            4'h9:  cathode = 8'h90;
            4'hA:  cathode = 8'h88;
            4'hB:  cathode = 8'h83;
            4'hC:  cathode = 8'hC6;
            4'hD:  cathode = 8'hA1;
            4'hE:  cathode = 8'h86;
//            4'hF:  cathode = 8'h8E;
            default: cathode = 8'hFF;
        endcase
    end
    
    // Anode Shift Reg (Rotate Left)
    always @(posedge clk, posedge rst)
        if (rst) anode <= 8'hFE; else
        if (tick) 
        begin
            if (anode > 8'h7F) anode <= (anode << 1) | 8'h1;
            else anode <= 8'hFE;
        end    
endmodule
