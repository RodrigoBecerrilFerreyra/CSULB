----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 10/12/2021 03:35:27 PM
-- Design Name: mux
-- Module Name: onebit_2to1mux
-- Project Name: CECS 440 Lab 3
-- Description: Simple multiplexer.
-- 
-- Dependencies: 
-- 
-- Revision: 2
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mux is
    Port
    (
        in1:    in  std_logic;
        in2:    in  std_logic;
        sel:    in  std_logic;
        mux_out: out std_logic 
    );
end mux;

architecture Behavioral of mux is
begin

-- combinatorial assign
-- equivalent statement:
--     assign result = sel ? in1 : in0;
-- 'Z' when others needed to cover all 9 cases
-- see https://www2.cs.sfu.ca/~ggbaker/reference/std_logic/1164/std_logic.html
with sel select mux_out <= in2 when '1', in1 when '0','Z' when others;

end Behavioral;
