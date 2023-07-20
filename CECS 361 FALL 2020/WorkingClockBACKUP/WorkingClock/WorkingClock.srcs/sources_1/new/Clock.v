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


module Clock(clk, rst, BTNC, outVal, setvalue, hours, minutes, seconds, songFlag, plus12, milSTD, timeZoneOffset, timeZoneName);
    
input wire clk, rst;
input wire BTNC;
input [15:0] setvalue;
output reg [31:0] outVal;
output seconds, minutes, hours;
output songFlag;
input wire plus12, milSTD;
input wire [4:0] timeZoneOffset;
input wire [2:0] timeZoneName;

assign status = 0;

wire tick;
reg [26:0] tcount;
reg [5:0] seconds;
reg [5:0] minutes;
reg [4:0] hours;

reg [3:0] minutesOut [1:0];
reg [3:0] hoursOut [1:0];

reg added12;

reg songFlag;
    
// Timer
// Tick Generator (Tick every 1ms)
assign tick = (tcount == 27'd99_999_999);
//assign tick = tcount == 27'd99_999;
always @(posedge clk)
begin
    if (rst)
    begin
        tcount <= 0;
        hours <= 0;
        minutes <= 0;
        seconds <= 0;

        minutesOut[0] <= 0;
        minutesOut[1] <= 0;
        hoursOut[0] <= 0;
        hoursOut[1] <= 0;
        added12 <= 0;
    end else if (tick)
    begin
        tcount <= 15'b0;
        // assign SSD output
        if (seconds < 6'd59)
        begin
            seconds <= seconds + 1;
            if (seconds > 4'd7 && songFlag)
                songFlag <= 0;
        end
        else if (seconds >= 6'd59 && minutes < 6'd59)
        begin
             // assign minutesOut
             if (minutesOut[0] < 4'd9)
                 minutesOut[0] <= minutesOut[0] + 4'd1;
             else
             begin
                 minutesOut[0] <= 4'd0;
                 minutesOut[1] <= minutesOut[1] + 4'd1;
             end                      
            minutes <= minutes + 6'b1;
            seconds <= 6'd0;
        end
        else if (minutes >= 6'd59 && hours < 5'd23)
        begin
            if (!songFlag)
                songFlag <= 1;
            // assign hoursOut
            if (hoursOut[0] < 4'd9)
                hoursOut[0] <= hoursOut[0] + 4'd1;
            else
            begin
                 hoursOut[0] <= 4'd0;
                 hoursOut[1] <= hoursOut[1] + 4'd1;
            end     
            minutesOut[0] <= 4'd0;
            minutesOut[1] <= 4'd0;
            hours <= hours + 5'b1;
            minutes <= 4'd0;
            seconds <= 4'd0;
        end
        else if (hours >= 5'd23)
        begin
            minutesOut[0] <= 4'd0;
            minutesOut[1] <= 4'd0;
            hoursOut[0] <= 4'd0;
            hoursOut[1] <= 4'd0;
        
            hours <= 4'd0;
            minutes <= 4'd0;
            seconds <= 4'd0;
        end
    end
    else
        if(BTNC)
            tcount <= tcount;
        else
            tcount <= tcount + 1;

    // load values into register
    if(BTNC)// && setvalue[5:0] <= 59 && setvalue[11:6] <= 59)
    begin
        if (setvalue[5:0] > 6'd59) begin
            seconds <= setvalue[5:0] - 6'd60;
            if (setvalue[11:6] > 6'd58) begin
                minutes <= setvalue[11:6] - 6'd59;
                if (setvalue[15:12] > 5'd22)
                    hours <= setvalue[15:12] - 5'd23;
                else
                    hours <= setvalue[15:12] + 1;
            end
            else begin
                minutes <= setvalue[11:6] + 1;
                if (setvalue[15:12] > 5'd23)
                    hours <= setvalue[15:12] - 5'd24;
                else
                    hours <= setvalue[15:12];
            end
        end
        else if(setvalue[5:0] <= 6'd59) begin
            seconds <= setvalue[5:0];
            if (setvalue[11:6] > 6'd59) begin
                minutes <= setvalue[11:6] - 6'd60;
                    if (setvalue[15:12] > 5'd22)
                        hours <= setvalue[15:12] - 5'd23;
                    else
                        hours <= setvalue[15:12] + 1;
            end
            else if(setvalue[11:6] <= 6'd59) begin
                    minutes <= setvalue[11:6];
                    if (setvalue[15:12] > 5'd23)
                        hours <= setvalue[15:12] - 5'd24;
                    else if(setvalue[15:12] <= 5'd23)
                        hours <= setvalue[15:12];
            end
        end

        if(timeZoneOffset != 0)
        begin
            if(hours + timeZoneOffset <= 23)
                hours <= hours + timeZoneOffset;
            else
                hours <= hours + timeZoneOffset - 24;
        end

        // set minutes out
        minutesOut[1] <= (minutes >= 6'd10) ? minutes/10 : 0;
        minutesOut[0] <= minutes % 10;
        // set hours out
        hoursOut[1] <= (hours >= 6'd10) ? hours/10 : 0;
        hoursOut[0] <= hours % 10;
    end
end
    
// assign outVal
always @(*)
begin
    case(timeZoneName)
        // PST
        3'b000: begin    
            outVal[3:0] = 4'h6; // T
            outVal[7:4] = 4'h5; // S
            outVal[11:8] = 4'h4;  // P
        end
        // JST
        3'b001: begin
            outVal[3:0] = 4'h6;  // T
            outVal[7:4] = 4'h5;  // S
            outVal[11:8] = 4'h2;  // J
        end
        // UTC
        3'b010: begin
            outVal[3:0] = 4'h8;  // C
            outVal[7:4] = 4'h6;  // T
            outVal[11:8] = 4'h7;  // U
        end
        // EST
        3'b011: begin
            outVal[3:0] = 4'h6;  // T
            outVal[7:4] = 4'h5;  // S
            outVal[11:8] = 4'h1;  // E
        end
        // CST
        3'b100: begin
            outVal[3:0] = 4'h6;  // T
            outVal[7:4] = 4'h5;  // S
            outVal[11:8] = 4'h8;  // C
        end
        // HST
        3'b101: begin
            outVal[3:0] = 4'h6;  // T
            outVal[7:4] = 4'h5;  // S
            outVal[11:8] = 4'h3;  // H
        end
        default: begin
            outVal[3:0] = 4'h6;  // T
            outVal[7:4] = 4'h5;  // S
            outVal[11:8] = 4'h4;  // P
        end
    endcase
    outVal[19:16] = minutesOut[0];
    outVal[23:20] = minutesOut[1];

    case({milSTD, plus12})
        // military time, plus 0
        2'b00:
        begin
            outVal[31:24] = {hoursOut[1], hoursOut[0]};
        end
        // military time, plus 12
        2'b01:
        begin
            outVal[27:24] = hoursOut[0] + 2;
            if(outVal[27:24] >= 10)
            begin
                outVal[27:24] = outVal[27:24] - 10;
                outVal[31:28] = outVal[31:28] + 1;
            end
            outVal[31:28] = hoursOut[1] + 1;
        end
        // standard time, plus 0 (AM)
        2'b10:
        begin
            outVal[15:12] = 5'h10;
        end
        // standard time, plus 12 (PM)
        2'b11: 
        begin
            outVal[15:12] = 5'h14;
        end
    endcase
end
    
endmodule