#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
// <<<<<<<<<<<<<<< Macro definitions >>>>>>>>>>>>>>>>>>
#define LCD_Raw   2
#define LCD_Col   16
#define Key_Raw   4
#define Key_Col   4

char password[6],i;

// <<<<<<<<<<<<<<< Variables definition >>>>>>>>>>>>>>>>
char Keypad_Value[Key_Raw][Key_Col] =
{
  { '1'  , '2' , 3 , 'A'},
  {'4'  , '5' , 6 , 'B'},
  { '7'  , '8' ,  '9' , 'C'},
  {'*' , '0' , 'S' , 'D'}
};
byte pin_rows[Key_Raw]      = {19, 18, 5, 17}; // GPIO19, GPIO18, GPIO5, GPIO17 connect to the row pins
byte pin_column[Key_Col] = {16, 4, 2, 15};   // GPIO16, GPIO4, GPIO0, GPIO2 connect to the column pins
LiquidCrystal_I2C lcd(0x27, LCD_Col, LCD_Raw);   
String messageToScroll = "Welcome to my LAB ^-^" ;
Keypad keypad = Keypad( makeKeymap(Keypad_Value), pin_rows, pin_column, Key_Raw, Key_Col );

// <<<<<<<<<<<<<<< Function definitions >>>>>>>>>>>>>>>>>>
void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

// <<<<<<<<<<<<<<<<<<<<< Main Loop >>>>>>>>>>>>>>>>>>>>>>>>
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  // <<<<<<<<<<<<<<<<< LCD Start >>>>>>>>>>>>>>>
  lcd.setCursor(0, 0);
  lcd.print("Hello, Ziad ^-^ ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,1);
  scrollText(1, messageToScroll, 250, LCD_Col);
  delay(1000);
  lcd.clear(); 
}

void loop() {
  first:
  lcd.clear();
   lcd.print("ENTER PASSWORD");
   lcd.setCursor(0,1);
  do
 {
  char key = keypad.getKey();// Read the key
  if (key){
    Serial.print("Key Pressed : ");
    Serial.println(key);
    password[i]=key;
    i++;
    lcd.print('*');
    delay(500);
  }
 }
 while(i<6);
 i=0;
  if(password[0]=='1'&&password[1]=='2'&&password[2]=='4'&&password[3]=='5'&&password[4]=='7'&&password[5]=='8')
  {
    lcd.clear();
    lcd.print("AccessAuthorized");
    lcd.setCursor(1,0);
    scrollText(1, "Welcome Back Ziad ^-^", 250, LCD_Col);
    delay(4000);
    goto first;
  }
  else
  {
    lcd.clear();
    lcd.print("Access Denied");
    delay(4000);
    goto first;
  }
  
}
