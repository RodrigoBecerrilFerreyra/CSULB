----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra

-- Module Name: MUX31 - Behavioral
-- Project Name: Lab 4
-- Description: I improved the mux block (is now an actual mux).
--   The last version had an RTL_LATCH in it, which I hear is something to avoid
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity MUX31 is
    -- define ports
    port
    (
        Input1: in  std_logic;
        Input2: in  std_logic;
        Input3: in  std_logic;
        S:      in  std_logic_vector(1 downto 0);
        Sout:   out std_logic
    );
end MUX31;

architecture Behavioral of MUX31 is
begin
    process (S, Input1, Input2, Input3)
    begin
        case S is
            when  "00"  => Sout <= Input1;
            when  "01"  => Sout <= Input1;
            when  "10"  => Sout <= Input2;
            when  "11"  => Sout <= Input3;
            when others => Sout <= 'Z';
        end case;
    end process;

end Behavioral;

-- previous file by the professor:

--entity MUX31 is
--port(	Input1		:	in	std_logic;
--		Input2		:	in	std_logic;
--		Input3		:	in	std_logic;
--		S			:	in	std_logic_vector(1 downto 0);
--		Sout		:	out	std_logic);
--end MUX31;

--architecture Behavioral of MUX31 is

--Begin
----MUX31 Logic (using When - ElSE structure)
--	Sout <=	Input1 when S="00" else
--				Input1 when S="01" else
--				Input2 when S="10" else
--				Input3 when S="11";


--end Behavioral;
