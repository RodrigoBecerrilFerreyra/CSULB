`timescale 1ns / 1ps

module majority_rule_tb();

reg man, eng0, eng1, eng2;
wire out;

majority_rule uut(.man(man), .eng0(eng0), .eng1(eng1), .eng2(eng2), .out(out));

integer i;

initial
begin
    for(i = 0; i <= 4'b1111; i = i + 1) // you can also use i < 16
    begin
        {man, eng0, eng1, eng2} = i; //concatination operator
        //0     0     0     0
        //0     0     0     1
        //0     0     1     0
        //0     0     1     1
        //etc
        #50;
    end
end
endmodule
