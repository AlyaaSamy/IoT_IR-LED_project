#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char ssid[] = "Infinix HOT 20i";
const char pass[] = "12345678";

// MQTT broker settings
const char broker[] = "broker.emqx.io";
const int port = 1883;

// Hardware pins
const int ledPin = 15;
const int irSensorPin = 4;

// Globals
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsgTime = 0;
int ledState = 0;

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi... Status: ");
    Serial.println(WiFi.status());
    delay(500);
  }

  Serial.println("WiFi Connected!");
  Serial.println("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Setup MQTT
  client.setServer(broker, port);
  client.setCallback(callback);

  // Connect to MQTT broker
  while (!client.connect("AliaaID", NULL, NULL, "/will/topic", 1, true, "client: AliaaID is disconnected")) {
    Serial.print("Connecting to MQTT Broker: ");
    Serial.println(broker);
    delay(500);
  }

  Serial.println("Connected to MQTT broker!");

  // Subscribe to LED control topic
  if (client.subscribe("/aliaa/led")) {
    Serial.println("Subscription successful");
  } else {
    Serial.println("Subscription failed");
  }

  lastMsgTime = millis();
}

void loop() {
  client.loop();

  // Check sensor and publish every 300 ms
  if (millis() - lastMsgTime >= 300) {
    lastMsgTime = millis();
    int irValue = digitalRead(irSensorPin);

    if (irValue == 0) {
      client.publish("/aliaa/ir", "OBJECT_DETECTED");
      Serial.println("Published: OBJECT_DETECTED");
    } else {
      client.publish("/aliaa/ir", "NO_OBJECT_DETECTED");
      Serial.println("Published: NO_OBJECT_DETECTED");
    }
  }

  // Control LED based on message received
  digitalWrite(ledPin, ledState ? HIGH : LOW);
}

// Handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';

  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(message);

  if (strcmp(topic, "/aliaa/led") == 0) {
    if (strcmp(message, "LED_ON") == 0) {
      ledState = 1;
    } else if (strcmp(message, "LED_OFF") == 0) {
      ledState = 0;
    }
  }
}
