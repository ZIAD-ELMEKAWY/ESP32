/**
 * Created by: Ziad Elmekawy
**/

#define BLYNK_TEMPLATE_ID "TMPL5Gia-jRsv"
#define BLYNK_TEMPLATE_NAME "Sensors"
/************************* Include *************************/
#include <Wire.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <NewPing.h>

/************************* Pin definitions *************************/
#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define LM35  34           // ESP32 pin GPIO34 (ADC6) connected to LM35
#define led1  21               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN     
#define ldr  36               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define echoPin 12              // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin 13              // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define servopin 26
#define SOUND_SPEED 0.034       //define sound speed in cm/uS

// Global Variable declaration 
int duration;
float distanceCm;

Servo servoMotor ;
BlynkTimer timer; 
// WiFi and BLYNK info

char auth[] = "6r0xbjnE2KIMgu2B6Zl572UvYy2-I46L";  // Blynk Auth Token
char ssid[] = "YOUR_SSID";         // WiFi SSID
char pass[] = "YOUR_PASSWORD";     // WiFi Password

/************************* Function proto-type *************************/
void Read_LDR();
void Read_Ultra_Sonic_Sensor();
void Read_Temp_Sensor();
void Servo_Turn_ClockWise (void);
void Servo_Turn_Anti_ClockWise (void);
void Gate_ON(void);
void Gate_OFF(void);
/**************************************************/
void sendSensorData()
{
  Read_Temp_Sensor();
  Read_Ultra_Sonic_Sensor();
  Read_LDR();
}

BLYNK_WRITE(V3)
{
  int value = param.asInt();
  digitalWrite(led1, value);
}

BLYNK_WRITE(V4)
{
  int value = param.asInt();
  if(value == HIGH)
  {
    Gate_ON();
  }
  else if(value == LOW)
  {
    Gate_OFF();
  }
}
/*************************** Setup Function ***************************/
void setup() 
{
  // Serial monitor setup
  Serial.begin(115200);
  Serial.println("Serial is started ");
  // ldr setup
  pinMode(ldr, INPUT);
  // LED setup
  pinMode(led1, OUTPUT);
  // Ultra-sonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Servo setup
  servoMotor.attach(servopin);
  // LM35 setup
  analogSetPinAttenuation(LM35, ADC_11db);
  // Blynk setup
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendSensorData);  // Every 2 seconds
}

/*************************** Void Loop ***************************/
void loop() 
{ 
  Blynk.run();
  timer.run();
  
}


/***********************  Function Definition *********************/
void Read_LDR() 
{
  /*
  * Comment : Max value for LDR = 4000 lumine
  */
  int Function_Ret_Value = 0;
  Function_Ret_Value = analogRead(ldr);
  Blynk.virtualWrite(V1, Function_Ret_Value);
  Serial.print("LDR Value : ");
  Serial.println(Function_Ret_Value);
}

void Read_Ultra_Sonic_Sensor()
{
  /*
  * Comment : Max value for Ultra-sonic sensor = 50 cm
  */
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration / 58.2 ;
  Blynk.virtualWrite(V0, distanceCm);
  if((distanceCm<=50) && (distanceCm>=0))
  {
    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
  }
}

void Read_Temp_Sensor()
{
  int adcVal = 0;
  adcVal = analogRead(LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in °C
  float tempC = milliVolt / 10;
  Blynk.virtualWrite(V2, tempC);
  // print the temperature in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  Serial.println(" ");
}

void Servo_Turn_ClockWise (void)
{
  servoMotor.attach(servopin);
  //  clock wise
  for(int pos = 10 ; pos< 20 ; pos++ )
  {
    servoMotor.write(pos);
    delay(15); // this speeds up the simulation
  }
  servoMotor.detach();
  delay(1000);
}

void Servo_Turn_Anti_ClockWise (void)
{
  servoMotor.attach(servopin);
  //  anti clock wise
  for(int pos = 90 ; pos< 120 ; pos++ )
  {
    servoMotor.write(pos);
    delay(15); // this speeds up the simulation
  }
  servoMotor.detach();
  delay(1000);
}

void Gate_ON(void)
{
  for(int i = 0 ; i<5 ; i++)
  {
    Servo_Turn_Anti_ClockWise();
  }
  servoMotor.detach();
}

void Gate_OFF(void)
{
  for(int i = 0 ; i<3 ; i++)
  {
    Servo_Turn_ClockWise();
  }
  servoMotor.detach();
}

