library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity signextend_tb is
end signextend_tb;

architecture Behavioral of signextend_tb is

    component signextend
        port
        (
            immIn: in std_logic_vector(3 downto 0);
            immout: out std_logic_vector(15 downto 0)
        );
    end component;

    signal in_tb: std_logic_vector(3 downto 0) := "0000";
    signal out_tb: std_logic_vector(15 downto 0);
    constant tick: time := 50 ns;

begin

    uut: signextend
    port map
    (
        immIn => in_tb,
        immOut => out_tb
    );

    main: process
    begin
        wait for tick;

        in_tb <= x"8";
        wait for tick;

        report "simulation finished successfully" severity FAILURE;
    end process main;

end Behavioral;
