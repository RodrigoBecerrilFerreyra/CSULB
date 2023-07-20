`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab Test 2
    Start Date: 03 September 2020
    End Date: 03 September 2020
*/
module two2onemux(
    input in0,
    input in1,
    input sel,
    output out
);

assign out = sel ? in1 : in0;

endmodule
