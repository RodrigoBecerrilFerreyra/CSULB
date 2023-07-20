library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

-- define file as testbench 
entity testbench is
end testbench;

-- define module
architecture beh of testbench is
    signal a : std_logic_vector(0 to 3) := "0000";
    signal b : std_logic_vector(0 to 3) := "0000";
    signal q : std_logic_vector(0 to 3);
    constant tick : time := 1 us;
begin
    wide_or : entity work.or_word -- not sure what wide_or is
    -- get values from work.or_word
    port map (
        a => a,
        b => b,
        q => q
    );

    -- process that assigns increasing numbers to a
    drive_a : process
    begin
        wait for tick;
        a <= a + "0001";
    end process drive_a;

    -- process that assigns increasing numbers to b
    drive_b : process
    begin
        wait for (tick*4);
        b <= b + "0001";
    end process drive_b;
end architecture beh;
