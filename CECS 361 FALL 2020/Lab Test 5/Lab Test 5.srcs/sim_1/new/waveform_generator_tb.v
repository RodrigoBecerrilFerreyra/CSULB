`timescale 1ns / 1ps

module waveform_generator_tb();

reg a, clk;
wire [2:0] q;

waveform_generator uut(.a(a), .clk(clk), .q(q));

always #20 clk = ~clk;

initial begin

    clk = 0; a = 1;
    #10;
    #100;
    a = 0;
    #450;
    a = 1;
    #100;
    a = 0;

end
endmodule
