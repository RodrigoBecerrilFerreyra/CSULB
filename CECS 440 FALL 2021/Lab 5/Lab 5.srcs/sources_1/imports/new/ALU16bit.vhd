----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
--
-- Create Date: 10/25/2021 01:23:54 PM
-- Module Name: ALU16bit - Behavioral
-- Project Name: Lab 4
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
--use IEEE.NUMERIC_STD.ALL;

-- define top-level ports for ALU16bit
entity ALU16bit is
    port
    (
        A:    in  std_logic_vector(15 downto 0);
        B:    in  std_logic_vector(15 downto 0);
        S:    in  std_logic_vector(1 downto 0);
        Cout: out std_logic;
        Sout: out std_logic_vector(15 downto 0)
    );
end ALU16bit;

architecture Behavioral of ALU16bit is
    -- ALU1bit declaration
    component ALU1bit
        port(
                A       :   in  std_logic;
                B       :   in  std_logic;
                Cin     :   in  std_logic;
                S       :   in  std_logic_vector(1 downto 0);
                Sout    :   out std_logic;
                Cout    :   out std_logic
        );
    end component;

    -- cin-cout inbetween wires
    signal inbetween: std_logic_vector(14 downto 0);
begin

    Sum0: ALU1bit
    port map
    (
        A => A(0),
        B => B(0),
        Cin => S(0),
        S => S,
        Cout => inbetween(0),
        Sout => Sout(0)
    );

    Sum1: ALU1bit
    port map
    (
        A => A(1),
        B => B(1),
        Cin => inbetween(0),
        S => S,
        Cout => inbetween(1),
        Sout => Sout(1)
    );

    Sum2: ALU1bit
    port map
    (
        A => A(2),
        B => B(2),
        Cin => inbetween(1),
        S => S,
        Cout => inbetween(2),
        Sout => Sout(2)
    );

    Sum3: ALU1bit
    port map
    (
        A => A(3),
        B => B(3),
        Cin => inbetween(2),
        S => S,
        Cout => inbetween(3),
        Sout => Sout(3)
    );

    Sum4: ALU1bit
    port map
    (
        A => A(4),
        B => B(4),
        Cin => inbetween(3),
        S => S,
        Cout => inbetween(4),
        Sout => Sout(4)
    );

    Sum5: ALU1bit
    port map
    (
        A => A(5),
        B => B(5),
        Cin => inbetween(4),
        S => S,
        Cout => inbetween(5),
        Sout => Sout(5)
    );

    Sum6: ALU1bit
    port map
    (
        A => A(6),
        B => B(6),
        Cin => inbetween(5),
        S => S,
        Cout => inbetween(6),
        Sout => Sout(6)
    );

    Sum7: ALU1bit
    port map
    (
        A => A(7),
        B => B(7),
        Cin => inbetween(6),
        S => S,
        Cout => inbetween(7),
        Sout => Sout(7)
    );

    Sum8: ALU1bit
    port map
    (
        A => A(8),
        B => B(8),
        Cin => inbetween(7),
        S => S,
        Cout => inbetween(8),
        Sout => Sout(8)
    );

    Sum9: ALU1bit
    port map
    (
        A => A(9),
        B => B(9),
        Cin => inbetween(8),
        S => S,
        Cout => inbetween(9),
        Sout => Sout(9)
    );

    Sum10: ALU1bit
    port map
    (
        A => A(10),
        B => B(10),
        Cin => inbetween(9),
        S => S,
        Cout => inbetween(10),
        Sout => Sout(10)
    );

    Sum11: ALU1bit
    port map
    (
        A => A(11),
        B => B(11),
        Cin => inbetween(10),
        S => S,
        Cout => inbetween(11),
        Sout => Sout(11)
    );

    Sum12: ALU1bit
    port map
    (
        A => A(12),
        B => B(12),
        Cin => inbetween(11),
        S => S,
        Cout => inbetween(12),
        Sout => Sout(12)
    );

    Sum13: ALU1bit
    port map
    (
        A => A(13),
        B => B(13),
        Cin => inbetween(12),
        S => S,
        Cout => inbetween(13),
        Sout => Sout(13)
    );

    Sum14: ALU1bit
    port map
    (
        A => A(14),
        B => B(14),
        Cin => inbetween(13),
        S => S,
        Cout => inbetween(14),
        Sout => Sout(14)
    );

    Sum15: ALU1bit
    port map
    (
        A => A(15),
        B => B(15),
        Cin => inbetween(14),
        S => S,
        Cout => Cout,
        Sout => Sout(15)
    );

end Behavioral;
