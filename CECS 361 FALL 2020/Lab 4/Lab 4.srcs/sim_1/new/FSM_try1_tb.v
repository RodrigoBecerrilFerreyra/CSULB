`timescale 1ns / 1ns
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 30 October 2020
*/
module FSM_try1_tb();
reg clk, rst, E, cout, zC;
wire LAB, EA, EC, sclrC, sclrR, LR, ER, done;

FSM_try1 uut(.clk(clk), .rst(rst), .E(E), .cout(cout), .zC(zC), .LAB(LAB), .EA(EA), .EC(EC), .sclrC(sclrC), .sclrR(sclrR), .LR(LR), .ER(ER), .done(done));

always #5 clk = ~clk;

initial begin

    rst = 1; clk = 1; {E, cout, zC} = 0;
    #6;
    rst = 0;
    
    // test values for E = 0 (State 1)
    #5;
    if({sclrR, sclrC, ER, EC} != 4'b1111 || {LAB, EA, LR, done} != 4'b0000)
        $display("T=%0t Test 1 failed.", $realtime);
    else
        $display("T=%0t Test 1 passed.", $realtime);
    
    // test values for State 2
    E = 1;
    #10;
    if({LAB, sclrC, sclrR, done} != 4'b0000 || {ER, EA} != 2'b11)
        $display("T=%0t Test 2 failed.", $realtime);
    else
        $display("T=%0t Test 2 passed.", $realtime);
    
    // Test values for cout = 1, zC = 0 (State 2)
    {cout, zC} = 2'b10;
    #10;
    if({ER, EA, LR, EC} != 4'b1111 || {LAB, sclrR, sclrC, done} != 4'b0000)
        $display("T=%0t Test 3 failed.", $realtime);
    else
        $display("T=%0t Test 3 passed.", $realtime);
    
    // Test values for cout = 0, zC = 1 (State 3)
    {cout, zC} = 2'b01;
    #10;
    if(done != 1'b1 || {LAB, EA, EC, sclrC, sclrR, LR, ER} != 7'b0)
        $display("T=%0t Test 4 failed.", $realtime);
    else
        $display("T=%0t Test 4 passed.", $realtime);

    $finish;
end
endmodule
