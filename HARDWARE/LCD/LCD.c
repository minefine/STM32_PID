#include "LCD.h"

#include "stm32f4xx.h"

#include "delay.h"

//向SPI总线传输一个8位数据
void  SPI_WriteData(unsigned char Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
		LCD_SDA=1; //输出数据
		else LCD_SDA=0;
		LCD_SCL=0;
		LCD_SCL=1;
		Data<<=1;
	}
}

//复位
void Reset(void)
{
    LCD_RST=0;
    delay_ms(100);
    LCD_RST=1;
    delay_ms(100);
}


//向液晶屏写一个8位指令
void  Lcd_WriteIndex(unsigned char Data)
{
		
		LCD_CS=0;
		LCD_RS=0;
		SPI_WriteData(Data); 		
		LCD_CS=1;
}

//向液晶屏写一个8位数据
void  Lcd_WriteData(unsigned char Data)
{	
		//unsigned char i=0;
		LCD_CS=0;
		LCD_RS=1;
		SPI_WriteData(Data); 	
		LCD_CS=1;
}

//向液晶屏写一个16位数据
void  LCD_WriteData_16Bit(unsigned int Data)
{
	//unsigned char i=0;
	LCD_CS=0;
	LCD_RS=1;
	SPI_WriteData(Data>>8); 	//写入高8位数据
	SPI_WriteData(Data); 			//写入低8位数据
	LCD_CS=1;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//液晶屏初始化 for S6D02A1   厂家提供
void lcd_initial(void)
{	Reset();//Reset before LCD Init.
		
	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
#ifdef USE_LANDSCAPE
	Lcd_WriteData(0xA8); //竖屏C8 横屏08 A8
#else
	Lcd_WriteData(0xC8); //竖屏C8 横屏08 A8
#endif		
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x80+3);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on

}


/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	
#ifdef USE_LANDSCAPE//使用横屏模式
	Lcd_WriteIndex(0x2a);  //输入列地址
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+3);

	Lcd_WriteIndex(0x2b); //输入行地址
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+2);

#else//竖屏模式	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+3);	
#endif
	Lcd_WriteIndex(0x2c);//写内存
}

void dsp_single_colour(int color)
{
 	unsigned char i,j;
	Lcd_SetRegion(0,0,128-1,128-1);
 	for (i=0;i<128;i++)
    	for (j=0;j<128;j++)
        	LCD_WriteData_16Bit(color);
}

//取模方式 水平扫描 从左到右 低位在前
void showimage(const unsigned char *p) //显示40*40 QQ图片
{
  	int i,j,k; 
	unsigned char picH,picL;
	dsp_single_colour(WHITE); //清屏  
	
	for(k=0;k<3;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}

void showimage1(const unsigned char *p) //显示128*127 dog图片
{
  	int i; 
	unsigned char picH,picL;
	dsp_single_colour(WHITE); //清屏  
	
		      Lcd_SetRegion(0,0,128-1,128-1);		//坐标设置
		    for(i=0;i<128*127;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }			
}


//采用设置窗口方法填充字库数据，相比Gui_DrawFont_GBK16更快速
void Fast_DrawFont_GBK16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc, unsigned char *s)
{
	unsigned char i,j;
	Lcd_SetRegion(x,y,x+40-1,y+40-1);
	
				    for(i=0;i<200;i++)
				    {
						for(j=0;j<8;j++)
				    	{
							if(s[i]&(0x80>>j))	
								LCD_WriteData_16Bit(fc);
							else 
							{
							if (fc!=bc)
								LCD_WriteData_16Bit(bc);
							}
						}
	}
}

/*画点*/
void huadian(int X,int Y)
{
	unsigned char i;
	
  Lcd_SetRegion(X,Y,X+2,Y);
	
	for(i=0;i<2;i++)
	{
	   LCD_WriteData_16Bit(WHITE);
	}
	
}




/*显示坐标轴*/
void XY_show(void)
{
	unsigned char i,j;
   Lcd_SetRegion(0,80,1,128); //列
	
	 for(i=0;i<2;i++)   
	  for(j=0;j<48;j++)
	     LCD_WriteData_16Bit(WHITE);
	
	Lcd_SetRegion(0,126,128,128);//行
	for(i=0;i<2;i++)
	  for(j=0;j<129;j++)
	     LCD_WriteData_16Bit(WHITE);
	
}


extern float set_speed;
static int X=0,Y=0,set_Y=0;

/*折线图*/
void ZXT(float speed)
{ 
	 unsigned char i,j;
	 static int Last_y=0;
	 //int ki;
	
   X+=2;
	
	 if(X>128)
	 {  
	    X=2;
	 }
	 
	 Lcd_SetRegion(X,80,X+10,126); //中间间隔的地方
	 for(i=0;i<11;i++)
	   for(j=0;j<46;j++)
	     LCD_WriteData_16Bit(BLACK);
	
	 
	 if(speed>=0)
	 {
		 Y=80+24-((speed/8)*24);       //5为最高时候的速度  所以设置为8 画点  
	 }
	 else
	 {
	   Y=80+24+((-speed/8)*24); 
	 }
	 
	 	if(set_speed>=0)
	 {
 	   set_Y=80+24-((set_speed/8)*24);  
	 }
	 else
	 {
		 set_Y=80+24+((set_speed/8)*24);//计算设定速度线的位置
	 }
	 
	 Lcd_SetRegion(0,set_Y,128,set_Y+2);
	  for(i=0;i<128;i++)
	   LCD_WriteData_16Bit(RED);  //红线为设定的速度
	 
	 
	 
	  // ki=Last_y-Y;
	   

	 
	 /*if(ki!=0&&X>2)
	 {
		 if(ki<0)
		 {
			 ki=-ki;
	     Lcd_SetRegion(X-1,Last_y,X,Y);
		 }
		 else
			 Lcd_SetRegion(X-1,Y,X,Last_y); 
	   for(i=0;i<2*ki;i++)
	   LCD_WriteData_16Bit(WHITE);  
	 }*/
		 huadian(X,Y);
	 
    
	 
	 Lcd_SetRegion(0,103,128,104);  //零线
	 	for(i=0;i<128;i++)
	   for(j=0;j<2;j++)
	     LCD_WriteData_16Bit(WHITE);
	 
	 Last_y=Y;
}

void ZXT_QL(void) //坐标清零
{
  X=0;
	Y=0;
	set_Y=0;
}



