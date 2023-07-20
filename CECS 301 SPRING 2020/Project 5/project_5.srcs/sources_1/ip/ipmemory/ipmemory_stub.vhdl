-- Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
-- Date        : Tue May 05 10:39:24 2020
-- Host        : PC-2 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub {c:/Users/oscar/Coding Projects/CSULB/CECS 301 SPRING
--               2020/project_5/project_5.srcs/sources_1/ip/ipmemory/ipmemory_stub.vhdl}
-- Design      : ipmemory
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ipmemory is
  Port ( 
    a : in STD_LOGIC_VECTOR ( 14 downto 0 );
    d : in STD_LOGIC_VECTOR ( 15 downto 0 );
    clk : in STD_LOGIC;
    we : in STD_LOGIC;
    spo : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );

end ipmemory;

architecture stub of ipmemory is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "a[14:0],d[15:0],clk,we,spo[15:0]";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "dist_mem_gen_v8_0_10,Vivado 2016.2";
begin
end;
