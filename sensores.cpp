#include "clienteMqtt.h"
#include <DHT.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN D2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Pines de los modulos
#define pinDHT D2
#define pinSensorHumedadSuelo A0

//Control tiempos con millis()
unsigned long tiempo1HumedadSuelo = 0;
unsigned long tiempo2HumedadSuelo = 0;
unsigned long difTiempoHumedadSuelo = 3000;
unsigned long tiempo1HumedadAmbiente = 0;
unsigned long tiempo2HumedadAmbiente = 0;
unsigned long difTiempoHumedadAmbiente = 3100;
unsigned long tiempo1TemperaturaAmbiente = 0;
unsigned long tiempo2TemperaturaAmbiente = 0;
unsigned long difTiempoTemperaturaAmbiente = 3200;

//Valores de las variables de los sensores
int humedadSuelo = 0;
float humedadAmbiente = 0;
float tempAmbiente = 0;

void controlHumedadSuelo();
void controlHumedadAmbiente();
void controlTemperaturaAmbiente();

void inicializarSensores()
{

  //Control tiempos con millis()
  tiempo1HumedadSuelo = millis();
  tiempo1HumedadAmbiente = millis();
  tiempo1TemperaturaAmbiente = millis();
  inicializarMqttClient();
  // Comenzamos el sensor DHT
  dht.begin();
  Serial.println("setup iniciado");
}

void loopSensores()
{

  controlHumedadSuelo();
  controlHumedadAmbiente();
  controlTemperaturaAmbiente();
  loopClientMqtt();
}

void controlHumedadSuelo()
{


  // humedadSuelo = 10;
  humedadSuelo = analogRead(pinSensorHumedadSuelo);
  delay(3);

  tiempo2HumedadSuelo = millis();
  if (tiempo2HumedadSuelo >= (tiempo1HumedadSuelo + difTiempoHumedadSuelo))
  {
    tiempo1HumedadSuelo = millis(); //Actualiza el tiempo actual
    Serial.println("");
//    int porcentaje = map(humedadSuelo, 0, 1024, 100, 0);
//    Serial.println("porcentaje humedad: " + (String) porcentaje + "%");
    publicarMqtt("HS/data", (String) humedadSuelo);

  }
}

void controlHumedadAmbiente()
{

  tiempo2HumedadAmbiente = millis();
  if (tiempo2HumedadAmbiente >= (tiempo1HumedadAmbiente + difTiempoHumedadAmbiente))
  {
    tiempo1HumedadAmbiente = millis(); //Actualiza el tiempo actual
    humedadAmbiente = dht.readHumidity();
    publicarMqtt("HA/data", (String) humedadAmbiente);
  }
}

void controlTemperaturaAmbiente()
{

  tiempo2TemperaturaAmbiente = millis();
  if (tiempo2TemperaturaAmbiente >= (tiempo1TemperaturaAmbiente + difTiempoTemperaturaAmbiente))
  { //Si ha pasado 2 segundo ejecuta el IF
    tiempo1TemperaturaAmbiente = millis(); //Actualiza el tiempo actual
    tempAmbiente = dht.readTemperature();
    publicarMqtt("TA/data", (String)tempAmbiente);
  }
}
