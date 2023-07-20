`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module RGBflash
/*
Purpose: starts flashing in the order {red -> green -> blue}
when enable is high, changing every 0.5 s.
Modeled using a Moore Finite State Machine.
*/
(
    input wire clk, input wire rst, input wire enable, input wire tick,
    output reg red_on, output reg green_on, output reg blue_on
);

// state declarations
localparam off = 0, red = 1,
           green = 2, blue = 3; 

// state switching logic
reg [1:0] cs, ns;
always @(posedge clk, posedge rst)
    if(rst) cs <= off;
    else    cs <= ns;

// next state logic
always @(*)
    case(cs)
        off:
            if(enable && tick) ns = red;
            else ns = off;
        red:
            if(!enable) ns = off;
            else if(!tick) ns = red;
            else ns = green;
        green:
            if(!enable) ns = off;
            else if(!tick) ns = green;
            else ns = blue;
        blue:
            if(!enable) ns = off;
            else if(!tick) ns = blue;
            else ns = red;
    endcase

// output logic (Moore)
always @(*)
    case(cs)
        off:   {red_on, green_on, blue_on} = 3'b0;
        red:   {red_on, green_on, blue_on} = 3'b100;
        green: {red_on, green_on, blue_on} = 3'b010;
        blue:  {red_on, green_on, blue_on} = 3'b001;
    endcase

endmodule
