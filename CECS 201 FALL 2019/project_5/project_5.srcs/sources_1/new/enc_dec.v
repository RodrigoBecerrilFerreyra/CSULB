`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/29/2019 04:32:00 PM
// Design Name: 
// Module Name: enc_dec
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


module enc_dec(
    input [7:0] in,
    output [7:0] out
);

wire [2:0] encoder_out;
wire encoder_valid;

encoder enc(.in(in), .valid(encoder_valid), .out(encoder_out));
decoder dec(.in(encoder_out), .enable(encoder_valid), .out(out));

endmodule
