`timescale 1ns / 1ps

module testbench_tb();

reg a, b, c;
wire o1, o2, o3;
integer i;

circuit1 uut1(.a(a), .b(b), .c(c), .o(o1));
circuit2 uut2(.a(a), .b(b), .c(c), .o(o2));

initial begin

    for(i = 0; i < 8; i = i + 1) begin
        {a, b, c} = i;
        #100;
    end

end
endmodule
