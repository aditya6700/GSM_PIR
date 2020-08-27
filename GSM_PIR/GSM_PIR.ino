/***********************************************************************

 connect your components to respective pins as mentioned below
 rx = receiver
 tx = transmitter  
 
 ***********************************************************************/





/* this is for SIM800*/
#include<SoftwareSerial.h>
SoftwareSerial SIM800(10,11);   //rx =connected to pin 10  tx= connected to pin 11

/* this initialization is for PIR sensor*/ 
int pir = 2;  // connect this pin to PIR data pin
int value = 0;
int pirstate = LOW;

/* this is for buzzer*/
int buz=3; // connect the long pin of buzzer


void setup()
{
  
  Serial.begin(9600); 
  SIM800.begin(9600);
  pinMode(buz, OUTPUT);
  pinMode(pir, INPUT);
  Serial.print("System Ready");
}
void loop()
{
    
       value = digitalRead(pir);    //read pir sensor
       if (value == HIGH)
        {   
             
            buzz();   //calling buzzer function
            if ( pirstate == LOW)
            {
               Serial.println("Motion detected!"); 
               sendSMS();  // calling sendSMS function
               pirstate = HIGH; // update variable state to HIGH
               delay(2000);
            }
        } 
     else 
       {
             buzz();   //calling buzzer function
             if ( pirstate == HIGH)
              {
                 Serial.println("Motion stopped!");
                 sendSMS1();  // calling sendSMS1 function
                 pirstate = LOW;       // update variable state to LOW
               }
      }
}
 
void sendSMS()
{
  
  SIM800.println("AT+CMGF=1");  //set to sms mode
  delay(500);
  SIM800.print("AT + CMGS = \"+919063607175\""); //sending sms 
  SIM800.println();
  delay(500);
  SIM800.println("An Animal is approaching your Field...!!!"); // message
  delay(500);
  SIM800.write(26);  
  delay(1000);
  
}

void sendSMS1()
{
  
  SIM800.println("AT+CMGF=1");  //set to sms mode
  delay(500);
  SIM800.print("AT + CMGS = \"+919063607175\""); //sending sms 
  SIM800.println();
  delay(500);
  SIM800.println("your field is free from animals"); // message
  delay(500);
  SIM800.write(26);  
  delay(1000);
  
}

void buzz()
{
  for(int b=0;b<3;b++)
     {
        digitalWrite(buz, HIGH); // turn buzzer ON
        delay(250); 
        digitalWrite(buz, LOW); // turn buzzer OFF
        delay(100); 
     }
}
