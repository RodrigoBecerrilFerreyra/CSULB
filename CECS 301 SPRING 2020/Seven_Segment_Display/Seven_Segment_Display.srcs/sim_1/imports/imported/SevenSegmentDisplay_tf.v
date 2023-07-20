`timescale 1ns/1ns

///////////////////////////////////////////////////////////////////
// john tramel csulb cecs 301 seven segment display test fixture //
// 19 february 2020                                              //
// run simulation with your design - ensure ports match below    //
// also ensure that the instance name is the same                //
// simulation will confirm correct results                       //
// in event of an error the bad information will be displayed    //
///////////////////////////////////////////////////////////////////

module SevenSegmentDisplay_tf();

reg           clk;         //100Mhz clock
reg           rst;         //HA asynchronous reset
reg    [15:0] switches;    //data to display on Seven Segment Display
wire   [ 7:0] cathode;     //seven segment cathode signals
wire   [ 7:0] anode;       //seven segment anode signals
reg    [ 3:0] switch;      //for testing

/////////////////////////////////////////////////////////
// instantiate the device under test
/////////////////////////////////////////////////////////
seven_segment ssd
       (
       .clk       (clk),       
       .rst       (rst),       
       .value  (switches),       
       .cathode   (cathode),
       .anode     (anode)       
       );

/////////////////////////////////////////////////////////
// drive the clock
/////////////////////////////////////////////////////////
always #5 clk = ~clk;

/////////////////////////////////////////////////////////
// drive the inputs
/////////////////////////////////////////////////////////
initial begin
   clk = 0;
   rst = 1;
   switches = 16'h0000;
   switch = 4'b0;
   #100
   rst = 0;
   repeat (512)
      @(anode) switches = $random;
   $stop;
   end
   
always @(anode)
   begin
      #200
      case(anode)
         8'hFE: switch = switches[ 3: 0];
         8'hFD: switch = switches[ 7: 4];
         8'hFB: switch = switches[11: 8];
         8'hF7: switch = switches[15:12];
         8'hEF: switch = switches[ 3: 0];
         8'hDF: switch = switches[ 7: 4];
         8'hBF: switch = switches[11: 8];
         8'h7F: switch = switches[15:12];
         endcase
      
      $display("");   
      $display("Data In: %h Anode: %h Digit: %h",switches,anode,switch);
      case(switch[3:0])
         4'h0: if (cathode !== 8'hC0) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h1: if (cathode !== 8'hF9) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h2: if (cathode !== 8'hA4) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h3: if (cathode !== 8'hB0) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h4: if (cathode !== 8'h99) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h5: if (cathode !== 8'h92) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h6: if (cathode !== 8'h82) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h7: if (cathode !== 8'hF8) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h8: if (cathode !== 8'h80) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'h9: if (cathode !== 8'h90) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'hA: if (cathode !== 8'h88) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'hB: if (cathode !== 8'h83) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'hC: if (cathode !== 8'hC6) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'hD: if (cathode !== 8'hA1) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'hE: if (cathode !== 8'h86) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
         4'hF: if (cathode !== 8'h8E) $display("Error:   switch %h cathode %h anode %h ",switch,cathode,anode); else 
                                      $display("Correct: switch %h cathode %h anode %h",switch,cathode,anode);
      endcase
   end
      
endmodule

