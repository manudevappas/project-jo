//The circuit:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
// * LCD R/W pin to ground
// * LCD VSS pin to ground
// * LCD VCC pin to 5V
// * 10K resistor:
// * ends to +5V and ground
// * wiper to LCD VO pin (pin 3)


//  Motor                             D6
//  Heating Coil                      D7
//  Temperature_set (Potentiometer)   A0
//temperature_sensor                A1


// include the library code:
#include <LiquidCrystal.h>  // LCD Library
#include <EEPROM.h>         // EEPROM Library

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int motor = 6;
int heating_coil = 7;
int enter = 8;
int temp;
int check_enter;
int temp_sensor;
int temp_pot;
void setup() {

  pinMode(motor,OUTPUT);
  pinMode(heating_coil,OUTPUT);
  pinMode(enter,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Incubator");
  lcd.setCursor(0,1);
  lcd.print("Ph: 8098067349");
  delay(3000);
  Serial.begin(9600);

}

void loop() {
    check_enter = 0;
    temp_sensor = analogRead(A1);
    temp_sensor = map(temp_sensor,0,288,0,70);
    EEPROM.get( 0, temp);
//    Serial.print(temp);
    check_enter = digitalRead(enter);
    
    if(temp > temp_sensor){
      digitalWrite(heating_coil,HIGH);      
      check_enter = digitalRead(enter);    
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Coil ON");
      lcd.setCursor(0,1);
      lcd.print("Temp :");
      lcd.setCursor(6,1);
      lcd.print(temp_sensor);
      delay(50);

      
      if(check_enter == HIGH){
        set_temp();
        }
      }
    else if(temp < temp_sensor){
     digitalWrite(heating_coil,LOW);
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Coil OFF");
      lcd.setCursor(0,1);
      lcd.print("Temp :");
      lcd.setCursor(6,1);
      lcd.print(temp_sensor);
      
     check_enter = digitalRead(enter);    
      delay(50);
     if(check_enter == HIGH){
        set_temp();
        }


        
     }
    

    
// put your main code here, to run repeatedly:
//  EEPROM.put( eeAddress, f ); f = variable that need to save
//EEPROM.get( eeAddress, f );   f contains address value
}

void set_temp(){
  delay(100);
  lcd.clear();
  temp_pot = analogRead(A0);
  temp_pot = map(temp_pot,0,1024,0,70);
  lcd.setCursor(0,0);
  lcd.print("Select Temp: ");
  lcd.setCursor(13,0);
  lcd.print(temp_pot);
  
    int enter_check = 0;
    enter_check = digitalRead(enter);
    delay(100);
     
    if(enter_check == HIGH){
    EEPROM.put(0,temp_pot);
    lcd.setCursor(0,1);
    lcd.print("Tep Set Done");
    delay(500);
    }
    else{
      set_temp();
      }
  }


  
