`timescale 1ns / 1ps
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
// note: <name>_n means the next value the register takes on at the next posedge clk
module AlarmClock(clk, rst, BTNU, inval, seconds, minutes, hours, alarmFlag, outVal, milSTD, status);
input wire clk, rst;
input wire BTNU;
input [15:0] inval;
output reg [31:0] outVal;
output wire [2:0] status;
input [5:0] seconds, minutes, hours;
output reg alarmFlag; reg alarmFlag_n;
input wire milSTD;

reg [5:0] target_s, target_m;
reg [5:0] target_h;
reg [5:0] target_s_n, target_m_n;
reg [5:0] target_h_n;
wire [3:0] secondsOut [0:1];
wire [3:0] minutesOut [0:1];
wire [3:0] hoursOut [0:1];

assign status[2] = alarmFlag;
assign status[1] = BTNU;

// if alarm is inactive, BTNU sets s, m, h, and activates alarm
// if alarm is done counting (if target time has been reached),
// alarm flag is set, music plays, BTNU clears registers and deactivates alarm

// synchronous section
// defines reset and next values
always @(posedge clk, posedge rst)
    if(rst)
    begin
        target_s <= 0; target_m <= 0; target_h <= 0;
        alarmFlag <= 0;
    end
    else
    begin
        target_s <= target_s_n; target_m <= target_m_n; target_h <= target_h_n;
        alarmFlag <= alarmFlag_n;
    end

// determines what the next values are based on inputs
always @(*)
begin
    case({BTNU, alarmFlag})
    2'b10:
    begin
        //target_s_n = inval[5:0]; target_m_n = inval[11:6]; target_h_n = inval[15:12];
        if (inval[4:0] > 6'd59) begin
            target_s_n[5:1] = inval[4:0] - 6'd60;
            if (inval[10:5] > 6'd58) begin
                target_m_n = inval[10:5] - 6'd59;
                if (inval[15:11] > 5'd22)
                    target_h_n = inval[15:11] - 5'd23;
                else
                    target_h_n = inval[15:11] + 1;
            end
            else begin
                target_m_n = inval[10:5] + 1;
                if (inval[15:11] > 5'd23)
                    target_h_n = inval[15:11] - 5'd24;
                else
                    target_h_n = inval[15:11];
            end
        end
        else if(inval[4:0] <= 6'd59) begin
            target_s_n[5:1] = inval[4:0];
            if (inval[10:5] > 6'd59) begin
                target_m_n = inval[10:5] - 6'd60;
                    if (inval[15:11] > 5'd22)
                        target_h_n = inval[15:11] - 5'd23;
                    else
                        target_h_n = inval[15:11] + 1;
            end
            else if(inval[10:5] <= 6'd59) begin
                    target_m_n = inval[10:5];
                    if (inval[15:11] > 5'd23)
                        target_h_n = inval[15:11] - 5'd24;
                    else if(inval[15:11] <= 5'd23)
                        target_h_n = inval[15:11];
            end
        end
    end
    2'b11:
    begin
        target_s_n = 0; target_m_n = 0; target_h_n = 0;
        alarmFlag_n = 0;
    end
    default:
    begin
        target_s_n = target_s; target_m_n = target_m; target_h_n = target_h;
        alarmFlag_n = alarmFlag;
    end
    endcase
    
    // determines when time is up (alarm condition reached)
    if(seconds == target_s && minutes == target_m && hours == target_h)
        alarmFlag_n = 1;
end

// assigns output values
assign secondsOut[1] = (target_s >= 10) ? target_s/10 : 0;
assign secondsOut[0] = target_s % 10;
assign minutesOut[1] = (target_m >= 10) ? target_m/10 : 0;
assign minutesOut[0] = target_m % 10;
assign hoursOut[1] = (target_h >= 10) ? target_h/10 : 0;
assign hoursOut[0] = target_h % 10;

// assign outVal
always @(*)
begin
    outVal[7:4]   = 4'hF;

    outVal[11:8]  = secondsOut[0];
    outVal[15:12] = secondsOut[1];
    // visual fix for seconds > 59
    if(outVal[15:12] >= 4'd6)
    begin
        outVal[15:12] = 4'd5;
        outVal[11:8]  = 4'd9;
    end
    outVal[19:16] = minutesOut[0];
    outVal[23:20] = minutesOut[1];
    outVal[27:24] = hoursOut[0];
    outVal[31:28] = hoursOut[1];
    if(milSTD) // if STD
    begin
        case({outVal[31:28], outVal[27:24]})
            {4'h1, 4'h2}: outVal[3:0] = 4'h4; // P
            {4'h1, 4'h3}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h1;
            end
            {4'h1, 4'h4}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h2;
            end
            {4'h1, 4'h5}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h3;
            end
            {4'h1, 4'h6}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h4;
            end
            {4'h1, 4'h7}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h5;
            end
            {4'h1, 4'h8}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h6;
            end
            {4'h1, 4'h9}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h7;
            end
            {4'h2, 4'h0}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h8;
            end
            {4'h2, 4'h1}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h0;
                outVal[27:24] = 4'h9;
            end
            {4'h2, 4'h2}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h1;
                outVal[27:24] = 4'h0;
            end
            {4'h2, 4'h3}:
            begin
                outVal[3:0] = 4'h4; // P
                outVal[31:28] = 4'h1;
                outVal[27:24] = 4'h1;
            end
            default:
            begin
                outVal[3:0] = 4'h0; // A
            end
            
        endcase
    end else
        outVal[3:0] = 4'hF; // blank
end
endmodule
