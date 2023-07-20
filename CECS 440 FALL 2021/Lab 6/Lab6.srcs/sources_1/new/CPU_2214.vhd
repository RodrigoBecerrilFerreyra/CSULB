--------------------------------------------------------------------------------
-- Company: California State University, Long Beach
-- Engineer: Rodrigo Becerril Ferreyra
-- 
-- Create Date: 11/30/2021 06:39:35 PM
-- Module Name: CPU_2214 - Behavioral
-- Project Name: Lab 6
--------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity cpu_2214 is
	port(
		clk	: in std_logic;
		clear : in std_logic;
		mem_dump : in std_logic := '0';
		instruction : in std_logic_vector(15 downto 0)
 	);
end cpu_2214;

architecture behavioral of cpu_2214 is
	component ALU16bit
		port(
			a			:	in		std_logic_vector(15 downto 0);
			b			:	in		std_logic_vector(15 downto 0);
			s			:	in		std_logic_vector(1 downto 0);
			sout		:	out 	std_logic_vector(15 downto 0);
			cout		:	out	std_logic
		);
	end component;

	component RegisterFile
		port(
			clk			:	in	 std_logic;
			clear			:	in  std_logic;

			a_addr		:	in	 std_logic_vector( 3 downto 0);
			a_data		:	in	 std_logic_vector(15 downto 0);
			load			:	in	 std_logic;

			b_addr		:	in	 std_logic_vector( 3 downto 0);
			c_addr		:	in	 std_logic_vector( 3 downto 0);

			b_data		:	out std_logic_vector(15 downto 0);
			c_data		:	out std_logic_vector(15 downto 0)
		);
	end component;

  -- todo 1: implement the control component
  component control
    port
    (
      op			:	in	std_logic_vector(3 downto 0);
      -- alu_op goes to the ALU
      alu_op        :    out    std_logic_vector(1 downto 0);
      -- alu_src selects either a register or the signextend
      alu_src        :    out    std_logic;
      reg_dest    :    out    std_logic;
      reg_load    :    out    std_logic;
      reg_src        :    out    std_logic_vector(1 downto 0);
      mem_read    :    out    std_logic;
      mem_write    :    out    std_logic
    );
    end component;

  -- todo 2: implement the signextend component
  component signextend
    port
    (
      immIn: in std_logic_vector(3 downto 0);
      immout: out std_logic_vector(15 downto 0)
    );
  end component;

	component mux3_1
   generic (width : positive:=16);
	port(
		input1		:	in		std_logic_vector(width-1 	downto 0);
		input2		:	in		std_logic_vector(width-1 	downto 0);
		input3		:	in		std_logic_vector(width-1 	downto 0);
		s				:	in		std_logic_vector(1 			downto 0);
		sout			:	out	std_logic_vector(width-1 	downto 0));
	end component;

	component mux2_1
   generic (width : positive:=16);
	port(
		input1		:	in		std_logic_vector(width-1 	downto 0);
		input2		:	in		std_logic_vector(width-1 	downto 0);
		s				:	in		std_logic;
		sout			:	out	std_logic_vector(width-1 	downto 0));
	end component;

	-- signals
	signal  op						:	std_logic_vector( 3 downto 0)	;
	signal	rd						:	std_logic_vector( 3 downto 0)	;
	signal	rs						:	std_logic_vector( 3 downto 0)	;
	signal	rt						:	std_logic_vector( 3 downto 0)	;

	signal	alu_result			:	std_logic_vector(15 downto 0)	;
	signal	cout					:	std_logic							;
	signal	alu_src_mux_out	:	std_logic_vector(15 downto 0)	;
	signal 	sign_ex_out			:	std_logic_vector(15 downto 0)	;
	signal	rs_data				:	std_logic_vector(15 downto 0)	;
	signal	rt_data				:	std_logic_vector(15 downto 0)	;
	signal	reg_dest_mux_out	:	std_logic_vector( 3 downto 0)	;
	signal	reg_src_mux_out	:	std_logic_vector(15 downto 0)	;

	signal	ctrl_alu_src		:	std_logic							;
	signal	ctrl_alu_op			:	std_logic_vector( 1 downto 0)	;
	signal	ctrl_reg_dest		:	std_logic							;
	signal	ctrl_reg_src		:	std_logic_vector( 1 downto 0)	;
	signal	ctrl_reg_load		:	std_logic							;
	signal	ctrl_mem_read		:	std_logic							;
	signal	ctrl_mem_write		:	std_logic							;

begin
	--------------------------------------------------------------------------
	-- instruction fetch
	--------------------------------------------------------------------------
	op		<=	instruction(15 downto 12);
	rd		<= instruction(11 downto  8);
	rs		<= instruction(7  downto  4);
	rt		<= instruction(3  downto  0);
	--------------------------------------------------------------------------
	-- instruction decode
	--------------------------------------------------------------------------
	-- todo 3: implement the complete port map for the control
	controlprocess: control
	port map
	(
	  op => op, -- the second op refers to the op above,
	  alu_op => ctrl_alu_op,
	  alu_src => ctrl_alu_src,
	  reg_dest => ctrl_reg_dest,
	  reg_load => ctrl_reg_load,
	  reg_src => ctrl_reg_src,
	  mem_read => ctrl_mem_read,
	  mem_write => ctrl_mem_write
	);

	-- todo 4: finish the port map for the register file
    cpu_registers_0: RegisterFile
    port map
    (
      clk => clk,
      clear => clear,
      a_addr => rd,
      a_data => alu_result,
      load => ctrl_reg_load,
      b_addr => rs,
      c_addr => reg_dest_mux_out,
      c_data => rt_data
    );

-- todo 5: implement the complete port map for the signextend
    signextendmodule: signextend
    port map
    (
      immIn => rt,
      immOut => sign_ex_out
    );

cpu_reg_dest_mux:		mux2_1 generic map(4) port map(
	input1		=>		rd,
	input2		=>		sign_ex_out,
	s				=>		ctrl_reg_dest,
	sout			=>		reg_dest_mux_out
);

	--------------------------------------------------------------------------
	-- execute
	--------------------------------------------------------------------------
	cpu_alu_src_mux:		mux2_1 generic map(16) port map(
		input1		=>		rt_data,
		input2		=>		sign_ex_out,
		s				=>		ctrl_alu_src,
		sout			=>		alu_src_mux_out
	);

	cpu_alu_0:				ALU16bit
	port map(
		a				=>		rs_data,
		b				=>		alu_src_mux_out,
		s				=>		ctrl_alu_op,
		sout			=>		alu_result,
		cout			=>		cout
	);

	--------------------------------------------------------------------------
	-- memory
	--------------------------------------------------------------------------
	-- not in this lab

	--------------------------------------------------------------------------
	-- write back
	--------------------------------------------------------------------------
	-- not in this lab

end behavioral;
