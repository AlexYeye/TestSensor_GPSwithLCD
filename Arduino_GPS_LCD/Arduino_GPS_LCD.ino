#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(10, 11); // RX, TX
TinyGPS gps1;
//Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Variaveis
long latitude, longitude;
unsigned long idadeInfo;

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);

  Serial.println("O GPS do BAJA aguarda pelo sinal dos satelites...");
  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  comunicaGPS();
  //mostraLCD();

}

void comunicaGPS(){
  bool recebido = false;
  //Recebendo Dados
  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }

  if (recebido) {
     Serial.println("----------------------------------------");
     
     //Latitude e Longitude
     gps1.get_position(&latitude, &longitude, &idadeInfo);     

     if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }

     if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
        Serial.print("Idade da Informacao (ms): ");
        Serial.println(idadeInfo);
     }

     //altitude
     float altitudeGPS;
     altitudeGPS = gps1.f_altitude();

     if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
        Serial.print("Altitude (cm): ");
        Serial.println(altitudeGPS);
     }
     // Mostrar no LCD
     mostraLCD();
  }
}

void mostraLCD(){
  
  // Posisionando texto na Primeira Linha e Primeira Coluna
  lcd.setCursor(0,0);
  lcd.print("La: ");
  lcd.print(float(latitude) / 100000, 6);

  lcd.setCursor(0,1);
  lcd.print("Lo: ");
  lcd.print(float(longitude) / 100000, 6);

}
