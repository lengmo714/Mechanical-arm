#include "74HC595.h"

//code unsigned char seg[16] = {
//                   0x28,0xeb,0x32,0xa2,//0,1,2,3,
//                   0xe1,0xa4,0x24,0xea,//4,5,6,7,
//                   0x20,0xa0,0xff,0x70,//8,9,空,P,             10空  11P  12-  13E
//                   0xf7,0x34,0x34,0x71 //-,E, , ,
//                             };

const u8 seg[13] = {
                   0x28,0xeb,0x32,0xa2, //0,1,2,3,
                   0xe1,0xa4,0x24,0xea, //4,5,6,7,
                   0x20,0xa0,0xf7,0xdf, //8,9,-,.,
                   0xff                 //空
                             };

u8 disp_buff[2];        //定义缓存
u8 dig_buff1=1, dig_buff2=2, dig_buff3=3, dig_buff4=4,         //每一位显示的缓冲，由中断发送
   dig_buff5=5, dig_buff6=6, dig_buff7=7, dig_buff8=8;

u8 num = 1;


void GPIO_Configuration_74HC595(void) //74HC595端口配置
{
	GPIO_InitTypeDef   GPIO_InitStructure;   //定义名为GPIO_InitStructure的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //打开GPIOB的时钟，并使能。
	
	//配置PB口：
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;              //选定哪个IO口 现选定PB567口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		             //设定IO口的模式为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	                 //设定IO口的输出速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	                             //初始化GPIOB
}

void buff_to_595(void)     //缓冲区
{
   u8 char_seg;     //待显示数码管的数值
   char i;
   rclk=0;

      char_seg=disp_buff[1];   //595高8位，用于控制位
      for(i=0;i<8;i++)         //把单片机内的数值转换为串行数据传送给595，由595自动再将串行转并行
      {
         srclk=0;
         ser=char_seg&0x01;        //先发缓冲低位
         srclk=1;
         char_seg=char_seg>>1;
      }

      char_seg=disp_buff[0];   //595低8位用于控制段
      for(i=0;i<8;i++)         //把单片机内的数值转换为串行数据传送给595，由595自动再将串行转并行
      {
         srclk=0;
         ser=char_seg&0x01;       //先发缓冲低位
         srclk=1;
         char_seg=char_seg>>1;
      }

   rclk=1;      //发送595里面的数值给数码管显示
}

void disp_bit(unsigned char num, unsigned char dig)   //位显示，要显示的字符num在第dig位
{
   switch(dig)
   {
       case 1:   disp_buff[1]=0xfb;    break;
       case 2:   disp_buff[1]=0xfd;    break;
       case 3:   disp_buff[1]=0xfe;    break;
       case 4:   disp_buff[1]=0xf7;    break;
       case 5:   disp_buff[1]=0xef;    break;
       case 6:   disp_buff[1]=0xdf;    break;
       case 7:   disp_buff[1]=0xbf;    break;
       case 8:   disp_buff[1]=0x7f;    break;
       default: break;
   }

   disp_buff[0]=seg[num];
   buff_to_595();
}


void disp_num3(u32 num)  //在显示板的上面4位大数码管
{
    dig_buff1=num/1000%10; dig_buff2=num/100%10; dig_buff3=num/10%10; dig_buff4=num%10;
    //dig_buff2=num/100%10;dig_buff3=num/10%10; dig_buff4=num%10;
}

void disp_num4(u32 num)  //在显示板的下面4位小数码管
{
    dig_buff5=num/1000%10; dig_buff6=num/100%10; dig_buff7=num/10%10; dig_buff8=num%10;
}


void sao_miao_xian_shi(void)
{
    switch(num)         //按位扫描数码管
    {
        case 1:  disp_bit(dig_buff1, 1);        break;
        case 2:  disp_bit(dig_buff2, 2);        break;
        case 3:  disp_bit(dig_buff3, 3);        break;
        case 4:  disp_bit(dig_buff4, 4);        break;
        case 5:  disp_bit(dig_buff5, 5);        break;
        case 6:  disp_bit(dig_buff6, 6);        break;
        case 7:  disp_bit(dig_buff7, 7);        break;
        case 8:  disp_bit(dig_buff8, 8);        break;
        default:  break;
    }

    num ++;
    if(num > 8)
    {
        num = 1;
    }
}

