#ifndef __74HC595_H
#define __74HC595_H

#include "stm32f10x.h"
#include "sys.h"

#define srclk   PBout(5)
#define rclk    PBout(6)
#define ser     PBout(7)

extern u8 num;
extern u8 dig_buff1, dig_buff2, dig_buff3, dig_buff4,         //每一位显示的缓冲，由中断发送
          dig_buff5, dig_buff6, dig_buff7, dig_buff8;

void GPIO_Configuration_74HC595(void);      //74HC595端口配置
void disp_num3(u32 num);                    //在显示板的上面4位大数码管
void disp_num4(u32 num);                    //在显示板的下面4位小数码管
void sao_miao_xian_shi(void);               //扫描数码管

#endif

