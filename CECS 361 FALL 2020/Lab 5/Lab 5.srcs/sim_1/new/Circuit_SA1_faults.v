`timescale 1ns / 1ps
/*
    Engineer: Rodrigo Becerril Ferreyra
    Company: California State University, Long Beach
    Project: Lab 5
    Date: 28 November 2020
*/
module Circuit_SA1_faults();
reg a, b, c;
wire f1, f0;

Circuit_SA1 uut(.A(a), .B(b), .C(c), .F1(f1), .F0(f0));

initial begin

    // activate and propogate S01
    a = 0; // activate
    c = 1; b = 1; // propogate
    #10; // wait
    a = 1; // flip activation input
    #10; // should see a change in f0
    
    // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S02
    b = 0;
    a = 1; c = 1;
    #10;
    b = 1;
    #10; // change in f0
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S03
    c = 0;
    a = 1; b = 0;
    // also a = 0; b = 1;
    #10;
    c = 1;
    #10; // change in both
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S04
    a = 0;
    b = 1; c = 1;
    #10;
    a = 1;
    #10; // change in f0
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S05
    b = 0;
    a = 1; c = 1;
    #10;
    b = 1;
    #10; // chnage in f0
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S06
    a = 0; b = 0;
    c = 1;
    #10;
    a = 1; // only need to flip one to change XOR from 0 to 1
    #10; // change in both
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S07
    b = 0;
    a = 1; c = 1;
    #10;
    b = 1;
    #10; // change in f0
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S08
    a = 0;
    b = 1; c = 1;
    #10;
    a = 1;
    #10; // change in f0
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S09
    c = 0;
    a = 0; b = 1;
    // also a = 1; b = 0;
    #10;
    c = 1;
    #10; // change in both
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S10
    a = 0; b = 0;
    c = 1;
    #10;
    a = 1; // only need to flip one to change XOR from 0 to 1
    #10; // change in both
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S11
    a = 0; b = 0;
    c = 1; // also c = 0;
    #10;
    a = 1; // only need to flip one to change XOR from 0 to 1
    #10; // change in both
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    // S12
    c = 0;
    a = 1; b = 1;
    // a and b can be anything
    #10;
    c = 1;
    #10; // change in f0
    
        // intermediary space
    {a, b, c} = 0;
    #5;
    
    $finish;

end
endmodule
