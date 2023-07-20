`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CSULB
// Engineer: Colton Curtis, Rodrigo Becerril Ferreya, Ethan Hua
// 
// Create Date: 11/16/2020 04:49:52 AM
// Design Name: 
// Module Name: Clock
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


module Clock(clk, rst, mode, clockLock, BTNU, BTNL, BTNR, BTND, outVal, AUD_PWM, AUD_SD);
    
    input clk, rst;
    input BTNU, BTNL, BTNR, BTND;
    input [1:0] mode;
    input clockLock;
    output AUD_PWM;
    output AUD_SD;
    output reg [31:0] outVal;

    reg songChoice;
    wire tick;
    reg [16:0] tcount;    
    reg [3:0] milliseconds;
    reg [6:0] jiffys;
    reg [5:0] seconds;
    reg [5:0] minutes;
    reg [4:0] hours;
    
    reg [3:0] minutesOut [1:0];
    reg [3:0] hoursOut [1:0];
    
    reg songFlag;    
    reg cursor;
    
    /* manage switches
    always @(*) begin
    // if swith 0, then 24hr mode
    // if switch 2, then arm alarm
    // if switch 3, then arm timer
    // if switch 10, then Hawaii time
    // if switch 11, then LA time (Default)
    // if switch 12, then Chicago time
    // if switch 13, then NY time
    // if switch 14, then London time
    // if switch 15, then Tokyo time
    end */
    
    // Timer
    // Tick Generator (Tick every 1ms)
        assign tick = tcount == 17'd999; //17'd99999
        always @(posedge clk, posedge rst) begin
            if (rst) begin
                tcount <= 0;
                hours <= 0;
                minutes <= 0;
                seconds <= 0;
                jiffys <= 0;
                milliseconds <= 0;        
        
                minutesOut[0] <= 0;
                minutesOut[1] <= 0;
                hoursOut[0] <= 0;
                hoursOut[1] <= 0;
                
                songFlag <= 0;
            end else if (tick) begin
                tcount <= 15'b0;
                if (milliseconds < 4'd10) begin
                    milliseconds <= milliseconds + 4'b1;
                end else if (milliseconds >= 4'd10 && jiffys < 7'd99) begin
                    jiffys <= jiffys + 7'b1;
                    milliseconds <= 4'd0;
                 end else if (jiffys >= 7'd99 && seconds < 6'd59) begin
                    seconds <= seconds + 6'b1;
                    jiffys <= 4'd0;
                    milliseconds <= 4'd0;
                    // assign songFlag
//                    if (seconds > 4'd7 && songFlag && songChoice)
//                        songFlag <= 0;
                end else if (seconds >= 6'd59 && minutes < 6'd59) begin
                     // assign minutesOut
                     if (minutesOut[0] < 4'd9)
                         minutesOut[0] <= minutesOut[0] + 4'd1;
                     else begin
                         minutesOut[0] <= 4'd0;
                         minutesOut[1] <= minutesOut[1] + 4'd1;
                     end                      
                    minutes <= minutes + 6'b1;
                    seconds <= 6'd0;
                    jiffys <= 4'd0;
                    milliseconds <= 4'd0;
                end else if (minutes >= 6'd59 && hours < 5'd23) begin
                    // assign songFlag
                    if (!songFlag) begin
                        songFlag <= 1;
                        // assign songChoice (meglovania)
                        songChoice <= 1;
                    end
                     // assign hoursOut
                     if (hoursOut[0] < 4'd9)
                         hoursOut[0] <= hoursOut[0] + 4'd1;
                     else begin
                         hoursOut[0] <= 4'd0;
                         hoursOut[1] <= hoursOut[1] + 4'd1;
                     end          
                    minutesOut[0] <= 4'd0;
                    minutesOut[1] <= 4'd0;
                
                    hours <= hours + 5'b1;
                    minutes <= 4'd0;
                    seconds <= 6'd0;
                    jiffys <= 4'd0;
                    milliseconds <= 4'd0;
                end else if (hours >= 5'd23) begin
                    minutesOut[0] <= 4'd0;
                    minutesOut[1] <= 4'd0;
                    hoursOut[0] <= 4'd0;
                    hoursOut[1] <= 4'd0;
                
                    hours <= 4'd0;
                    minutes <= 4'd0;
                    seconds <= 4'd0;
                    jiffys <= 4'd0;
                    milliseconds <= 4'd0;
                end 
            end
            else if (clockLock)
                tcount <= tcount + 15'b1;
                        
            // set clock 
  /*          if (mode == 2'b00 && !clockLock) begin
                if (BTNU) begin
                    if (cursor == 1'b0) begin
                        if (hours < 5'd23) begin
                            hours <= hours + 1;
                            if (hoursOut[0] < 4'd9)
                                hoursOut[0] <= hoursOut[0] + 4'd1;
                            else begin
                                hoursOut[0] <= 4'd0;
                                hoursOut[1] <= hoursOut[1] + 4'd1;
                            end
                        end else begin
                            hours <= 5'd0;
                            hoursOut[0] <= 4'd0;
                            hoursOut[1] <= 4'd0;
                        end
                    end
                    else begin
                        if (minutes < 6'd59) begin
                            minutes <= minutes + 6'd1;
                            if (minutesOut[0] < 4'd9)
                                minutesOut[0] <= minutesOut[0] + 4'd1;
                            else begin
                                minutesOut[0] <= 4'd0;
                                minutesOut[1] <= minutesOut[1] + 4'd1;
                            end
                        end
                        else begin
                            minutes <= 6'd0;
                            minutesOut[0] <= 4'd0;
                            minutesOut[1] <= 4'd0;
                        end       
                    end
                end
                if (BTNL || BTNR) begin
                    if (cursor == 1'b0)
                        cursor <= 1'b1;
                    else
                        cursor <= 1'b0;
                end            
                if (BTND) begin
                    if (cursor == 1'b0) begin
                        if (hours > 5'd0) begin
                            hours <= hours - 5'd1;
                            if (hoursOut[0] > 4'd0)
                                hoursOut[0] <= hoursOut[0] - 4'd1;
                            else begin
                                hoursOut[0] <= 4'd9;
                                hoursOut[1] <= hoursOut[1] - 4'd1;
                            end
                        end else begin
                            hours <= 5'd23;
                            hoursOut[0] <= 4'd3;
                            hoursOut[1] <= 4'd2;
                        end
                    end
                    else begin
                        if (minutes > 6'd0) begin
                            minutes <= minutes - 6'd1;
                            if (minutesOut[0] > 4'd0)
                                minutesOut[0] <= minutesOut[0]  - 4'd1;
                            else begin
                                minutesOut[0] <= 4'd9;
                                minutesOut[1] <= minutesOut[1] - 4'd1;
                            end
                        end
                        else begin
                            minutes <= 6'd59;
                            minutesOut[0] <= 4'd9;
                            minutesOut[1] <= 4'd5;
                        end       
                    end
                end
            end */
        end
    
    // assign outVal
    always @(*) begin
        outVal[3:0] = 4'hF;
        outVal[7:4] = 4'hF;
        outVal[11:8] = 4'hF;
        outVal[15:12] = 4'hF;
        outVal[19:16] = minutesOut[0];
        outVal[23:20] = minutesOut[1];
        outVal[27:24] = hoursOut[0];
        outVal[31:28] = hoursOut[1];
    end
    
Music(.songChoice(songChoice), .clk(clk), .songFlag(songFlag), .AUD_PWM(AUD_PWM), .AUD_SD(AUD_SD));
    
endmodule