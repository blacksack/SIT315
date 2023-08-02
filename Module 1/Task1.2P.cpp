#define SOILMOISTURESENSOR_PIN A0 //soil moisture sensor input pin
#define PUMP_PIN 7 //motor control output pin
#define SWITCH_PIN 2 // slide switch is connected to digital pin 2
#define MOISTURE_LIMIT 350 //calibrate the moisture limit here

volatile bool manualOverride = false; //global variable to store manual override status
unsigned long previousTime = 0;  //will store the last time the moisture was checked
const long interval = 1000;  //interval at which the system will check moisture (milliseconds)

void setup() {
  pinMode(SOILMOISTURESENSOR_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP); //set slide switch pin as input with pullup
  analogWrite(PUMP_PIN, 0); //motor starts OFF - no voltage  
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), handleInterrupt, CHANGE);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) {
    //save the last time the moisture was checked
    previousTime = currentTime;
    checkSoilMoisture();
  }
}

void checkSoilMoisture() {
  int moisture = analogRead(SOILMOISTURESENSOR_PIN);

  if (manualOverride || moisture < MOISTURE_LIMIT) {
    analogWrite(PUMP_PIN, 255); //pump starts at full speed. This can be calibrated as required.
    Serial.println("Low soil moisture detected or manual override activated. Watering system is ON.");
  } else {
    analogWrite(PUMP_PIN, 0); //pump will switch OFF
    Serial.println("Soil moisture is OK. Watering system is OFF.");
  }
}

void handleInterrupt() {
	//if the switch is closed/ON, activate manual override
  if (digitalRead(SWITCH_PIN) == LOW) {
    manualOverride = true;
  } else {
    //if the switch is open/OFF, deactivate manual override
    manualOverride = false;
  }
}
