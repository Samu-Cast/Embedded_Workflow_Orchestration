#include <Keyboard.h>

const int triggerPin = 2;

void setup() {
  pinMode(triggerPin, INPUT);
  Keyboard.begin();
  delay(4000);
}

void chiamaApp(String nomeApp) {
  Keyboard.press(KEY_LEFT_GUI); Keyboard.press(' ');
  delay(150); Keyboard.releaseAll();
  delay(800);
  Keyboard.print(nomeApp);
  delay(500);
  Keyboard.write(KEY_RETURN);
  delay(1500);
}

void usaMagnet(char tasto) {
  Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_ALT); Keyboard.press(tasto);
  delay(150); Keyboard.releaseAll();
  delay(500);
}

void chiudiApp() {
  Keyboard.press(KEY_LEFT_GUI); Keyboard.press('q');
  delay(150); Keyboard.releaseAll();
  delay(500);
}

void nascondiApp() {
  Keyboard.press(KEY_LEFT_GUI); Keyboard.press('h');
  delay(150); Keyboard.releaseAll();
  delay(500);
}

// Volume al 100% via terminale — niente virgolette, così evitiamo
// il problema del layout tastiera IT che manda in prompt secondario ">"
void impostaVolumeMax() {
  chiamaApp("terminal");
  Keyboard.print("osascript -e set\\ volume\\ output\\ volume\\ 100");
  Keyboard.write(KEY_RETURN);
  delay(500);
  chiudiApp();
  delay(500);
}

void loop() {
  if (digitalRead(triggerPin) == HIGH) {

    // 1. Spostamento su Scrivania 2
    Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_RIGHT_ARROW);
    delay(150); Keyboard.releaseAll();
    delay(1000);

    // 2. Volume al 100%
    impostaVolumeMax();

    // 3. Vocale J.A.R.V.I.S. (musica.command)
    chiamaApp("terminal");
    Keyboard.print("bash musica.command.txt");
    Keyboard.write(KEY_RETURN);
    delay(1000);
    nascondiApp();   // nascondi invece di chiudere, evita di killare lo script in esecuzione

    // 4. Safari (Sinistra)
    chiamaApp("safari");
    Keyboard.press(KEY_LEFT_GUI); Keyboard.press('l');
    delay(150); Keyboard.releaseAll();
    delay(400);
    Keyboard.print("news oggi");
    delay(200);
    Keyboard.write(KEY_RETURN);
    delay(600);
    usaMagnet(KEY_LEFT_ARROW);

    // 5. Calendario (Destra)
    chiamaApp("calendario");
    usaMagnet(KEY_RIGHT_ARROW);

    // 6. Audio finale (afplay jarvis.mp3)
    chiamaApp("terminal");
    Keyboard.print("afplay jarvis.mp3");
    Keyboard.write(KEY_RETURN);
    delay(500);
    nascondiApp();   // idem: nascondi per non interrompere afplay

    delay(10000);  // pausa prima di poter ritriggerare
  }
}
