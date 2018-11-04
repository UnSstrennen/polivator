#define min_hum_reg PB5
#define hum_sensor PB2
#define min_light_reg PB4
#define light_sensor PB3
#define pump 1

const byte HYSTERESIS = 5;
void setup() {
  pinMode(hum_sensor, INPUT);
  pinMode(min_hum_reg, INPUT);
  pinMode(light_sensor, INPUT);
  pinMode(min_light_reg, INPUT);
  pinMode(pump, OUTPUT);
}

void loop() {
  byte min_hum = map(analogRead(min_hum_reg), 0, 1023, 0, 100);
  byte hum_now = map(analogRead(hum_sensor), 0, 1023, 100, 0);
  byte min_light = map(analogRead(min_light_reg), 0, 1023, 100, 500);
  byte light_now = analogRead(light_sensor);
  // пока не будет светло, насос не дергать
  if (light_now > min_light) {
    // ниже цикл работы насоса
    // в него мы не попадем, если условие при while не исполнится
    while (hum_now <= min_hum - HYSTERESIS) {
      digitalWrite(pump, HIGH);
      byte hum_now = map(analogRead(hum_sensor), 0, 1023, 0, 100);
      if (hum_now > min_hum + HYSTERESIS) {
        digitalWrite(pump, LOW);
        break;
      }
    }
  }
}
