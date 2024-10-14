#include <avr/io.h>
#include "dio.h"
#include "main.h"

void dio_init(void) {
  Set_PIN_Direction(&DDRD, PIN_Segment_A, DIO_OUTPUT);
  Set_PIN_Direction(&DDRD, PIN_Segment_B, DIO_OUTPUT);
  Set_PIN_Direction(&DDRD, PIN_Segment_C, DIO_OUTPUT);
  Set_PIN_Direction(&DDRD, PIN_Segment_D, DIO_OUTPUT);
  Set_PIN_Direction(&DDRD, PIN_Segment_E, DIO_OUTPUT);
  Set_PIN_Direction(&DDRD, PIN_Segment_F, DIO_OUTPUT);
  Set_PIN_Direction(&DDRD, PIN_Segment_G, DIO_OUTPUT);
  Set_PIN_Direction(&DDRB, PIN_Button_0, DIO_INPUT);
  Set_PIN_Direction(&DDRB, PIN_Button_1, DIO_INPUT_PULLUP);
  Set_PIN_Direction(&DDRB, PIN_Emergency_Button, DIO_INPUT_PULLUP);
  Set_PIN_Direction(&DDRB, PIN_Buzzer, DIO_OUTPUT);
  Set_PIN_Direction(&DDRB, PIN_Red_LED, DIO_OUTPUT);
}

void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t value) {
  if (value == INPUT) {
      *ddr |= (1 << pin);
  } 
  else if (value == OUTPUT) {
      *ddr &= ~(1 << pin);
  }
  else if (value == INPUT_PULLUP) {
      *ddr |= (1 << pin);
  }
}

void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t value) {
    if (value == HIGH) {
        *port |= (1 << pin);
    } 
    else if (value == LOW) {
        *port &= ~(1 << pin);
    }
}


inline void Register_ToggleBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register ^ (1 << Bit);
}

inline unsigned char Register_GetBit(volatile unsigned char* Register, unsigned char Bit){
  return (*Register >> Bit) & (unsigned char)0x01;
} 