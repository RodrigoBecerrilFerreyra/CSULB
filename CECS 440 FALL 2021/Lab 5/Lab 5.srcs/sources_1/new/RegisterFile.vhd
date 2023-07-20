--------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 11/08/2021 09:09:02 PM
-- Design Name: RegisterFile
-- Module Name: RegisterFile - Behavioral
-- Project Name: Lab 5
-- Short description: A 16x16 register with special constant-valued registers
--     and asynchronous reads.
--------------------------------------------------------------------------------
-- Long description:
--     This module resembles a standard 16-wide 16-bit load register.
--     The data inside the register is retained until it is overwritten
--     by a load. A load happens on the rising edge of the clock if the
--     load bit is set; the data inside address a_addr is overwritten with
--     the data on a_data.
--     The value inside address 0 is always 0, and the value inside address 1
--     is always 1. Writes to these addresses are ignored.
--     The register should be reset before use; use before a reset results in
--     undefined and unsupported behavior.
--     Reset is achieved by asserting a low signal on clear_n.
--     The data on b_data and c_data is the data pointed to by
--     b_addr and c_addr; in C terms,
--     (b_data == *b_addr) and (c_data == *c_addr). These reads are
--     asynchronous; this means that the data is available immediately after the
--     pointer is changed.

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.STD_LOGIC_SIGNED;
use IEEE.NUMERIC_STD.ALL;

entity RegisterFile is
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
end RegisterFile;

architecture Behavioral of RegisterFile is

    -- this is the main 2D array that stores all data
    type memory is array (15 downto 0) of std_logic_vector(15 downto 0);
    --type memory is array (15 downto 0, 15 downto 0) of std_logic;

    -- declaration of memory
    signal mymem: memory;
begin

    -- asynchronous read (assign statement) from b and c
    b_data <= mymem(to_integer(unsigned(b_addr)));
    c_data <= mymem(to_integer(unsigned(c_addr)));

    process (clk, clear_n)
    begin

        -- if reset is asserted, then
        if clear_n = '0' then
            for i in 0 to 15 loop
                mymem(i) <= "0000000000000000";
            end loop;
            mymem(1) <= "0000000000000001";

        -- if reset is not asserted (if posedge clk)
        elsif clk = '1' then
            -- if load is asserted
            if load = '1' then
                case a_addr is
                    when "0000" => null;
                    when "0001" => null;
                    when others =>
                        mymem(to_integer(unsigned(a_addr))) <= a_data;
                end case;
            end if;
        end if;
    end process;
end Behavioral;
