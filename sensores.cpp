#include "clienteMqtt.h"

//Pines de los modulos
// #define DHTPIN D2
// #define LM393 A0

//Control tiempos con millis()
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long difTiempo = 2000;

//Valores de las variables de los sensores
int humedadSuelo = 0;
int humedadAmbiente = 0;
int tempAmbiente = 0;

void controlHumedadSuelo();
void controlHumedadAmbiente();
void controlTemperaturaAmbiente();

void inicializarSensores()
{
  Serial.println("setup iniciado");

  //Control tiempos con millis()
  unsigned long tiempo1 = 0;
  unsigned long tiempo2 = 0;

  inicializarMqttClient();
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
  humedadSuelo = analogRead(A0);

  String mensaje = "";

  if (humedadSuelo >= 1000)
  {
    mensaje = "sensor desconectado o fuera del suelo";
  }else if (humedadSuelo < 1000 && humedadSuelo >= 600)
  {
    mensaje = "El suelo esta seco";
  }else if (humedadSuelo < 600 && humedadSuelo >= 370)
  {
    mensaje = "El suelo esta humedo";
  }else if (humedadSuelo < 370)
  {
    mensaje = "El sensor esta practicamente en agua";
  }
  
  
  tiempo2 = millis();
  if (tiempo2 > (tiempo1 + difTiempo))
  {                     //Si ha pasado 2 segundo ejecuta el IF
    tiempo1 = millis(); //Actualiza el tiempo actual
    Serial.println(mensaje);
    Serial.println("Enviando humedad suelo: " + (String) humedadSuelo);
    publicarMqtt("proyecto/desTel/HS/data", (String) humedadSuelo);
  }
}

void controlHumedadAmbiente()
{

  humedadAmbiente = 20;

  tiempo2 = millis();
  if (tiempo2 > (tiempo1 + difTiempo))
  {                     //Si ha pasado 2 segundo ejecuta el IF
    tiempo1 = millis(); //Actualiza el tiempo actual

    publicarMqtt("proyecto/desTel/HA/data", (String) humedadAmbiente);
  }
}

void controlTemperaturaAmbiente()
{

  tempAmbiente = 30;

  tiempo2 = millis();
  if (tiempo2 > (tiempo1 + difTiempo))
  {                     //Si ha pasado 2 segundo ejecuta el IF
    tiempo1 = millis(); //Actualiza el tiempo actual

    publicarMqtt("proyecto/desTel/TA/data", (String)tempAmbiente);
  }
}