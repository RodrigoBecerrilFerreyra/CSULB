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

module fib_beh(
    input en, input clk,
    output [15:0] out
);

reg [15:0] reg0, reg1;

initial begin
    reg0 = 0;
    reg1 = 1;
end

assign out = reg0 + reg1;
// f_n = f_(n-1) + f_(n-2)

always @(posedge clk)
begin
    if(en)
    begin
        reg0 <= reg1;
        reg1 <= out;
    end
end
endmodule
