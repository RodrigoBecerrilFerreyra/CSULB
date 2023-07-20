--------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 11/30/2021 04:47:56 PM
-- Module Name: control - Behavioral
-- Project Name: Lab 6
-- Description: Combinational control unit for CPU 
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity control is
	port(
		op			:	in	std_logic_vector(3 downto 0);
		-- alu_op goes to the ALU
		alu_op		:	out	std_logic_vector(1 downto 0);
		-- alu_src selects either a register or the signextend
		alu_src		:	out	std_logic;
		reg_dest	:	out	std_logic;
		reg_load	:	out	std_logic;
		reg_src		:	out	std_logic_vector(1 downto 0);
		mem_read	:	out	std_logic;
		mem_write	:	out	std_logic
		);
end control;

architecture syn of control is

begin
	process (op) is
	begin
		case op is

			-- op=0, add
			when x"0" =>
				alu_op		<=	"00";
				alu_src		<=	'0';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"01";
				mem_read		<=	'0';
				mem_write	<=	'0';

				-- todo 1: implement the subtraction
			-- op=1, sub
			when x"1" =>
				alu_op		<=	"01";
				alu_src		<=	'0';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"01";
				mem_read		<=	'0';
				mem_write	<=	'0';

				-- todo 2: implement the and
			-- op=2, and
			when x"2" =>
				alu_op		<=	"10";
				alu_src		<=	'0';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"01";
				mem_read		<=	'0';
				mem_write	<=	'0';

				-- todo 3: implement the or
			-- op=3, or
			when x"3" =>
				alu_op		<=	"11";
				alu_src		<=	'0';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"01";
				mem_read		<=	'0';
				mem_write	<=	'0';

		  	-- todo 4: implement the addition immeadiate
			-- op=4, addi
			when x"4" =>
				alu_op		<=	"00";
				alu_src		<=	'1';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"11";
				mem_read		<=	'0';
				mem_write	<=	'0';

				-- todo 5: implement the subtraction immeadiate
			-- op=5, subi
			when x"5" =>
				alu_op		<=	"01";
				alu_src		<=	'1';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"11";
				mem_read		<=	'0';
				mem_write	<=	'0';

			-- op=8, lw
			when x"8" =>
				alu_op		<=	"00";
				alu_src		<=	'1';
				reg_dest		<=	'0';
				reg_load		<=	'1';
				reg_src		<=	"00";
				mem_read		<=	'1';
				mem_write	<=	'0';

				-- todo 6: implement the store word
			-- op=c, sw
			when x"c" =>
				alu_op		<=	"00";
				alu_src		<=	'1';
				reg_dest		<=	'1';
				reg_load		<=	'0';
				reg_src		<=	"00";
				mem_read		<=	'0';
				mem_write	<=	'1';

			-- op=7, slt
			when x"7" =>
				alu_op		<= "01";
				alu_src		<= '0';
				reg_dest		<= '0';
				reg_load		<= '1';
				reg_src		<= "10";
				mem_read		<= '0';
				mem_write	<= '0';

			when others =>
				alu_op	<=	"00";
				alu_src	<=	'0';
				reg_dest	<=	'0';
				reg_load	<=	'0';
				reg_src	<=	"01";
				mem_read	<=	'0';
				mem_write<=	'0';

		end case;
	end process;
end syn;
