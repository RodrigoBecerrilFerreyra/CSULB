library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- declaration of module (entity)
-- (this is where you put the name of the module and any local variables)
entity or_word is
    generic
    (
        -- this allows you to change the word size easily
        WIDTH : natural :=4
    );

    -- definition of input and output ports
    port
    (
        a : in std_logic_vector(0 to WIDTH-1); -- [0:3]
        b : in std_logic_vector(0 to WIDTH-1); -- [0:3]
        q : out std_logic_vector(0 to WIDTH-1) -- [0:3]
    );

end entity or_word;

-- module definition
-- (this is where you put what this actually does)
architecture beh of or_word is
begin

    or_bits: process(a, b) -- define a new process called or_bits
    begin -- process is equivalent to always in Verilog
        -- ORs all bits in q signal one by one
        for i in q'range loop
            q(i) <= a(i) or b(i);
        end loop;
    end process or_bits;

end architecture beh;
