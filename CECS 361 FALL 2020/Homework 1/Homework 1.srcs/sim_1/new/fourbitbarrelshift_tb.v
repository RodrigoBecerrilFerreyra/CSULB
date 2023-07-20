`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08/27/2020 06:17:06 PM
// Design Name: 
// Module Name: fourbitbarrelshift_tb
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


module fourbitbarrelshift_tb();

reg [1:0] shift;
reg [3:0] in;
wire [3:0] out;

fourbitbarrelshift uut(.shift(shift), .in(in), .out(out));

initial begin

    in = 4'b1110;
    shift = 2'd0;
    #50;
    shift = 2'd1;
    #50;
    shift = 2'd2;
    #50;
    shift = 2'd3;
    #50;

end
endmodule
