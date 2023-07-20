`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module Top_Module
(
    input wire clk, input wire reset,
    input wire A, input wire B, input wire C,
    output wire [2:0] RGB
);

// expected and actual (faulty) circuit instantiation
wire F0_expected, F0_actual;
wire F1_expected, F1_actual;
Circuit_SA1 actual_circuit(.A(A), .B(B), .C(C), .F1(F1_actual), .F0(F0_actual));
Circuit_SA1_expected expected_circuit(.A(A), .B(B), .C(C), .F1(F1_expected), .F0(F0_expected));

// RGB flash logic
wire tick;
pulse_counter half_second_pulse(.clk(clk), .rst(reset), .tick(tick));
RGBflash RGB_controller
(
    .clk(clk), .rst(reset),
    // the following is high if any pair of outputs is different
    .enable((F0_expected ^ F0_actual) | (F1_expected ^ F1_actual)),
    .tick(tick),
    .red_on(RGB[2]), .green_on(RGB[1]), .blue_on(RGB[0])
);

endmodule
