// Tinkercad Arduino Tutorials: To Interface ESP8266+ThingSpeak+Arduino in Tinkercad Simulator

String ssid     = "YourSSID";  // SSID to connect to WIFI
String password = "YourSSIDPassword"; // 
String host     = "https://api.thingspeak.com";
const int httpPort   = 80;
//https://thingspeak.com/channels/1107661/private_show

String uri     = "/update?api_key=ALFD8NAVDPS77D9I";

String field1 = "field1";
String field2 = "field2";

int setupESP8266(void) {
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 1;
    
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 2;
  
  // Open TCP connection to the host:
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 3;
  
  return 0;
}

void TempandLightReadESP8266(void) {
  
  int tempSensor1=0;
  
  int lightSensor2=0;
  
  tempSensor1 = map(analogRead(A0),20,350,-40,125);

  lightSensor2 = map(analogRead(A1),-5,980,0, 100);
  
  // Construct our HTTP call
    
 String httpPacket= "GET "+ uri +"&  "+ field1 +"=  "+String(tempSensor1)+"  &  "+ field2 +"=  "+String(lightSensor2)+ " HTTP/1.1\r\nHost: " + host + "\r\n\r\n"; 
 
  int length = httpPacket.length();
  
  Serial.println("TempSensorvalue: "+ String(tempSensor1)+"\n\n");
  Serial.println("LightSensorvalue: "+ String(lightSensor2)+"\n\n");
  
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
    
}


void setup() {
  
  setupESP8266();
               
}

void loop() {
  
  TempandLightReadESP8266();
  
  delay(10000);
}
