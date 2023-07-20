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

module top(clk, rst, BTNC, BTNU, BTNL, BTNR, anode, cathode, AUD_PWM, AUD_SD, DataIn, RGB);
input wire clk, rst;
input wire [15:0] DataIn;
input wire BTNC, BTNU, BTNL, BTNR;
output wire AUD_PWM;
output wire AUD_SD;
output wire [7:0] anode, cathode;
output wire [2:0] RGB;

wire [31:0] clockOutVal, alarmOutVal;
reg [31:0] inval;
wire [5:0] current_s, current_m;
wire [5:0] current_h;

always @(*)
    if(BTNU) inval = alarmOutVal;
    else inval = clockOutVal;

wire songFlag, alarmFlag;
wire songChoice; assign songChoice = ~alarmFlag;

// debouncing buttons
wire BTNC_DB, BTNR_DB, BTNU_DB, BTNL_DB;
DB_PED #(.POSEDGEDETECT(0)) btnc_db(.clk(clk), .rst(rst), .signal(BTNC), .out(BTNC_DB));
DB_PED btnr_db(.clk(clk), .rst(rst), .signal(BTNR), .out(BTNR_DB));
DB_PED #(.POSEDGEDETECT(0)) btnu_db(.clk(clk), .rst(rst), .signal(BTNU), .out(BTNU_DB));
DB_PED btnl_db(.clk(clk), .rst(rst), .signal(BTNL), .out(BTNL_DB));

wire milSTDtoggle;
toggle milstftoggle(.clk(clk), .rst(rst), .in(BTNL_DB), .out(milSTDtoggle));

Clock clock(.clk(clk), .rst(rst), .BTNC(BTNC_DB), .outVal(clockOutVal), .setvalue(DataIn), .hours(current_h), .minutes(current_m), .seconds(current_s), .songFlag(songFlag), .milSTD(milSTDtoggle));
AlarmClock alarm(.clk(clk), .rst(rst), .BTNU(BTNU_DB), .inval(DataIn), .seconds(current_s), .minutes(current_m), .hours(current_h), .alarmFlag(alarmFlag), .outVal(alarmOutVal), .milSTD(milSTDtoggle), .status(RGB));
Music musicbox(.clk(clk), .songFlag(songFlag | alarmFlag), .songChoice(songChoice), .AUD_PWM(AUD_PWM), .AUD_SD(AUD_SD));

SevenSegmentDisplay ssg(.clk(clk), .rst(rst), .inVal(inval), .anode(anode), .cathode(cathode));
endmodule
