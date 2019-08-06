#include "printf.h"
#include "time_text.h"
#include "delay.h"

/*24����д��ĸ*/
char A[]={0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00};/*"A",0*/
char B[]={0x00,0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0xF8,0x00,0x00};/*"B",1*/
char C[]={0x00,0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00};/*"C",2*/
char D[]={0x00,0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00};/*"D",3*/
char E[]={0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x42,0x42,0xFC,0x00,0x00};/*"E",4*/
char F[]={0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x40,0x40,0xE0,0x00,0x00};/*"F",5*/
char G[]={0x00,0x00,0x00,0x3C,0x44,0x44,0x80,0x80,0x80,0x8E,0x84,0x44,0x44,0x38,0x00,0x00};/*"G",6*/
char H[]={0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00};/*"H",0*/
char I[]={0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00};/*"I",1*/
char J[]={0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0xF0};/*"J",2*/
char K[]={0x00,0x00,0x00,0xEE,0x44,0x48,0x50,0x70,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00};/*"K",3*/
char L[]={0x00,0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFE,0x00,0x00};/*"L",4*/
char M[]={0x00,0x00,0x00,0xEE,0x6C,0x6C,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x54,0xD6,0x00,0x00};/*"M",0*/
char N[]={0x00,0x00,0x00,0xC7,0x62,0x62,0x52,0x52,0x4A,0x4A,0x4A,0x46,0x46,0xE2,0x00,0x00};/*"N",1*/
char O[]={0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00};/*"O",2*/
char P[]={0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0xE0,0x00,0x00};/*"P",3*/
char Q[]={0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0xB2,0x4C,0x38,0x06,0x00};/*"Q",4*/
char R[]={0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x48,0x44,0x44,0x42,0xE3,0x00,0x00};/*"R",0*/
char S[]={0x00,0x00,0x00,0x3E,0x42,0x42,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x7C,0x00,0x00};/*"S",1*/
char T[]={0x00,0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00};/*"T",2*/
char U[]={0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00};/*"U",3*/
char V[]={0x00,0x00,0x00,0xE7,0x42,0x42,0x44,0x24,0x24,0x28,0x28,0x18,0x10,0x10,0x00,0x00};/*"V",4*/
char W[]={0x00,0x00,0x00,0xD6,0x54,0x54,0x54,0x54,0x54,0x6C,0x28,0x28,0x28,0x28,0x00,0x00};/*"W",5*/
char X[]={0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00};/*"X",6*/
char Y[]={0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00};/*"Y",7*/
char Z[]={0x00,0x00,0x00,0x7E,0x84,0x04,0x08,0x08,0x10,0x20,0x20,0x42,0x42,0xFC,0x00,0x00};/*"Z",8*/



char aa[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x0C,0x34,0x44,0x4C,0x36,0x00,0x00};/*"a",0*/
char bb[]={0x00,0x00,0x00,0x00,0xC0,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x00,0x00};/*"b",1*/
char cc[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x22,0x1C,0x00,0x00};/*"c",2*/
char dd[]={0x00,0x00,0x00,0x00,0x06,0x02,0x02,0x3E,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00};/*"d",3*/
char ee[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x7E,0x40,0x42,0x3C,0x00,0x00};/*"e",4*/
char ff[]={0x00,0x00,0x00,0x00,0x0C,0x12,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00};/*"f",5*/
char gg[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x38,0x40,0x3C,0x42,0x42,0x3C};/*"g",6*/
char hh[]={0x00,0x00,0x00,0x00,0xC0,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00};/*"h",7*/
char ii[]={0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00};/*"i",8*/
char jj[]={0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x1C,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x78};/*"j",9*/
char kk[]={0x00,0x00,0x00,0x00,0xC0,0x40,0x40,0x4E,0x48,0x50,0x70,0x48,0x44,0xEE,0x00,0x00};/*"k",10*/
char ll[]={0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00};/*"l",11*/
char mm[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00};/*"m",12*/
char nn[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00};/*"n",13*/
char oo[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00};/*"o",14*/
char pp[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x64,0x58,0x40,0xE0};/*"p",15*/
char qq[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x02,0x07};/*"q",16*/
char rr[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x32,0x20,0x20,0x20,0x20,0xF8,0x00,0x00};/*"r",17*/
char ss[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x40,0x3C,0x02,0x42,0x7C,0x00,0x00};/*"s",18*/
char tt[]={0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x12,0x0C,0x00,0x00};/*"t",19*/
char uu[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00};/*"u",20*/
char vv[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x00,0x00};/*"v",21*/
char ww[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDB,0x89,0x4A,0x5A,0x54,0x24,0x24,0x00,0x00};/*"w",22*/
char xx[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x24,0x18,0x18,0x18,0x24,0x6E,0x00,0x00};/*"x",23*/
char yy[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x10,0x10,0x60};/*"y",24*/
char zz[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x08,0x10,0x10,0x22,0x7E,0x00,0x00};/*"z",25*/




char A0[]={0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00};/*"0",0*/
char A1[]={0x00,0x00,0x00,0x08,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00};/*"1",0*/
char A2[]={0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x02,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00};/*"2",1*/
char A3[]={0x00,0x00,0x00,0x3C,0x42,0x42,0x02,0x04,0x18,0x04,0x02,0x42,0x42,0x3C,0x00,0x00};/*"3",2*/
char A4[]={0x00,0x00,0x00,0x04,0x0C,0x0C,0x14,0x24,0x24,0x44,0x7F,0x04,0x04,0x1F,0x00,0x00};/*"4",3*/
char A5[]={0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x78,0x44,0x02,0x02,0x42,0x44,0x38,0x00,0x00};/*"5",4*/
char A6[]={0x00,0x00,0x00,0x18,0x24,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x22,0x1C,0x00,0x00};/*"6",5*/
char A7[]={0x00,0x00,0x00,0x7E,0x42,0x04,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00};/*"7",6*/
char A8[]={0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00};/*"8",7*/
char A9[]={0x00,0x00,0x00,0x38,0x44,0x42,0x42,0x42,0x46,0x3A,0x02,0x02,0x24,0x18,0x00,0x00};/*"9",8*/
char A10[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00};/*".",0*/

