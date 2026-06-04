#pragma config FOSC = INTRC_NOCLKOUT //osilator selection bit(INTOSCIO oscillator:I\O function on RA6/OSC2/CLOCK)
#pragma config WDTE = OFF   //watchdog timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDT)
#pragma config PWRTE = ON   //Power-up timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON //RE3/MCLR pin function select bit (RE/MCLR pin function is MCLR)
#pragma config CP = OFF  //Code Protection bit(program memory code protection is disabled)
#pragma config CPD = OFF //Data code protection bit(data memory protection is disabled)
#pragma config BOREN = OFF//Brown out Reset Selection bits(BOR disabled)
#pragma config IESO = ON  //Internal and External Switchover bit(Internal/EXternal Switchover mode is enabled)
#pragma config FCMEN = ON //Fail-safe Clock Moniter Enabled bit(Fail-safe Clock Monitoris enabled)
#pragma config LVP = OFF //low voltage programming Enable bit(RB3 pin has digital I/O,#V on MCLR must be use)

// CONFIG2
#pragma config BOR4V = BOR40V // Brown -out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF //flsh Program Memory Self Write Enable bits (Write protection)

#include <xc.h>

void delay(unsigned int a)
{
    while(a--);
}
void enable()
{
    RE1=1;
       delay(100);
    RE1=0;
       delay(100);
}
void lcd(char cmd,char data)
{

    RE2 = 0;
    RE0 = cmd;
    PORTD = data;
    enable();

}
void lcdstr(char *p)
{
    while(*p)
    {
        lcd(1,*p);
        p++;
    }
}
int floor=0,sensor=0;

void main(void)
{
    PORTA = PORTC = PORTD = PORTE = TRISD = TRISE = 0X00;
    TRISC = 0XFF;
    TRISA = 0X00;
    ANSEL = ANSELH = 0X00;

    lcd(0,0x38);
    lcd(0,0x02);
    lcd(0,0x0E);
    lcd(0,0x01);

     lcd(0,0X80);
    lcdstr("FLOOR G");


    while(1)
    {
        if(RC4==1)
        {
         floor = 0;
         lcd(0,0X80);
         lcdstr("FLOOR G");
        }

        if(RC5==1)
        {
            floor = 1;
            lcd(0,0X80);
            lcdstr("FLOOR 1");
        }

        if(RC6==1)
        {
            floor = 2;
            lcd(0,0X80);
            lcdstr("FLOOR 2");
        }

        if(RC7==1)
        {
            floor = 3;
            lcd(0,0X80);
            lcdstr("FLOOR 3");
        }
        if(RC0==1)
        {
            sensor = 0;
        }
        if(RC1==1)
        {
            sensor = 1;
        }
        if(RC2==1)
        {
            sensor = 2;
        }
        if(RC3==1)
        {
            sensor = 3;
        }
        if(floor < sensor)
        {
            RA1 = 1;      // DOWN
            RA0 = 0;

            lcd(0,0x88);
            lcdstr("DOWN ");
        }

        if(floor > sensor)
        {
            RA0 = 1;      // UP
            RA1 = 0;

            lcd(0,0x88);
            lcdstr("UP  ");
        }

        if(floor == sensor)
        {
            RA0 = 0;
            RA1 = 0;
                                //STOP
            lcd(0,0x88);
            lcdstr("STOP ");
        }
    }
}
