// Analog Input with LED
// The voltage measured is then assigned to a value between 0 and 4095, in which 0 V corresponds to 0, and 3.3 V corresponds to 4095.
const int Analoginput = 15 ;
const int LEDpin = 4 ;
int Potvalue = 0 ;

void setup() {
  Serial.begin(115200);
  pinMode(Analoginput , INPUT);
  pinMode(LEDpin , OUTPUT);  
}

void loop() {
  Potvalue = analogRead(Analoginput);
  Serial.println(Potvalue);
  analogWrite(LEDpin, (Potvalue/16));
  delay(500);
}
