/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
© Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 15.04.2013
Author  : AtXMega
Company : 
Comments: 


Chip type           : ATmega32
Program type        : Application
Clock frequency     : 12,000000 MHz
Memory model        : Small
External RAM size   : 0
Data Stack size     : 128
*****************************************************/

#include <mega32.h>

#define LCD_RS  PORTD.6
#define LCD_RES PORTD.5 
#define LCD_WR  PORTD.7
//#define LCD_RD  PORTD.1НА ПЛЮС
//#define LCD_CS PORTB.4  НА ЗЕМЛЮ    
#define PB_ODR PORTB
#define PF_ODR PORTC

#define OUT PORTD.1
#define LED PORTD.0
//#define HARD_RESET PORTA.7
#define ZUMMER PORTA.6

#include <delay.h>
  
    
// I2C Bus functions
#asm
   .equ __i2c_port=0x12 ;PORTD
   .equ __sda_bit=2
   .equ __scl_bit=3
#endasm
#include <i2c.h>
  
// DS1307 Real Time Clock functions
#include <ds1307.h>
                   
// 1 Wire Bus functions
#asm
//  .equ __w1_port=0x12 ;PORTD
//  .equ __w1_bit=4
 
   .equ __w1_port=0x1B ;PORTA
   .equ __w1_bit=5
#endasm


#include <1wire.h>

// DS1820 Temperature Sensor functions
#include <ds1820.h>
// maximum number of DS1820 devices
// connected to the 1 Wire bus
#define MAX_DS1820 2
// number of DS1820 devices
// connected to the 1 Wire bus
unsigned char ds1820_devices=0;
// DS1820 devices ROM code storage area,
// 9 bytes are used for each device
// (see the w1_search function description in the help)
unsigned char ds1820_rom_codes[MAX_DS1820][9];

                    



   flash unsigned char NewFont8x8[] = {
     
0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00, //48/ --> 0
0x00,0x42,0x42,0x7F,0x40,0x40,0x00,0x00, //49/ --> 1
0x00,0x00,0x62,0x51,0x49,0x46,0x00,0x00, //50/ --> 2
0x22,0x41,0x49,0x49,0x49,0x36,0x00,0x00, //51/ --> 3
0x00,0x10,0x18,0x14,0x12,0x7F,0x10,0x00, //52/ --> 4
0x00,0x26,0x45,0x45,0x45,0x45,0x39,0x00, //53/ --> 5
0x00,0x3E,0x49,0x49,0x49,0x49,0x32,0x00, //54/ --> 6
0x00,0x01,0x01,0x71,0x09,0x05,0x03,0x00, //55/ --> 7
0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00, //56/ --> 8
0x00,0x46,0x49,0x49,0x49,0x3E,0x00,0x00, //57/ --> 9  
                                                         
0x3C,0x42,0x19,0x25,0x3D,0x22,0x1C,0x00,   
0x7E,0x11,0x11,0x11,0x7E,0x00,0x00,0x00,
0x7F,0x49,0x49,0x49,0x31,0x00,0x00,0x00,
0x7F,0x49,0x49,0x49,0x36,0x00,0x00,0x00,
0x7F,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
0x40,0x7E,0x41,0x41,0x7F,0x40,0x00,0x00,
0x7F,0x49,0x49,0x49,0x41,0x00,0x00,0x00,
0x63,0x14,0x08,0x7F,0x08,0x14,0x63,0x00,
0x22,0x41,0x41,0x49,0x36,0x00,0x00,0x00,
0x7F,0x10,0x08,0x04,0x7F,0x00,0x00,0x00,
0x7F,0x10,0x09,0x04,0x7F,0x00,0x00,0x00,
0x7F,0x08,0x14,0x22,0x41,0x00,0x00,0x00,
0x40,0x3E,0x01,0x01,0x7F,0x00,0x00,0x00,
0x7F,0x02,0x04,0x08,0x04,0x02,0x7F,0x00,
0x7F,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x3E,0x41,0x41,0x41,0x3E,0x00,0x00,0x00,
0x7F,0x01,0x01,0x01,0x7F,0x00,0x00,0x00,
0x7F,0x11,0x11,0x11,0x0E,0x00,0x00,0x00,
0x3E,0x41,0x41,0x41,0x22,0x00,0x00,0x00,
0x01,0x01,0x7F,0x01,0x01,0x00,0x00,0x00,
0x27,0x48,0x48,0x48,0x3F,0x00,0x00,0x00,
0x1C,0x22,0x22,0x7F,0x22,0x22,0x1C,0x00,
0x63,0x14,0x08,0x14,0x63,0x00,0x00,0x00,
0x7F,0x40,0x40,0x40,0x7F,0xC0,0x00,0x00,
0x07,0x08,0x08,0x08,0x7F,0x00,0x00,0x00,
0x7F,0x40,0x40,0x78,0x40,0x40,0x7F,0x00,
0x7F,0x40,0x40,0x78,0x40,0x40,0x7F,0xC0,
0x01,0x7F,0x44,0x44,0x38,0x00,0x00,0x00,
0x7F,0x44,0x44,0x38,0x00,0x7F,0x00,0x00,
0x7F,0x44,0x44,0x38,0x00,0x00,0x00,0x00,
0x22,0x41,0x49,0x49,0x3E,0x00,0x00,0x00,
0x7F,0x08,0x3E,0x41,0x41,0x3E,0x00,0x00,
0x46,0x29,0x19,0x09,0x7F,0x00,0x00,0x00,
0x20,0x54,0x54,0x78,0x40,0x00,0x00,0x00,
0x7C,0x54,0x54,0x20,0x00,0x00,0x00,0x00,
0x7C,0x54,0x54,0x28,0x00,0x00,0x00,0x00,
0x7C,0x04,0x04,0x04,0x00,0x00,0x00,0x00,
0x40,0x78,0x44,0x7C,0x40,0x00,0x00,0x00,
0x7C,0x54,0x54,0x44,0x00,0x00,0x00,0x00,
0x44,0x28,0x7C,0x28,0x44,0x00,0x00,0x00,
0x28,0x44,0x54,0x28,0x00,0x00,0x00,0x00,
0x7C,0x20,0x10,0x7C,0x00,0x00,0x00,0x00,
0x7C,0x21,0x11,0x7C,0x00,0x00,0x00,0x00,
0x7C,0x10,0x28,0x44,0x00,0x00,0x00,0x00,
0x40,0x38,0x04,0x7C,0x00,0x00,0x00,0x00,
0x7C,0x08,0x10,0x08,0x7C,0x00,0x00,0x00,
0x7C,0x10,0x10,0x7C,0x00,0x00,0x00,0x00,
0x38,0x44,0x44,0x38,0x00,0x00,0x00,0x00,
0x7C,0x04,0x04,0x7C,0x00,0x00,0x00,0x00,
0x7C,0x14,0x14,0x08,0x00,0x00,0x00,0x00,
0x38,0x44,0x44,0x28,0x00,0x00,0x00,0x00,
0x04,0x04,0x7C,0x04,0x04,0x00,0x00,0x00,
0x0C,0x50,0x50,0x3C,0x00,0x00,0x00,0x00,
0x38,0x44,0x7C,0x44,0x38,0x00,0x00,0x00,
0x44,0x28,0x10,0x28,0x44,0x00,0x00,0x00,
0x7C,0x40,0x40,0x7C,0xC0,0x00,0x00,0x00,
0x0C,0x10,0x10,0x7C,0x00,0x00,0x00,0x00,
0x7C,0x40,0x70,0x40,0x7C,0x00,0x00,0x00,
0x7C,0x40,0x70,0x40,0x7C,0xC0,0x00,0x00,
0x04,0x7C,0x50,0x50,0x20,0x00,0x00,0x00,
0x7C,0x50,0x50,0x20,0x00,0x7C,0x00,0x00,
0x7C,0x50,0x50,0x20,0x00,0x00,0x00,0x00,
0x44,0x54,0x54,0x38,0x00,0x00,0x00,0x00,
0x7C,0x10,0x38,0x44,0x38,0x00,0x00,0x00,
0x48,0x34,0x14,0x7C,0x00,0x00,0x00,0x00,                 
0x00,0x00,0x00,0x36,0x36,0x00,0x00,0x00, //75/ --> :
0x40,0x66,0x36,0x18,0x6C,0x66,0x02,0x00, //76/ --> %
0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00, //77/ --> .
0x00,0x24,0x24,0x24,0x24,0x24,0x00,0x00, //78/ --> =
0x00,0x06,0x09,0x09,0x06,0x00,0x00,0x00, //79/ --> °
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //80/ --> пробел 
0x00,0xB0,0x70,0x00,0x00,0x00,0x00,0x00, //81/ -->,
0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00, //82/ --> + 
0x00,0x08,0x08,0x08,0x08,0x00,0x00,0x00, //83/ --> -  
0x00,0x44,0x44,0x5F,0x44,0x44,0x00,0x00,  //84/ +-  
0x00,0x9C,0xBE,0xCF,0xDE,0xBC,0x98,0x00, //горит/ --> 
0x00,0x80,0x80,0xC0,0xC0,0x80,0x80,0x00, //не горит/ -->                                                
};
   


