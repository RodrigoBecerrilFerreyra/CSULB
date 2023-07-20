`timescale 1ns / 1ps
module Clock_tb();

reg clk, rst, BTNC;
wire [31:0] outVal;
wire AUD_PWN, AUD_SD;
reg [15:0] setvalue;
wire [5:0] seconds, minutes; wire [3:0] hours;

Clock uut(.clk(clk), .rst(rst), .BTNC(BTNC), .outVal(outVal), .AUD_PWM(AUD_PWM), .AUD_SD(AUD_SD), .setvalue(setvalue), .hours(hours), .minutes(minutes), .seconds(seconds));

always #5 clk = ~clk;

initial begin

clk = 1; rst = 1;
#5;
rst = 0;

end
endmodule
