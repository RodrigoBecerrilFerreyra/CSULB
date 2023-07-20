----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 10/13/2021 12:17:35 AM
-- Design Name: full_adder
-- Module Name: full_adder
-- Project Name: CECS 440 Lab 3
-- Description: full_adder testbench.
-- 
-- Dependencies: 
-- 
-- Revision: 1
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity full_adder_tb is
    -- no ports in tb
end full_adder_tb;

architecture Behavioral of full_adder_tb is

    -- define (and connect to) full_adder module
    component full_adder
        port
        (
            a:    in  std_logic;
            b:    in  std_logic;
            cin:  in  std_logic;
            sum:  out std_logic;
            cout: out std_logic
        );
    end component;

    -- this goes here to define signals and variables in architecture
    -- := is always used for initialization
    signal first: std_logic := '0';
    signal second: std_logic := '0';
    signal carryin: std_logic := '0';
    signal carryout: std_logic;
    signal answer: std_logic;
    constant tick: time := 1 us;

begin

    -- instantiate full_adder as uut 
    uut: full_adder port map
    (
        -- format: <port_name> => <assigned_signal>
        a => first,
        b => second,
        cin => carryin,
        cout => carryout,
        sum => answer
    );

    -- process to load values for first
    first_update: process
    begin
        wait for tick;
        first <= not first;
    end process first_update;
    
    -- process to load values for second
    second_update: process
    begin
        wait for (tick*2);
        second <= not second;
    end process second_update;
    
    -- process to load values for carrying
    carryin_update: process
    begin
        wait for (tick*4);
        carryin <= not carryin;
    end process carryin_update;

end Behavioral;
