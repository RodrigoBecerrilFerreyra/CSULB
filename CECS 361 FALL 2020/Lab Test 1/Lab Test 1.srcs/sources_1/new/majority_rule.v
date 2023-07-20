`timescale 1ns / 1ps

module majority_rule(
    input man,
    input eng0, input eng1, input eng2,
    output out
);

assign out = man | (eng0 & eng1) | (eng0 & eng2) | (eng1 & eng2);

endmodule
