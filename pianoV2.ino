#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Arduino.h"
#include "songs.hpp"
#include "uart.hpp"





void setup() {
	//Setup for the buttons and the buzzer
	for (int i = 0; i < 10; i++) {
		pinMode(buttonPins[i], INPUT);
		digitalWrite(buttonPins[i],HIGH);
	}

	//Setup for the Putty
	sei();
	uart_init(9600, 0);

	uart_send_string("Play the piano with letters 'q' to 'm'");
	uart_send_byte(13);
	uart_send_byte(10);
	uart_send_byte(10);
	uart_send_string("Type '1' to play the Super Mario Bros theme");
	uart_send_byte(13);
	uart_send_byte(10);
	uart_send_string("Type '2' to play the Happy Birthday song");

}

void loop() {
	uint16_t data = 0;

	for (int i = 0; i < 10; i++) {


		while (digitalRead(buttonPins[i]) == LOW) { // boucle tant que le bouton est enfoncé
			tone(12, notes_buttons[i]);
			_delay_ms(10); // ajoutez un délai de 10 ms
		}
		noTone(12); // arrêtez le son lorsque le bouton est relâché
	}


	if(uart_read_count() > 0) {
		char data = uart_read();
		if(data == 49) {
			play_SuperMarioBros();
		}
		if(data == 50) {
			play_happyBirthday();
		}


		switch (data) {
			case 'q':
				tone(12, NOTE_C5);
		        break;
		    case 's':
		        tone(12, NOTE_CS5);
		        break;
		    case 'd':
		        tone(12, NOTE_D5);
		        break;
		    case 'f':
		        tone(12, NOTE_DS5);
		        break;
		    case 'g':
		        tone(12, NOTE_E5);
		        break;
		    case 'h':
		        tone(12, NOTE_F5);
		        break;
		    case 'j':
		        tone(12, NOTE_FS5);
		        break;
		    case 'k':
		        tone(12, NOTE_G5);
		        break;
		    case 'l':
		        tone(12, NOTE_GS5);
		        break;
		    case 'm':
		        tone(12, NOTE_A5);
		        break;

		    default:
		    	noTone(12);
		    	break;

		}
		_delay_ms(50);



	}
}

















