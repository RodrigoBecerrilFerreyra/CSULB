library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


entity CPU_2214 is
	port(
		clk	: in std_logic;
		clear : in std_logic;
		mem_dump : in std_logic := '0';
		instruction : in std_logic_vector(15 downto 0)
 	);
end CPU_2214;

architecture Behavioral of CPU_2214 is
	COMPONENT ALU_16Bit
		port(
			A			:	in		std_logic_vector(15 downto 0);
			B			:	in		std_logic_vector(15 downto 0);
			S			:	in		std_logic_vector(1 downto 0);
			Sout		:	out 	std_logic_vector(15 downto 0);
			Cout		:	out	std_logic
		);
	END COMPONENT;

	COMPONENT Registers
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
	END COMPONENT;

  -- TODO 1: Implement the control component

  -- TODO 2: Implement the signextend component


	component mux3_1
   generic (WIDTH : positive:=16);
	port(
		Input1		:	in		std_logic_vector(WIDTH-1 	downto 0);
		Input2		:	in		std_logic_vector(WIDTH-1 	downto 0);
		Input3		:	in		std_logic_vector(WIDTH-1 	downto 0);
		S				:	in		std_logic_vector(1 			downto 0);
		Sout			:	out	std_logic_vector(WIDTH-1 	downto 0));
	end component;

	component mux2_1
   generic (WIDTH : positive:=16);
	port(
		Input1		:	in		std_logic_vector(WIDTH-1 	downto 0);
		Input2		:	in		std_logic_vector(WIDTH-1 	downto 0);
		S				:	in		std_logic;
		Sout			:	out	std_logic_vector(WIDTH-1 	downto 0));
	end component;

	-- Signals
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
	-- Instruction Fetch
	--------------------------------------------------------------------------
	op		<=	instruction(15 downto 12);
	rd		<= instruction(11 downto  8);
	rs		<= instruction(7  downto  4);
	rt		<= instruction(3  downto  0);
	--------------------------------------------------------------------------
	-- Instruction Decode
	--------------------------------------------------------------------------
	-- TODO 3: Implement the complete port map for the control

	-- TODO 4: Finish the port map for the register file
	CPU_Registers_0:		Registers port map(
		clk			=>		clk,
		clear			=>		clear,
		a_addr		=>		rd,
		a_data		=>		,
		load			=>		,
		b_addr		=>		rs,
		c_addr		=>		,
		b_data		=>		rs_data,
		c_data		=>		rt_data
	);

-- TODO 5: Implement the complete port map for the signextend


CPU_reg_dest_mux:		mux2_1 generic map(4) port map(
	Input1		=>		rt,
	Input2		=>		rd,
	S				=>		ctrl_reg_dest,
	Sout			=>		reg_dest_mux_out
);

	--------------------------------------------------------------------------
	-- Execute
	--------------------------------------------------------------------------
	CPU_alu_src_mux:		mux2_1 generic map(16) port map(
		Input1		=>		rt_data,
		Input2		=>		sign_ex_out,
		S				=>		ctrl_alu_src,
		Sout			=>		alu_src_mux_out
	);

	CPU_ALU_0:				ALU_16Bit port map(
		A				=>		rs_data,
		B				=>		alu_src_mux_out,
		S				=>		ctrl_alu_op,
		Sout			=>		alu_result,
		Cout			=>		cout
	);

	--------------------------------------------------------------------------
	-- Memory
	--------------------------------------------------------------------------
	-- Not in this lab

	--------------------------------------------------------------------------
	-- Write Back
	--------------------------------------------------------------------------
	-- Not in this lab

end Behavioral;
