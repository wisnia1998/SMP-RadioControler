<<<<<<< Updated upstream
#include "433MHz.h"

uint8_t get_LR_power(){
	return LR_power;
}

uint8_t get_LR_dir(){
	return LR_dir;
}

void set_LR_power(uint16_t power){
	if(power > 8000){
		set_LR_dir(L_motor);
		LR_power = (float)(16384 - power)/1024*50;
	}
	else{
		set_LR_dir(R_motor);
		LR_power = (float)power/1024*50;
	}
}

void set_LR_dir(uint8_t dir){
	LR_dir = dir;
}

uint8_t get_FR_power(){
	return FR_power;
}

uint8_t get_FR_dir(){
	return LR_dir;
}

void set_FR_power(uint16_t power){
	if(power > 8000){
		set_FR_dir(F_motor);
		FR_power = (float)(16384 - power)/1024*100;
	}
	else{
		set_FR_dir(Rear_motor);
		FR_power = (float)power/1024*100;
	}
}

void set_FR_dir(uint8_t dir){
		FR_dir = dir;
}
void calculate_motor_power(){//uint8_t x_axis, uint8_t x_dir, uint8_t y_axis, uint8_t y_dir){	
	L_motor_power = R_motor_power = FR_power;
	if(LR_dir == L_motor){
		L_motor_power -= LR_power;
		L_motor_dir = F_motor;
		if(L_motor_power < 0){		
			L_motor_dir = Rear_motor;
			L_motor_power *=(-1);
			}
		}
	else if(LR_dir == R_motor){
		R_motor_power -= LR_power;
		R_motor_dir = 0;			
		if(R_motor_power < 0){		
			R_motor_dir = 1;
			R_motor_power *=(-1);
			}
		}
	if(FR_dir == 1){//jazda do tylu
		L_motor_dir ^= 1;
		R_motor_dir ^= 1;
	}
}

uint8_t get_L_motor_power(){
	return L_motor_power;
}
uint8_t get_R_motor_power(){
	return R_motor_power;
}

uint8_t get_L_motor_dir(){
	return L_motor_dir;
}
uint8_t get_R_motor_dir(){
	return R_motor_dir;
}

void prepare_data(){
	set_FR_power(X_axis());
	set_LR_power(Y_axis());
	calculate_motor_power();
}

void prepare_data_frame(){
	tx_buff[0] = 1;
	tx_buff[1] = 1;
	tx_buff[2] = 1;
	tx_buff[3] = 1;
	tx_buff[4] = 1;
	tx_buff[5] = 0;
	tx_buff[6] = 1;
	tx_buff[7] = 1;		//start frame
	tx_buff[8] = get_L_motor_dir();		//L_dir bit

	tx_buff[16] = get_R_motor_dir();	//R_dir bit
	
	power2bin(get_L_motor_power(), get_R_motor_power());
}

void power2bin(uint8_t L_power, uint8_t R_power){
	tx_buff[15] =  L_power %2;		///////////	
	tx_buff[14] = (L_power >> 1)%2;
	tx_buff[13] = (L_power >> 2)%2;
	tx_buff[12] = (L_power >> 3)%2;	//data
	tx_buff[11] = (L_power >> 4)%2;
	tx_buff[10] = (L_power >> 5)%2;
	tx_buff[9] 	= (L_power >> 6)%2;	/////////
	tx_buff[23] =  R_power %2;		/////////
	tx_buff[22] = (R_power >> 1)%2;
	tx_buff[22] = (R_power >> 2)%2;
	tx_buff[20] = (R_power >> 3)%2;	//data
	tx_buff[19] = (R_power >> 4)%2;
	tx_buff[18] = (R_power >> 5)%2;
	tx_buff[17] = (R_power >> 6)%2;	/////////
	
}

uint8_t get_byte_value(uint8_t byte_num){
	return tx_buff[byte_num];
}


=======
#include "433MHz.h"

uint8_t get_LR_power(){
	return LR_power;
}

uint8_t get_LR_dir(){
	return LR_dir;
}

void set_LR_power(uint16_t power){
	if(power > 8000){
		set_LR_dir(L_motor);
		LR_power = (float)(16384 - power)/1024*50;
	}
	else{
		set_LR_dir(R_motor);
		LR_power = (float)power/1024*50;
	}
}

