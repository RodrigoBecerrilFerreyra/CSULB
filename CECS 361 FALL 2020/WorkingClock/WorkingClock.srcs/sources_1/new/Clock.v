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

module Clock(clk, rst, BTNC, outVal, setvalue, hours, minutes, seconds, songFlag, milSTD);
    
input wire clk, rst;
input wire BTNC;
input [15:0] setvalue;
output reg [31:0] outVal;
output seconds, minutes, hours;
output songFlag;
input wire milSTD;

wire tick;
reg [27:0] tcount;
reg [5:0] seconds;
reg [5:0] minutes;
reg [5:0] hours;

reg [3:0] secondsOut [1:0];
reg [3:0] minutesOut [1:0];
reg [3:0] hoursOut [1:0];

reg added12;

reg songFlag;
    
// Timer
// Tick Generator (Tick every 1ms)
assign tick = (tcount == 28'd99_999_999);
//assign tick = tcount == 27'd99_999;
always @(posedge clk)
begin
    if (rst)
    begin
        tcount <= 0;
        hours <= 0;
        minutes <= 0;
        seconds <= 0;

        secondsOut[0] <= 0;
        secondsOut[1] <= 0;
        minutesOut[0] <= 0;
        minutesOut[1] <= 0;
        hoursOut[0] <= 0;
        hoursOut[1] <= 0;
    end else if (tick)
    begin
        tcount <= 15'b0;
        // assign SSD output
        if (seconds < 6'd59)
        begin
            // assign secondsOut
             if (secondsOut[0] < 4'd9)
                 secondsOut[0] <= secondsOut[0] + 4'd1;
             else
             begin
                 secondsOut[0] <= 4'd0;
                 secondsOut[1] <= secondsOut[1] + 4'd1;
             end
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
            {secondsOut[1], secondsOut[0]} = 0;
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
            secondsOut[0] <= 4'd0;
            secondsOut[1] <= 4'd0;
            minutesOut[0] <= 4'd0;
            minutesOut[1] <= 4'd0;
            hours <= hours + 5'b1;
            minutes <= 4'd0;
            seconds <= 4'd0;
        end
        else if (hours >= 5'd23)
        begin
            secondsOut[0] <= 4'd0;
            secondsOut[1] <= 4'd0;
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
    begin
        //tcount <= tcount + ~BTNC;
        if(BTNC)
            tcount <= tcount;
        else
            tcount <= tcount + 1;
    end

    // load values into register
    if(BTNC && setvalue[4:0] <= 58)// && setvalue[11:6] <= 59)
    begin
        if (setvalue[4:0] > 6'd59) begin
            seconds[5:1] <= setvalue[4:0] - 6'd60;
            if (setvalue[10:5] > 6'd58) begin
                minutes <= setvalue[10:5] - 6'd59;
                if (setvalue[15:11] > 5'd22)
                    hours <= setvalue[15:11] - 5'd23;
                else
                    hours <= setvalue[15:11] + 1;
            end
            else begin
                minutes <= setvalue[10:5] + 1;
                if (setvalue[15:11] > 5'd23)
                    hours <= setvalue[15:11] - 5'd24;
                else
                    hours <= setvalue[15:11];
            end
        end
        else if(setvalue[4:0] <= 6'd59) begin
            seconds[5:1] <= setvalue[4:0];
            if (setvalue[10:5] > 6'd59) begin
                minutes <= setvalue[10:5] - 6'd60;
                    if (setvalue[15:11] > 5'd22)
                        hours <= setvalue[15:11] - 5'd23;
                    else
                        hours <= setvalue[15:11] + 1;
            end
            else if(setvalue[10:5] <= 6'd59) begin
                    minutes <= setvalue[10:5];
                    if (setvalue[15:11] > 5'd23)
                        hours <= setvalue[15:11] - 5'd24;
                    else if(setvalue[15:11] <= 5'd23)
                        hours <= setvalue[15:11];
            end
        end

        // set seconds out
        secondsOut[1] <= (seconds >= 6'd10) ? seconds/10 : 0;
        secondsOut[0] <= seconds % 10;
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
    outVal[7:4]   = 4'hF;

    outVal[11:8]  = secondsOut[0];
    outVal[15:12] = secondsOut[1];
    /*
    // visual fix for seconds > 59
    if(outVal[15:12] >= 4'd6)
    begin
        outVal[15:12] = 4'd5;
        outVal[11:8]  = 4'd9;
    end*/
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
