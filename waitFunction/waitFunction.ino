bool temp;
int savedAt = 0;
unsigned int previousMillis;
bool logged = false;

int i = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  temp = waitForMillis(2000);//wait for 2000ms(2sec).
  if (temp && !logged) {
    i++;//counting number every 2sec
    logged = true;
    Serial.println(i);//show current number to Serial monitor.
  } else if (!temp) logged = false;
}

//Main delay function
bool waitForMillis(int dur) {
  if (savedAt == 0) {
    savedAt = millis();
  } else if (savedAt != 0) {
    previousMillis = millis();
    if (previousMillis - savedAt >= dur) {
      savedAt = 0;
      return true;
    } else {
      return false;
    }
  }
}
