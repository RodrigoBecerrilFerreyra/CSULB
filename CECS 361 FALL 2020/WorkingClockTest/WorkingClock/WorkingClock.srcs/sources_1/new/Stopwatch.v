`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/16/2020 03:51:34 AM
// Design Name: 
// Module Name: Stopwatch
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


module Stopwatch(clk, rst, mode, BTNC, BTNU, BTNL, BTNR, BTND, outVal);
    
    input clk, rst;
    input BTNC, BTNU, BTNL, BTNR, BTND;
    input [1:0] mode;
    
    reg [16:0] tcount;
    wire tick;
    output wire [31:0] outVal;
    reg [3:0] milliseconds;
    reg [6:0] jiffys;
    reg [5:0] seconds;
    reg [5:0] minutes;
    reg [4:0] hours;
    
    reg [3:0] jiffysOut [1:0];
    reg [3:0] secondsOut [1:0];
    reg [3:0] minutesOut [1:0];
    reg [3:0] hoursOut [1:0];
    
    /*
                BTNC = (EXIT TO CLOCK MODE)
                BTNU = (RESET STOPWATCH TO 'ZERO')
                BTND = (START/STOP STOPWATCH) */
    
    // if in stopwatch mode
        always @(*) begin
            if (mode == 2'b10) begin
                if (BTNC) begin
                
                end
                if (BTNU) begin
                
                end
                if (BTNL) begin
                
                end
                if (BTNR) begin
                
                end
                if (BTND) begin
                
                end
            end
        end
    
    // Timer
    // Tick Generator (Tick every 1ms)
        assign tick = tcount == 17'd99999;
        always @(posedge clk, posedge rst)
            if (rst) begin
                tcount <= 15'b0;
                hours <= 0;
                minutes <= 0;
                seconds <= 0;
                jiffys <= 0;
                milliseconds <= 0;
                
                jiffysOut[0] <= 0;
                jiffysOut[1] <= 0;
                secondsOut[0] <= 0;
                secondsOut[1] <= 0;
                minutesOut[0] <= 4'd7;
                minutesOut[1] <= 4'd2;
                hoursOut[0] <= 4'd8;
                hoursOut[1] <= 0;
            end else if (tick) begin
                tcount <= 15'b0;
                if (milliseconds < 4'd10) begin
                    milliseconds <= milliseconds + 4'b1;
                end else if (milliseconds >= 4'd10 && jiffys < 7'd99) begin
                    // assign jiffysOut
                    if (jiffysOut[0] < 4'd9)
                        jiffysOut[0] <= jiffysOut[0] + 4'd1;
                    else begin
                        jiffysOut[0] <= 0;
                        jiffysOut[1] <= jiffysOut[1] + 4'd1;
                    end
                    jiffys <= jiffys + 7'b1;
                    milliseconds <= 0;
                 end else if (jiffys >= 7'd99 && seconds < 6'd59) begin
                     // assign jiffysOut
                     if (secondsOut[0] < 4'd9)
                         secondsOut[0] <= secondsOut[0] + 4'd1;
                     else begin
                         secondsOut[0] <= 0;
                         secondsOut[1] <= secondsOut[1] + 4'd1;
                     end
                    jiffysOut[0] <= 0;
                    jiffysOut[1] <= 0;
                    seconds <= seconds + 6'b1;
                    jiffys <= 0;   
                end else if (seconds >= 6'd59 && minutes < 6'd59) begin
                     // assign jiffysOut
                     if (minutesOut[0] < 4'd9)
                         minutesOut[0] <= minutesOut[0] + 4'd1;
                     else begin
                         minutesOut[0] <= 0;
                         minutesOut[1] <= minutesOut[1] + 4'd1;
                     end                 
                    jiffysOut[0] <= 0;
                    jiffysOut[1] <= 0;
                    secondsOut[0] <= 0;
                    secondsOut[1] <= 0;            
                    minutes <= minutes + 6'b1;
                    seconds <= 0;
                end else if (minutes >= 6'd59 && hours < 5'd23) begin 
                     // assign jiffysOut
                     if (hoursOut[0] < 4'd9)
                         hoursOut[0] <= hoursOut[0] + 4'd1;
                     else begin
                         hoursOut[0] <= 0;
                         hoursOut[1] <= hoursOut[1] + 4'd1;
                     end                 
                    jiffysOut[0] <= 0;
                    jiffysOut[1] <= 0;
                    secondsOut[0] <= 0;
                    secondsOut[1] <= 0;
                    minutesOut[0] <= 0;
                    minutesOut[1] <= 0;
                
                    hours <= hours + 5'b1;
                    minutes <= 0;
                end else if (hours >= 5'd23) begin
                    jiffysOut[0] <= 0;
                    jiffysOut[1] <= 0;
                    secondsOut[0] <= 0;
                    secondsOut[1] <= 0;
                    minutesOut[0] <= 0;
                    minutesOut[1] <= 0;
                    hoursOut[0] <= 0;
                    hoursOut[1] <= 0;
                
                    hours <= 0;
                    minutes <= 0;
                    seconds <= 0;
                    jiffys <= 0;
                    milliseconds <= 0;
                end 
            end
            else
                tcount <= tcount + 15'b1;
    
        assign outVal[3:0] = jiffysOut[0];
        assign outVal[7:4] = jiffysOut[1];
        assign outVal[11:8] = secondsOut[0];
        assign outVal[15:12] = secondsOut[1];
        assign outVal[19:16] = minutesOut[0];
        assign outVal[23:20] = minutesOut[1];
        assign outVal[27:24] = hoursOut[0];
        assign outVal[31:28] = hoursOut[1];
    
endmodule
