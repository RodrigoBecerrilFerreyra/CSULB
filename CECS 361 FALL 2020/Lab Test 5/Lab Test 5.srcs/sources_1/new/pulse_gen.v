`timescale 1ns / 1ps

/*
    Gita Temelkova
    Alexander Valladarez
    Barbara Reveles
    Don Li
    Len Quach
    Mackenzee Gormican-Navarro
    Zane Navarro
    Rodrigo Becerril Ferreyra
*/

module pulse_gen(
    input clk, rst,
    output pulse
);

reg [2:0] counter;
always @(posedge clk, posedge rst)
    if(rst) counter <= 0;
    else counter = counter + 1; // automatically resets to 0 after 7

assign pulse = (counter == 7); // 1 if counter is 7, 0 if not

endmodule
