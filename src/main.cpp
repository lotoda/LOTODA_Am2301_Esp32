#include <Arduino.h>
/**
 * main.cpp - Read and Send AM2301 Sensor's value to LOTODA IoT Platform
 */
#include <LOTODA.h>
#include "DHT.h"
#include <Wire.h>

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif

#ifdef ESP32
  #include <WiFi.h>
#endif

/**
 * AM2301 sensor parameters.
 */
#define DHTPIN 5
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);
/**
 * WiFi parameters.
 */
const char* ssid      = "ssid";
const char* password  = "password";
WiFiClient client;

/**
 * Initialize the connection with the cloud.
 */
String useridkey    = "xxxxxxxx";
String passidkey  = "yyyyyyyyyyyyyyyyyyyy";
String deviceid      = "id1002";
LOTODA lotoda = LOTODA(useridkey, passidkey, deviceid);

void setup() {
    Serial.begin(115200);
    delay(10);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.print(".");
    }
    Serial.println("");

    /**
     * Initialize DHT/AM sensor.
     */
    dht.begin();
    /**
     * Set the debug printer (optional).
     */
    lotoda.setDebugPrinter(&Serial);
    /**
     * Set LOTODA client.
     */
    lotoda.setConnectClient(&client);
}

void loop() {
    lotoda.loop();
    /**
     * Send AM2301 Sensor's temperature/humidity value.
     */
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    //lotoda.publishSensorJsonValueOne("temperature", t);
    lotoda.publishSensorJsonValueTwo("Temperature", t, "Humidity", h);
}