// flash unsigned char New[] ={0};     // оставить для массива запяси в память 24с512

//eeprom unsigned char ic[4]={0xAA,0xBB, 0xCC,0xDD};
unsigned char dann_epp[130] ;

 int tempH[24] = {            //тут в ram хранится заданная температура дома 
 180,180,180,180,180,180,190,190,190,190,190,190,190,190,190,190,190,190,190,190,180,180,180,180         
 };
 
 eeprom int tempHepp[24];    //тут в eeprom хранится заданная температура дома 
 eeprom unsigned int temUepp[146]; 
 eeprom unsigned int  deltaE;
 unsigned int temU[146];
 

// Standard Input/Output functions
#include <stdio.h>
#define ADC_VREF_TYPE 0x40

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

   int y,x,s1;
  int korX,korY;
    unsigned char x1,x2,x3,y1,y2,y3;
   char MODE,  razovo, button, MODEr, MODEm,  timDp, timDpU, tempDi;
unsigned int   fon, delta;
int x,y, tex, a,sepp;
  unsigned int b, out;
  int c,f2,timeStep;
 int tempU, tempD,tempSr=500, tempSrU=500;
 int tempUst, tempDst,
 char tU1,tU2,tU3,tD1,tD2,tD3,tDi1,tDi2,tDi3;
 int    del60, del600, delSensor;        
char vr=10, mnoz, zalit, cykle, ae;       
   char hour, minute,second;
   int  itt, MasMax, MasMin;
   float Pazmah,Ntim;
   char r1,r2,r3,r4,r5;//удалить
   int vivA, vivB;
   unsigned  int tempo ;                      //удалить
   int tempPredU,tempPredD; 
   
   
      void LCD_WriteIndex(unsigned int index)
{     //    LCD_CS=0;

  LCD_RS = 0; 		// Тип данных - команда (в данном случае адрес)
//  LCD_RD = 1; 		// При записи RD должен быть стопудово равен 1, а то не запишет
  PB_ODR = (index & 0x00FF);		// Выставляем младшую часть адреса на шину
  PF_ODR = ((index & 0xFF00) >> 8);	// и старшую
  LCD_WR = 0; 		// Следующие три строки - строб /WR
 // delay_us(2);
  LCD_WR = 1;
//  LCD_CS=1;

};
 
// Процедура записи данных в регистр или ОЗУ
  void LCD_WriteData(unsigned int data)
{   //  LCD_CS=0;

  LCD_RS = 1; 			// Тип данных - данные
  PB_ODR = (data & 0x00FF); 	// Вывод на шину старшего
  PF_ODR = ((data & 0xFF00) >> 8);  	// и младшего байтов данных
  LCD_WR = 0; 			// Строб
 // delay_us(2);
  LCD_WR = 1;
 // LCD_CS=1;
 
} ;
    
     void LCD_WR_REG (unsigned int LCD_Reg, unsigned int LCD_RegValue)
{  
 // LCD_CS = 0;			// Активируем Chip Select
 
  LCD_WriteIndex(LCD_Reg);	// Пишем адрес регистра
  LCD_WriteData(LCD_RegValue);	// Пишем в него данные
 // LCD_CS = 1;			// Деактивируем Chip Select
};
    

    void LCD_Clear(unsigned int Color)
    {

  unsigned long index=0;

 	// Устанавливаем курсор в начало
			// Здесь запись организована "атомарно" для ускорения процедуры
  LCD_WriteIndex(0x0022); 	// Запись этого адреса в регистр индекса означает, что
                          	// сейчас будут выводиться данные в экранное ОЗУ
                          	// Как себя будут вести счетчики строк и столбцов определяется
                          	// регистром с адресом 0x0011
  for(index=0;index < 0x12C00;index++)
 // for(index=0;index < 0x257F;index++)   1/8
	{ 			// цикл с количеством итераций 320*240
   	LCD_WriteData(Color); 	// ставим точки заданного цвета
    	}
   		
}


      void LCD_SetCursor ( unsigned int Y , unsigned int X)
       {
           
         LCD_WR_REG(0x0020, X);       //y
         LCD_WR_REG(0x0021, Y);   //x
           LCD_WriteIndex(0x0022);
           
        }


        
//Функция вывода точки зхаданного размера, по координатам, заданного цвета
void point (unsigned char size,unsigned int x,unsigned int y,unsigned int color)
{
    unsigned char j,i;
          
    for(j=0;j < size; j++)
	{
	   LCD_WriteIndex(0x0020);   
	    LCD_WriteData(y+j);       
	   LCD_WriteIndex(0x0021);   
	   LCD_WriteData(x);
        LCD_WriteIndex(0x0022);
	    for(i=0;i < size;i++) LCD_WriteData(color);
	}
     
    
}    

   
//Функция вывода  прямоугльнрка зхаданного размера, по координатам, заданного цвета
void kelly (unsigned int xx ,unsigned int yy,unsigned int x,unsigned int y,unsigned int color)
{
    unsigned int j,i;
             
    for(j=0;j <= yy; j++)
	{  

	   LCD_WriteIndex(0x0020);   
	    LCD_WriteData(y+j);       
	   LCD_WriteIndex(0x0021);   
	   LCD_WriteData(x);
        LCD_WriteIndex(0x0022);
         
	    for(i=0;i < xx;i++) { 
          if (j<2 || j>yy-2 || i<2 || i>xx-3) {LCD_WriteData(0xF81F);} else {LCD_WriteData(color);}
          }
    }
  
}      

   /*
//Функция вывода окружности заданного размера, по координатам, заданного радиуса и цвета
void circle (unsigned char size,int x0,int y0,int radius,unsigned int color)
{
        int x = 0;//работает по алгоритму Брезенхема (см. Википедию)
        int y = radius;
        int delta = 2 - 2 * radius;
        int error = 0;
  #asm("cli")         
        
        while(y >= 0) 
		{
                point(size,x0 + x, y0 + y,color);
                point(size,x0 + x, y0 - y,color);
                point(size,x0 - x, y0 + y,color);
                point(size,x0 - x, y0 - y,color);
                error = 2 * (delta + y) - 1;
                if(delta < 0 && error <= 0)
                {
                        ++x;
                        delta += 2 * x + 1;
                        continue;
                }
                error = 2 * (delta - x) - 1;
                if(delta > 0 && error > 0)
                {
                        --y;
                        delta += 1 - 2 * y;
                        continue;
                }
                ++x;
                delta += 2 * (x - y);
                --y;
        }
    #asm("sei")       
}
   */
       
          void LCD_ClearH( unsigned int Color)               //очистка центра  , вывод сетки
    {
 int index=0;
 int index2=0;
  int pozY=16;
 
   LCD_SetCursor (25, pozY);
                          	
  for(index=0;index < 194;index++)
 	{ 			// цикл с количеством итераций
       
        for(index2=0;index2 < 295 ;index2++)
          {
         	LCD_WriteData(Color); 	// ставим точки заданного цвета
                  }
       //    poz=poz-12;
           pozY++;
         LCD_SetCursor (25, pozY);   
    	}
   
              for (y=0;y<9;y++) {                         //вывод сетки
                   for (x=0;x<24;x++) {
                    point(2,35+x*12,36+y*20,0xF800) ;
                 };
                };
                    		
}

   void LCD_ClearT( unsigned int Color)               //очистка текста
    {
 int index=0;
 int index2=0;
  int pozY=213;
  
   LCD_SetCursor (0, pozY);
                          	
  for(index=0;index < 28;index++)
 	{ 			// цикл с количеством итераций
        for(index2=0;index2 < 320 ;index2++)
          {
         	LCD_WriteData(Color); 	// ставим точки заданного цвета
                  }
       //    poz=poz-12;
           pozY++;
         LCD_SetCursor (0, pozY);   
    	} 
     		
}



  unsigned int X7;         // Вывод буквы в текущую позицию дисплея
  unsigned int Y7;
  unsigned int paper;
  unsigned int ink;
  unsigned char sizeP; 
    unsigned char sizeH=0;
    
     void LCD_PutcharH  ( unsigned int H7 )  {
    sizeH=H7;
     
   }
    
    
   void LCD_PutcharKor  ( unsigned int a7, unsigned int b7,unsigned char s7 )  {
   
    X7=a7;
    Y7=b7;
    sizeP=s7;
     
   }
    
  void LCD_PutcharColor    (  unsigned int c78,  unsigned int d78) {
  
   paper=c78;
   ink=d78;
   
   }

