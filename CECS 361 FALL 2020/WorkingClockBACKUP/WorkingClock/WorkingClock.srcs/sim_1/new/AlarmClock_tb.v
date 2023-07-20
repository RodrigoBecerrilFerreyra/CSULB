`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/31/2020 09:04:42 PM
// Design Name: 
// Module Name: AlarmClock_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module AlarmClock_tb();

reg clk, rst, en, ctrl, ctdn;
reg [15:0] datain;

wire done;

//AlarmClock uut(.clk(clk), .rst(rst), .en(en), .ctrl(ctrl), .ctdn(ctdn), .datain(datain), .done(done));
AlarmClock uut(.clk(clk), .rst(rst), .en(en), .ctrl(ctrl), .datain(datain), .ctdn(ctdn), .done(done));

always
    #5
    clk = ~clk;


initial 
    begin    
        clk = 1;
        rst = 1;
        en = 0;
        ctrl = 0;
        ctdn = 0;
        datain = 16'b0000_00000_000111;     
        
        #10
        
        rst = 0;
        en = 1;
        ctrl = 1;
        
        #10
        
        ctrl = 0;
        
        #50
        
        en = 0;
        
        #50
        
        ctrl = 1;
        
        #50
        
        en = 1;
        ctrl = 0;
        
        forever
            #20
            ctdn = ~ctdn;
    end 
    
endmodule
