#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "DA_INSERIRE";
const char* passwd = "DA_INSERIRE";
const int ledPin = 2;

WebServer server(80);

// 1. L'HTML aggiornato con il JavaScript integrato
String generaHTML() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body{text-align:center; font-family:Arial; margin-top:50px; background-color:#222; color:white;} ";
  // Ho trasformato i link in veri 'button' per evitare strani comportamenti su mobile
  html += ".btn{background-color:#4CAF50; color:white; padding:40px 60px; font-size:30px; margin:20px; border-radius:15px; border:none; cursor:pointer;} ";
  html += ".btn-off{background-color:#f44336;}</style></head><body>";
  html += "<h1>ESP32 Istantaneo</h1>";
  
  // LA MAGIA È QUI: Invece di 'href', usiamo 'onclick=fetch()' per fare la richiesta in background
  html += "<button onclick=\"fetch('/accendi')\" class=\"btn\">ACCENDI</button><br><br>";
  html += "<button onclick=\"fetch('/spegni')\" class=\"btn btn-off\">SPEGNI</button>";
  html += "</body></html>";
  
  return html;
}

// 2. Pagina iniziale (Viene scaricata UNA SOLA VOLTA)
void paginaPrincipale() {
  server.send(200, "text/html", generaHTML());
}

// 3. Cosa succede se premiamo "ACCENDI"
void azioneAccendi() {
  digitalWrite(ledPin, HIGH);
  // Rispondiamo al volo solo con un microscopico "OK" di testo, niente HTML!
  server.send(200, "text/plain", "OK"); 
}

// 4. Cosa succede se premiamo "SPEGNI"
void azioneSpegni() {
  digitalWrite(ledPin, LOW);
  // Come sopra, risposta leggerissima e istantanea
  server.send(200, "text/plain", "OK"); 
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Pausa veloce per agganciare la seriale
  for(int i = 2; i > 0; i--) { delay(1000); }
  
  Serial.println("\nConnessione al Wi-Fi...");
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Connesso! VAI SU: http://");
  Serial.println(WiFi.localIP());

  server.on("/", paginaPrincipale);      
  server.on("/accendi", azioneAccendi);  
  server.on("/spegni", azioneSpegni);    

  server.begin(); 
}

void loop() {
  server.handleClient();
}