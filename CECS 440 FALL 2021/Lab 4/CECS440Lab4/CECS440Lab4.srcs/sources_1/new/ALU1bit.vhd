----------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
--
-- Create Date: 10/25/2021 11:31:08 AM
-- Module Name: ALU1bit - Behavioral
-- Project Name: Lab 4
----------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;

-- assign top-level ports
entity ALU1bit is
    port(
            A       :   in  std_logic;
            B       :   in  std_logic;
            Cin     :   in  std_logic;
            S       :   in  std_logic_vector(1 downto 0);
            Sout    :   out std_logic;
            Cout    :   out std_logic
    );
end ALU1bit;

Architecture behavior of ALU1bit is
    -- intstantiate full_adder module
    component full_adder
        port
        (
            a       :   in  std_logic;
            b       :   in  std_logic;
            cin     :   in  std_logic;
            sum     :   out std_logic;
            cout    :   out std_logic
        );
    end component;

    -- intstantiate MUX31 module
    component MUX31
        port
        (
            Input1  :   in  std_logic;
            Input2  :   in  std_logic;
            Input3  :   in  std_logic;
            S       :   in  std_logic_vector(1 downto 0);
            Sout    :   out std_logic
        );
    end component;

    -- intstantiate and_gate module
    component and_gate
        port
        (
            In1     :   in  std_logic;
            In2     :   in  std_logic;
            Sout    :   out std_logic
        );
    end component;

    -- intstantiate or_gate module
    component or_gate
    port
    (
        In1     :   in  std_logic;
        In2     :   in  std_logic;
        Sout    :   out std_logic
    );
    end component;

    -- signal definitions
    signal Sout_full_adder: std_logic;
    signal Sout_and_gate  : std_logic;
    signal Sout_or_gate   : std_logic;
    signal Xor_out        : std_logic;
    signal Cin_muxed      : std_logic;

begin

    -- assign statements
    -- flips B if S(0) is 1
    Xor_out <= B xor S(0);
    -- If S(0) is set (subtract mode), then a 1 should always go into the
    --   Cin port on the full adder (two's compliment is flip all bits
    --   then add 1). If S(0) is cleared, then simply pass Cin into
    --   the Cin port in full_adder.
    --with S(0) select Cin_muxed <= '1' when '1', Cin when '0', 'Z' when others;

    fulladderblock: full_adder
    port map
    (
        a => A,
        b => Xor_out,
        cin => Cin,
        sum => Sout_full_adder,
        cout => Cout
    );

    andgateblock: and_gate
    port map
    (
        In1 => A,
        In2 => B,
        Sout => Sout_and_gate
    );

    orgateblock: or_gate
    port map
    (
        In1 => A,
        In2 => B,
        Sout => Sout_or_gate
    );

    muxblock: MUX31
    port map
    (
        Input1 => Sout_full_adder,
        Input2 => Sout_and_gate,
        Input3 => Sout_or_gate,
        S => S,
        Sout => Sout
    );

end;
