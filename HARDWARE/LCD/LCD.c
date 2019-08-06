#include "LCD.h"

#include "stm32f4xx.h"

#include "delay.h"

//��SPI���ߴ���һ��8λ����
void  SPI_WriteData(unsigned char Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
		if(Data&0x80)	
		LCD_SDA=1; //�������
		else LCD_SDA=0;
		LCD_SCL=0;
		LCD_SCL=1;
		Data<<=1;
	}
}

//��λ
void Reset(void)
{
    LCD_RST=0;
    delay_ms(100);
    LCD_RST=1;
    delay_ms(100);
}


//��Һ����дһ��8λָ��
void  Lcd_WriteIndex(unsigned char Data)
{
		
		LCD_CS=0;
		LCD_RS=0;
		SPI_WriteData(Data); 		
		LCD_CS=1;
}

//��Һ����дһ��8λ����
void  Lcd_WriteData(unsigned char Data)
{	
		//unsigned char i=0;
		LCD_CS=0;
		LCD_RS=1;
		SPI_WriteData(Data); 	
		LCD_CS=1;
}

//��Һ����дһ��16λ����
void  LCD_WriteData_16Bit(unsigned int Data)
{
	//unsigned char i=0;
	LCD_CS=0;
	LCD_RS=1;
	SPI_WriteData(Data>>8); 	//д���8λ����
	SPI_WriteData(Data); 			//д���8λ����
	LCD_CS=1;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//Һ������ʼ�� for S6D02A1   �����ṩ
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
	Lcd_WriteData(0xA8); //����C8 ����08 A8
#else
	Lcd_WriteData(0xC8); //����C8 ����08 A8
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
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
void Lcd_SetRegion(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	
#ifdef USE_LANDSCAPE//ʹ�ú���ģʽ
	Lcd_WriteIndex(0x2a);  //�����е�ַ
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+3);

	Lcd_WriteIndex(0x2b); //�����е�ַ
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+2);

#else//����ģʽ	
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
	Lcd_WriteIndex(0x2c);//д�ڴ�
}

void dsp_single_colour(int color)
{
 	unsigned char i,j;
	Lcd_SetRegion(0,0,128-1,128-1);
 	for (i=0;i<128;i++)
    	for (j=0;j<128;j++)
        	LCD_WriteData_16Bit(color);
}

//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void showimage(const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	int i,j,k; 
	unsigned char picH,picL;
	dsp_single_colour(WHITE); //����  
	
	for(k=0;k<3;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Lcd_SetRegion(40*j,40*k,40*j+39,40*k+39);		//��������
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}

void showimage1(const unsigned char *p) //��ʾ128*127 dogͼƬ
{
  	int i; 
	unsigned char picH,picL;
	dsp_single_colour(WHITE); //����  
	
		      Lcd_SetRegion(0,0,128-1,128-1);		//��������
		    for(i=0;i<128*127;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }			
}


//�������ô��ڷ�������ֿ����ݣ����Gui_DrawFont_GBK16������
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

/*����*/
void huadian(int X,int Y)
{
	unsigned char i;
	
  Lcd_SetRegion(X,Y,X+2,Y);
	
	for(i=0;i<2;i++)
	{
	   LCD_WriteData_16Bit(WHITE);
	}
	
}




/*��ʾ������*/
void XY_show(void)
{
	unsigned char i,j;
   Lcd_SetRegion(0,80,1,128); //��
	
	 for(i=0;i<2;i++)   
	  for(j=0;j<48;j++)
	     LCD_WriteData_16Bit(WHITE);
	
	Lcd_SetRegion(0,126,128,128);//��
	for(i=0;i<2;i++)
	  for(j=0;j<129;j++)
	     LCD_WriteData_16Bit(WHITE);
	
}


extern float set_speed;
static int X=0,Y=0,set_Y=0;

/*����ͼ*/
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
	 
	 Lcd_SetRegion(X,80,X+10,126); //�м����ĵط�
	 for(i=0;i<11;i++)
	   for(j=0;j<46;j++)
	     LCD_WriteData_16Bit(BLACK);
	
	 
	 if(speed>=0)
	 {
		 Y=80+24-((speed/8)*24);       //5Ϊ���ʱ����ٶ�  ��������Ϊ8 ����  
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
		 set_Y=80+24+((set_speed/8)*24);//�����趨�ٶ��ߵ�λ��
	 }
	 
	 Lcd_SetRegion(0,set_Y,128,set_Y+2);
	  for(i=0;i<128;i++)
	   LCD_WriteData_16Bit(RED);  //����Ϊ�趨���ٶ�
	 
	 
	 
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
	 
    
	 
	 Lcd_SetRegion(0,103,128,104);  //����
	 	for(i=0;i<128;i++)
	   for(j=0;j<2;j++)
	     LCD_WriteData_16Bit(WHITE);
	 
	 Last_y=Y;
}

void ZXT_QL(void) //��������
{
  X=0;
	Y=0;
	set_Y=0;
}