void set_LR_dir(uint8_t dir){
	LR_dir = dir;
}

uint8_t get_FR_power(){
	return FR_power;
}

uint8_t get_FR_dir(){
	return LR_dir;
}

void set_FR_power(uint16_t power){
	if(power > 8000){
		set_FR_dir(F_motor);
		FR_power = (float)(16384 - power)/1024*100;
	}
	else{
		set_FR_dir(Rear_motor);
		FR_power = (float)power/1024*100;
	}
}

void set_FR_dir(uint8_t dir){
		FR_dir = dir;
}
void calculate_motor_power(){//uint8_t x_axis, uint8_t x_dir, uint8_t y_axis, uint8_t y_dir){	
	L_motor_power = R_motor_power = FR_power;
	if(LR_dir == L_motor){
		L_motor_power -= LR_power;
		L_motor_dir = F_motor;
		if(L_motor_power < 0){		
			L_motor_dir = Rear_motor;
			L_motor_power *=(-1);
			}
		}
	else if(LR_dir == 1){
		R_motor_power -= LR_power;
		R_motor_dir = 0;			
		if(R_motor_power < 0){		
			R_motor_dir = 1;
			R_motor_power *=(-1);
			}
		}
	if(FR_dir == 1){//jazda do przodu
		L_motor_dir ^= 1;
		R_motor_dir ^= 1;
	}
}

uint8_t get_L_motor_power(){
	return L_motor_power;
}
uint8_t get_R_motor_power(){
	return R_motor_power;
}

uint8_t get_L_motor_dir(){
	return L_motor_dir;
}
uint8_t get_R_motor_dir(){
	return R_motor_dir;
}

void prepare_data(){
	set_FR_power(X_axis());
	set_LR_power(Y_axis());
	calculate_motor_power();
}

void prepare_data_frame(){
	tx_buff[0] = 1;
	tx_buff[1] = 1;
	tx_buff[2] = 0;
	tx_buff[3] = 0;
	tx_buff[4] = 1;
	tx_buff[5] = 1;
	tx_buff[6] = 1;
	tx_buff[7] = 0;
	tx_buff[8] = 0;
	tx_buff[9] = 1;
	tx_buff[10] = 1;
	tx_buff[11] = 0;
	tx_buff[12] = 0;
	tx_buff[13] = 1;
	tx_buff[14] = 0;
	tx_buff[15] = 1;
	tx_buff[16] = 0;
	tx_buff[17] = 1;
	tx_buff[18] = 0;
	tx_buff[19] = 1;
	tx_buff[20] = 0;
	tx_buff[21] = 1;
	tx_buff[22] = 0;
	tx_buff[23] = 1;
	
	/*tx_buff[0] = 1;
	tx_buff[1] = 1;
	tx_buff[2] = 1;
	tx_buff[3] = 1;
	tx_buff[4] = 1;
	tx_buff[5] = 0;
	tx_buff[6] = 1;
	tx_buff[7] = 1;		//start frame
	tx_buff[8] = get_L_motor_dir();		//L_dir bit

	tx_buff[16] = get_R_motor_dir();	//R_dir bit
	
	power2bin(get_L_motor_power(), get_R_motor_power());*/
}

void power2bin(uint8_t L_power, uint8_t R_power){
	tx_buff[15] 	=  L_power %2;		///////////	
	tx_buff[14] = (L_power >> 1)%2;
	tx_buff[13] = (L_power >> 2)%2;
	tx_buff[12] = (L_power >> 3)%2;	//data
	tx_buff[11] = (L_power >> 4)%2;
	tx_buff[10] = (L_power >> 5)%2;
	tx_buff[9] = (L_power >> 6)%2;	/////////
	tx_buff[23] =  R_power %2;	/////////
	tx_buff[22] = (R_power >> 1)%2;
	tx_buff[21] = (R_power >> 2)%2;
	tx_buff[20] = (R_power >> 3)%2;	//data
	tx_buff[19] = (R_power >> 4)%2;
	tx_buff[18] = (R_power >> 5)%2;
	tx_buff[17] = (R_power >> 6)%2;	/////////
}

uint8_t get_byte_value(uint8_t byte_num){
	return tx_buff[byte_num];
}

>>>>>>> Stashed changes
