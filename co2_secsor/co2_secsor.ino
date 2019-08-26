#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); // RX, TX
void retrievepm25(){
int count = 0;
long pmat10 = 0;
long pmat25 = 0;
long pmat100 = 0;
unsigned int temperature = 0;
unsigned int humandity = 0;

  unsigned char c;
  unsigned char high;
  while (ss.available()) { 
    c = ss.read();
    if((count==0 && c!=0x42) || (count==1 && c!=0x4d)){
      Serial.println("check failed");
      break;
    }
    if(count > 27){ 
      Serial.println("complete");
      break;
    }
     else if(count == 10 || count == 12 || count == 14 || count == 24 || count == 26) {
      high = c;
    }
    else if(count == 11){
      pmat10 = 256*high + c;
      Serial.print("PM1.0=");
      Serial.print(pmat10);
      Serial.println("ug/m3");
    }
    else if(count == 13){
      pmat25 = 256*high + c;
      Serial.print("PM2.5=");
      Serial.print(pmat25);
      Serial.println("ug/m3");
    }
    else if(count == 15){
      pmat100 = 256*high + c;
      Serial.print("PM10=");
      Serial.print(pmat100);
      Serial.println("ug/m3");
    }
     else if(count == 25){        
      temperature = (256*high + c)/10;
      Serial.print("Temp=");
      Serial.print(temperature);
      Serial.println(" (C)");
    }
    else if(count == 27){            
      humandity = (256*high + c)/10;
      Serial.print("Humidity=");
      Serial.print(humandity);
      Serial.println(" (%)");
    }   
    count++;
  }
  while(ss.available()) 
  ss.read();
  Serial.println();
}
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  
}



void loop() {
  retrievepm25();
  delay(1000);
  //display.clearDisplay();
  

}