void LCD_Putchar(unsigned char chr, ){  // Аргумент - код буквы 
  unsigned char i, a;
  unsigned int addr;
   
      addr = chr << 3;
        LCD_SetCursor(X7, Y7);
       
      for(i=0;i<8*sizeP;i++){     //Счетчик строки знакоместа
        	   LCD_WriteIndex(0x0020);   
	    LCD_WriteData(Y7); 
         // Установка координаты Y
           // Выводим строку точек
        LCD_WriteIndex(0x0022);
        for(a=0;a<8*sizeP;a++){   //Счетчик столбцов знакоместа
          if(NewFont8x8[addr+a/sizeP]&(0x80>>i/sizeP)){ // Если в знакоместе точка = 1
            LCD_WriteData(ink);     // Выводим цвет ink
          }else{
            LCD_WriteData(paper);   // Иначе цвет фона
          }
        }
         Y7++;  // Переходим на новую строку знакоместа
      }
    //  Y = tmp;  // Восстанавливаем значение буквы по вертикали
      // Ниже расположено вычисление ширины буквы для более плотного расположения текста на экране
     i = 3; 
      for(a=7;a!=0;a--){
        if(NewFont8x8[addr+a] != 0x00){
        if(sizeP==1) {i = a + 2;};
        if(sizeP==2) {i=(a*2)+3;};
        if(sizeP>2)  {i=(a*3)+4;};
          break;
        }
      }     
      X7 += i; 
       Y7=Y7-8*sizeP;

}

  /*

void LCD_Put(unsigned int chr, ){  // Аргумент - код буквы  БОЛЬШИЕ 128x128
  unsigned int i, a, tmp,m;
  unsigned int addr;
      #asm("cli")
      addr = chr*512;
      tmp = Y7;  // сохраняем позицию для возврата при отображении новой строки точек 
         LCD_SetCursor(X7, Y7);
       
      for(m=0;m<16;m++){    
       for(i=0;i<8;i++){     //Счетчик строки знакоместа
        	   LCD_WriteIndex(0x0020); 
              
	    LCD_WriteData(Y7); 
         // Установка координаты Y
           // Выводим строку точек
        LCD_WriteIndex(0x0022);
        for(a=0;a<128;a++){   //Счетчик столбцов знакоместа
          if(New[addr+a]&(0x80>>i)){ // Если в знакоместе точка = 1
            LCD_WriteData(ink);     // Выводим цвет ink
          }else{
            LCD_WriteData(paper);   // Иначе цвет фона
          }
        }
         Y7++;  // Переходим на новую строку знакоместа
       }
         Y7=Y7-16;
       addr=addr+128;
        
      }
        
       X7=X7+45; 
       Y7=Y7+64;
        #asm("sei")
    }

                */

   

void LCD_PutM(unsigned int chr){  // Аргумент - код буквы  БОЛЬШИЕ  из 24C256
  unsigned int i, a, m,n;
  unsigned int addr,zaz=5;
         addr = chr*2100;
   //   tmp = Y7;  // сохраняем позицию для возврата при отображении новой строки точек 
         LCD_SetCursor(X7, Y7);
         
     
          
    for(m=0;m<16;m++){  
             
           for(tex=0; tex<128; tex++){     
           i2c_start();                          //чтение сектора
             i2c_write(0xA0);
            i2c_write(((addr+(tex+(128*m))) & 0xFF00) >> 8);
             i2c_write(((addr+tex+(128*m))) & 0x00FF);
               i2c_start();  
            i2c_write(0xA1);
            dann_epp[tex]=i2c_read(0);           
             i2c_stop();       
           
            }
      
        for(i=0;i<8;i++){     //Счетчик строки знакоместа
        if(sizeH==1){i++;}	
           LCD_WriteIndex(0x0020); 
          n=0;    
	    LCD_WriteData(Y7); 
          LCD_WriteIndex(0x0022);
        for(a=0;a<128;a++){   //Счетчик столбцов знакоместа
        n++;
          if(n==5){n=0;}
           
          if(sizeP==1) {
            if(n==0 || n==2 || n==4 ){
                     if(dann_epp[a]&(0x80>>i)){ // Если в знакоместе точка = 1
                  LCD_WriteData(ink);     // Выводим цвет ink
                    }else{
                     LCD_WriteData(paper);   // Иначе цвет фона
                  }
           }
          } 
          
           if(sizeP==2) {
            if(n<4 ){
                     if(dann_epp[a]&(0x80>>i)){ // Если в знакоместе точка = 1
                  LCD_WriteData(ink);     // Выводим цвет ink
                    }else{
                     LCD_WriteData(paper);   // Иначе цвет фона
                  }
           }
          } 
          
          
          
          
          if(X7+a>329 &&sizeP==2) {a=150; }
          if(X7+a>361 &&sizeP==1) {a=150; }
           }
         Y7++;  // Переходим на новую строку знакоместа
       }
       //  Y7=Y7-16;
        if(sizeH==1){ Y7=Y7-8; } else{Y7=Y7-16;}	      
   }
 
     if(sizeP==1){        
        zaz=3;          
        switch(chr) {
case 0:  { X7=X7+zaz+70;  break; }
case 1:  { X7=X7+zaz+37;  break; }
case 2:  { X7=X7+zaz+68;  break; }
case 3:  { X7=X7+zaz+63;  break; }
case 4:  { X7=X7+zaz+67;  break; }
case 5:  { X7=X7+zaz+66;  break; }
case 6:  { X7=X7+zaz+73;  break; }
case 7:  { X7=X7+zaz+65;  break; }
case 8:  { X7=X7+zaz+64;  break; }
case 9:  { X7=X7+zaz+73;  break; }
case 10: { X7=X7+zaz+53;  break; }
case 11: { X7=X7+zaz+40;  break; }
case 12: { X7=X7+zaz+18;  break; }
case 13: { X7=X7+zaz+25;  break; }
                    }
   }else{  

       switch(chr) {
case 0:  { X7=X7+zaz+98;  break; }
case 1:  { X7=X7+zaz+44;  break; }
case 2:  { X7=X7+zaz+81;  break; }
case 3:  { X7=X7+zaz+73;  break; }
case 4:  { X7=X7+zaz+81;  break; }
case 5:  { X7=X7+zaz+80;  break; }
case 6:  { X7=X7+zaz+87;  break; }
case 7:  { X7=X7+zaz+77;  break; }
case 8:  { X7=X7+zaz+76;  break; }
case 9:  { X7=X7+zaz+88;  break; }
case 10: { X7=X7+zaz+64;  break; }
case 11: { X7=X7+zaz+48;  break; }
case 12: { X7=X7+zaz+28;  break; }
case 13: { X7=X7+zaz+36;  break; }
                    }
               }  
      if(sizeH==1){ Y7=Y7+64; } else{ Y7=Y7+128;}	        
      // Y7=Y7+128;
     }

 
void LCD_PutK(unsigned int chr ){  // Аргумент - код картинки
  unsigned int i, a,m;
  unsigned int addr;
           addr = (chr*600)+29400;
      // сохраняем позицию для возврата при отображении новой строки точек 
         LCD_SetCursor(X7, Y7);
         
         
         
       for(m=0;m<8;m++){ 
           for(tex=0; tex<64; tex++){   
        
       
          
             
           i2c_start();                          //чтение сектора
             i2c_write(0xA0);
            i2c_write(((addr+(tex+(64*m))) & 0xFF00) >> 8);
             i2c_write(((addr+tex+(64*m))) & 0x00FF);
               i2c_start();  
            i2c_write(0xA1);
            dann_epp[tex]=i2c_read(0);           
             i2c_stop();  
          
            } 
             
      for(i=0;i<8;i++){     //Счетчик строки знакоместа
        	   LCD_WriteIndex(0x0020);   
	    LCD_WriteData(Y7); 
         // Установка координаты Y
           // Выводим строку точек
        LCD_WriteIndex(0x0022);
        for(a=0;a<64;a++){   //Счетчик столбцов знакоместа
     
          if(dann_epp[a]&(0x80>>i)){ // Если в знакоместе точка = 1
            LCD_WriteData(ink);     // Выводим цвет ink
          }else{
            LCD_WriteData(paper);   // Иначе цвет фона
          }
        }
         Y7++;  // Переходим на новую строку знакоместа
      }
     Y7=Y7-16;
  }  
   }




        
 
