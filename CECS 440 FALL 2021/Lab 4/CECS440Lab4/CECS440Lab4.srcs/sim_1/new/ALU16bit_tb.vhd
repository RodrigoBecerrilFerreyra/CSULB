----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
--
-- Create Date: 10/25/2021 04:45:35 PM
-- Module Name: ALU16bit_tb - Behavioral
-- Project Name: Lab 4
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

entity ALU16bit_tb is
end ALU16bit_tb;

architecture Behavioral of ALU16bit_tb is

    -- define unit to test
    component ALU16bit
        port
        (
            A:    in  std_logic_vector(15 downto 0);
            B:    in  std_logic_vector(15 downto 0);
            S:    in  std_logic_vector(1 downto 0);
            Cout: out std_logic;
            Sout: out std_logic_vector(15 downto 0)
        );
    end component;

    -- define signals
    signal A_tb: std_logic_vector(15 downto 0) := "0000000000000000";
    signal B_tb: std_logic_vector(15 downto 0) := "0000000000000000";
    signal S_tb: std_logic_vector(1 downto 0) := "00";
    signal Cout_tb: std_logic;
    signal Sout_tb: std_logic_vector(15 downto 0);
    constant tick: time := 50 ns;

begin

    -- instantiate ALU16bit and tie inputs/outputs
    uut: ALU16bit
    port map
    (
        A => A_tb,
        B => B_tb,
        S => S_tb,
        Cout => Cout_tb,
        Sout => Sout_tb
    );

    -- main process
    process
    begin
        S_tb <= "00";
        A_tb <= x"0096"; -- 150
        B_tb <= x"0104"; -- 260
        wait for tick;

        S_tb <= "00";
        A_tb <= x"FFE7"; -- -25
        B_tb <= x"0041"; -- 65
        wait for tick;

        S_tb <= "00";
        A_tb <= x"0002"; -- 2
        B_tb <= x"0002"; -- 2
        wait for tick;

        S_tb <= "01";
        A_tb <= x"0226"; -- 550
        B_tb <= x"0140"; -- 320
        wait for tick;

        S_tb <= "01";
        A_tb <= x"0019"; -- 25
        B_tb <= x"003C"; -- 60
        wait for tick;

        S_tb <= "01";
        A_tb <= x"FFFE"; -- -2
        B_tb <= x"0010"; -- 16
        wait for tick;

        S_tb <= "10";
        A_tb <= x"0040"; -- 64
        B_tb <= x"0100"; -- 256
        wait for tick;

        S_tb <= "10";
        A_tb <= x"07D0"; -- 2000
        B_tb <= x"0003"; -- 3
        wait for tick;

        S_tb <= "10";
        A_tb <= x"14DE"; -- 5342
        B_tb <= x"03DA"; -- 986
        wait for tick;

        S_tb <= "11";
        A_tb <= x"000C"; -- 12
        B_tb <= x"0007"; -- 7
        wait for tick;

        S_tb <= "11";
        A_tb <= x"0000"; -- 0
        B_tb <= x"0929"; -- 2345
        wait for tick;

        S_tb <= "11";
        A_tb <= x"FFFF"; -- -1
        B_tb <= x"0005"; -- 5
        wait for tick;

        -- exits the simulation
        report "simulation finished successfully" severity FAILURE;
    end process;

end Behavioral;
