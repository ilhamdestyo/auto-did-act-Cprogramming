// include libraries
#include <stdio.h>
#include "ssd1306.h"

#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1
float FCPU = 1;


int main(void)
{
  uint8_t addr = SSD1306_ADDRESS;

  // init ssd1306
  SSD1306_Init (addr);

  // clear screen
  SSD1306_ClearScreen ();
  // draw line
  SSD1306_DrawLine (0, MAX_X, 4, 4);
  // set position
  SSD1306_SetPosition (7, 1);
  // draw string
  SSD1306_DrawString ("SSD1306 OLED DRIVER");
  // draw line
  SSD1306_DrawLine (0, MAX_X, 18, 18);
  // set position
  SSD1306_SetPosition (40, 3);
  // draw string
  SSD1306_DrawString ("Hello Ilham");
  // set position
  SSD1306_SetPosition (53, 5);
  // draw string
  SSD1306_DrawString ("2022");
  // update
  SSD1306_UpdateScreen (addr);

  // return value
  return 0;
}
