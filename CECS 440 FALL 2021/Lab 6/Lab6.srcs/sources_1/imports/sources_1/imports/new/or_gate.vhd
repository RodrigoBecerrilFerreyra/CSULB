----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
--
-- Create Date: 10/25/2021 11:46:06 AM
-- Module Name: or_gate - Behavioral
-- Project Name: Lab 4
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

entity or_gate is
    port
    (
        In1 : in  std_logic;
        In2 : in  std_logic;
        Sout: out std_logic
    );
end or_gate;

architecture Behavioral of or_gate is
begin

    Sout <= In1 or In2;

end Behavioral;
