----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
--
-- Create Date: 10/25/2021 12:37:32 PM
-- Module Name: ALU1bit_tb - Behavioral
-- Project Name: Lab 4
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

entity ALU1bit_tb is
end ALU1bit_tb;

architecture Behavioral of ALU1bit_tb is

    -- declare unit under test
    component ALU1bit
        port
        (
            A       :   in  std_logic;
            B       :   in  std_logic;
            Cin     :   in  std_logic;
            S       :   in  std_logic_vector(1 downto 0);
            Sout    :   out std_logic;
            Cout    :   out std_logic
        );
    end component;

    -- declare signals
    signal A_tb: std_logic := '0';
    signal B_tb: std_logic := '0';
    signal Cin_tb: std_logic := '0';
    signal S_tb: std_logic_vector(1 downto 0) := "00";
    signal Sout_tb: std_logic;
    signal Cout_tb: std_logic;
    constant tick: time := 100 ns;

begin

    -- instantiate ALU1bit as uut
    uut: ALU1bit
    port map
    (
        A => A_tb,
        B => B_tb,
        Cin => Cin_tb,
        S => S_tb,
        Sout => Sout_tb,
        Cout => Cout_tb
    );

    -- process to change A
    process
    begin
        wait for tick;
        A_tb <= not A_tb;
    end process;

    -- process to change B
    process
    begin
        wait for (tick*2);
        B_tb <= not B_tb;
    end process;

    -- process to change Cin
    process
    begin
        wait for (tick*4);
        Cin_tb <= not Cin_tb;
    end process;

    -- process to change S(0)
    process
    begin
        wait for (tick*8);
        S_tb(0) <= not S_tb(0);
    end process;

    -- process to change S(1)
    process
    begin
        wait for (tick*16);
        S_tb(1) <= not S_tb(1);
    end process;

end Behavioral;
