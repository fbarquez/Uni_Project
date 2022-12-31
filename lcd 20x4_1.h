/************************************************************************
 ************************************************************************
 ******* Datei: Bibliothek lcd20x4.h ************************************
 ******* Autor: Fernando Barriga Vasquez ********************************
 ******* Kommentare:  Bibliothek für LCD-Modul 20x4 Compiler XC8 ********
 ************************************************************************
 ***********************************************************************/

#ifndef XC_LCD_20x4_H
#define	XC_LCD_20x4_H
#define _XTAL_FREQ 4000000

//HD44780 or compatible Lcd (16x2, 20x2, 20x4) library
//Copyright (c) Jayanth D, 2016

#define _LCD_FIRST_ROW          0x80     //der Cursor geht auf die erste Spalte
#define _LCD_SECOND_ROW         0xC0     //der Cursor geht auf die zweite Spalte
#define _LCD_THIRD_ROW          0x94     //der Cursor geht auf die dritte Spalte
#define _LCD_FOURTH_ROW         0xD4     //der Cursor geht auf die vierte Spalte
#define _LCD_CLEAR              0x01     //zum Reinigen des LCD-Displays.
#define _LCD_RETURN_HOME        0x02     //Return cursor to home position, returns a
                                         //shifted display to its original position.
                                         //Display data RAM is unaffected.
#define _LCD_CURSOR_OFF         0x0C     //Den Cursor deaktivieren
#define _LCD_UNDERLINE_ON       0x0E     //Der Unterstrich für den Cursor wird aktiviert
#define _LCD_BLINK_CURSOR_ON    0x0F     //blink der Cursor wird aktviert
#define _LCD_MOVE_CURSOR_LEFT   0x10     //Move cursor left without changing
                                         //display data RAM
#define _LCD_MOVE_CURSOR_RIGHT  0x14     //Move cursor right without changing
                                         //display data RAM
#define _LCD_TURN_ON            0x0C     //Turn Lcd display on
#define _LCD_TURN_OFF           0x08     //Turn Lcd display off
#define _LCD_SHIFT_LEFT         0x18     //Shift display left without changing
                                         //display data RAM
#define _LCD_SHIFT_RIGHT        0x1E     //Shift display right without changing
                                         //display data RAM

#define LCD_RS LATBbits.LATB2
#define LCD_EN LATBbits.LATB3
#define LCD_D4 LATBbits.LATB4
#define LCD_D5 LATBbits.LATB5
#define LCD_D6 LATBbits.LATB6
#define LCD_D7 LATBbits.LATB7

#define LCD_RS_Direction TRISBbits.TRISB2
#define LCD_EN_Direction TRISBbits.TRISB3
#define LCD_D4_Direction TRISBbits.TRISB4
#define LCD_D5_Direction TRISBbits.TRISB5
#define LCD_D6_Direction TRISBbits.TRISB6
#define LCD_D7_Direction TRISBbits.TRISB7

#define EN_DELAY 200
#define LCD_STROBE {LCD_EN = 1; __delay_us(EN_DELAY); LCD_EN = 0; __delay_us(EN_DELAY);};

void LCD_Cmd(char out_char) {
    LCD_RS = 0;

    LCD_D4 = (out_char & 0x10)?1:0;             
    LCD_D5 = (out_char & 0x20)?1:0;
    LCD_D6 = (out_char & 0x40)?1:0;
    LCD_D7 = (out_char & 0x80)?1:0;
    LCD_STROBE

    LCD_D4 = (out_char & 0x01)?1:0; 
    LCD_D5 = (out_char & 0x02)?1:0;
    LCD_D6 = (out_char & 0x04)?1:0;
    LCD_D7 = (out_char & 0x08)?1:0;
    LCD_STROBE

    if(out_char == 0x01)__delay_ms(2);
}

void LCD_Clear ( void)
{
    LCD_Cmd(_LCD_CLEAR);
}

void LCD_Chr(char row, char column, char out_char)
{
    switch(row) {
        case 1:
            LCD_Cmd(0x80 + (column - 1));
            break;
        case 2:
            LCD_Cmd(0xC0 + (column - 1));
            break;
        case 3:
            LCD_Cmd(0x94 + (column - 1));
            break;
        case 4:
            LCD_Cmd(0xD4 + (column - 1));
            break;
    }

    LCD_RS = 1;

    LCD_D4 = (out_char & 0x10)?1:0;
    LCD_D5 = (out_char & 0x20)?1:0;
    LCD_D6 = (out_char & 0x40)?1:0;
    LCD_D7 = (out_char & 0x80)?1:0;
    LCD_STROBE

    LCD_D4 = (out_char & 0x01)?1:0;
    LCD_D5 = (out_char & 0x02)?1:0;
    LCD_D6 = (out_char & 0x04)?1:0;
    LCD_D7 = (out_char & 0x08)?1:0; 
    LCD_STROBE
}

void LCD_Chr_Cp(char out_char) 
{
    LCD_RS = 1;

    LCD_D4 = (out_char & 0x10)?1:0;
    LCD_D5 = (out_char & 0x20)?1:0;
    LCD_D6 = (out_char & 0x40)?1:0;
    LCD_D7 = (out_char & 0x80)?1:0;
    LCD_STROBE

    LCD_D4 = (out_char & 0x01)?1:0;
    LCD_D5 = (out_char & 0x02)?1:0;
    LCD_D6 = (out_char & 0x04)?1:0;
    LCD_D7 = (out_char & 0x08)?1:0; 
    LCD_STROBE
}

void LCD_Init () 
{
    __delay_ms(200);

    LCD_RS_Direction = 0;
    LCD_EN_Direction = 0;
    LCD_D4_Direction = 0;
    LCD_D5_Direction = 0;
    LCD_D6_Direction = 0;
    LCD_D7_Direction = 0;
 
    LCD_RS = 0;
    LCD_EN = 0;
    LCD_D4 = 0;
    LCD_D5 = 0;
    LCD_D6 = 0;
    LCD_D7 = 0; 
    __delay_ms(30);
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_D4 = 0;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_Cmd(0x28);
    LCD_Cmd(0x06);
    LCD_Cmd(_LCD_CURSOR_OFF);
}

void LCD_gotoxy_putc(char row, char col, char *text) {
    while(*text)
         LCD_Chr(row, col++, *text++);
}

void LCD_Out_Cp(char *text) {
    while(*text)
         LCD_Chr_Cp(*text++);
}


#endif   /* XC_LCD_20x4_H */
