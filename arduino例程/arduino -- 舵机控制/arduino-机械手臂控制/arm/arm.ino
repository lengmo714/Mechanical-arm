//
#include <Servo.h> 

int count=0;

Servo myservo2;                 
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;
Servo myservo9;
Servo myservo10;
Servo myservo11;

float L1,L2,L3,L4,L5;

int compare2 = 150;
int compare3 = 150;
int compare4 = 150;
int compare5 = 150;
int compare6 = 150;

bool flag = 0;
float anglere = 0;
float anglere1 = 0;
float anglere2 = 0;

unsigned char Re_buf[15],counter=0;
unsigned char sign=0;
float a[3],w[3],angle[3],T;
void setup() {
  // initialize serial:
  Serial.begin(115200);
  
 //pinMode(2, OUTPUT); 
 //pinMode(3, OUTPUT); 
 //pinMode(4, OUTPUT);
 //pinMode(5, OUTPUT);
 //pinMode(6, OUTPUT);
 //pinMode(7, OUTPUT);
 
//  myservo2.attach(2);
//  myservo3.attach(3);
//  myservo4.attach(4);
//  myservo5.attach(5);
//  myservo6.attach(6);
//  myservo7.attach(7);
myservo2.attach(2);
myservo3.attach(3);
myservo4.attach(4);
myservo5.attach(5);
myservo6.attach(6);
myservo7.attach(7);
myservo8.attach(8);
myservo9.attach(9);
myservo10.attach(10);
myservo11.attach(11);
 Serial.write(0xcc);  
  delay(1000);

   
}

void loop() {
  if(sign)
  {  
     sign=0;
     if(Re_buf[0]==0x55)      //检查帧头
     {  
	switch(Re_buf [1])
	{
	case 0x51:
		a[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*16;
		a[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*16;
		a[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*16;
		T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
		break;
	case 0x52:
		w[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*2000;
		w[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*2000;
		w[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*2000;
		T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
		break;
	case 0x53:
    angle[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*180;
		angle[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*180;
		angle[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*180;
		T = (short(Re_buf [9]<<8| Re_buf [8]))/340.0+36.25;
                break;         
                
	} 
    
                if(flag == 0)
             {
               flag = 1;
               anglere = angle[2];
               anglere1 = angle[1];
               anglere2 = angle[0];
               
             }
     
          if(angle[2] - anglere + 60 < 0)
          {
            angle[2]  = anglere - 60;
          }
          
          if(angle[2] - anglere + 60> 170)
          {
           angle[2]  = 160 + anglere - 60;
          }
          
          
          if(count >= 3)
          {
           count = 0;
          }
          
          if(count%2 == 0)
         {
         
          myservo2.write(angle[2] - anglere + 90); 
           myservo4.write( -0.5*angle[0] + 90 );
           myservo6.write( angle[1] + 110 );
          }
          else 
          {
            myservo3.write( 0.3*angle[0] + 90 );
            myservo5.write( -0.5*angle[0] + 90 );
            myservo6.write( angle[1] + 110 );
          }
          count ++;
        

     

    }
    
    if(Re_buf[8]==0xaa)
    {
    if(-Re_buf [9]+180>170)
   {
    myservo7.write(170);
   }else if(-Re_buf [9]+180<10)
   {
    myservo7.write(10);
   }else{
       myservo7.write(-Re_buf [9]+180);
   }
   if(-Re_buf [10]*4+575>170)
   {
    myservo8.write(170);
   }else if(-Re_buf [10]*4+575<10)
   {
    myservo8.write(10);
   }else
    {myservo8.write(-Re_buf [10]*4+575);}
   if(-Re_buf [11]+220>170)
   {
     myservo9.write(170);
   }else if(-Re_buf [11]+220<10)
   {
    myservo9.write(10);
   }else
   {
    myservo9.write(-Re_buf [11]+220);
   }
   if(Re_buf [12]-55>170)
   {
     myservo10.write(170);
   }else if(Re_buf [12]-55<10)
   {
     myservo10.write(10);
   }else{
       myservo10.write(Re_buf [12]-55);
   }
   if(-Re_buf [13]*3+485>170)
   {
     myservo11.write(170);
   }else if(-Re_buf [13]*3+485<10)
   {
    myservo11.write(10);
   }else
   {
       myservo11.write(-Re_buf [13]*3+485);
   }
   
    }

     
  } 
}

void serialEvent() {
  while (Serial.available()) {
    
    //char inChar = (char)Serial.read(); Serial.print(inChar); //Output Original Data, use this code 
  
    Re_buf[counter]=(unsigned char)Serial.read();
    if(counter==0&&Re_buf[0]!=0x55) return;      //第0号数据不是帧头              
    counter++;       
    if(counter==15)             //接收到11个数据
    {    
       counter=0;               //重新赋值，准备下一帧数据的接收 
       sign=1;
    }
      
  }
}


