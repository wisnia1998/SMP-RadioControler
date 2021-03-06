#include "MKL25Z4.h"                    // Device header
#include "433MHz.h"

#define transmit_pin 0 //PORTB 3
#define transmit 1
#define return_zero 2
static uint8_t current_byte = 0;	//range 0:23
static uint8_t GetData = 1;		//get data flag

void transmit_0();
void transmit_1();
void return_to_zero();
void transmision_init();
void start_transmision();
void transmit_byte();
uint8_t get_GetData();
void clear_GetData();