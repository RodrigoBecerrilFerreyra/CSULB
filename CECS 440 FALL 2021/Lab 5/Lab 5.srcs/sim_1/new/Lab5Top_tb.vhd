----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 11/09/2021 12:20:02 AM
-- Design Name: Lab5Top_tb
-- Module Name: Lab5Top_tb - Behavioral
-- Project Name: Lab 5
-- Description: Testbench file for Lab5Top.vhd 
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

entity Lab5Top_tb is
end Lab5Top_tb;

architecture Behavioral of Lab5Top_tb is

    -- declare Lab5Top
    component Lab5Top
        port
        (
            clk: in std_logic;
            clear: in std_logic;
            instruction: in std_logic_vector(15 downto 0)
        );
    end component;

    -- declare testbench signals
    signal clk: std_logic := '1';
    signal rst: std_logic := '1';
    signal inst: std_logic_vector(15 downto 0) := "0000000000000000";
    constant tick: time := 50 ns;

begin

    -- instantiate Lab5Top
    uut: Lab5Top
    port map
    (
        clk => clk,
        clear => rst,
        instruction => inst
    );

    -- clock process
    clock: process
    begin
        clk <= not clk;
        wait for tick;
    end process clock;

    -- main process
    main: process
    begin
        rst <= '0';
        wait for tick;
        rst <= '1';
        wait for tick;

        -- add $2, $1, $1
        --   op <= inst[15:12]
        --   rd <= inst[11:8]
        --   rs <= inst[7:4]
        --   rt <= inst[3:0]

        inst <= x"0211";
        wait for (tick*2);

        -- add $3, $2, $1
        inst <= x"0321";
        wait for (tick*2);
        
        -- add $4, $3, $2
        inst <= x"0432";
        wait for (tick*2);
        
        -- sub $5, $4, $3
        inst <= x"1543";
        wait for (tick*2);
        
        -- sub $1, $5, $1
        inst <= x"1151";
        wait for (tick*2);
        
        -- sub $0, $3, $0
        inst <= x"1030";
        wait for (tick*2);
        
        -- and $6, $1, $1
        inst <= x"2611";
        wait for (tick*2);
        
        -- and $7, $3, $0
        inst <= x"2730";
        wait for (tick*2);
        
        -- or $8, $4, $1
        inst <= x"3841";
        wait for (tick*2);

        -- exits the simulation
        report "simulation finished successfully" severity FAILURE;
    end process main;

end Behavioral;
