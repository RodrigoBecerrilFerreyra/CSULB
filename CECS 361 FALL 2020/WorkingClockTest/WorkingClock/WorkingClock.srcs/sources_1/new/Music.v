`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineer: Colton Curtis, Rodrigo Becerril Ferreya, Ethan Hua
// 
// Create Date: 11/16/2020 07:28:58 PM
// Design Name: 
// Module Name: Music
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

module Music(
input songChoice,
input clk,
input songFlag,
output AUD_PWM,
output AUD_SD
);

reg [31:0] tone;
always @(posedge clk) begin
    if (songFlag) 
        tone <= tone + 31'b1;
    else
        tone <= 0;
end

wire [7:0] fullnote;

Music_ROM get_fullnote(.songChoice(songChoice), .clk(clk), .address(tone[29:24]), .note(fullnote));

wire [2:0] octave;
wire [3:0] note;
Divide_by12 divideby12(.numer(fullnote[5:0]), .quotient(octave), .remain(note));

reg [10:0] clkdivider;
always @(note)
    case(note)
      0: clkdivider = 11'd2047; // A
      1: clkdivider = 11'd1935; // Bb
      2: clkdivider = 11'd1823; // B
      3: clkdivider = 11'd1723; // C
      4: clkdivider = 11'd1623; // Db
      5: clkdivider = 11'd1535; // D
      6: clkdivider = 11'd1447; // Eb
      7: clkdivider = 11'd1367; // E
      8: clkdivider = 11'd1291; // F
      9: clkdivider = 11'd1215; // Gb
      10: clkdivider = 11'd1147; // G
      11: clkdivider = 11'd1087; // Ab
      default: clkdivider = 11'd0;
    endcase
    
reg [10:0] counter_note;
always @(posedge clk)
    if(counter_note==0) counter_note <= clkdivider;
    else counter_note <= counter_note - 9'd1;

reg [7:0] counter_octave;
    always @(posedge clk)
        if(counter_note==0)
            counter_octave <= counter_octave==0 ? 8'd255 >> octave : counter_octave-8'd1;

reg speaker;
always @(posedge clk) begin
    if(counter_note==0 && counter_octave==0 && tone[23:20] != 0 && fullnote != 0) 
        speaker <= ~speaker;
end

assign AUD_PWM = speaker;
assign AUD_SD = songFlag;
endmodule
