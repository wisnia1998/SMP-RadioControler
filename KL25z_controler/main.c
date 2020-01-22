#include "MKL25Z4.h"                    // Device header
#include "I2C.h" 
#include "UART_0.h" 
#include "leds.h"
#include "MMA8451Q.h"

int ii = 0xaffff;// delay value
volatile uint8_t DataReady = 1;
volatile uint8_t RAW_DATA[6];
uint16_t A_DATA = 0;

void main(void){
	UART_init(9600);
	print_char('U');
	I2C_init();
	print_char('F');
	ACCEL_init(); 
	print_word("\n\rInit Uart, I2C, Accel done \n\r");
	A_DATA = I2C_read(MMA_addr, WHO_AM_I);
	print_word("Who I am: \n\r");
	print_num(A_DATA);
	print_word("\n\rI2C 1st read done \n\r");
	//I2C_multiRegRead(MMA_addr, OUT_X_MSB_REG, 2, RAW_DATA);
//	print_word(RAW_DATA[0]);
	print_word("I2C 2nd read done \n\r");
	
	while(1){
<<<<<<< Updated upstream
		print_word("\r\nPrint data: \n\r");
		if(DataReady){
			DataReady = 0;
			print_word("\r\nwait data");
			MMA_DATA(RAW_DATA);
//			RAW_DATA[0] = I2C_read(MMA_addr, OUT_X_MSB_REG);
//			RAW_DATA[1] = I2C_read(MMA_addr, OUT_X_LSB_REG);
//			RAW_DATA[2] = I2C_read(MMA_addr, OUT_Y_MSB_REG);
//			RAW_DATA[3] = I2C_read(MMA_addr, OUT_Y_LSB_REG);
//			RAW_DATA[4] = I2C_read(MMA_addr, OUT_Z_MSB_REG);
//			RAW_DATA[5] = I2C_read(MMA_addr, OUT_Z_LSB_REG);
			print_word("\r\nready data");
			
			A_DATA = (uint16_t)(RAW_DATA[0]<<8) | (uint16_t)(RAW_DATA[1]>>2);
			print_word("X-axis: ");
			print_num(A_DATA);
			print_char('\n');
			A_DATA = (uint16_t)(RAW_DATA[2]<<8) | (uint16_t)(RAW_DATA[3]>>2);
			print_word("\rY-axis: ");
			print_num(A_DATA);
			print_char('\n');
			A_DATA = (uint16_t)(RAW_DATA[4]<<8) | (uint16_t)(RAW_DATA[5]>>2);
			print_word("\rZ-axis: ");
			print_num(A_DATA);
			print_char('\n');
		}
		print_word("\rpentla while\n");
=======
		if(GetData){
			GetData = 0;
			prepare_data();
			prepare_data_frame();
			print_word("L-motor power: ");
			print_num(get_L_motor_power());
			print_word("	");
			print_word("R-motor power: ");
			print_num(get_R_motor_power());
			print_word("	");
/*			print_word("X: ");
			print_num(X_axis());
			print_word("	");
			print_word("Y: ");
			print_num(Y_axis());
			print_word("\r");	*/
			for(ii=0;ii<24;ii++){
				A_DATA=get_byte_value(ii);
				print_num(A_DATA);
				if((ii+1)%8==0){print_word("	");}
			}
			print_word("\r");
		}
			ii = 0xdffff;
>>>>>>> Stashed changes
		while(ii){
			--ii;
		}
		print_word("\rData ready");
		DataReady = 1;
		ii = 0xbffff;
		
	}
	
};


void PORTA_IRQHandler()
{
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag 
	print_word("\rInterroupt");
	DataReady = 1;	
}

