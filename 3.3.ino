int led = 6;
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Aadarsh";    // your network SSID (name)
char pass[] = "123456789";    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "mqtt-dashboard.com";
int        port     = 1883;
const char topic[]  = "Aadarsh-wave";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 //Set the LED pin as output
  pinMode(led, OUTPUT);
  
  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop()
{
  int messageSize = mqttClient.parseMessage();
  if (messageSize)
  {
    // we received a message, print out the topic and contents
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");
    
    // use the Stream interface to print the contents
    if(mqttClient.available()) 
    {
      Serial.print((float)mqttClient.read());
       digitalWrite(led, HIGH); //state the tx led high
  delay(1000); 
  digitalWrite(led,LOW );  //state the rx led low 
  delay(1000);                  // wait for half a second
  digitalWrite(led, HIGH);    //state the tx led high
  delay(1000); 
  digitalWrite(led, LOW);  //state the rx led low 
  delay(1000);                       // wait for half a second
  digitalWrite(led, HIGH);    //state the tx led high
  delay(1000); 
  digitalWrite(led, LOW);  //state the rx led low 
  delay(1000);  

    }
    Serial.println();
    }
}