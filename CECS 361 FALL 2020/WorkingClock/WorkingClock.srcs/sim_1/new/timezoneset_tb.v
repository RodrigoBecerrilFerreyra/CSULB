`timescale 1ns / 1ps
module timezoneset_tb();

reg btn;
reg [2:0] setvalue;
wire [2:0] outvalue;
wire [5:0] currentstate;

timezoneset uut(.BTN(btn), .setValue(setvalue), .outVal(outvalue), .currentState(currentState));

initial begin

    btn = 1; setvalue = 0;
    #10; // should see currentstate == 0
    btn = 0;
    
    setvalue = 1;
    #10; // should see currentstate == 1
    btn = 1;
    #10;
    
    setvalue = 0;
    #10;
    $finish;

end
endmodule
