#include <stdio.h>
#include <system.h>
#include <io.h>

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
/*  --------------------------------------------------------------------------------------------- */

int digit_to_hex(int value);

int main()
{
  int rooms[5] = {0, 0, 0, 0, 0};
  int sliders = 0;
  int leds = 0;
  int flag = 0;
  int error_flag = 0;
  int pb = 0;
  int dir = 0;
  do {
      // kirunek
      pb = IORD(PUSHBUTTON_BASE, 0);
      pb = DIR_PB & pb;
      if(!pb) {
          if(dir == 1)
              dir = 0;
          else
              dir = 1;
      }

    // przejscie
    sliders = IORD(SW_SLIDERS_BASE, 0);
    switch(sliders) {
    	  case CD1: {
    		if(flag == 1) {
				if(dir == 0) {
					rooms[S5]++;
					error_flag = 0;
				}
				else {
					if(rooms[S5] > 0) {
						rooms[S5]--;
						error_flag = 0;
					}
					else
						error_flag = 1;
				}
				flag = 0;
    		}
    		break;
    	  }
    	  case CD2: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  rooms[S1]++;
					  error_flag = 0;
				  }
				  else {
					  if(rooms[S1] > 0) {
						  rooms[S1]--;
						  error_flag = 0;
					  }
					  else
						  error_flag = 1;
				  }
				  flag = 0;
    		  }
			  break;
    	  }
    	  case CD3: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  rooms[S3]++;
					  error_flag = 0;
				  }
				  else {
					  if(rooms[S3] > 0) {
						  rooms[S3]--;
						  error_flag = 0;
					  }
					  else
						  error_flag = 1;
				  }
      	      flag = 0;
    		  }
  	      break;
    	  }
    	  case CD4: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  if(rooms[S3] > 0) {
						  rooms[S1]++;
						  rooms[S3]--;
						  error_flag = 0;
					  }
					  else
						  error_flag = 1;
				  }
				  else {
					  if(rooms[S1] > 0) {
						  rooms[S1]--;
						  rooms[S3]++;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  flag = 0;
    		  }
    		  break;
    	  }
    	  case CD5: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  if(rooms[S1] > 0) {
						  rooms[S1]--;
						  rooms[S5]++;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  else {
					  if(rooms[S5] > 0) {
						  rooms[S1]++;
						  rooms[S5]--;
						  error_flag = 0;
					  } else
						  error_flag = 1;
				  }
				  flag = 0;
    		  }
    		  break;
    	  }
    	  case CD6: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  if(rooms[S5] > 0 ) {
						  rooms[S5]--;
						  rooms[S4]++;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  else {
					  if(rooms[S4] > 0) {
						  rooms[S5]++;
						  rooms[S4]--;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  flag = 0;
    		  }
    		  break;
    	  }
    	  case CD7: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  if(rooms[S4] > 0) {
						  rooms[S4]--;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  else {
					  rooms[S4]++;
					  error_flag = 0;
				  }
				  flag = 0;
    		  }
    		  break;
    	  }
    	  case CD8: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  if(rooms[S2] > 0) {
						  rooms[S2]--;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  else {
					  rooms[S2]++;
					  error_flag = 0;
				  }
				  flag = 0;
    		  }
    		  break;
    	  }
    	  case CD9: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  rooms[S2]++;
					  error_flag = 0;
				  }
				  else {
					  if(rooms[S2] > 0) {
						  rooms[S2]--;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  flag = 0;
    		  }
    		  break;
    	  }
    	  case CD10: {
    		  if(flag == 1) {
				  if(dir == 0) {
					  if(rooms[S2] > 0) {
						  rooms[S4]++;
						  rooms[S2]--;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  else {
					  if(rooms[S4] > 0) {
						  rooms[S4]--;
						  rooms[S2]++;
						  error_flag = 0;
					  }else
						  error_flag = 1;
				  }
				  flag = 0;
    		  }
			  break;
    	  }
    	  default:
    		  flag = 1;
    }


      // leds & hex
      if(rooms[S1] > 0)
		  leds |= LED_S1;
	  else
		  leds &= ~(LED_S1);

      if(rooms[S2] > 0)
    	  leds |= LED_S2;
      else
    	  leds &= ~(LED_S2);

      if(rooms[S3] > 0)
    	  leds |= LED_S3;
      else
    	  leds &= ~(LED_S3);

      if(rooms[S4] > 0)
    	  leds |= LED_S4;
      else
    	  leds &= ~(LED_S4);

      if(rooms[S5] > 0)
    	  leds |= LED_S5;
      else
    	  leds &= ~(LED_S5);


      if(dir == 1)
    	  leds |= DIR_LED;
      else
    	  leds &= ~(DIR_LED);

      if(error_flag)
    	  leds |= ERROR_LED;
      else
    	  leds &= ~(ERROR_LED);


	IOWR(LEDS_BASE, 0, leds);
	IOWR(HEX_BASE, 0, digit_to_hex(rooms[S1]));
	IOWR(HEX_BASE, 1, digit_to_hex(rooms[S2]));
	IOWR(HEX_BASE, 2, digit_to_hex(rooms[S3]));
	IOWR(HEX_BASE, 3, digit_to_hex(rooms[S4]));
	IOWR(HEX_BASE, 4, digit_to_hex(rooms[S5]));

    /*printf("S1 = %d, S2 = %d, S3 = %d, S4 = %d, S5 = %d",
        	rooms[S1], rooms[S2], rooms[S3], rooms[S4], rooms[S5]); */

  }while(1);

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
            return SEGG;
    }
}