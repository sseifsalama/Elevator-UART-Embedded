#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "dio.h"

volatile char receivedCommand[BUFFER_SIZE];  // Shared buffer for received commands
volatile uint8_t commandIndex = 0;  // Index for command buffer
volatile int rx_flag = 0;  // Flag indicating a command has been received

int main(void) {
    // Initialize UART, DIO, and enable interrupts
    UART_Init(9600);
    dio_init();
    sei();

    while (1) {
        // Button Pressed using polling
        if (!(PINB & (1 << PIN_Button_0))) {  // Button 0 pressed
            UART_SendString("Button 0 Pressed\n");
            _delay_ms(300);  // Debounce delay
        }

        if (!(PINB & (1 << PIN_Button_1))) {  // Button 1 pressed
            UART_SendString("Button 1 Pressed\n");
            _delay_ms(300);  // Debounce delay
        }

        if (!(PINB & (1 << PIN_Emergency_Button))) {  // Emergency Button pressed
            UART_SendString("Emergency Button Pressed\n");
            _delay_ms(300);  // Debounce delay
        }

        // If a command has been received, process it
        if (rx_flag) {
            // Command to turn LED ON
            if (strcmp(receivedCommand, "led_on") == 0) {
                Set_PIN_State(&PORTB, PIN_Red_LED, HIGH);  // Turn on Red LED
                UART_SendString("Command: Red LED ON\n");
            }
            // Command to turn LED OFF
            else if (strcmp(receivedCommand, "led_off") == 0) {
                Set_PIN_State(&PORTB, PIN_Red_LED, LOW);   // Turn off Red LED
                UART_SendString("Command: Red LED OFF\n");
            }
            // Command to turn on 7 Segment Digit 0
            else if (strcmp(receivedCommand, "7Segment_0") == 0) {
              for (uint8_t i = PIN_Segment_A; i <= PIN_Segment_F; i++) {
                Set_PIN_State(&PORTD, i, HIGH);
              }
                UART_SendString("Command: 0 Displayed\n");
            }
            // Command to turn on 7 Segment Digit 1
            else if (strcmp(receivedCommand, "7Segment_1") == 0) {
                Set_PIN_State(&PORTD, PIN_Segment_A, LOW);
                Set_PIN_State(&PORTD, PIN_Segment_B, HIGH);
                Set_PIN_State(&PORTD, PIN_Segment_C, HIGH);
                Set_PIN_State(&PORTD, PIN_Segment_D, LOW);
                Set_PIN_State(&PORTD, PIN_Segment_E, LOW);
                Set_PIN_State(&PORTD, PIN_Segment_F, LOW);
                UART_SendString("Command: 1 Displayed\n");
            }
            else {
                UART_SendString("Not a valid command\n");
            }
            // Clear the buffer and reset the flag after processing
            receivedCommand[0] = '\0';
            commandIndex = 0;
            rx_flag = 0;  // Ready for the next command
        }
    }
    return 0;
}