// Timer 1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)          //1Hz
{TCNT1H=0x00; TCNT1L=0x00;
   del60++;    
    del600++; 
  

    if(del600>300){ del600=0;                                         //тут добавить опрос 1 раз в 5 минут  То есть написать 300
    timeStep=((hour*60)+minute)/10;  
 // timeStep=(minute*60+second)/30;  
       temU[timeStep]=tempU;
        if(MODE==3){razovo=0; }
          };                                                        
  



}        
         
// Timer 2 output compare interrupt service routine
interrupt [TIM2_COMP] void timer2_comp_isr(void)  //50Hz
{TCNT2=0x00;
      
    if(PINA.4==1){
     
        for (ae=0; ae<25; ae++){ 
      tempHepp[ae]=tempH[ae] ;  //это заполнение массива дома 
      } 
    
      for (a=0; a<145; a++){ 
       temUepp[a] = temU[a];  //это заполнение массива улицы 
      }
 
      deltaE=delta;
    
           ZUMMER=1;
      delay_ms(300);   
      ZUMMER=0;
       /*
PORTA=0x00;
DDRA=0x00;
PORTB=0x00;
DDRB=0x00;
PORTC=0x00;
DDRC=0x00;
PORTD=0x00;
DDRD=0x00;  */
   delay_ms(4000);   delay_ms(4000);   delay_ms(4000); delay_ms(4000); delay_ms(4000);  delay_ms(4000); delay_ms(4000); delay_ms(4000); delay_ms(4000);

            }; 
 
        
           

 if(MODE==2){vr=3;}else{vr=10;};
    delSensor++; if( delSensor>vr){ delSensor=0;
     
        // PORTA=0x01;     //опрос сенсора      // X+ >A2    Y+ >A1      
        // DDRA=0xFC;                           // X- >A3    Y- >A0
           PORTA.0=1;   PORTA.1=0;  PORTA.2=0;  PORTA.3=0;
           DDRA.0=0; DDRA.1=0;  DDRA.2=1; DDRA.3=1;  
         
          
           delay_us(300);
            
      if(PINA.0==0){        //если нажат
        
        
       //  PORTA=0x04;
        // DDRA=0xFC; 
             DDRA.0=0; DDRA.1=0;  DDRA.2=1; DDRA.3=1;    
            PORTA.0=0;   PORTA.1=0;  PORTA.2=1;  PORTA.3=0;
        
        
            delay_us(300);       //было700
       korX=(read_adc(0)-70)/2.55;   //коэффициенты не трогать
        // PORTA=0x01;
       //  DDRA=0xF3; 
                     PORTA.0=1;   PORTA.1=0;  PORTA.2=0;  PORTA.3=0;
            DDRA.0=1; DDRA.1=1;    DDRA.2=0; DDRA.3=0;  
           
             delay_us(700);
       korY=(read_adc(3)-130)/3.2;   //коэффициенты не трогать    
        
      //  PORTA=0x01;     //снова опрос сенсора
       //  DDRA=0xFC;
                  PORTA.0=1;   PORTA.1=0;  PORTA.2=0;  PORTA.3=0;
          DDRA.0=0; DDRA.1=0;  DDRA.2=1; DDRA.3=1;  
         
            delay_us(300); 

             if(PINA.0==0){                    
         //    point(1,korX, korY ,0xFCA0 );      //вывод точки в месте касания
          button=1; //значит есть касание
          
          
          
          if(korX>320)  {    // 5 кнопок справа

           if(korY>194)             { MODE=5;      }              // самая верхняя кнопочка Настройки
           if(korY<183&& korY>145)  { MODE=4;    }                 //часы
           if(korY<135&& korY>98 )  { MODE=3;     }               //пусть пока режим графика улицы / температура улицы
           if(korY<85 && korY>50 )  { MODE=2;             }      //рехим записи в массив
           if(korY<40)              { MODE=1;           }      // режим с часами и графиком задания /часы и температура дома
            timDp=timDpU=1;
             razovo=0;   
               
         }                

        if(korX>15 && korX<300){
         if(MODE==4 || MODE==3 || MODE==1|| MODE==0){
         
          MODE=7;
           razovo=0; 
             timDp=timDpU=1;
         }
        } 
         
              }else{ button=0; korX=korY=0;};
        } else{ button=0; korX=korY=0;};     
} }         
         
