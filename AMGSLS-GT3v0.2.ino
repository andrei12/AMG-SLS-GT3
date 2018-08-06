
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "xxxxxxxxx";
char pass[] = "xxxxxx";
char ssid[] = "xxxxxx";

//GPIOs
int AIN1=14;
int AIN2=27;
int PWMA=4;
int BIN1=26;
int BIN2=25;
int STBY=23;
int PWMB=15;


void setup()
{
  //debug
  Serial.begin(9600); 
  
  //pwm channel config
  ledcSetup(3, 12000, 8);  
  ledcAttachPin(4, 3);
  
  Blynk.begin(auth, ssid, pass);
   
  //GPIO mode setup
    pinMode(14, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(23, OUTPUT); 
    pinMode(15, OUTPUT);
  }
void loop()
{
  Blynk.run();    
}

//PWM power slider widget
BLYNK_WRITE(V7)
{
 int dutyCycle = param.asInt();
 ledcWrite(3, dutyCycle); 
}


//joystick setup
BLYNK_WRITE(V3)
{

  int x = param[0].asInt();
  int y = param[1].asInt();
           
if(x==2 && y==2){   //center-stby               
 
  digitalWrite(STBY, LOW);
}
else if(x==2 && y==3){    //fwd
  digitalWrite(PWMA, HIGH); 
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWMB, LOW);    
}
else if(x==3 && y==3){   //fwd-r
  digitalWrite(PWMA, HIGH); 
  digitalWrite(PWMB, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  digitalWrite(STBY, HIGH);
}
else if(x==3 && y==2){   ///r
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  digitalWrite(STBY, HIGH);
  digitalWrite(PWMB, HIGH);
 
}
else if(x==3 && y==1){ //bwd-r
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  digitalWrite(STBY, HIGH);
  digitalWrite(PWMB, HIGH);
  digitalWrite(PWMA, HIGH); 
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);    
} 
else if(x==2 && y==1){  //bwd
  digitalWrite(PWMA, HIGH); 
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWMB, LOW);
} 
else if(x==1 && y==1){  //bwd-L
  digitalWrite(PWMA, HIGH); 
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWMB, HIGH);
}
else if(x==1 && y==2){  //L
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWMB, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWMA, LOW);
}
else if(x==1 && y==3){  //fwd-L
  digitalWrite(STBY, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWMB, HIGH);
  digitalWrite(PWMA, HIGH); 
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);   
}
  //joystick debug
  Serial.print(" x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  }
