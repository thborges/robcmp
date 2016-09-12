#include "Arduino.h"

void setupPosition() {

  // pisca leds
  digitalWrite(13, HIGH); delay(1000);
  digitalWrite(13, LOW);  delay(1000);
  digitalWrite(13, HIGH); delay(1000);
  digitalWrite(13, LOW);  delay(1000);

  const int ports[10] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 12};

  int port;
 
  for(port = 0; port < 10; port++)
    pinMode(port, OUTPUT);
   
  for(port = 0; port < 10; port++) {
    
    while (digitalRead(A2) == LOW) {
      digitalWrite(ports[port], HIGH);
      delay(50);
      digitalWrite(ports[port], LOW);
      delay(50);
    }
    digitalWrite(ports[port], LOW);

    // aguarda um instante para mudar de porta
    delay(1000);
  }

  // pisca leds
  digitalWrite(13, HIGH); delay(1000);
  digitalWrite(13, LOW);  delay(1000);
  digitalWrite(13, HIGH); delay(1000);
  digitalWrite(13, LOW);  delay(1000);
}


void piscaJob() {
 // pisca leds
  digitalWrite(13, HIGH); delay(200);
  digitalWrite(13, LOW);  delay(200);
  digitalWrite(13, HIGH); delay(200);
  digitalWrite(13, LOW);  delay(200);
  digitalWrite(13, HIGH); delay(200);
  digitalWrite(13, LOW);  delay(200);
  digitalWrite(13, HIGH); delay(200);
  digitalWrite(13, LOW);  delay(200);
}

void ovo_de_pascoa() {
  pinMode(13, OUTPUT);

  while(true) {
    if (digitalRead(A2) == HIGH) {
      delay(500);
      int ativ_liga = 1;
      int ativ_setup = (digitalRead(A2) == HIGH);

      if (ativ_setup) {
        delay(4000);
        ativ_setup = (digitalRead(A2) == HIGH);
      }

      if (ativ_setup)
        setupPosition();
      else if (ativ_liga) {
        piscaJob();
      }
        
      return;
    }
    delay(10);
  }
}

