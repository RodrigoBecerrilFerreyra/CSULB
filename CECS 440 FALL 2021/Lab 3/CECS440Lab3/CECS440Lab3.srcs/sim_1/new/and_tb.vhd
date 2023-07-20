----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 10/12/2021 03:35:27 PM
-- Design Name: and_tb
-- Module Name: and_tb
-- Project Name: CECS 440 Lab 3
-- Description: Testbench file for and_word.vhd
-- 
-- Dependencies: 
-- 
-- Revision: 1
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity and_tb is
end and_tb;

architecture Behavioral of and_tb is
    signal a: std_logic_vector(0 to 3) := "0000";
    signal b: std_logic_vector(0 to 3) := "0000";
    signal q: std_logic_vector(0 to 3);
    constant tick: time := 1 us;
begin -- all below code taken from or_tb.vhd
    wide_and : entity work.and_word -- not sure what wide_or is
    -- get values from work.and_word
    port map (
        a => A,
        b => B,
        result => q
    );

    -- process that assigns increasing numbers to a
    drive_a : process
    begin
        wait for tick;
        a <= a + "0001";
    end process drive_a;

    -- process that assigns increasing numbers to b
    drive_b : process
    begin
        wait for (tick*4);
        b <= b + "0001";
    end process drive_b;
end architecture Behavioral;
