#include <stdio.h>
#include <system.h>
#include <io.h>
#include <sys/alt_alarm.h>
#include "alt_types.h"
#include <sys/alt_timestamp.h>
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include <unistd.h>
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include <stddef.h>


#define  SW0 0x00000001
#define  SW1 0x00000002
#define  SW2 0x00000004
#define  SW3 0x00000008
#define  SW4 0x00000010
#define  SW5 0x00000020
#define  SW6 0x00000040
#define  SW7 0x00000080
#define  SW8 0x00000100
#define  SW9 0x00000200
#define  SW10 0x00000400

//      pushbuttons
#define  KEY1 0x00000002
#define  KEY2 0x00000004
#define  KEY3 0x00000008
#define  KEY4 0x00000010

//      leds
#define  LED0 0x00000001
#define  LED1 0x00000002
#define  LED2 0x00000004
#define  LED3 0x00000008
#define  LED4 0x00000010
#define  LED5 0x00000020
#define  LED6 0x00000040
#define  LED7 0x00000080
#define  LED8 0x00000100
#define  LED9 0x00000200
#define  LED10 0x00000400

//      hex
#define  SEGA 0x00001
#define  SEGB 0x00002
#define  SEGC 0x00004
#define  SEGD 0x00008
#define  SEGE 0x00010
#define  SEGF 0x00020
#define  SEGG 0x00040

//     hex - numbers
#define ZERO SEGA | SEGB | SEGC | SEGD |SEGE | SEGF
#define ONE  SEGB | SEGC
#define TWO  SEGA | SEGB | SEGG | SEGE | SEGD
#define THREE SEGA | SEGB | SEGC | SEGD | SEGG
#define FOUR SEGC | SEGG | SEGF
#define FIVE SEGA | SEGC | SEGD | SEGF  | SEGG
#define SIX SEGA | SEGC | SEGD | SEGE | SEGF | SEGG
#define SEVEN SEGA | SEGB | SEGC
#define EIGHT SEGA | SEGB | SEGC | SEGD |SEGE | SEGF | SEGG
#define NINE SEGA | SEGB | SEGC | SEGD | SEGF | SEGG

/*  --------------------------------------------------------------------------------------------- */
#define HEX_SIZE 8
#define DIR_LED LED8
#define DIR_PB KEY1
#define ERROR_LED LED9
#define ERROR_RESET KEY2
#define E_HEX SEGA | SEGD |SEGE | SEGF | SEGG
#define R_HEX SEGE | SEGG

#define S1 0
#define S2 1
#define S3 2
#define S4 3
#define S5 4

#define LED_S1 LED0
#define LED_S2 LED1
#define LED_S3 LED2
#define LED_S4 LED3
#define LED_S5 LED4

#define CD1 SW0
#define CD2 SW1
#define CD3 SW2
#define CD4 SW3
#define CD5 SW4
#define CD6 SW5
#define CD7 SW6
#define CD8 SW7
#define CD9 SW8
#define CD10 SW9

#define CALLBACK_TIME 3
/*  --------------------------------------------------------------------------------------------- */

int digit_to_hex(int value);


int leds = 0;

alt_u32 my_alarm_callback (void* context)
{

  /* This function is called once per second */
  /*return alt_ticks_per_second(); */
	leds |= LED0;
	return 0;
}



int main()
{
	static alt_alarm alarm;
	int sw = 0;
	int flag = 0;

  while(1) {
	  sw = IORD(SW_SLIDERS_BASE, 0);
	  if(sw & SW0) {
		  if(flag == 0) {
			  if (alt_alarm_start(&alarm,CALLBACK_TIME * alt_ticks_per_second(), my_alarm_callback, NULL) < 0)
				  printf ("No system clock available\n");
		  }
		  flag = 1;
	  }
	  else {
		  if(flag == 1)
			  alt_alarm_stop(&alarm);
		  flag = 0;
		  leds &= LED0;
	  }
	  IOWR(LEDS_BASE, 0, leds);
  }

  return 0;
}

int digit_to_hex(int value){
    switch(value) {
        case 0:
            return ZERO;
            break;
        case 1:
            return ONE;
            break;
        case 2:
            return TWO;
            break;
        case 3:
            return THREE;
            break;
        case 4:
            return FOUR;
            break;
        case 5:
            return FIVE;
            break;
        case 6:
            return SIX;
            break;
        case 7:
            return SEVEN;
            break;
        case 8:
            return EIGHT;
            break;
        case 9:
            return NINE;
            break;
        default:
            return NINE;
    }
}
