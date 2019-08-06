#ifndef __LCD_H
#define __LCD_H	 

#define LCD_SCL  PFout(0)
#define LCD_SDA  PFout(1)
#define LCD_CS  PFout(2)
#define LCD_RS  PFout(3)
#define LCD_RST  PFout(4)

//定义常用颜色
#define RED  		0xf800
#define GREEN		0x07e0
#define BLUE 		0x001f
#define WHITE		0xffff
#define BLACK		0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   
#define GRAY1   0x8410      	
#define GRAY2   0x4208
#define ser     0x7FBF

void Reset(void);
void  SPI_WriteData(unsigned char Data);
void  Lcd_WriteIndex(unsigned char Data);
void  Lcd_WriteData(unsigned char Data);
void  LCD_WriteData_16Bit(unsigned int Data);
void lcd_initial(void);
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end);
void dsp_single_colour(int color);
void showimage(const unsigned char *p);
void showimage1(const unsigned char *p);
void Fast_DrawFont_GBK16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,unsigned char *s);
void XY_show(void);
void ZXT(float speed);
void huadian(int X,int Y);
void ZXT_QL(void) ;
#endif

