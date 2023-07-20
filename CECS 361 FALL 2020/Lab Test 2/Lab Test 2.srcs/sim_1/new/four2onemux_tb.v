`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project Name: Lab Test 2
    Start Date: 03 September 2020
    End Date: 03 September 2020
*/
module four2onemux_tb();

reg a, b, c, d;
reg [1:0] sel;
wire out;

integer i, j;

four2onemux uut(.a(a), .b(b), .c(c), .d(d), .sel(sel), .out(out));

initial begin
    j = 4'b1000;
    sel = 0;
    for(i = 0; i < 4; i = i + 1)
    begin
        
        {a, c, b, d} = j;
        #50;
        j = j >> 1;
        sel = sel + 1;
        
    end
end
endmodule
