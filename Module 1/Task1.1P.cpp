#define SOILMOISTURESENSOR_PIN A0 //soil moisture sensor input pin
#define PUMP_PIN 7 //motor control output pin

#define MOISTURE_LIMIT 350 //calibrate the moisture limit here

void setup() {
  pinMode(SOILMOISTURESENSOR_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  analogWrite(PUMP_PIN, 0); //motor starts OFF - no voltage
  Serial.begin(9600);
}

void loop() {
  int moisture = analogRead(SOILMOISTURESENSOR_PIN);

  if (moisture < MOISTURE_LIMIT) {
    analogWrite(PUMP_PIN, 255); //pump starts at full speed. This can be calibrated as required.
    Serial.println("Low soil moisture detected. Watering system is ON.");
  } else {
    analogWrite(PUMP_PIN, 0); //pump will switch OFF
    Serial.println("Soil moisture is adequate. Watering system is OFF.");
  }
  
  delay(1000); //1 second delay before the next reading.
}
