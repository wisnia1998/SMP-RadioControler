#define PWM_RANGE 255

#define LEFT_IN1_PIN 6
#define LEFT_IN2_PIN 7
#define LEFT_SPEED_PIN 10
#define RIGHT_IN1_PIN A1
#define RIGHT_IN2_PIN A2
#define RIGHT_SPEED_PIN 9

#define LEFT_ENGINE_OFFSET 184
#define RIGHT_ENGINE_OFFSET 201

#define INTERRUPT_PIN 2

int received_bit = 0; // VOLATILE ????

int instr[4];

int data_frame[24];

uint8_t start_f = 0;
#define start 0b11111011
uint16_t fr = 0;
/*
 * 0 - left engine % power
 * 1 - left engine direction (0 forward, 1 backward)
 * 2 - right engine % power
 * 3 - right engine direction
 */
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
  {
    Serial.begin(9600);
    //randomSeed(analogRead(0));
    engine_init(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN);
    engine_init(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN);

    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), irq_receiver_handler, RISING ); // CHANGE ?????
    
    setup_timer();
  }

void loop() 
  {  
     /*decode_data();
      engine_control(LEFT_IN1_PIN, LEFT_IN2_PIN, LEFT_SPEED_PIN, LEFT_ENGINE_OFFSET, instr[0], instr[1]);
      engine_control(RIGHT_IN1_PIN, RIGHT_IN2_PIN, RIGHT_SPEED_PIN, RIGHT_ENGINE_OFFSET, instr[2], instr[3]) ;
      //delay(100);*/    
  }
////////////////////////////////////////////////////////////////////////////////////////////////////
void engine_control(int IN1, int IN2, int SPEED, int ENGINE_OFFSET, int POWER, int DIR)
  {
    if(DIR == 0)
      {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
      }
    else
      {
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, LOW); 
      }
    
    analogWrite(SPEED, ENGINE_OFFSET + (POWER * (PWM_RANGE - ENGINE_OFFSET)));
  }


void engine_init(int IN1, int IN2, int SPEED)
  {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(SPEED, OUTPUT);
  }


void irq_receiver_handler()
  {
    received_bit = 1;
  }

  
void setup_timer()
  {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 1999;//16 000 000/8=2 000 000/(1999+1)=1000
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11);  //dzielnik 8
    TIMSK1 |= (1 << OCIE1A);
  }

  int ii=0;
ISR(TIMER1_COMPA_vect)
  {
    data_frame[0] = received_bit ;
    if(start_f != start){
      shift_array();
      //Serial.println("start_f: "); 
      //Serial.println(start_f); 
    } 
    //Serial.println(received_bit);
    else if(start_f == start){//Serial.println("DDDDDDDDD");
         data_frame[ii+8] = received_bit;
         if(23==ii+8){
          ii=0;
          for(int j=0;j<16;j++){
            fr = (fr << 1) | data_frame[j+8];
          }
          Serial.println(fr, BIN);
          //Serial.println(data_frame[15]);
          //Serial.println("dach");
          start_f=0;
          }
         ii++;
      }   
    //Serial.println(start_f); 
    received_bit = 0;
  }

  
void shift_array()
  {
    start_f = (start_f << 1) | data_frame[0];
  }

void decode_data()
  {
      if(start_f == start)
          {
            instr[1] = data_frame[15];
            instr[3] = data_frame[7];
            instr[0] = bin_to_dec(14);
            instr[0] = bin_to_dec(6);
            Serial.println("DU");
          }  
//          Serial.printf("%l %l %l %l %l %l %l %l %l",data_frame[23],data_frame[22],data_frame[21],data_frame[20],data_frame[19],data_frame[18],data_frame[17],data_frame[16]); 
  }

  
int bin_to_dec(int offset)
  {
    int tmp = 0;
    int e = 7;

    for(int i = offset; i >= offset - 6; i--)
      {
        tmp += pow(2, e--);
      }
      
    return tmp;
  }
