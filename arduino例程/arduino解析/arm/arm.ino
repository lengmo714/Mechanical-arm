

unsigned char Re_buf[15],counter=0;
unsigned char sign=0;
float a[3],w[3],angle[3],T;
void setup() {
  // initialize serial:
  Serial.begin(115200);
  
  delay(1000);
  Serial.write(0xcc);

   
}

void loop() {
  if(sign)
  {  
     sign=0;
     if(Re_buf[0]==0x55&&Re_buf[1]==0x53)      //检查帧头
     {  
      angle[0] = (short(Re_buf [3]<<8| Re_buf [2]))/32768.0*180;
	   	angle[1] = (short(Re_buf [5]<<8| Re_buf [4]))/32768.0*180;
	    angle[2] = (short(Re_buf [7]<<8| Re_buf [6]))/32768.0*180;
	                      
                Serial.print("angle:");//角度
                Serial.print(angle[0]);Serial.print(" ");
                Serial.print(angle[1]);Serial.print(" ");
                Serial.print(angle[2]);Serial.print(" ");
        
    }
    
    if(Re_buf[8]==0xaa)
    {
 
       Serial.print(Re_buf [1]);//手指1
       Serial.print(Re_buf [2]);//手指2
       Serial.print(Re_buf [3]);//手指3
       Serial.print(Re_buf [4]);//手指4
       Serial.print(Re_buf [5]);//手指5
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


