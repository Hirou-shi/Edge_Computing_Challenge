#include <LiquidCrystal.h>

LiquidCrystal lcd(13,12,4,5,6,7);

const int LED_VERDE=9; 
const int LED_VERMELHO=11;
const int LED_AMARELO=3;
const int PinSensorV= A3; 
int PinSensorTemp=A0; 
const int pinAlarme = 10;  

void setup(){
  lcd.begin(16,2);
  pinMode(PinSensorTemp,INPUT);
  pinMode(PinSensorV,INPUT); 
  pinMode(LED_VERDE,OUTPUT);
  pinMode(LED_VERMELHO,OUTPUT);
  pinMode(LED_AMARELO,OUTPUT);
  pinMode(pinAlarme, OUTPUT);

  Serial.begin(9600); 
}

void loop(){
  int LeituraV = analogRead(PinSensorV); 
  float VoltSensorV = (LeituraV*0.314); 
  float Velocidade = VoltSensorV;
  
  int LeituraTemp = analogRead(PinSensorTemp);
  float Calc = LeituraTemp*5;
  Calc /= 1024;
  float Temperatura = (Calc-0.5)*100;
     
  Serial.print("Velocidade: ");
  Serial.print(Velocidade);
  Serial.println(" ");
  Serial.print("Temperatura atual: ");
  Serial.print(Temperatura);
  
  	
  if (Velocidade >= 270.0 and Temperatura >=110.0){
    lcd.clear();
    lcd.write("PIT STOP IMEDIATO!");
    lcd.setCursor (0,1);
    lcd.print("PERIGO");
    tone(pinAlarme, 1000);
    delay(2000);  
    noTone(pinAlarme);
    delay(1000);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }
  else if (Temperatura >=109.0){
    
  lcd.clear();
  lcd.write("Temp.:");
  lcd.print(Temperatura);
  lcd.print(" !!!");
  lcd.setCursor (0,1);
  lcd.print("Km/h: ");
  lcd.print(Velocidade);
  digitalWrite(LED_AMARELO, HIGH);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  }
    
  else{
  lcd.clear();
  lcd.write("Temperatura:");
  lcd.print(Temperatura);
  lcd.setCursor (0,1);
  lcd.print("Km/h: ");
  lcd.print(Velocidade);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
  }
  delay(1000);
}
    