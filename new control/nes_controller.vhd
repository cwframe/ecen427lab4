----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:12:08 11/21/2015 
-- Design Name: 
-- Module Name:    nes_controller - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_arith.all;
--use ieee.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity nes_controller is
    Port ( clk : in  STD_LOGIC;
					 data : in STD_LOGIC;
					 reset : in STD_LOGIC;
           interrupt : out  STD_LOGIC;
					 latch : out STD_LOGIC;
					 pulse : out STD_LOGIC);
end nes_controller;

architecture Behavioral of nes_controller is

signal interrupt_wire : std_logic := '0';
signal latch_start : std_logic := '0';
signal latch_wire : std_logic := '0';
signal pulse_wire : std_logic := '0';
signal data_reg : std_logic_vector(7 downto 0) := (others =>'0');
signal counter : integer := 0;
signal latch_counter : integer := 0;
signal latch_counter_next : integer := 0;
signal pulse_counter : integer := 0;
signal pulse_counter_next : integer := 0;
signal pulse_num : integer := 0;
signal pulse_num_next : integer := 0;
constant COUNTER_MAX : integer := 1666667;
constant LATCH_COUNTER_MAX : integer := 1200;
constant PULSE_COUNTER_MAX : integer:= 600;
constant PULSE_NUM_MAX : integer:= 8;
signal slv_reg0 : std_logic_vector(7 downto 0);
type state_type is (IDLE, LATCH_S, PULSE_HIGH, PULSE_LOW);
signal state_reg, state_reg_next : state_type;



begin

counter_proc : process(clk, interrupt_wire)
begin
	if(reset = '1') then
		counter <= 0;
	elsif(clk 'event and clk = '1') then
		if(counter = COUNTER_MAX) then
			counter <= 0;
		else
			counter <= counter + 1;
		end if;
	end if;

end process;

latch_start <= '1' when counter = COUNTER_MAX else '0';



--State Machine

--state register
process (clk, reset)
begin
	if(reset = '1') then
		state_reg <= IDLE;
	elsif(clk'event and clk = '1') then
		state_reg <= state_reg_next;
	end if;
end process;

--next state logic
process (clk)
begin
	if(clk'event and clk = '1') then
		case state_reg is
			when IDLE =>
				if(latch_start = '1') then
					state_reg_next <= LATCH_S;
				end if;
			when LATCH_S =>
				if(latch_counter = LATCH_COUNTER_MAX) then
					state_reg_next <= PULSE_LOW;
				end if;
			when PULSE_HIGH =>
				if(pulse_counter = PULSE_COUNTER_MAX) then
					if(PULSE_NUM = PULSE_NUM_MAX) then
							state_reg_next <= IDLE;
							pulse_num <= pulse_num_next;
					else
						state_reg_next <= PULSE_LOW;
						data_reg(pulse_num) <= data;
					end if;
				end if;
			when PULSE_LOW =>
				if(pulse_counter = PULSE_COUNTER_MAX) then
						state_reg_next <= PULSE_HIGH;
						pulse_num <= pulse_num_next;
				end if;
		end case;
	end if;
end process;


--moore action
process(clk)
begin
	if(clk'event and clk = '1') then
		case state_reg is
			when IDLE =>
				latch_counter <= 0;
				pulse_counter <= 0;
			when LATCH_S =>
				pulse_counter <= 0;
				latch_counter <= latch_counter_next;
			when PULSE_HIGH =>
				pulse_counter <= pulse_counter_next;
			when PULSE_LOW =>
				pulse_counter <= pulse_counter_next;
			when others =>
		end case;
	end if;
end process;

--NEXT LOGIC
latch_counter_next <= latch_counter + 1 when latch_counter < LATCH_COUNTER_MAX else 0;
pulse_counter_next <= pulse_counter + 1 when pulse_counter < PULSE_COUNTER_MAX else 0;
pulse_num_next <= pulse_num + 1 when pulse_num < PULSE_NUM_MAX else 0;

--latch wire
latch_wire <= '1' when state_reg = LATCH_S else '0';

--pulse wire
pulse_wire <= '1' when state_reg = PULSE_HIGH else '0';

interrupt_wire <= '1' when pulse_counter = PULSE_COUNTER_MAX and pulse_num = PULSE_NUM_MAX and state_reg = PULSE_HIGH else '0';

interrupt <= interrupt_wire;
latch <= latch_wire;
pulse <= pulse_wire;
slv_reg0 <= data_reg;

end Behavioral;

