#include <OneWire.h>                
#include <DallasTemperature.h>
 
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor


//Declaramos ventiladores y relé
int Ventiladores=9;
int Rele=7;
//Para leer el string
char Dato;
//Valores para el PWM
int PWM=0;
int Switch=0;
bool stringComplete = false; 


void setup() {
  //Asignamos pin para ventiladores
  pinMode(Ventiladores,OUTPUT);
  pinMode(Rele,OUTPUT);
  //Iniciamos comunicacion Serial
  Serial.begin(9600);
  //Se inicia el sensor
  sensors.begin();   
}
/*
void loop() {
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
    escribir();
    if(stringComplete){
        Serial.println(temp);
        stringComplete=false;
    }
}*/

void escribir(){
    while (Serial.available()) {
    // se obtiene byte:
    stringComplete=true;
    Dato = Serial.read();
    if(Dato=='V'){                  //Para los Veltiladores
          PWM=Serial.parseInt();
        }
    analogWrite(Ventiladores,PWM);
    
    if(Dato=='R'){                 //Para relé
      Switch=Serial.parseInt();
      if(Switch==1){
        digitalWrite(Rele,HIGH);
      }
      else{
        digitalWrite(Rele,LOW);
      }
    }
      stringComplete = false;
  }
}

// CODIGO 2
void loop() {

    if(stringComplete==false){
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
    Serial.println(temp);  
      }
    escribir();
}
