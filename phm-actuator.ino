// This #include statement was automatically added by the Particle IDE.
#include "MQTT/MQTT.h"

int R1 = D5;
int R2 = D6;

void callback(char* topic, byte* payload, unsigned int length);

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);
 **/
MQTT client("mqtt_server_address", 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    
    Particle.publish("Particle MQTT callback.");
    
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);
    

    if(message.equals("ON")) {
        Particle.publish("Turning heating", "ON");
        digitalWrite(R1, LOW);
        digitalWrite(R2, LOW);
    } 

    if(message.equals("OFF")) {
        Particle.publish("Turning heating", "OFF");
        digitalWrite(R1, HIGH);
        digitalWrite(R2, HIGH);
    } 

    delay(1000);
}

void setup() {
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);
    
    client.connect("boiler", "mqtt_username", "mqtt_password");

    // publish/subscribe
    if (client.isConnected()) {
        client.subscribe("phm/actuators");
        Particle.publish("Particle is connected to MQTT broker.");
    }
    
}

void loop() {
    if (client.isConnected()) {
        client.loop();
    }
}
