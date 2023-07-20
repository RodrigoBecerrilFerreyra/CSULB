/*
    Rio Bungalon Jr.
    Angel Espinoza
    Kenneth E
    Miguel Cabada
    Rodolfo Bustos
    Ryan Cachu
    Rodrigo Becerril Ferreyra
*/
`timescale 1ns / 1ns
module debounce(
	input wire clk, reset,
	input wire sw,
	output reg db
	);
	
	//symbolic state declaration
	localparam [2:0]
		   zero		= 3'b000,
		   wait1_1 	= 3'b001,
		   wait1_2	= 3'b010,
		   wait1_3	= 3'b011,
		   one		= 3'b100,
		   wait0_1	= 3'b101,
		   wait0_2	= 3'b110,
		   wait0_3	= 3'b111;
						  
	//number of counter bits (2^N * 10 ns = 10ms tick )
	//signal declaration
	
	localparam N = 20;
	reg [N-1:0] q_reg;
	wire [N-1:0] q_next;
	
	
	wire m_tick;
	reg [2:0] state_reg, state_next;

	//body
	
	//===================================================================
	// Counter to generate 10 ms tick
	//===================================================================

	always @(posedge clk, posedge reset)
		if (reset)
			q_reg <= 20'b0;
		else 
			q_reg <= q_next;

	// next-state logic
		assign q_next = (m_tick) ? 1'b0 : q_reg + 1;
	// output tick
		assign m_tick = (q_reg== 20'd999_999 ) ? 1'b1 : 1'b0;

	//===================================================================
	// debouuncing FSM
	//===================================================================
	// state register
	always @(posedge clk, posedge reset)
		if (reset)
			state_reg <= zero;
		else 
			state_reg <= state_next;
			
	// next-state logic
	always @*
	begin
		state_next = state_reg; //default state : the same
		//db = 1'b0;
		case(state_reg)
			zero:
				state_next = sw ? wait1_1 : zero;
			wait1_1:
				case({sw, m_tick})
				    2'b11: state_next = wait1_2;
				    2'b10: state_next = wait1_1;
				    2'b00: state_next = zero;
				    2'b01: state_next = zero;
				endcase
			wait1_2:
			    case({sw, m_tick})
                    2'b11: state_next = wait1_3;
                    2'b10: state_next = wait1_2;
                    2'b00: state_next = zero;
                    2'b01: state_next = zero;
                endcase
			wait1_3:
				case({sw, m_tick})
                    2'b11: state_next = one;
                    2'b10: state_next = wait1_3;
                    2'b00: state_next = zero;
                    2'b01: state_next = zero;
                endcase
			one:
			    state_next = sw ? one : wait0_1;
			wait0_1:
				case({sw, m_tick})
                    2'b10: state_next = one;
                    2'b11: state_next = one;
                    2'b01: state_next = wait0_2;
                    2'b00: state_next = wait0_1;
                endcase
			wait0_2:
				case({sw, m_tick})
                    2'b10: state_next = one;
                    2'b11: state_next = one;
                    2'b01: state_next = wait0_3;
                    2'b00: state_next = wait0_2;
                endcase
			wait0_3:
				case({sw, m_tick})
                    2'b10: state_next = one;
                    2'b11: state_next = one;
                    2'b01: state_next = zero;
                    2'b00: state_next = wait0_3;
                endcase
				
				default: state_next = zero;
			endcase
		end
		
		// output logic
		always @(*)
		  case(state_reg)
		      zero:    db = 0;
		      wait1_1: db = 0;
		      wait1_2: db = 0;
		      wait1_3: db = 0;
		      one:     db = 1;
		      wait0_1: db = 1;
		      wait0_2: db = 1;
		      wait0_3: db = 1;
		      default: db = 0;
		  endcase
	
endmodule
