#include <WiFi.h>


const char* ssid = "Rostelecom_153405";
const char* password = "94882295";

bool led1IsOn = false;
bool led2IsOn = false;
bool led3IsOn = false;
const int LED_0 = 15;
const int LED_1 = 2;
const int LED_2 = 4;

WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  delay(1000);
  digitalWrite(LED_0, HIGH);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  delay(1000);
  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
}



void loop() {
  // Check if a client has connected

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  controller(req, client);

  client.flush(); 
  // Prepare the response
  String s = "response";

  // Send the response to the client
  client.print(s);
  
  delay(1);
  client.stop();
  Serial.println("Client disonnected");
  

}

void controller(String req,  WiFiClient client){
   if(req.indexOf("/led1") != -1){
     setLedState(LED_0, led1IsOn);
     led1IsOn = !led1IsOn;
    } else if(req.indexOf("/led2") != -1){
      setLedState(LED_1, led2IsOn);
      led2IsOn = !led2IsOn;
    } else if(req.indexOf("/led3") != -1){
      setLedState(LED_2, led3IsOn);
      led3IsOn = !led3IsOn;
    } else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  }
void setLedState(int led, bool state){
  if(!state){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);}
  }
