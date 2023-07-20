`timescale 1ns/1ns

////////////////////////////////////////////////////////
// testbench for cecs 301 register file
// march 30, 2020 john tramel
// ensure the ports on instantiated module matches yours
////////////////////////////////////////////////////////
module RegFile_tb();

reg          clk;
reg          rst;
reg          LdReg;
reg    [2:0] WtAdrs;
reg    [7:0] WtData;
reg    [2:0] RdAdrsA;
reg    [2:0] RdAdrsB;
wire   [7:0] RdDataA;
wire   [7:0] RdDataB;
integer      i;

///////////////////////////////////////////////////////
// instantiate the device under test
// ensure ports match your design
///////////////////////////////////////////////////////
register_file RegFile(
	.clk(clk), 
	.rst(rst), 
	.write(LdReg), 
	.wAdrs(WtAdrs), 
	.rAdrsA(RdAdrsA), 
	.rAdrsB(RdAdrsB), 
	.wData(WtData), 
	.rDataA(RdDataA), 
	.rDataB(RdDataB)
        );

///////////////////////////////////////////////////////
// setup the system clock
///////////////////////////////////////////////////////
always #5 clk = ~clk;

///////////////////////////////////////////////////////
// exercise the design
///////////////////////////////////////////////////////
initial begin
   clk     = 0;
   rst     = 1;
   LdReg   = 0;
   WtAdrs  = 0;
   WtData  = 0;
   RdAdrsA = 0;
   RdAdrsB = 0;
   i       = 0;
   #100
   rst     = 0;

////////////////////////////////////////////////
// check the initial state of the register file
////////////////////////////////////////////////
   for (i=0; i<8; i = i + 1)
      begin
      @(posedge clk)
      if (RdDataA !== 8'h00) $display("Error Initial A: Adrs: %h is: %h sb: %h",i,RdDataA,WtData);
      if (RdDataB !== 8'h00) $display("Error Initial B: Adrs: %h is: %h sb: %h",i,RdDataB,WtData);
      end
////////////////////////////////////////////////
// check the functionality of the register file
////////////////////////////////////////////////      
   for (i=0; i<8; i = i + 1)
      begin
      WtAdrs  = i;
      RdAdrsA = i;
      RdAdrsB = i;
      WtData  = $random;
      
      @(posedge clk)
      LdReg = 1;
      @(posedge clk)
      LdReg = 0;
      @(posedge clk)
      if (RdDataA !== WtData) $display("Error Read A: Adrs: %h is: %h sb: %h",i,RdDataA,WtData);
      if (RdDataB !== WtData) $display("Error Read B: Adrs: %h is: %h sb: %h",i,RdDataB,WtData);
      end

   end
endmodule


