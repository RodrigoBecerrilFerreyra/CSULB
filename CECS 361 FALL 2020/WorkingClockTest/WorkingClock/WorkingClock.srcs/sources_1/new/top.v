`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineer: Colton Curtis, Rodrigo Becerril Ferreya, Ethan Hua
// 
// Create Date: 11/13/2020 07:35:11 PM
// Design Name: 
// Module Name: top
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


module top(clk, rst, BTNC, BTNU, BTNL, BTNR, BTND, anode, cathode, AUD_PWM, AUD_SD);
input clk, rst;
input BTNC, BTNU, BTNL, BTNR, BTND;
output AUD_PWM;
output AUD_SD;
output wire [7:0] anode, cathode;

reg [31:0] inVal;
wire [31:0] clockOutVal, alarmOutVal, stopwatchOutVal, timerOutVal;
reg [1:0] mode;
wire cTST, uTST, lTST, rTST, dTST;
// wire hourFlag, alarmFlag, timerFlag;
reg clockLock;

// manage inVal
always @(*) begin
    case (mode)
        // clock
        2'b00: inVal = clockOutVal;
        // alarm
        2'b01: inVal = alarmOutVal;
        // stopwatch
        2'b10: inVal = stopwatchOutVal;
        // timer
        2'b11: inVal = timerOutVal;
        // clock
        default: inVal = clockOutVal;
    endcase
end

// mode switch
always @(posedge clk, posedge rst) begin
    if (rst) begin
        clockLock <= 1'b1;
        mode <= 0;
    end else if (mode == 0) begin
        if (clockLock) begin
            if (cTST)
                clockLock = 1'b0;
          else if (uTST)
                mode = 2'b01; // alarm
            else if (lTST)
                mode = 2'b11; // stopwatch
            else if (rTST)
                mode = 2'b10; // timer
        end else if (!clockLock) begin
            if (BTNC && !cTST)
                clockLock = 1'b1;
        end
    end
end

ThreeSecondTimer center(.clk(clk), .rst(rst), .btn(BTNC), .mode(mode), .tst(cTST));
ThreeSecondTimer up(.clk(clk), .rst(rst), .btn(BTNU), .mode(mode), .tst(uTST));
ThreeSecondTimer left(.clk(clk), .rst(rst), .btn(BTNL), .mode(mode), .tst(lTST));
ThreeSecondTimer right(.clk(clk), .rst(rst), .btn(BTNR), .mode(mode), .tst(rTST));
ThreeSecondTimer down(.clk(clk), .rst(rst), .btn(BTND), .mode(mode), .tst(dTST));

Clock clock(.clk(clk), .rst(rst), .mode(mode), .clockLock(clockLock), .BTNU(BTNU), .BTNL(BTNL), .BTNR(BTNR), .BTND(BTND), .outVal(clockOutVal), .AUD_PWM(AUD_PWM), .AUD_SD(AUD_SD));
//Alarm alarm(.clk(clk), .rst(rst), .mode(mode), .alarmFlag(alarmFlag), .BTNC(BTNC), .BTNU(BTNU), .BTNL(BTNL), .BTNR(BTNR), .BTND(BTND), .outVal(alarmOutVal));
//Stopwatch stopwatch(.clk(clk), .rst(rst), .mode(mode), .BTNC(BTNC), .BTNU(BTNU), .BTNL(BTNL), .BTNR(BTNR), .BTND(BTND), .outVal(stopwatchOutVal));
//Timer timer(.clk(clk), .rst(rst), .mode(mode), .timerFlag(timerFlag), .BTNC(BTNC), .BTNU(BTNU), .BTNL(BTNL), .BTNR(BTNR), .BTND(BTND), .outVal(timerOutVal));

SevenSegmentDisplay ssg(.clk(clk), .rst(rst), .inVal(inVal), .anode(anode), .cathode(cathode));

endmodule
