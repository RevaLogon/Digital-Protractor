#include <Servo.h> 
#include <LCD5110_Basic.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

LCD5110 ekran(8,9,10,11,12);


extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

#define buton 4
Servo motor; 
int aci = 0;
boolean durum = true;
void setup()
{
  ekran.InitLCD();
  ekran.setContrast(80);
  Serial.begin(9600);
  Serial.println("Açı Ölçer Test");
  motor.attach(3); 
  pinMode(buton,INPUT);
 ekran.print("KUZEY TUNCER", CENTER, 0);
 ekran.setFont(SmallFont);
 ekran.print("ACI OLCER", CENTER, 5);
 ekran.setFont(SmallFont);
 ekran.print("ACI", CENTER, 15);
}
void loop(){

 if(durum==true){
    for(int i=0; i<180; i++){
        motor.write(i);
        delay(100);
          if(digitalRead(buton)==0){
            motor.write(i);
            
            aci=i;
             ekran.setFont(MediumNumbers);
  //ekran.print(aci, CENTER, 30);
            durum=false;
            break;
          }
      }
  }
   if(durum==false){
     Serial.print("Açı değeri : ");
     ekran.print(aci, CENTER, 30);
     Serial.print(aci);
     Serial.println(" derecedir.");
      ekran.setFont(SmallFont);
      

 ekran.setFont(MediumNumbers);
 ekran.printNumI(aci, 13 , 30);
 ekran.setFont(SmallFont);
 ekran.print("Derece",RIGHT, 33);
 

     delay(4000);
     durum=true;
     
  }
  




  

}
