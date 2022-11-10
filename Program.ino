#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_I2CDevice.h>
#define pinSensorHujan 5
#define pinHujan A0
#define relay 7

//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);
//suhu
DHT dht(2, DHT22); //Pin, Jenis DHT
float suhu;
//sensor hujan
int sensorHujan;
int nilaiHujan;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  pinMode(pinSensorHujan, INPUT);
  pinMode(pinHujan, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop() {
  suhu = dht.readTemperature();
  nilaiHujan = analogRead(pinHujan);
  nilaiHujan = 100 - (nilaiHujan / 10.24);
  
  Serial.print("Suhu : ");
  Serial.println(suhu);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String() + "T:" + suhu + " C" + " H:" + nilaiHujan + " %");
  kondisi();
  delay(2000);
}
void kondisi() {
  sensorHujan = digitalRead(pinSensorHujan);
  if (sensorHujan == 0) {
    digitalWrite(relay, LOW);
    Serial.println("Pengering Nyala");
    lcd.setCursor(0, 1);
    lcd.print("PENGERING NYALA");
  } else if (sensorHujan == 1 && suhu <= 48) {
    digitalWrite(relay, HIGH);
    Serial.println("Sudah Kering bos");
    lcd.setCursor(0, 1);
    lcd.print("SUDAH KERING");
  } else if (suhu > 60) {
    digitalWrite(relay, HIGH);
  } else if (suhu < 50) {
    digitalWrite(relay, LOW);
  }
  else {
    digitalWrite(relay, HIGH);
  }
  Serial.print("Kelembaban: ");
  Serial.print(nilaiHujan);
  Serial.println(" %");
}
