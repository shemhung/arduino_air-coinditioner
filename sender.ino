#include <IRremote.h> // >v3.0.0
#include <SimpleDHT.h> 
SimpleDHT11 dht11; 
int pinDHT11 = 2;                                          
int buzzPin =7;
int waterpin=A0;
int water_val=0;
void setup(){
  Serial.begin(9600);   
  pinMode(buzzPin, OUTPUT);
  digitalWrite(buzzPin, HIGH);  //有源蜂鳴器關閉 
}

void loop()                     
{
   byte temperature = 0;
   byte humidity = 0;
   int err = SimpleDHTErrSuccess;
   // start working...
   Serial.println("=================================");
   if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
      return;
   }
   water_val = analogRead(waterpin);
   Serial.print("Humidity = ");   
   Serial.print((int)humidity);   
   Serial.print("% , ");   
   Serial.print("Temperature = ");
   Serial.print((int)temperature);
   Serial.print("C ");//ln
   Serial.print(" , val = "); // 串口输出 val 当前的数据
   Serial.print(water_val); 
   if(water_val < 280)  
    Serial.println(" | dry"); 
   else if(water_val < 510) 
    Serial.println(" | water level: ~ 0-0.5 cm"); // 水位大约在0-1cm ，以下语句如此类推
   else if(water_val < 570) 
    Serial.println(" | water level: ~ 0.5-1 cm");
   else if(water_val < 630) 
    Serial.println(" | water level: ~ 1-1.5 cm");
   else if(water_val < 690) 
    Serial.println(" | water level: ~ 1.5-2 cm");
   else
    Serial.println(" | water level: over 2 cm");
   if(int(temperature)>=29 || int(humidity)>=68 || water_val>=690 ){
     digitalWrite(buzzPin, LOW);//有源蜂鳴器響起
   }
   else{
     digitalWrite(buzzPin, HIGH);  //有源蜂鳴器關閉
   }
   delay(3000);  //每3秒顯示一次
     
}
