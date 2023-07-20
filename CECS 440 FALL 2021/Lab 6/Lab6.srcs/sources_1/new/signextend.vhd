--------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 11/30/2021 04:14:50 PM
-- Design Name: Lab 6
-- Module Name: signextend - Behavioral
-- Project Name: Lab 6
-- Description: Combinational module that extends the sign of a 4-bit
--     number into a 16-bit number.
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

entity signextend is
    port
    (
        immIn: in std_logic_vector(3 downto 0);
        immout: out std_logic_vector(15 downto 0)
    );
end signextend;

architecture Behavioral of signextend is
begin

    immOut(0) <= immIn(0);
    immOut(1) <= immIn(1);
    immOut(2) <= immIn(2);
    immOut(3) <= immIn(3);
    immOut(4) <= immIn(3);
    immOut(5) <= immIn(3);
    immOut(6) <= immIn(3);
    immOut(7) <= immIn(3);
    immOut(8) <= immIn(3);
    immOut(9) <= immIn(3);
    immOut(10) <= immIn(3);
    immOut(11) <= immIn(3);
    immOut(12) <= immIn(3);
    immOut(13) <= immIn(3);
    immOut(14) <= immIn(3);
    immOut(15) <= immIn(3);

end Behavioral;
