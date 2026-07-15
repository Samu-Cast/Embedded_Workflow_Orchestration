#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "DA_INSERIRE";
const char* passwd = "DA_INSERIRE";
const int triggerPin = 4; // Pin che invia il segnale al Pro Micro

WebServer server(80);

String generaHTML() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body{text-align:center; font-family:Arial; margin-top:50px; background-color:#111; color:#00FF00;} ";
  html += ".btn{background-color:#007AFF; color:white; padding:40px 60px; font-size:25px; margin:20px; border-radius:10px; border:none; cursor:pointer; box-shadow: 0 0 15px #007AFF;} </style></head><body>";
  html += "<h2>J.A.R.V.I.S. INTERFACE</h2>";
  html += "<button onclick=\"fetch('/buongiorno')\" class=\"btn\">INITIATE<br>MORNING PROTOCOL</button>";
  html += "</body></html>";
  
  return html;
}

void paginaPrincipale() {
  server.send(200, "text/html", generaHTML());
}

void azioneBuongiorno() {
  digitalWrite(triggerPin, HIGH); // Invia il segnale al Pro Micro
  delay(500); 
  digitalWrite(triggerPin, LOW);
  server.send(200, "text/plain", "OK"); 
}

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);

  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", paginaPrincipale);      
  server.on("/buongiorno", azioneBuongiorno);  

  server.begin(); 
}

void loop() {
  server.handleClient();
}
