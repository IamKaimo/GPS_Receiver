#ifndef LCD_H
#define LCD_H
void lcd_init (void);
void display_data (char* data);
void lcd_send_cmd(char cmd);
void lcd_set_cursor(char row, char col);
#endif
