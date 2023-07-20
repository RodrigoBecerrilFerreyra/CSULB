`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/29/2019 04:37:04 PM
// Design Name: 
// Module Name: enc_dec_tb
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


module enc_dec_tb();

reg [7:0] in_tb;
wire [7:0] out_tb;
integer i;

enc_dec uut(.in(in_tb), .out(out_tb));

initial
begin

    in_tb = 8'b00000001;
    for(i=0; i<8; i=i+1)
    begin
        in_tb = in_tb << 1;
        #100;
    end

end

endmodule
