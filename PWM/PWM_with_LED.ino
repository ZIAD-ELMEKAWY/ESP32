const int ledpin = 15 ;

void setup() 
{
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // increasing the LED brightenss
  for(int dutycycle = 0 ; dutycycle <= 255 ; dutycycle++)
  {
      analogWrite(ledpin , dutycycle);
      delay(15);
  }
  // decreasing the LED brightenss 
  for(int dutycycle = 255 ; dutycycle >= 0 ; dutycycle--)
  {
      analogWrite(ledpin , dutycycle);
      delay(15);
  }
}

// ************************* Another Code  **************************** //
const int ledpin = 15 ;        // 15 corresponds to GPIO15 in ESP32 board
// setting PWM properties
const int freq = 5000;
const int resolution = 8;

void setup() 
{
  ledcAttach(ledpin,freq , resolution);
}

void loop() {
  // increasing the LED brightenss
  for(int dutycycle = 0 ; dutycycle <= 255 ; dutycycle++)
  {
      ledcWrite(ledpin , dutycycle);
      delay(15);
  }
  // decreasing the LED brightenss 
  for(int dutycycle = 255 ; dutycycle >= 0 ; dutycycle--)
  {
      ledcWrite(ledpin , dutycycle);
      delay(15);
  }
}
