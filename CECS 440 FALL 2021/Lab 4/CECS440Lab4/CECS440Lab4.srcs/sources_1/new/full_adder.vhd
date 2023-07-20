--------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
--
-- Create Date: 10/12/2021 11:54:07 PM
-- Design Name: full_adder
-- Module Name: full_adder
-- Project Name: CECS 440 Lab 3
-- Description: A simple 1-bit wide full adder.
--
-- Dependencies:
--
-- Revision: 1
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity full_adder is
    port
    (
        a:    in  std_logic;
        b:    in  std_logic;
        cin:  in  std_logic;
        sum:  out std_logic;
        cout: out std_logic
    );
end full_adder;

architecture Behavioral of full_adder is
begin

    -- two simple assign statements for a one-bit adder
    sum <= a xor b xor cin;
    cout <= (a and b) or (b and cin) or (cin and a);

end Behavioral;
