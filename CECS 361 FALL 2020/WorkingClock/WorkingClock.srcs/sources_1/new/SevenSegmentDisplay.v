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
    wire tick; reg adjustedspecialvalue;
    
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
            3'h0:  begin hexVal = inVal[3:0]; adjustedspecialvalue = 1; end
            3'h1:  begin hexVal = inVal[7:4]; adjustedspecialvalue = 1; end
            3'h2:  begin hexVal = inVal[11:8]; adjustedspecialvalue = 0; end
            3'h3:  begin hexVal = inVal[15:12]; adjustedspecialvalue = 0; end
            3'h4:  begin hexVal = inVal[19:16]; adjustedspecialvalue = 0; end
            3'h5:  begin hexVal = inVal[23:20]; adjustedspecialvalue = 0; end
            3'h6:  begin hexVal = inVal[27:24]; adjustedspecialvalue = 0; end
            3'h7:  begin hexVal = inVal[31:28]; adjustedspecialvalue = 0; end
        endcase
    end
    
    // Decoder (4:8)
    always @(*)
    begin     
        case({adjustedspecialvalue, hexVal})
             // special value outputs
             {1'b1, 4'h0}:  cathode = 8'h88; // A
             {1'b1, 4'h1}:  cathode = 8'h86; // E
             {1'b1, 4'h2}:  cathode = 8'hE1; // J
             {1'b1, 4'h3}:  cathode = 8'h89; // H
             {1'b1, 4'h4}:  cathode = 8'h8C; // P
             {1'b1, 4'h5}:  cathode = 8'h92; // S
             {1'b1, 4'h6}:  cathode = 8'h87; // T
             {1'b1, 4'h7}:  cathode = 8'hC1; // U
             {1'b1, 4'h8}:  cathode = 8'hC6; // C
            5'h0:  cathode = 8'hC0;
            5'h1:  cathode = 8'hF9;
            5'h2:  cathode = 8'hA4;
            5'h3:  cathode = 8'hB0;
            5'h4:  cathode = 8'h99;
            5'h5:  cathode = 8'h92;
            5'h6:  cathode = 8'h82;
            5'h7:  cathode = 8'hF8;
            5'h8:  cathode = 8'h80;
            5'h9:  cathode = 8'h90;
            5'hA:  cathode = 8'h88;
            5'hB:  cathode = 8'h83;
            5'hC:  cathode = 8'hC6;
            5'hD:  cathode = 8'hA1;
            5'hE:  cathode = 8'h86;
            5'hF:  cathode = 8'hFF; // blank
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
