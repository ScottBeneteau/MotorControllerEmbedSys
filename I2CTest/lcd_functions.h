#ifndef LCDFUNCT_H_
#define LCDFUNCT_H_

#define LCD_ADDR 0x27
#define EN 0x04
#define RS 0x01
#define BACKLIGHT 0x08


//Methods Implemented
void setup_lcd(void);
void print_char_4bit_mode(const char *c);
void print_string_4bit_mode(const char *c);
void write_byte_4bit_mode(uint8_t byte, bool rs);
void check_busy_flag();
void backlight_on();


//Methods not implemented yet
uint8_t get_cursor_pos();
void set_cursor_pos(uint8_t pos_addr);
void backlight_off();
void clear_screen();
void cursor_home();


#endif  /* LCDFUNCT_H_  */
