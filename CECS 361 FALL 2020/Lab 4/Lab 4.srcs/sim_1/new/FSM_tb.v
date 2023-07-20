`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 4
    Date: 29 October 2020
*/
module FSM_tb();

reg clk, rst, E, cout, zC;
wire LAB, EA, EC, sclrC, sclrR, LR, ER, done;

FSM uut(.clk(clk), .rst(rst), .E(E), .cout(cout), .zC(zC), .LAB(LAB), .EA(EA), .EC(EC), .sclrC(sclrC), .sclrR(sclrR), .LR(LR), .ER(ER), .done(done));

always #5 clk = ~clk;
localparam clock = 10;

initial begin

    clk = 1; rst = 1; {E, cout, zC} = 0;
    #6;
    rst = 0;
    
    // go to state 1
    #5;
    if({LAB, EA, LR, done} != 0 || {sclrR, ER, EC, sclrC} != 4'b1111)
        $write("State 1 is bugged.\n");
    else
        $write("State 1 passed.\n");
    
    // go to state 2
    E = 1;
    #clock;
    if({EC, sclrC, sclrR, LR, ER, done} != 0 || {LAB, EA} != 2'b11)
        $write("State 2 is bugged.\n");
    else
        $write("State 2 passed.\n");
    
    // go to state 3
    #clock;
    if({LAB, EC, sclrC, sclrR, LR, done} != 0 || {ER, EA} != 2'b11)
        $write("State 3 is bugged.\n");
    else
        $write("State 3 passed.\n");
    
    // go to state 4
    cout = 1;
    #clock;
    if({LAB, EA, EC, sclrC, sclrR, ER, done} != 0 || LR != 1)
        $write("State 4 is bugged.\n");
    else
        $write("State 4 passed.\n");
    
    // go to state 5
    zC = 0;
    #clock;
    if({LAB, EA, sclrC, sclrR, LR, ER, done} != 0 || EC != 1)
        $write("State 5 is bugged.\n");
    else
        $write("State 5 passed.\n");
    
    // go to state 6
    cout = 0; zC = 1;
    #clock; #clock;
    if({LAB, EA, EC, sclrC, sclrR, LR, ER} != 0 || done != 1)
        $write("State 6 is bugged.\n");
    else
        $write("State 6 passed.\n");
    
    // go to state 1
    E = 0;
    #clock;
    if({LAB, EA, LR, done} != 0 || {sclrR, ER, EC, sclrC} != 4'b1111)
        $write("State 1 is bugged.\n");
    else
        $write("State 1 passed.\n");
    
    $finish;

end
endmodule
