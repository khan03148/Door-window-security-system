
#include <Keypad.h>
#include<EEPROM.h>

int tiger=13;
int echo=12;
int a=11;
int Duration,Distance;

char password[4];

char initial_password[4];

int i=0;


char key_pressed=0;

const byte rows = 4; 

const byte columns = 4; 

char hexaKeys[rows][columns] = {

{'1','2','3','A'},

{'4','5','6','B'},

{'7','8','9','C'},

{'*','0','#','D'}

};

byte row_pins[rows] = {A0,A1,A2,A3};

byte column_pins[columns] = {4,3,2,1};   

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);



void setup()
{
 
  pinMode(tiger,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  initialpassword();
  pinMode(a,OUTPUT);
  
}

void loop()
{
  digitalWrite(tiger,HIGH);
  delayMicroseconds(1000);
  digitalWrite(tiger,LOW);
  Duration=pulseIn(echo,HIGH);
  Distance=(Duration/2)/29.1;
//  Serial.print("cm=");
//  Serial.print(Distance);
 
  key_pressed = keypad_key.getKey();
  if (key_pressed){
    Serial.println(key_pressed);
  }

  
   if (key_pressed){
       password[i++]=key_pressed;
       
    
  
   }
  
  if(i==4)

  {

    delay(200);

    for(int j=0;j<4;j++){

       initial_password[j]=EEPROM.read(j);
      Serial.print(initial_password);}
     
      

  if(!(strncmp(password, initial_password,4))){
     digitalWrite(a,LOW);
      delay(30000);
     i=0;     
     }
  }
   else

    {
     if (Distance<50)
  {
   digitalWrite(a,HIGH);
   delay(2000);
    }
 else {
 digitalWrite(a,LOW);
    delay(200);
  
}
    }
  
 
}
void initialpassword(){

  for(int j=0;j<4;j++)

    EEPROM.write(j, j+49);

  for(int j=0;j<4;j++)

    initial_password[j]=EEPROM.read(j);}
