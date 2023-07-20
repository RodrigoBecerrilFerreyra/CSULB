`timescale 1ns / 1ps
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
// note: <name>_n means the next value the register takes on at the next posedge clk
module AlarmClock(clk, rst, BTNU, inval, seconds, minutes, hours, alarmFlag, outVal, LED, plus12);
input wire clk, rst;
input wire BTNU;
input [15:0] inval;
output reg [31:0] outVal;
//output [2:0] status;
input [5:0] seconds, minutes; input [3:0] hours;
output reg alarmFlag; reg alarmFlag_n;
output wire [5:0] LED;
input wire plus12;

reg [5:0] target_s, target_m;
reg [3:0] target_h;
reg [5:0] target_s_n, target_m_n;
reg [3:0] target_h_n;
reg isActive; reg isActive_n;
wire [3:0] minutesOut [0:1];
wire [3:0] hoursOut [0:1];
/*
assign status[2] = isActive;
assign status[1] = (inval != 0);
assign status[0] = (target_s != 0) | (target_m != 0) | (target_h != 0);
*/

assign LED = target_s;

// if alarm is inactive, BTNU sets s, m, h, and activates alarm
// if alarm is done counting (if target time has been reached),
// alarm flag is set, music plays, BTNU clears registers and deactivates alarm

// synchronous section
// defines reset and next values
always @(posedge clk, posedge rst)
    if(rst)
    begin
        target_s <= 0; target_m <= 0; target_h <= 0;
        alarmFlag <= 0; isActive <= 0;
    end
    else
    begin
        target_s <= target_s_n; target_m <= target_m_n; target_h <= target_h_n;
        alarmFlag <= alarmFlag_n; isActive <= isActive_n;
    end

// determines what the next values are based on inputs
always @(*)
begin
    case({BTNU, alarmFlag})
    2'b10:
    begin
        //target_s_n = inval[5:0]; target_m_n = inval[11:6]; target_h_n = inval[15:12];
        if (inval[5:0] > 6'd59) begin
            target_s_n = inval[5:0] - 6'd60;
            if (inval[11:6] > 6'd58) begin
                target_m_n = inval[11:6] - 6'd59;
                if (inval[15:12] > 5'd22)
                    target_h_n = inval[15:12] - 5'd23;
                else
                    target_h_n = inval[15:12] + 1;
            end
            else begin
                target_m_n = inval[11:6] + 1;
                if (inval[15:12] > 5'd23)
                    target_h_n = inval[15:12] - 5'd24;
                else
                    target_h_n = inval[15:12];
            end
        end
        else if(inval[5:0] <= 6'd59) begin
            target_s_n = inval[5:0];
            if (inval[11:6] > 6'd59) begin
                target_m_n = inval[11:6] - 6'd60;
                    if (inval[15:12] > 5'd22)
                        target_h_n = inval[15:12] - 5'd23;
                    else
                        target_h_n = inval[15:12] + 1;
            end
            else if(inval[11:6] <= 6'd59) begin
                    target_m_n = inval[11:6];
                    if (inval[15:12] > 5'd23)
                        target_h_n = inval[15:12] - 5'd24;
                    else if(inval[15:12] <= 5'd23)
                        target_h_n = inval[15:12];
            end
        end

        isActive_n = 1;
    end
    2'b11:
    begin
        target_s_n = 0; target_m_n = 0; target_h_n = 0;
        alarmFlag_n = 0; isActive_n = 0;
    end
    default:
    begin
        target_s_n = target_s; target_m_n = target_m; target_h_n = target_h;
        alarmFlag_n = alarmFlag; isActive_n = isActive;
    end
    endcase
    
    // determines when time is up (alarm condition reached)
    if(seconds == target_s && minutes == target_m && hours == target_h && isActive)
        alarmFlag_n = 1;
end

// assigns output values
assign minutesOut[1] = (target_m > 10) ? target_m/10 : 0;
assign minutesOut[0] = target_m % 10;
assign hoursOut[1] = (target_h > 10) ? target_h/10 : 0;
assign hoursOut[0] = target_h % 10;

// assign outVal
always @(*)
begin
    outVal[3:0] = 4'b0;
    outVal[7:4] = 4'b0;
    outVal[11:8] = 4'b0;
    outVal[15:12] = 4'b0;
    outVal[19:16] = minutesOut[0];
    outVal[23:20] = minutesOut[1];
    outVal[27:24] = plus12 ? hoursOut[0] + 2 : hoursOut[0];
    if(outVal[27:24] >= 10)
    begin
        outVal[27:24] = outVal[27:24] - 10;
        outVal[31:28] = outVal[31:28] + 1;
    end
    outVal[31:28] = plus12 ? hoursOut[1] + 1 : hoursOut[1];
end
/*
always @(*)
begin
    outVal[3:0] = 4'hf;
    outVal[7:4] = 4'hf;
    outVal[11:8] = 4'hf;
    outVal[15:12] = 4'hf;
    outVal[19:16] = minutesOut[0];
    outVal[23:20] = minutesOut[1];
    outVal[27:24] = hoursOut[0];
    outVal[31:28] = hoursOut[1];
end
*/
endmodule
