--------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 11/08/2021 11:40:22 PM
-- Design Name: Lab5Top
-- Module Name: Lab5Top - Behavioral
-- Project Name: Lab 5
-- Description: Top-level module for Lab 5
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

entity Lab5Top is

    port
    (
        clk: in std_logic;
        clear: in std_logic;
        instruction: in std_logic_vector(15 downto 0)
    );

end Lab5Top;

architecture Behavioral of Lab5Top is

    -- declare modules to use
    component RegisterFile
        port
        (
            clk:     in std_logic;
            clear_n: in std_logic; -- reset
            
            a_addr: in std_logic_vector(3 downto 0);
            a_data: in std_logic_vector(15 downto 0);
            load:   in std_logic;
    
            b_addr: in  std_logic_vector(3 downto 0);
            b_data: out std_logic_vector(15 downto 0);
    
            c_addr: in  std_logic_vector(3 downto 0);
            c_data: out std_logic_vector(15 downto 0)
        );
    end component;

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

    signal ALUout: std_logic_vector(15 downto 0);
    --signal ALUcout: std_logic;
    signal Bout: std_logic_vector(15 downto 0);
    signal Cout: std_logic_vector(15 downto 0);

begin

    -- instantiate modules
    mainregister: RegisterFile
    port map
    (
        clk => clk,
        clear_n => clear,
        a_addr => instruction(11 downto 8),
        a_data => ALUout,
        load => '1',
        b_addr => instruction(7 downto 4),
        c_addr => instruction(3 downto 0),
        b_data => Bout,
        c_data => Cout
    );

    alu: ALU16bit
    port map
    (
        A => Bout,
        B => Cout,
        S => instruction(13 downto 12),
        Sout => ALUout
    );

end Behavioral;
