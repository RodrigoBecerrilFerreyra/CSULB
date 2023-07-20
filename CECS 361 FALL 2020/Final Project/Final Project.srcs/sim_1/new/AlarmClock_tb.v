`timescale 1ns / 1ps
/*
    Engineers: Colton Curtis, Ethan Hua, Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Alarm Clock Final Project
    Date: 31 October 2020
*/
module AlarmClock_tb();
reg clk, rst, en, ctrl;
reg [16:0] datain;
wire done;
integer counter;
wire pulse;

AlarmClock uut(.clk(clk), .rst(rst), .en(en), .ctrl(ctrl), .datain(datain), .ctdn(pulse), .done(done));

always #5 clk = ~clk;
always @(posedge clk, posedge rst)
    if(rst) counter <= 100000000;
    else if(pulse) counter <= 100000000;
    else counter <= counter - 1;

assign pulse = (counter == 0);

initial begin
    clk = 1; rst = 1; datain = 10; ctrl = 1; en = 0;
    #7.5;
    rst = 0;
    #5;
    ctrl = 0; en = 1;
    
    while(~done) #5;
    $finish;
end
endmodule
