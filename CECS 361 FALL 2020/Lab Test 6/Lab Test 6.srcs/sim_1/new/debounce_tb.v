`timescale 1ns / 1ns
/*
    Rio Bungalon Jr.
    Angel Espinoza
    Kenneth E
    Miguel Cabada
    Rodolfo Bustos
    Ryan Cachu
    Rodrigo Becerril Ferreyra
*/
module debounce_tb();
reg clk, rst, sw;
wire db;
integer i;

debounce uut(.clk(clk), .reset(rst), .sw(sw), .db(db));

always #5 clk = ~clk;

initial begin
    clk = 1; rst = 1; sw = 0; i = 0;
    #5;
    rst = 0;
    
    // bounce btw 1 and 0, no longer than 20 ms
    for(i = 0; i < 10; i = i + 1) begin
        sw = ~sw;
        #15_000_000;
    end
    
    // wait on 1
    sw = 1;
    #21_000_000;
    
    // bounce btw 1 and 0, no longer than 20 ms
    for(i = 0; i < 10; i = i + 1) begin
        sw = ~sw;
        #15_000_000;
    end
    
    // wait on 0
    sw = 0;
    #21_000_000;
    $finish;
end
endmodule
