/*
__________________________________________________________________________________
                     |
    APPLICATION NAME | WS2812 LED Array Controller-Code for ESP32
              AUTHOR | Harsh Benahalkar
                     |
          CREATED ON | 18th December 2022 
_____________________|____________________________________________________________
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>
#include <ArduinoJson.h>

// Red LED status variables
const int  STATUS_LED     = 13;                   // pin D6 of the ESP
int        i              = 0;

// WiFi details
const char *ssid          = "ssid";               // Enter WiFi router/access-point name/SSID
const char *password      = "p@s$w0Rd";           // Enter WiFi router/access-point password

// MQTT Broker details
const char *mqtt_broker   = "broker.name";        // Name of MQTT broker
const char *sub_topic     = "RGB_array/query";    // Name of topic to which ESP will subscribe and receive data
const char *pub_topic     = "RGB_array/response"; // Name of topic to which ESP will publish and send data
const char *mqtt_username = "";                   // Username credentials of MQTT broker
const char *mqtt_password = "";                   // Password credentials of MQTT broker
const int  mqtt_port      = 1883;                 // Port number of MQTT broker
String     client_id      = "esp8266-client-";    // Client name 

// RGB LED array details
const int  RGB_PIN        = 0;                    // Pin number of ESP to which WS2812 will be connected
const int  RGB_NUM        = 59;                   // Number of WS2812 LEDs in array
int        COL_R          = 0;
int        COL_G          = 0;
int        COL_B          = 0;

// Creating Objects
WiFiClient espClient;
PubSubClient client(espClient);
StaticJsonDocument<200> color_obj;
CRGB ledObj[RGB_NUM];

void setup()
{
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);

  connect_WiFi();
  client_id += String(WiFi.macAddress());

  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(get_led_data_callback);
  connect_MQTT();

  FastLED.addLeds<WS2812, RGB_PIN, GRB>(ledObj, RGB_NUM);
  digitalWrite(STATUS_LED, HIGH);
}

void loop()
{
  if(!client.connected()){
    digitalWrite(STATUS_LED, LOW);
    
    if (WiFi.status() != WL_CONNECTED){
      WiFi.disconnect();
      connect_WiFi();
    }
   
    connect_MQTT();
    
    digitalWrite(STATUS_LED, HIGH);
  }
  
  client.loop();

  for (i = 0 ; i < RGB_NUM ; i++)
  {
    ledObj[i] = CRGB ( COL_R, COL_G, COL_B);
  }
  FastLED.show();  
  
}

void connect_WiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(10);
  }
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

void connect_MQTT()
{
  while (!client.connected()) 
  {
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) 
    {
      client.subscribe(sub_topic);
    } 
    else 
    {
      delay(10);
    }
  }
}

void get_led_data_callback(char *topic, byte *message, unsigned int length) 
{
  
  String payload = "";
  for (i = 0; i < length; i++) 
  {
    payload += (char)message[i];
  }

  DeserializationError error = deserializeJson(color_obj, payload);
  COL_R = color_obj["R"];
  COL_G = color_obj["G"];
  COL_B = color_obj["B"];

  client.publish(pub_topic, &payload[0]);
}