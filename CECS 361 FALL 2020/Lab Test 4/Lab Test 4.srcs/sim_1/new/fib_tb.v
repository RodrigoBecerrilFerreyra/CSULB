`timescale 1ns / 1ps

/*
    Alex Gonzalez
    Jorge Aguilar
    Jorge Sanchez
    Kenneth Esquivel
    Musa Datti
    Nolan Santellanes
    Ryan Heng
    Rodrigo Becerril Ferreyra
*/

module fib_tb();

reg en, clk, rst;
wire [15:0] out_beh, out_str;

fib_beh behavioral(.en(en), .clk(clk), .out(out_beh));
fig_str structural(.en(en), .clk(clk), .out(out_str), .rst(rst));

always #20 clk = ~clk;

initial begin

    clk = 0; en = 0; rst = 1;
    #50;
    rst = 0;
    #50;
    en = 1;
    #200;
    en = 0;
    #100;
    en = 1;

end
endmodule
