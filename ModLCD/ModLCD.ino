// Inclusão das Bibliotecas
#include <LiquidCrystal_I2C.h>

//Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);


void setup() {
  // Inicializa Serial
  //Serial.begin(9600);

  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  // Posisionando texto na Primeira Linha e Primeira Coluna
  lcd.setCursor(0,0);
  lcd.print("Depois Termino!");
  lcd.setCursor(0,1);
  lcd.print("Boa Noite!");

  delay (1000);
}
