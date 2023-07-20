/*`timescale 1ns / 1ps
module timezoneset(clk, rst, BTN, setValue, outVal, currentState);

input wire clk, rst, BTN;
input [2:0] setValue;
output reg [5:0] outVal;

output reg [2:0] currentState;

reg [2:0] nextState;

always @(posedge clk, posedge rst)
    if(rst) currentState <= 0;
    else    currentState <= nextState;

// state switching 
always @(*)
    if(BTN)
    begin
    end else
        nextState = currentState;


//always @(*)
//begin
//    if (BTN) begin
//        case({currentState, setValue})
//        // CurrentState -> LA
//        6'b000_000: outVal <= 0; // LA -> LA
//        6'b000_001: begin outVal = 5'd17; currentState <= 3'b001; end // LA -> Tokyo
//        6'b000_010: begin outVal <= 5'd8; currentState <= 3'b010; end // LA -> London
//        6'b000_011: begin outVal <= 5'd3; currentState <= 3'b011; end // LA -> New York
//        6'b000_100: begin outVal <= 5'd2; currentState <= 3'b100; end // LA -> Chicago
//        6'b000_101: begin outVal <= -5'd2; currentState <= 3'b101; end // LA -> Honolulu
//        // CurrentState -> Tokyo
//        6'b001_000: begin outVal <= -5'd17; currentState <= 3'b000; end // Tokyo -> LA
//        6'b001_001: outVal <= 0; // Tokyo -> Tokyo
//        6'b001_010: begin outVal <= -5'd9; currentState <= 3'b010; end // Tokyo -> London
//        6'b001_011: begin outVal <= -5'd14; currentState <= 3'b011; end // Tokyo -> New York
//        6'b001_100: begin outVal <= -5'd15; currentState <= 3'b100; end // Tokyo -> Chicago
//        6'b001_101: begin outVal <= -5'd19; currentState <= 3'b101; end // Tokyo -> Honolulu
//        // CurrentState -> London
//        6'b010_000: begin outVal <= -5'd8; currentState <= 3'b000; end // London -> LA
//        6'b010_001: begin outVal <= 5'd9; currentState <= 3'b001; end // London -> Tokyo
//        6'b010_010: outVal <= 0; // London -> London
//        6'b010_011: begin outVal <= -5'd5; currentState <= 3'b011; end // London -> New York
//        6'b010_100: begin outVal <= -5'd6; currentState <= 3'b100; end // London -> Chicago
//        6'b010_101: begin outVal <= -5'd10; currentState <= 3'b101; end // London -> Honolulu
//        // CurrentState -> New York
//        6'b011_000: begin outVal <= -5'd3; currentState <= 3'b000; end // New York -> LA
//        6'b011_001: begin outVal <= 5'd14; currentState <= 3'b001; end // New York -> Tokyo
//        6'b011_010: begin outVal <= 5'd5; currentState <= 3'b010; end // New York -> London
//        6'b011_011: outVal <= 0; // New York -> New York
//        6'b011_100: begin outVal <= -5'd1; currentState <= 3'b100; end // New York -> Chicago
//        6'b011_101: begin outVal <= -5'd5; currentState <= 3'b101; end // New York -> Honolulu
//        // CurrentState -> Chicago
//        6'b100_000: begin outVal <= -5'd2; currentState <= 3'b000; end // Chicago -> LA
//        6'b100_001: begin outVal <= -5'd15; currentState <= 3'b001; end // Chicago -> Tokyo
//        6'b100_010: begin outVal <= 5'd6; currentState <= 3'b010; end // Chicago -> London
//        6'b100_011: begin outVal <= 5'd1; currentState <= 3'b011; end // Chicago -> New York
//        6'b100_100: outVal <= 0; // Chicago -> Chicago
//        6'b100_101: begin outVal <= -5'd4; currentState <= 3'b101; end // Chicago -> Honolulu
//        // CurrentState -> Honolulu
//        6'b101_000: begin outVal <= 5'd2; currentState <= 3'b000; end // Honolulu -> LA
//        6'b101_001: begin outVal <= 5'd19; currentState <= 3'b001; end // Honolulu -> Tokyo
//        6'b101_010: begin outVal <= 5'd10; currentState <= 3'b010; end // Honolulu -> London
//        6'b101_011: begin outVal <= 5'd5; currentState <= 3'b011; end // Honolulu -> New York
//        6'b101_100: begin outVal <= 5'd4; currentState <= 3'b100; end // Honolulu -> Chicago
//        6'b101_101: outVal <= 0; // Honolulu -> Honolulu        
//        default: outVal <= 0;
//        endcase
//    end
//    else if (outVal != 0)
//        outVal <= 0;
//end

endmodule*/
`timescale 1ns / 1ps
module timezoneset(clk, rst, BTN, setValue, outVal, currentState);
input wire clk, rst, BTN;
input [2:0] setValue;
output reg [5:0] outVal;

output reg [2:0] currentState;

always @(*)
begin
    if (BTN) begin
        case({currentState, setValue})
        // CurrentState -> LA
        6'b000_000: outVal = 0; // LA -> LA
        6'b000_001: begin outVal = 6'd17; currentState = setValue; end // LA -> Tokyo
        6'b000_010: begin outVal = 6'd8; currentState = setValue; end // LA -> London
        6'b000_011: begin outVal = 6'd3; currentState = setValue; end // LA -> New York
        6'b000_100: begin outVal = 6'd2; currentState = setValue; end // LA -> Chicago
        6'b000_101: begin outVal = -6'd2; currentState = setValue; end // LA -> Honolulu
        // CurrentState -> Tokyo
        6'b001_000: begin outVal = -6'd17; currentState = setValue; end // Tokyo -> LA
        6'b001_001: outVal = 0; // Tokyo -> Tokyo
        6'b001_010: begin outVal = -6'd9; currentState = setValue; end // Tokyo -> London
        6'b001_011: begin outVal = -6'd14; currentState = setValue; end // Tokyo -> New York
        6'b001_100: begin outVal = -6'd15; currentState = setValue; end // Tokyo -> Chicago
        6'b001_101: begin outVal = -6'd19; currentState = setValue; end // Tokyo -> Honolulu
        // CurrentState -> London
        6'b010_000: begin outVal = -6'd8; currentState = setValue; end // London -> LA
        6'b010_001: begin outVal = 6'd9; currentState = setValue; end // London -> Tokyo
        6'b010_010: outVal = 0; // London -> London
        6'b010_011: begin outVal = -6'd5; currentState = setValue; end // London -> New York
        6'b010_100: begin outVal = -6'd6; currentState = setValue; end // London -> Chicago
        6'b010_101: begin outVal = -6'd10; currentState = setValue; end // London -> Honolulu
        // CurrentState -> New York
        6'b011_000: begin outVal = -6'd3; currentState = setValue; end // New York -> LA
        6'b011_001: begin outVal = 6'd14; currentState = setValue; end // New York -> Tokyo
        6'b011_010: begin outVal = 6'd5; currentState = setValue; end // New York -> London
        6'b011_011: outVal = 0; // New York -> New York
        6'b011_100: begin outVal = -6'd1; currentState = setValue; end // New York -> Chicago
        6'b011_101: begin outVal = -6'd5; currentState = setValue; end // New York -> Honolulu
        // CurrentState -> Chicago
        6'b100_000: begin outVal = -6'd2; currentState = setValue; end // Chicago -> LA
        6'b100_001: begin outVal = -6'd15; currentState = setValue; end // Chicago -> Tokyo
        6'b100_010: begin outVal = 6'd6; currentState = setValue; end // Chicago -> London
        6'b100_011: begin outVal = 6'd1; currentState = setValue; end // Chicago -> New York
        6'b100_100: outVal = 0; // Chicago -> Chicago
        6'b100_101: begin outVal = -6'd4; currentState = setValue; end // Chicago -> Honolulu
        // CurrentState -> Honolulu
        6'b101_000: begin outVal = 6'd2; currentState = setValue; end // Honolulu -> LA
        6'b101_001: begin outVal = 6'd19; currentState = setValue; end // Honolulu -> Tokyo
        6'b101_010: begin outVal = 6'd10; currentState = setValue; end // Honolulu -> London
        6'b101_011: begin outVal = 6'd5; currentState = setValue; end // Honolulu -> New York
        6'b101_100: begin outVal = 6'd4; currentState = setValue; end // Honolulu -> Chicago
        6'b101_101: outVal = 0; // Honolulu -> Honolulu        
        default: outVal = 0;
        endcase
    end
    else if (outVal != 0)
        outVal = 0;
end
    
endmodule

