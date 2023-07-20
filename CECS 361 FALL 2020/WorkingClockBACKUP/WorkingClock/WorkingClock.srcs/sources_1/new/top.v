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


module top(clk, BTNC, BTNU, BTNL, BTNR, BTND, anode, cathode, AUD_PWM, AUD_SD, DataIn, LED, RGB);
input wire clk;
input wire [15:0] DataIn;
input wire BTNC, BTNU, BTNL, BTNR, BTND;
output wire AUD_PWM;
output wire AUD_SD;
output wire [7:0] anode, cathode;
output reg [15:0] LED;
output wire [2:0] RGB;
wire rst; assign rst = BTNL & BTNR;

wire [31:0] clockOutVal, alarmOutVal, alarmLED;
reg [31:0] inval;
wire [5:0] current_s, current_m;
wire [3:0] current_h;

always @(*)
    case({BTNC, BTNR, BTNU, BTNL, BTND})
        5'b00100:
        begin
            inval = alarmOutVal;
            LED = alarmLED;
        end
        default:
        begin
            inval = clockOutVal;
            LED = current_s;
        end
    endcase

wire songFlag, alarmFlag;
reg songChoice;
always @(*)
    case({songFlag, alarmFlag})
        2'b10: songChoice = 1;
        default: songChoice = 0;
    endcase

// debouncing buttons
wire BTNC_DB, BTNR_DB, BTNU_DB, BTNL_DB, BTND_DB;
DB_PED #(.POSEDGEDETECT(0)) btnc_db(.clk(clk), .rst(rst), .signal(BTNC), .out(BTNC_DB));
DB_PED btnr_db(.clk(clk), .rst(rst), .signal(BTNR), .out(BTNR_DB));
DB_PED #(.POSEDGEDETECT(0)) btnu_db(.clk(clk), .rst(rst), .signal(BTNU), .out(BTNU_DB));
DB_PED btnl_db(.clk(clk), .rst(rst), .signal(BTNL), .out(BTNL_DB));
DB_PED btnd_db(.clk(clk), .rst(rst), .signal(BTND), .out(BTND_DB));

wire AMPMtoggle, milSTDtoggle;
toggle ampmtoggle(.clk(clk), .rst(rst), .in(BTNR_DB), .out(AMPMtoggle));
toggle milstftoggle(.clk(clk), .rst(rst), .in(BTNL_DB), .out(milSTDtoggle));

wire [5:0] timeZoneOffset;
wire [2:0] timeZoneName;
timezoneset timezones(.clk(clk), .rst(rst), .BTN(BTND_DB), .setValue(DataIn[2:0]), .outVal(timeZoneOffset), .currentState(timeZoneName));

assign RGB[2] = (timeZoneName != 0);

wire specialvalue;
Clock clock(.clk(clk), .rst(rst), .BTNC(BTNC_DB), .outVal(clockOutVal), .setvalue(DataIn), .hours(current_h), .minutes(current_m), .seconds(current_s), .songFlag(songFlag), .plus12(AMPMtoggle), .milSTD(milSTDtoggle), .timeZoneOffset(timeZoneOffset), .timeZoneName(timeZoneName));
AlarmClock alarm(.clk(clk), .rst(rst), .BTNU(BTNU_DB), .inval(DataIn), .outVal(alarmOutVal), .seconds(current_s), .minutes(current_m), .hours(current_h), .alarmFlag(alarmFlag), .LED(alarmLED), .plus12(AMPMtoggle));
Music musicbox(.clk(clk), .songFlag(songFlag | alarmFlag), .songChoice(songChoice), .AUD_PWM(AUD_PWM), .AUD_SD(AUD_SD));

SevenSegmentDisplay ssg(.clk(clk), .rst(rst), .inVal(inval), .anode(anode), .cathode(cathode));

endmodule
