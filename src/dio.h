// PORTD
#define PIN_Segment_A 0
#define PIN_Segment_B 1
#define PIN_Segment_C 2
#define PIN_Segment_D 3
#define PIN_Segment_E 4
#define PIN_Segment_F 5
#define PIN_Segment_G 6

// PORTB
#define PIN_Button_0 0
#define PIN_Button_1 1
#define PIN_Emergency_Button 2
#define PIN_Buzzer 3
#define PIN_Red_LED 4

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_INPUT_PULLUP 1

#define LOW 0
#define HIGH 1

// function declarations
void Set_PIN_Direction(volatile uint8_t* ddr, uint8_t pin, uint8_t value)
void Set_PIN_State(volatile uint8_t* port, uint8_t pin, uint8_t value)
void dio_init(void)