`timescale 1ns/1ns

//testbench for alu module
//csulb cecs301 spring 2020
//make sure instantiated ALU ports match yours
//run for 1300ns

module alu_tb_instructor;

reg  [7:0] RdDataA, RdDataB;
reg  [2:0] OpCode;
reg  [8:0] SumResult;
reg  [8:0] DifResult;
reg  [8:0] ShiftResult;
reg  [8:0] RotResult;
reg  [8:0] AndResult;
reg  [8:0] OrResult;
reg  [8:0] XorResult;
reg  [8:0] NegResult;
reg        CryResult;
reg        ZerResult;

wire       zero, carry;
wire [7:0] AluOut;

reg  [5:0] i,j;

///////////////////////////////////////////
// instantiate the design under test
// ensure that the port names are the same
//////////////////////////////////////////
alu alu (
   .OperandA (RdDataA[7:0]),
   .OperandB (RdDataB[7:0]),
   .OpcodeSelect  (OpCode),
   .Zero    (zero),
   .Carry   (carry),
   .ALUout  (AluOut)
   );

///////////////////////////////////////////
// exercise the design to ensure that the
// alu is functional and report any errors
//////////////////////////////////////////
initial begin
   $timeformat(-9,2," ns",10);
   RdDataA     = 0;
   RdDataB     = 0;
   SumResult   = 0;
   DifResult   = 0;
   ShiftResult = 0;
   RotResult   = 0;
   AndResult   = 0;
   OrResult    = 0;
   XorResult   = 0;
   NegResult   = 0;
   CryResult   = 0;
   ZerResult   = 0;

   OpCode  = 0;
   for (j = 0; j < 16; j = j + 1)
      begin
      for (i = 0; i < 8; i = i + 1)
         begin
         RdDataA = $random;
         RdDataB = $random;
         #10
         case(OpCode)
            3'b000: begin
                    SumResult   =  RdDataA + RdDataB;
                    CryResult   =  SumResult[8];
                    ZerResult   = ~|SumResult[7:0];
                    if (AluOut !== SumResult[7:0])
                       $display("Add Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b001: begin
                    DifResult   =  RdDataA - RdDataB;
                    CryResult   =  DifResult[8];
                    ZerResult   = ~|DifResult[7:0];
                    if (AluOut !== DifResult[7:0])
                       $display("Sub Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b010: begin
                    ShiftResult =  RdDataA << 1;
                    CryResult   =  ShiftResult[8];
                    ZerResult   = ~|ShiftResult[7:0];
                    if (AluOut !== ShiftResult[7:0])
                       $display("Shift Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b011: begin
                    RotResult   = {RdDataA[0],RdDataA[7:1]};
                    CryResult   =  RotResult[8];
                    ZerResult   = ~|RotResult[7:0];
                    if (AluOut !== RotResult[7:0])
                       $display("Rot Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b100: begin
                    AndResult   =  RdDataA & RdDataB;
                    CryResult   =  AndResult[8];
                    ZerResult   = ~|AndResult[7:0];
                    if (AluOut !== AndResult[7:0])
                       $display("And Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b101: begin
                    OrResult    =  RdDataA | RdDataB;
                    CryResult   =  OrResult[8];
                    ZerResult   = ~|OrResult[7:0];
                    if (AluOut !== OrResult[7:0])
                       $display("Or Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b110: begin
                    XorResult   =  RdDataA ^ RdDataB;
                    CryResult   =  XorResult[8];
                    ZerResult   = ~|XorResult[7:0];
                    if (AluOut !== XorResult[7:0])
                       $display("Xor Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            3'b111: begin
                    NegResult   = ~RdDataA;
                    CryResult   =  NegResult[8];
                    ZerResult   = ~|NegResult[7:0];
                    if (AluOut !== NegResult[7:0])
                       $display("Neg Error: Op1: %h Op2: %h Is: %h Sb: %h ",
                                 RdDataA, RdDataB,AluOut,SumResult[7:0]);
                    end
            endcase
            if (carry !== CryResult)
                       $display("Cry Error:  Is: %b Sb: %b ",
                                  carry, CryResult);
            if (zero  !== ZerResult)
                       $display("Zer Error:  Is: %b Sb: %b ",
                                  zero, ZerResult);
         OpCode = OpCode + 1;
         end // for i
      end  //for j
   end //initial
endmodule

