----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 10/12/2021 03:35:27 PM
-- Design Name: and_word
-- Module Name: and_word - Behavioral
-- Project Name: CECS 440 Lab 3
-- Description: A simple 4-bit wide AND gate.
-- 
-- Dependencies: 
-- 
-- Revision: 1
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity and_word is
    generic
    (
        WIDTH : natural :=4
    );

    Port
    (
        -- ports are [0:3]
        A:      in  std_logic_vector(0 to WIDTH-1);
        B:      in  std_logic_vector(0 to WIDTH-1);
        result: out std_logic_vector(0 to WIDTH-1)
    );
end and_word;

architecture Behavioral of and_word is
begin

    -- combinatorial statements
    -- I do this instead of a for loop because it's faster and we don't have
    -- many bits in the vector
    
    -- this is equivalent to an assign statement in Verilog
    result(3) <= A(3) and B(3);
    result(2) <= A(2) and B(2);
    result(1) <= A(1) and B(1);
    result(0) <= A(0) and B(0);

end Behavioral;