void main(void)
{
// Declare your local variables here

  delay_ms(3000);
// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=Out Func5=Out Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=0 State5=0 State4=P State3=T State2=T State1=T State0=T 
PORTA=0x10;
DDRA=0x60;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=In Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=P State3=0 State2=0 State1=0 State0=0 
PORTD=0x10;
DDRD=0xEF;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 11,719 kHz
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x05;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x2D;
OCR1AL=0xC7;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 11,719 kHz
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x07;
TCNT2=0x00;
OCR2=0xEA;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x90;



// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;
       

// ADC initialization
// ADC Clock frequency: 62,500 kHz
// ADC Voltage Reference: AVCC pin
// ADC High Speed Mode: Off
// ADC Auto Trigger Source: None
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x87;
SFIOR&=0xEF;    
// Global enable interrupts

// I2C Bus initialization
i2c_init();
  
// DS1307 Real Time Clock initialization
// Square wave output on pin SQW/OUT: On
// Square wave frequency: 1Hz
rtc_init(0,1,0);
      
// Determine the number of DS1820 devices
// connected to the 1 Wire bus
ds1820_devices=w1_search(0xf0,&ds1820_rom_codes);
if (ds1820_devices<2){delay_ms(500); ds1820_devices=w1_search(0xf0,&ds1820_rom_codes);}
if (ds1820_devices<2){delay_ms(500); ds1820_devices=w1_search(0xf0,&ds1820_rom_codes);}
if (ds1820_devices<2){delay_ms(500); ds1820_devices=w1_search(0xf0,&ds1820_rom_codes);}

       ds1820_temperature_10(&ds1820_rom_codes[0][0]);    //эти функции опрашивают первый раз датчии и выбрасывают значения  
       ds1820_temperature_10(&ds1820_rom_codes[1][0]); 
   
    delay_ms(1); 
   
           // Сбров - низий уровень 10 мс
   LCD_RES=0;
   delay_ms(100);
   LCD_RES=1;         // reset
 LCD_WR_REG(0x00E5, 0x8000);  // Set the internal vcore voltage
 LCD_WR_REG(0x0000, 0x0001);    // Start internal OSC.
 LCD_WR_REG(0x0001, 0x0100);    // set SS and SM bit
 LCD_WR_REG(0x0002, 0x0700);    // set 1 line inversion
// LCD_WR_REG(0x0003, 0x1030 /* 0x1030 */); // set GRAM write direction and BGR=1.
   LCD_WR_REG(0x0003, 0x1028 /* 0x1030 */); // set GRAM write direction and BGR=1.
 LCD_WR_REG(0x0004, 0x0000);    // Resize register
 LCD_WR_REG(0x0008, 0x0202);    // set the back porch and front porch              0001000000110000
 LCD_WR_REG(0x0009, 0x0000);    // set non-display area refresh cycle ISC[3:0]
 LCD_WR_REG(0x000A, 0x0000);    // FMARK function
 LCD_WR_REG(0x000C, 0x0000);    // RGB interface setting
 LCD_WR_REG(0x000D, 0x0000);    // Frame marker Position
 LCD_WR_REG(0x000F, 0x0000);    // RGB interface polarity
 //*************Power On sequence ****************//
 LCD_WR_REG(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
 LCD_WR_REG(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
 LCD_WR_REG(0x0012, 0x0000); // VREG1OUT voltage
 LCD_WR_REG(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
 delay_ms(200);                 // Dis-charge capacitor power voltage
 LCD_WR_REG(0x0010, 0x17B0); // SAP, BT[3:0], AP, DSTB, SLP, STB
 LCD_WR_REG(0x0011, 0x0147); // DC1[2:0], DC0[2:0], VC[2:0]
 delay_ms(50);                  // Delay 50ms
 LCD_WR_REG(0x0012, 0x013C); // VREG1OUT voltage
 delay_ms(50); // Delay 50ms
 LCD_WR_REG(0x0013, 0x0E00); // VDV[4:0] for VCOM amplitude
 LCD_WR_REG(0x0029, 0x0009); // VCM[4:0] for VCOMH
 delay_ms(50);
 LCD_WR_REG(0x0020, 0x0000); // GRAM horizontal Address
 LCD_WR_REG(0x0021, 0x0000); // GRAM Vertical Address
 // ----------- Adjust the Gamma Curve ----------//
 LCD_WR_REG(0x0030, 0x0207);
 LCD_WR_REG(0x0031, 0x0505);
 LCD_WR_REG(0x0032, 0x0102);
 LCD_WR_REG(0x0035, 0x0006);
 LCD_WR_REG(0x0036, 0x0606);
 LCD_WR_REG(0x0037, 0x0707);
 LCD_WR_REG(0x0038, 0x0506);
 LCD_WR_REG(0x0039, 0x0407);
 LCD_WR_REG(0x003C, 0x0106);
 LCD_WR_REG(0x003D, 0x0601);
 //------------------ Set GRAM area ---------------//
 LCD_WR_REG(0x0050, 0x0000); // Horizontal GRAM Start Address
 LCD_WR_REG(0x0051, 0x00EF); // Horizontal GRAM End Address
 LCD_WR_REG(0x0052, 0x0000); // Vertical GRAM Start Address
 LCD_WR_REG(0x0053, 0x013F); // Vertical GRAM End Address
 LCD_WR_REG(0x0060, 0x2700); // Gate Scan Line
 LCD_WR_REG(0x0061, 0x0001); // NDL,VLE, REV
 LCD_WR_REG(0x006A, 0x0000); // set scrolling line
 //-------------- Partial Display Control ---------//
 LCD_WR_REG(0x0080, 0x0000);
 LCD_WR_REG(0x0081, 0x0000);
 LCD_WR_REG(0x0082, 0x0000);
 LCD_WR_REG(0x0083, 0x0000);
 LCD_WR_REG(0x0084, 0x0000);
 LCD_WR_REG(0x0085, 0x0000);
 //-------------- Panel Control -------------------//
 LCD_WR_REG(0x0090, 0x0010);
 LCD_WR_REG(0x0092, 0x0000);
 LCD_WR_REG(0x0093, 0x0003);
 LCD_WR_REG(0x0095, 0x0110);
 LCD_WR_REG(0x0097, 0x0000);
 LCD_WR_REG(0x0098, 0x0000);
 LCD_WR_REG(0x0007, 0x0173); // 262K color and display ON


         LCD_Clear(0x0000);

         LED=1;
            

           
 //rtc_set_date(26,08,2013); //установить дату 
//rtc_set_time(14,27,00);      //установить  время
               
       
   tempU=  (ds1820_temperature_10(&ds1820_rom_codes[0][0]))/10;  // ТУТ поменять на улицу
  if( tempU>1300 || tempU<-600) {  tempU=  (ds1820_temperature_10(&ds1820_rom_codes[0][0]))/10;}
  if( tempU>1300 || tempU<-600) {  tempU=  (ds1820_temperature_10(&ds1820_rom_codes[0][0]))/10;}     //восстановить
  if( tempU>1300 || tempU<-600) {  tempU=  (ds1820_temperature_10(&ds1820_rom_codes[0][0]))/10;}
  if( tempU<0){tempU=500-tempU;} else {tempU=tempU+500;}     //преобразование отрицательной температуры улицы
    
          
  for (a=0; a<145; a++){ 
   temU[a]=temUepp[a];  //это заполнение массива улицы 
    }
 
   
             
  for (a=0; a<25; a++){ 
   tempH[a]=tempHepp[a] ;  //это заполнение массива дома 
    } 
    
    
           delta=deltaE;

        //    kelly (30, 50, 20,  240,0xFFFF);
            //   circle (1,60,90,30,0xA510);    
           
                 LCD_PutcharColor(0x0000,0xFFFF);
                 LCD_Clear(0x0000); 
               LCD_ClearH(0x0000); 
               
              
   LCD_PutcharColor(0x0000,0xFFFF);for(y=0; y<10; y++) {  LCD_PutcharKor(3,12+y*20,1); b=(y+17)/10;   c=(y+17)%10;  LCD_Putchar(b); LCD_Putchar(c); }   //вывод надписей  температуры
  for(y=0; y<26; y=y+2) {LCD_PutcharKor((y*12)+15,3,1); b=y/10; c=y%10; LCD_Putchar(b); LCD_Putchar(c);   }                    //вывод надписей и времени 
  for(y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
             
               
  /*               
        temU[1 ]=5;
        temU[10]=400;
        temU[20]=600;
        //temU[30]=;
        //temU[40]=1490;
        temU[50]=500;
              
            
    */          
          
        /*
         for(a=32000; a<29348; a++){  
       i2c_start();                        //данные запись
       i2c_write(0xA0);
       i2c_write((a & 0xFF00) >> 8);
       i2c_write(a & 0x00FF);
       i2c_write(New[a-32000] );           
       i2c_stop();        
       delay_ms(10);    
          };  */

     
                 

      del60=65; 
      del600=295; 
      #asm("sei")                  
while (1)
{      

                                                                              //тут 1 раз в минуту опрашиваются оба датчика и если надо выводят температуру
       if(del60>59 && MODE!=2 ){
        if(del60<70 )   {
          //if(del60<70 && MODE==3)   {razovo=0;del60=0;}
            if(MODE==4){razovo=0;}
       
          #asm("cli")   
                                                            //изменить на 1 раз в минуту  написать не 5 а 60
          tempU= ( ds1820_temperature_10(&ds1820_rom_codes[0][0]))/8; 
          tempD= ( ds1820_temperature_10(&ds1820_rom_codes[1][0]))/8; 

         #asm("sei")  
                                                                     
        if ( tempD>=1200 || tempD<=-60){  tempU=tempPredU;  }          //исключение ошибки
        if ( tempD>=1200 || tempD<=-60){  tempD=tempPredD;   }
          
         tempPredU= tempU;
         tempPredD= tempD;
        
       
        if( tempU<0){tempU=500-tempU;} else{tempU=tempU+500;}    //преобразование отрицательной температуры улицы
       
             /*
         tempo=tempU;
          //удалить
          r1=tempo /10000;
          r2=(tempo/1000)%10;
          r3=(tempo/100)%10;
          r4=(tempo/10)%10;
          r5=tempo%10;
            LCD_PutcharKor(275,190,1);
             LCD_Putchar(r1);LCD_Putchar(r2);LCD_Putchar(r3);LCD_Putchar(r4);LCD_Putchar(r5); 
          
         
          tempo=tempD;
          //удалить
          r1=tempo /10000;
          r2=(tempo/1000)%10;
          r3=(tempo/100)%10;
          r4=(tempo/10)%10;
          r5=tempo%10;
            LCD_PutcharKor(275,180,1);
             LCD_Putchar(r1);LCD_Putchar(r2);LCD_Putchar(r3);LCD_Putchar(r4);LCD_Putchar(r5); 
       
                          LCD_PutcharKor(295,170,1);
            LCD_Putchar(ds1820_devices);   //удалить(число датчиков)
        
             */
        
        
        
        
        
        
        
       
          if (tempSr!=tempD) {
          tD1=(tempD%1000)/100;   tD2=(tempD%100)/10;  tD3=tempD%10;                  //  вычисление температуры дома и вывод на дисплей в уголок
              timDp=1; }
              
               if (tempSrU!=tempU) {
             if(tempU>=500) { tU1=((tempU-500)%1000)/100;   tU2=((tempU-500)%100)/10;  tU3=(tempU-500)%10; }                 //  вычисление температуры дома и вывод на дисплей в уголок
             if(tempU<500 ) { tU1=((500-tempU)%1000)/100;   tU2=((500-tempU)%100)/10;  tU3=(500-tempU)%10; }    
             // if(MODE==3){razovo=0;MODEr=5;}
           timDpU=1; }
            
         }     
              
            LCD_ClearT(0x0000);
              LCD_PutcharKor(10,215,2);
             LCD_Putchar(tD1 );    LCD_Putchar(tD2 );  LCD_Putchar(77);  LCD_Putchar(tD3 ); LCD_Putchar(79);
              LCD_PutcharKor(170,215,2);
           if(tempU<500){  LCD_Putchar(83 );}    LCD_Putchar(tU1 );    LCD_Putchar(tU2 );  LCD_Putchar(77);  LCD_Putchar(tU3 ); LCD_Putchar(79);
             tempSr=tempD; 
             tempSrU=tempU;
             
               
             rtc_get_time( &hour, &minute,&second);
             delay_ms(2);
             if(hour>30){rtc_get_time( &hour, &minute,&second);};
             LCD_PutcharKor(245,215,2);                                                     //вывести текст о режиме
            LCD_Putchar(hour/10);   LCD_Putchar(hour%10); LCD_Putchar(75); LCD_Putchar(minute/10); LCD_Putchar(minute%10);    //"время"
             
                                         //тут программма включения выхода
        tempDi= tempH[hour];
         tDi1=(tempDi%1000)/100;   tDi2=(tempDi%100)/10;  tDi3=tempDi%10;  
          LCD_PutcharKor(68,215,1);
             LCD_Putchar(tDi1 );    LCD_Putchar(tDi2 );  LCD_Putchar(77);  LCD_Putchar(tDi3 ); 
            LCD_Putchar(84);  LCD_Putchar(delta/10);  LCD_Putchar(77 ); LCD_Putchar(delta%10); LCD_Putchar(79);
         
         if(tempDi-delta>tempD){OUT=0;}
         if(tempDi+delta<tempD){OUT=1;}
         LCD_PutcharKor(132,215,2); 
         if(OUT==0){  LCD_PutcharColor(0x0000,0xF4C1);  LCD_Putchar(85);  LCD_PutcharColor(0x0000,0xFFFF);}else{ LCD_Putchar(86);}
         
         
           

            del60=0;
             
           }
       /*
         if(zalit==1){ zalit=0;
            LCD_Clear(0x0000); 
               LCD_ClearH(0x0000);    


          LCD_PutcharColor(0x0000,0xFFFF);    //вывод надписей  температуры
        for(y=0; y<10; y++) {
        LCD_PutcharKor(3,12+y*20,1);
        b=(y+17)/10;
        c=(y+17)%10;
            LCD_Putchar(b); LCD_Putchar(c); }
      
         for(y=0; y<26; y=y+2) {                     //вывод надписей и времени 
         LCD_PutcharKor((y*12)+15,3,1);
          b=y/10;
          c=y%10; 
           LCD_Putchar(b); LCD_Putchar(c);        
                                   }
    
                 for (y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
       }
       
          */
                                                                                                     

            /*
              
          x1=korX/100;     x2=(korX%100)/10;  x3=korX%10;                                     //  вычисление координат и вывод на дисплей
          y1=korY/100;  y2=(korY%100)/10;   y3=korY%10;
         LCD_PutcharKor(290,130,1); LCD_PutcharColor(0x0000,0xFFFF); LCD_Putchar(x1); LCD_Putchar(x2); LCD_Putchar(x3);
        LCD_PutcharKor(290,120,1);LCD_Putchar(y1);  LCD_Putchar(y2);  LCD_Putchar(y3);
                 
               */   
            
               
                if(out>5){                      //вывод оставшегося времени доо выхода из меню 2
                     
                  y1=(900-out)/100;
                 y2=((900-out)%100)/10;
                 y3=(900-out)%10;
                 LCD_PutcharKor(40,20,1);

                  LCD_Putchar(y1);
                 LCD_Putchar(y2);
               //  LCD_Putchar(y3);
               
                 }                       
        
         

            
      if( button==1){        //если есть касание

           
            
          
           if(MODE==2){                                       //    если нажата вторая кнопка и ЕСТЬ касание 
           razovo++;                                   // только 1 раз вывести текст
            if (razovo==1){
            razovo=7;
             MODEr=5;
             out=0;
             LCD_Clear(0x0000); 
               LCD_ClearH(0x0000); 
                LCD_ClearT(0x0000);
             LCD_PutcharColor(0x0000,0xFFFF);for(y=0; y<10; y++) {  LCD_PutcharKor(3,12+y*20,1); b=(y+17)/10;   c=(y+17)%10;  LCD_Putchar(b); LCD_Putchar(c); }   //вывод надписей  температуры
             for(y=0; y<26; y=y+2) {LCD_PutcharKor((y*12)+15,3,1); b=y/10; c=y%10; LCD_Putchar(b); LCD_Putchar(c);   }                    //вывод надписей и времени 
                 for (y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
             
             
            LCD_PutcharKor(190,215,2);                                                     //вывести текст о режиме
            LCD_Putchar(18);   LCD_Putchar(43); LCD_Putchar(58); LCD_Putchar(51); LCD_Putchar(60); LCD_Putchar(71);   //"Запись массива"
            LCD_Putchar(80);  LCD_Putchar(55);LCD_Putchar(43);LCD_Putchar(60);LCD_Putchar(60);LCD_Putchar(51);LCD_Putchar(45);LCD_Putchar(43);
               for (x=0;x<287;x++) {   y=tempH[x/12];  y=(y-170)*2;  f2=tempH[(x/12)+1];  f2=(f2-170)*2;    //чтение из массива и вывод кусочков прямой на экран
                point(3,x+24,y+15,0xFFE0) ;
                if(x%12==11){
                 // point(4,x+20,y+15,0xFFFF) ;
                 if(y>f2){for (s1=y; s1>f2; s1--)     {  point(3,x+25,s1+15,0xFFE0); };       };
                 if(y<f2){for (s1=y; s1<f2; s1++)     {  point(3,x+25,s1+15,0xFFE0); };       };
                
                
                };
               
               };  
                    LCD_PutcharColor(0x9199,0x0000);
               kelly (100, 40, 200, 167,0x9199);  LCD_PutcharKor(230,177,3); LCD_Putchar(82);  
               kelly (100, 40, 50,  167,0x9199);  LCD_PutcharKor(90,177,3); LCD_Putchar(83);
                    LCD_PutcharColor(0x0000,0xFFFF);
                }
                
                if( korY>165) {
                 if(korX>190){for(sepp=0;sepp<25;sepp++){tempH[sepp]=tempH[sepp]+5;};} //+0.5
                 if(korX<170){for(sepp=0;sepp<25;sepp++){tempH[sepp]=tempH[sepp]-5;};}     //-0.5
                 delay_ms(500);
                 
                 
                    LCD_ClearH(0x0000); 
                    
                       LCD_PutcharColor(0x9199,0x0000);
                    kelly (100, 40, 200, 167,0x9199);  LCD_PutcharKor(230,177,3); LCD_Putchar(82);  
                    kelly (100, 40, 50,  167,0x9199);  LCD_PutcharKor(90,177,3); LCD_Putchar(83);
                    LCD_PutcharColor(0x0000,0xFFFF);
                 
                        for (x=0;x<287;x++) {   y=tempH[x/12];  y=(y-170)*2;  f2=tempH[(x/12)+1];  f2=(f2-170)*2;    //чтение из массива и вывод кусочков прямой на экран
                    point(3,x+24,y+15,0xFFE0) ;
                   if(x%12==11){
                    // point(4,x+20,y+15,0xFFFF) ;
                   if(y>f2){for (s1=y; s1>f2; s1--)     {  point(3,x+25,s1+15,0xFFE0); };       };
                   if(y<f2){for (s1=y; s1<f2; s1++)     {  point(3,x+25,s1+15,0xFFE0); };       };
                
                
                   };
               
                 };  
                  
                 
                 
                   out=0;
                 
                 
                }  
               
                                                              
            if(korX>20 && korX<308 && korY>15 && korY<160){           //запись в массив
            point(2,korX, korY ,0x07E0 );                //и в месте касание вывести точку
             tempH[(korX-20)/12]= (korY-15)/2+170;
                delay_ms(20) ;out=0;
             }
            
           }      
         
             
         
              
          
           if(MODE==5){                                       //    если нажата вторая кнопка и ЕСТЬ касание 
           razovo++;                                   // только 1 раз вывести текст
             if (razovo==1){
            razovo=7;
             LCD_ClearT(0x0000);
            LCD_PutcharKor(190,215,2);                                                     //вывести текст о режиме
            LCD_Putchar(24);   LCD_Putchar(43); LCD_Putchar(60); LCD_Putchar(61); LCD_Putchar(59); LCD_Putchar(57);   //"Настройки"
            LCD_Putchar(52);  LCD_Putchar(53);LCD_Putchar(51);
             LCD_ClearH(0x0000) ; //очистка центра
                
                             LCD_PutcharColor(0x9199,0x0000);
                      
                      kelly (50, 20, 255, 150,0x9199);  LCD_PutcharKor(270,152,2); LCD_Putchar(82);   LCD_Putchar(1);  //уставка временни
                      kelly (50, 20, 255, 105,0x9199);  LCD_PutcharKor(270,107,2); LCD_Putchar(83);   LCD_Putchar(1);
                      kelly (50, 20, 255, 77, 0x9199);  LCD_PutcharKor(270,79,2); LCD_Putchar(82);   LCD_Putchar(1);
                      kelly (50, 20, 255, 25, 0x9199);  LCD_PutcharKor(270,27,2); LCD_Putchar(83);   LCD_Putchar(1);

                      kelly (60, 20, 159, 150,0x9199);  LCD_PutcharKor(165,152,2); LCD_Putchar(82);   LCD_Putchar(0); LCD_Putchar(77); LCD_Putchar(1);  //уставка дельты 
                      kelly (60, 20, 159, 105,0x9199);  LCD_PutcharKor(165,107,2); LCD_Putchar(83);   LCD_Putchar(0); LCD_Putchar(77); LCD_Putchar(1);
                      kelly (60, 20, 159, 77, 0x9199);  LCD_PutcharKor(161,79,2); LCD_Putchar(1);LCD_Putchar(0);LCD_Putchar(0);   LCD_Putchar(76);   // уставка яркости
                      kelly (60, 20, 159, 25, 0x9199);  LCD_PutcharKor(161,27,2); LCD_Putchar(5);  LCD_Putchar(0); LCD_Putchar(76);
                      
                      kelly (100, 20, 40, 25,0x9199);   LCD_PutcharKor(65,27,2); LCD_Putchar(27);   LCD_Putchar(16); LCD_Putchar(28); LCD_Putchar(16); LCD_Putchar(29);  //РЕСЕТ              
               
                     kelly (100, 20, 40, 52,0x9199);   LCD_PutcharKor(57,54,2); LCD_Putchar(27);   LCD_Putchar(16); LCD_Putchar(83); LCD_Putchar(26); LCD_Putchar(18); LCD_Putchar(30);  //очистить EEPROM         
            
              LCD_PutcharColor(0x0000,0xFFFF);    
               
                LCD_PutcharKor(255,183,2); LCD_Putchar(13);   LCD_Putchar(59); LCD_Putchar(48); LCD_Putchar(55); LCD_Putchar(74);//время
                LCD_PutcharKor(257,130,2); LCD_Putchar(34);   LCD_Putchar(43); LCD_Putchar(60); LCD_Putchar(70); //часы
                LCD_PutcharKor(250,55,2); LCD_Putchar(23);   LCD_Putchar(51); LCD_Putchar(56); LCD_Putchar(62);  LCD_Putchar(61); LCD_Putchar(70);//минуты
                
                LCD_PutcharKor(157,130,2);   LCD_Putchar(15);   LCD_Putchar(48); LCD_Putchar(54); LCD_Putchar(71); LCD_Putchar(61); LCD_Putchar(43);//дельта
                LCD_PutcharKor(155,55,2); LCD_Putchar(42);   LCD_Putchar(59); LCD_Putchar(53); LCD_Putchar(57); LCD_Putchar(60); LCD_Putchar(61); LCD_Putchar(71); //яркость
               // LCD_PutcharKor(150,55,2); LCD_Putchar(23);   LCD_Putchar(51); LCD_Putchar(56); LCD_Putchar(62);  LCD_Putchar(61); LCD_Putchar(70);//минуты
                  
              LCD_PutcharKor(195,180,2);
             LCD_Putchar(ds1820_devices);   //удалить(число датчиков)
            
                
                
               
                
            }
                                                             
             if( korX>250){   
               
                 rtc_get_time( &hour, &minute,&second);
                  delay_ms(2);
             if(hour>30){rtc_get_time( &hour, &minute,&second);};
                   
               if(korY>140)              {hour++;   if (hour>23)  {hour=23;  }};
               if(korY>100 && korY<125)  {hour--;   if (hour>30)   {hour=0;   }};
               if(korY>70 && korY<100 )   {minute++; if (minute>59){minute=59;}};
               if(korY<50 )               {minute--; if (minute>70) {minute=0; }};
               
                rtc_set_time(hour,minute,00);      //установить  время
               del60=99;
             };   
            
               if( korX>150 && korX<220){   

               if(korY>140)              {   delta++; if(delta>20){delta=20;}};
               if(korY>100 && korY<125)  {  delta--; if(delta<2){delta=2;}};
               if(korY>70 && korY<100 )   {LED=1;};
               if(korY<50 )               {LED=0;};
 
               del60=99;
             };    
            
              if(korX>15 && korX<150) {     
               if( korY<45 ){PORTA.7=0; DDRA.7=1; } 
               if( korY>50 && korY<75 ){for(sepp=0; sepp<145; sepp++){   temUepp[sepp]=tempU; }; MODE=4;} 
             
             }
           }          
          }           //конец обработки действий при нажатии
          
          if(razovo>15){razovo=10;};
          if(MODE==2){out++; if(out>900){out=0; MODE=1;   razovo=0;}}
          
               
                
          
          
          
          
          
          
          
          
          
          
          
             
           
           if(MODE==3){                                       //    если нажата третья кнопка режим графика улицы 
           razovo++;                                   // только 1 раз вывести текст
         
            if (razovo==1){
             razovo=7;   
                /*
             MODEm++; if(MODEm>1){MODEm=0;
               
                if( timDpU==1){  timDpU=0;     //если новое значение
                    LCD_ClearH(fon) ;
                  
          
                 LCD_PutcharKor(255,200,2); 
                 LCD_PutK(1);  
               
                 
                   if(tempU>=500){
                LCD_PutcharKor(25,140,2);               // вывод температуры улицы
                if (tempU>99) {LCD_PutM(tU1); }
                 LCD_PutM(tU2);
                LCD_PutM(13);  
                LCD_PutM(tU3);}else{
                  LCD_PutcharKor(25,140,1); 
                 LCD_PutM(11);
                 LCD_PutM(tU1);
                 LCD_PutM(tU2);
                LCD_PutM(13);  
                LCD_PutM(tU3);
                }
                 
               }
               
                  
               }
               
                     */
               
               
           
                       
               //      if(MODEm==1)   {
               
               
               
                 
                  MasMax=0;
                  MasMin=9999;
                 for(itt=0;itt<144; itt++){                                                          //нахождение мин и мах в массиве
                  if (temU[itt]>MasMax) {MasMax=temU[itt];};
                  if (temU[itt]<MasMin) {MasMin=temU[itt];};
                  }
                LCD_Clear(0x0000);                                                                                                                       //цыет половски времени
                 for (y=0;y<319;y++) {   if (y>23){ point(2,y,15,0x001F) ; point(3,y,210,0x001F);} if (y<210 && y>15){point(2,23,y,0x001F);point(1,(timeStep*2)+25,y,0xFCA0 ); } };  //вывод трех полосочек
                    LCD_PutcharKor(30,190,1);
                if(MasMax>=500){    x1=(MasMax-500)/100;  x2=((MasMax-500)%100)/10;  x3=(MasMax-500)%10;  } else{ x1=(500-MasMax)/100;  x2=((500-MasMax)%100)/10;  x3=(500-MasMax)%10; LCD_Putchar(83);}                                //  вычисление MIN и MAX вывод на дисплей
                     LCD_PutcharColor(0x0000,0xFFFF); LCD_Putchar(x1); LCD_Putchar(x2);LCD_Putchar(81); LCD_Putchar(x3);
                  LCD_PutcharKor(30,180,1);
                if(MasMin>=500){    y1=(MasMin-500)/100;  x2=((MasMin-500)%100)/10;   y3=(MasMin-500)%10; }  else {y1=(500-MasMin)/100;  y2=((500-MasMin)%100)/10;   y3=(500-MasMin)%10; LCD_Putchar(83);}
                     LCD_Putchar(y1);  LCD_Putchar(y2); LCD_Putchar(81);  LCD_Putchar(y3);
                 
                
                
               Pazmah= MasMax-MasMin;
               if(Pazmah<15){MasMax=MasMax+15; MasMin=MasMin-15;Pazmah= MasMax-MasMin;}
               if(Pazmah>14){MasMax=MasMax+1; MasMin=MasMin-1;Pazmah= MasMax-MasMin;}  
                 if(Pazmah<170){Ntim=Pazmah/10;mnoz=1;}   
                if(Pazmah>169 && Pazmah<340){Ntim=Pazmah/20;mnoz=2;}
                if(Pazmah>339){Ntim=Pazmah/30;mnoz=3;}  
                  
                        
                LCD_PutcharColor(0x0000,0xFFFF);    //вывод надписей  температуры
                for(y=0; y<=Ntim; y++) {
                LCD_PutcharKor(1,14+y*(190/Ntim),1);     //зазор от 12 не более 17 до 24это не более8
                 
                 vivA=(y*mnoz)+(MasMin/10);
                 if(vivA>=50){vivB=vivA-50;}
                 if(vivA<50){vivB=50-vivA;   LCD_Putchar(83);} 
                 b=vivB/10; c=vivB%10;
             //   LCD_Putchar(83);
                   LCD_Putchar(b); LCD_Putchar(c);  }
                  
                
                 for(y=0; y<26; y=y+2) {   LCD_PutcharKor((y*12)+15,3,1); b=y/10;  c=y%10; LCD_Putchar(b); LCD_Putchar(c);}  //вывод надписей времени 
                     //  del60=99;
                LCD_PutcharKor(255,200,2);  LCD_PutK(1);              // вывод значка улицы
                 
               
               
             
                  
               for (x=0;x<145;x++) { 
                                                                                          
    
                                                                                 
                 y=temU[x];  y=(y-MasMin)*(190/Pazmah);                                       //чтение из массива улицы и точек на экран

                point(2,(x*2)+25,y+17,0x1FE0) ;
                
                f2=temU[x+1];  f2=(f2-MasMin)*(190/Pazmah);  
                //if(x%2==1){
                
                 if(y>f2 && x<143){for (s1=y; s1>f2; s1--)     {  point(2,(x*2)+25,s1+17,0x1FE0); };       };
                 if(y<f2 && x<143){for (s1=y; s1<f2; s1++)     {  point(2,(x*2)+25,s1+17,0x1FE0); };       };
                    
               // };
               }; 
               
               
               
               
               
            //  }
             del60=100; 
              }
           }      
          
          
            
            
          
          
          
          
          
          
          
          
          
          
          
          
           
           if(MODE==1){                           // самый низ, Температура график дома
           
           
          
           
                                                 //    если первый режим
           razovo++;                                   // только 1 раз вывести текст
            if (razovo==1){ 
                LCD_Clear(0x0000); 
               LCD_ClearH(0x0000); 
            LCD_PutcharColor(0x0000,0xFFFF);for(y=0; y<10; y++) {  LCD_PutcharKor(3,12+y*20,1); b=(y+17)/10;   c=(y+17)%10;  LCD_Putchar(b); LCD_Putchar(c); }   //вывод надписей  температуры
              for(y=0; y<26; y=y+2) {LCD_PutcharKor((y*12)+15,3,1); b=y/10; c=y%10; LCD_Putchar(b); LCD_Putchar(c);   }                    //вывод надписей и времени 
                  for (y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
          
            
            
                                     
              razovo=7; 
              
              //MODEr++; if(MODEr>1){MODEr=0;
            
                    
               for (x=0;x<287;x++) {   y=tempH[x/12];  y=(y-170)*2;  f2=tempH[(x/12)+1];  f2=(f2-170)*2;    //чтение из массива и вывод кусочков прямой на экран
                point(3,x+24,y+15,0xFFE0) ;
                if(x%12==11){
                 // point(4,x+20,y+15,0xFFFF) ;
                 if(y>f2){for (s1=y; s1>f2; s1--)     {  point(3,x+25,s1+15,0xFFE0); };       };
                 if(y<f2){for (s1=y; s1<f2; s1++)     {  point(3,x+25,s1+15,0xFFE0); };       };
                };
               };         
           
               
                 
              //  }
               del60=100; 
             }
             
                 /*
                     if(MODEr==1)   {
                if( timDp==1){  timDp=0; 
                
               //     LCD_Clear(0x0000); 
              LCD_ClearH(0x0000); 
       //   LCD_PutcharColor(0x0000,0xFFFF);for(y=0; y<10; y++) {  LCD_PutcharKor(3,12+y*20,1); b=(y+17)/10;   c=(y+17)%10;  LCD_Putchar(b); LCD_Putchar(c); }   //вывод надписей  температуры
  for(y=0; y<26; y=y+2) {LCD_PutcharKor((y*12)+15,3,1); b=y/10; c=y%10; LCD_Putchar(b); LCD_Putchar(c);   }                    //вывод надписей и времени 
                  for (y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
          
            
                
                
                   // LCD_ClearH(fon) ;
              //  LCD_ClearT(fon) ;
                 LCD_PutcharKor(255,200,2); 
                 LCD_PutK(0);  
               
                  LCD_PutcharKor(25,140,2);               // вывод температуры дома
              
                LCD_PutM(tD1);
                 LCD_PutM(tD2);
                 LCD_PutM(13);  
                LCD_PutM(tD3);
                
                 
                    }
              } 
            //  del60=999;
                 
            
        
           
           
           
              */
          }
           
           if(MODE==4){                 //часы
           
           
          
           
                                                 //    если  режим
           razovo++;                                   // только 1 раз вывести текст
            if (razovo<3){  razovo=7; 
                LCD_Clear(0x0000); 
               LCD_ClearH(0x0000); 
             LCD_PutcharColor(0x0000,0xFFFF);for(y=0; y<10; y++) {  LCD_PutcharKor(3,12+y*20,1); b=(y+17)/10;   c=(y+17)%10;  LCD_Putchar(b); LCD_Putchar(c); }   //вывод надписей  температуры
              for(y=0; y<26; y=y+2) {LCD_PutcharKor((y*12)+15,3,1); b=y/10; c=y%10; LCD_Putchar(b); LCD_Putchar(c);   }                    //вывод надписей и времени 
                  for (y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
          
      
                  
             
                 
                    
                  LCD_PutcharKor(25,140,1);               // вывод температуры дома
              
                LCD_PutM(hour/10);
                 LCD_PutM(hour%10);
                 LCD_PutM(12);  
                LCD_PutM(minute/10);
                LCD_PutM(minute%10);
                
               
              
               
            del60=100;   
               
             }
             
             
             } 
                 
     
           
           if(MODE==7){                 //циферки
           
           
          
           
                                                 //    если  режим
           razovo++;                                   // только 1 раз вывести текст
            if (razovo<3){  razovo=7; 
                LCD_Clear(0x0000); 
               LCD_ClearH(0x0000); 
             LCD_PutcharColor(0x0000,0xFFFF);for(y=0; y<10; y++) {  LCD_PutcharKor(3,12+y*20,1); b=(y+17)/10;   c=(y+17)%10;  LCD_Putchar(b); LCD_Putchar(c); }   //вывод надписей  температуры
              for(y=0; y<26; y=y+2) {LCD_PutcharKor((y*12)+15,3,1); b=y/10; c=y%10; LCD_Putchar(b); LCD_Putchar(c);   }                    //вывод надписей и времени 
                  for (y=0;y<319;y++) {  point(3,y,210,0x001F) ; if (y>23){ point(2,y,15,0x001F) ;} if (y<210 && y>15){point(2,23,y,0x001F); } };  //вывод трех полосочек 
               
              
              
      
                  
               
               
               
              
            del60=100;   
               
             }
             
              
             
                                 if( timDpU==1){  timDpU=0;     //если новое значение
                   // LCD_ClearH(fon) ;
                  
                     LCD_PutcharH (1);  //ключение низкого шрифта
                // LCD_PutcharKor(255,200,2);   картинка улицы
                 //LCD_PutK(1);  
                
                 
                   if(tempU>=500){
                LCD_PutcharKor(25,80,1);               // вывод температуры улицы
                if (tempU>99) {LCD_PutM(tU1); }
                 LCD_PutM(tU2);
                LCD_PutM(13);  
                LCD_PutM(tU3);}else{
                  LCD_PutcharKor(25,140,1); 
                 LCD_PutM(11);
                 LCD_PutM(tU1);
                 LCD_PutM(tU2);
                LCD_PutM(13);  
                LCD_PutM(tU3);
                 LCD_PutcharH (0);  //кылючение низкого шрифта 
                }
                 
               }
               
               
                  if( timDp==1){  timDp=0; 
                    LCD_PutcharH (1);  //ключение низкого шрифта
                  LCD_PutcharKor(25,180,1);               // вывод температуры дома
              
                LCD_PutM(tD1);
                 LCD_PutM(tD2);
                 LCD_PutM(13);  
                LCD_PutM(tD3);
                 LCD_PutcharH (0);  //кылючение низкого шрифта 
                }
               
               
             
             
             } 
                   
           
           
           
           
           
           
          
     
          
 };
}
