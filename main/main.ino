#define min_hum_reg A0
#define hum_sensor A1
#define pump 2

const byte HYSTERESIS = 5;
void setup() {
  pinMode(hum_sensor, INPUT);
  pinMode(min_hum_reg, INPUT);
  pinMode(pump, OUTPUT);
}

void loop() {
  byte min_hum = map(analogRead(min_hum_reg), 0, 1023, 0, 100);
  byte hum_now = map(analogRead(hum_sensor), 0, 1023, 0, 100);
  // ниже цикл работы насоса
  // в него мы не попадем, если условие при while не исполнится
  while (hum_now <= min_hum - HYSTERESIS) {
    digitalWrite(pump, HIGH);
    byte hum_now = map(analogRead(hum_sensor, 0, 1023, 0, 100));
    if (hum_now > min_hum + HYSTERESIS) {
      digitalWrite(pump, LOW);
      break;
    }
  }
}
