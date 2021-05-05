#include <PubSubClient.h>

void inicializarMqttClient();
void reconnect();
void loopClientMqtt();
void publicarMqtt(char* topic, String mensaje);