char KONG[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*" ",0*/
char dou[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x20,0x20,0x40};/*",",0*/
char fen[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10};/*";",1*/
char xui[]={0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00};/*":",2*/
char fuhao[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"-",0*/
char xiao[]={0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00};/*"<",1*/
char da[]={0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00};/*">",2*/

static int x=0,y=0;

/*��������same_char     */
/*����:ʹ�������ַ���ƥ��*/
/*����ֵ��ָ��          */
char *same_char(char a) 
{
	static char *ying;
	
  switch(a)
	{
		case '0':ying = A0;break;
	  case '1':ying = A1;break;
		case '2':ying = A2;break;
		case '3':ying = A3;break;
		case '4':ying = A4;break;
		case '5':ying = A5;break;
		case '6':ying = A6;break;
		case '7':ying = A7;break;
		case '8':ying = A8;break;
		case '9':ying = A9;break;
	  case '.':ying = A10;break;
		case 'A':ying = A;break;
		case 'B':ying = B;break;
		case 'C':ying = C;break;
		case 'D':ying = D;break;
		case 'E':ying = E;break;
		case 'F':ying = F;break;
		case 'G':ying = G;break;
		case 'H':ying = H;break;
		case 'I':ying = I;break;
		case 'J':ying = J;break;
		case 'K':ying = K;break;
		case 'L':ying = L;break;
		case 'M':ying = M;break;
		case 'N':ying = N;break;
		case 'O':ying = O;break;
		case 'P':ying = P;break;
		case 'Q':ying = Q;break;
		case 'R':ying = R;break;
		case 'S':ying = S;break;
		case 'T':ying = T;break;
		case 'U':ying = U;break;
		case 'V':ying = V;break;
		case 'W':ying = W;break;
		case 'X':ying = X;break;
		case 'Y':ying = Y;break;
		case 'Z':ying = Z;break;
		case 'a':ying = aa;break;
		case 'b':ying = bb;break;
		case 'c':ying = cc;break;
		case 'd':ying = dd;break;
		case 'e':ying = ee;break;
		case 'f':ying = ff;break;
		case 'g':ying = gg;break;
		case 'h':ying = hh;break;
		case 'i':ying = ii;break;
		case 'j':ying = jj;break;
		case 'k':ying = kk;break;
		case 'l':ying = ll;break;
		case 'm':ying = mm;break;
		case 'n':ying = nn;break;
		case 'o':ying = oo;break;
		case 'p':ying = pp;break;
		case 'q':ying = qq;break;
		case 'r':ying = rr;break;
		case 's':ying = ss;break;
		case 't':ying = tt;break;
		case 'u':ying = uu;break;
		case 'v':ying = vv;break;
		case 'w':ying = ww;break;
		case 'x':ying = xx;break;
		case 'y':ying = yy;break;
		case 'z':ying = zz;break;
		case ' ':ying = KONG;break;
		case ';':ying = fen;break;
		case ',':ying = dou;break;
		case ':':ying = xui;break;
		case '-':ying = fuhao;break;
		case '>':ying = da;break;
		case '<':ying = xiao;break;
	} 
	
	return ying;
}

/*��������my_printf      */
/*���ܣ���ӡ�ַ�����ʾ����*/
/*�޷���ֵ               */
void  my_printf(char *s)
{
	char i,j;
	char *num;
	
	while((*s)!='\0')
	{
		if(*s!='\n'&&*s!='\b')
		{
	     Lcd_SetRegion(x,y,x+8-1,y+16-1);
		
		   num=same_char(*s);
		
			 for(i=0;i<16;i++)
				{
				  for(j=0;j<8;j++)
				   {
						  if(num[i]&(0x80>>j))	
							LCD_WriteData_16Bit(WHITE);
						  else 
							LCD_WriteData_16Bit(BLACK);

					 }
				 }
						
					x+=8;
   				s++;
				 
				 if(x>=128)
				 {
					 x=0;
				   y+=16;
				 }
				 
			}	
     else if(*s=='\n')
		 {
		   x=0;
			 y+=16;
			 s++;
		 }	
		 else if(*s=='\b')
		 {
		   x-=8;
			 if(x<=0)
			 {
			   x=120;
				 y-=16;
			 }
			 s++;
		 }
   	 
	}
	 //x=0;y=0;	
}

/*����һ��*/
void down_line(void)
{
  y+=16;
}

/*����һ��*/
void up_line(void)
{
  y-=16;
}

/*��������긴λ*/
void qingling(void)
{
	delay_ms(10);
  dsp_single_colour(BLACK);
	x=0;y=0;
}

/*��ʾ��ͷ*/
void show_arrow(void)
{
  x=112;
	y=0;
	my_printf("<-");
}

/*��ʾ�������õ�V*/
void show_v(void)
{
  x=32;
	y=0;
	my_printf("V");
}

/*�����ƶ�һ��*/
void left_move(void)
{
	x-=8;
	my_printf(" ");
  x-=8;
	x-=8;
	my_printf("V");
}

/*�����ƶ�һ��*/
void right_move(void)
{
	x-=8;
	my_printf(" ");
	my_printf("V");
}