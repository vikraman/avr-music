#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

#ifdef XTAL
#undef XTAL
#endif
#define XTAL 16000000UL
#define F_CPU XTAL

#include <util/delay.h>

volatile uint16_t freq;

int main (void) {
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);
  DDRD |= (1<<PD5) | (1<<PD6);
  DDRD &= ~(1<<PD3);

  PORTC |= (1<<PC0);
  PORTD |= (1<<PD3);

  TCCR1B |= (1<<WGM12) | (1<<CS10);
  TCCR1A |= (1<<COM1A0);

  freq = 0x000F;
  OCR1A = freq;

  char disp[13];
  lcd_init (LCD_DISP_ON);
  sprintf (disp, "OCR1A : %04X", freq);
  lcd_puts (disp);

  while (1) {
    if (!(PIND & (1<<PD3))) {
      freq += 0x000F;
      OCR1A = freq;
      sprintf (disp, "OCR1A : %04X", freq);
      lcd_clrscr ();
      lcd_puts (disp);
      _delay_ms (20);
    }
  }
}
