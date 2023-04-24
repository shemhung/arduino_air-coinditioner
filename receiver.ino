#include <IRremote.h>
int light=5 ;
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(RECV_PIN, INPUT); 
  pinMode(light, OUTPUT);
  Serial.println("IR remote Initial completed");
}

void loop(){
  //IrSender.sendNEC(0xAE6AE573,32);
  
  if (irrecv.decode(&results)){
        Serial.print("results value in HEX is "); 
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
  if(results.value == 0xFFA25D){  //如果按下遙控器的特定鍵，就顯示訊息！
        Serial.println("Turn On!");//亮三下
        digitalWrite(5, HIGH);
        delay(500);
        digitalWrite(5, LOW);
        delay(500);
        digitalWrite(5, HIGH);
        delay(500);
        digitalWrite(5, LOW);
        delay(500);
        digitalWrite(5, HIGH);
        delay(500);
        digitalWrite(5, LOW);
        delay(500);
  }
  else if(results.value == 0xFF){
        Serial.println("Turn off!");//快速亮兩下
        digitalWrite(5, HIGH);
        delay(200);
        digitalWrite(5, LOW);
        delay(200);
        digitalWrite(5, HIGH);
        delay(200);
        digitalWrite(5, LOW);
        delay(200);
  }
  

  else if(results.value == 0xFFE01F){
   
        Serial.println("temperture up!");
        digitalWrite(5, HIGH);         //正常亮暗   
        delay(500);
        digitalWrite(5, LOW);
  }
  else if(results.value == 0xFF12345){
   
        Serial.println("tempurture down!");
        digitalWrite(5, HIGH);            //正常亮暗
        delay(500);
        digitalWrite(5, LOW);
  }
  else
    digitalWrite(5, LOW);                 
  delay(2000);
}
