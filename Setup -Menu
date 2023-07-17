#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <stdlib.h>

//Keypad program by Bagaz P
//This code is very badly optimized & bad code readability
//I'll fix as soon as i come to the workshop ;)

/*how this works in simple words is that there's a function called state controller
it control the switching between states of the program, so it can switch back and forth between menu,
and make sure that there's no state collisions/crash*/

//keypad init
const byte ROW_NUM    = 4; //numbers of row
const byte COLUMN_NUM = 4; //numbers of column

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9,8,7,6}; //rows pin, we use analog pin here, there's a chance analog pins will be use for sensors, adjust accordingly!
byte pin_column[COLUMN_NUM] = {5,4,3,2}; //same for column, we use analog pins too

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

//lcd init
LiquidCrystal_I2C lcd(0x27, 16,2);

//Currently Unused
String menuItems[] = {
  "Menu 1",
  "Menu 2",
  "Menu 3",
  "Menu 4"
};

int currentMenu = 1;    
int currentSPSelector = 1;
int currentState = 0; //var for current State of the program
int stateCount = 6;   //var for counting how many states in the program 
int menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

  //CURRENT VALUE FROM THE SENSOR READINGS
  float sayur1_phValue = 0.0;
  float sayur2_phValue = 0.0;
  float sayur3_phValue = 0.0;
  float sayur4_phValue = 0.0;

  float sayur1_TDSValue = 0.0;
  float sayur2_TDSValue = 0.0;
  float sayur3_TDSValue = 0.0;
  float sayur4_TDSValue = 0.0;

  //PH SET POINTS SET BY THE USER
  float sayur1_phSP = 0.0;
  float sayur2_phSP = 0.0;
  float sayur3_phSP = 0.0;
  float sayur4_phSP = 0.0;

  float sayur1_TDSSP = 0.0;
  float sayur2_TDSSP = 0.0;
  float sayur3_TDSSP = 0.0;
  float sayur4_TDSSP = 0.0;

  String enteredText;

void setup() {
  // Setup LCD
  lcd.backlight();
  lcd.begin(16, 2);
  // lcd.print("Menu LCD 16x2");
  delay(2000);
  lcd.clear();
  lcd.backlight();
  lcd.init();

  stateController();
}

void loop() {
  keyPadController(); //call keypad controller function
}

void keyPadController()
{
  char key = keypad.getKey();
  if (key) {
    if(currentState == 5)
    {
      if (key == 'D') {
      //D is for saving the set points
        currentState = 3;
        saveText();
      }
      else if (key == 'C')
      {
        currentState--;
        stateController();
      }
      else if (key == '*')
      {
        enteredText = "";
        lcd.setCursor(0,1);
        lcd.print("__             ");
      }
      else
      {
        if(key == '#'){
          enteredText += '.';
        }
        else{
          enteredText += key;
        }
        lcd.setCursor(0,1);
        lcd.print(enteredText);
      }
    }
    else{
      switch (key) {
      case 'A':
        // Tombol A ditekan, pindah ke menu sebelumnya
        if(currentState == 1)
        {
          currentMenu--;
          if (currentMenu < 0) {
            currentMenu = menuCount - 1;
          }
        }
        else if(currentState == 3){
          currentSPSelector--;
          if(currentSPSelector < 0){
            currentSPSelector = 1;
          }
        }
        stateController();
        break;
        
      case 'B':
        // Tombol D ditekan, pindah ke menu berikutnya
        if(currentState == 1)
        {
          currentMenu++;
          if (currentMenu >= menuCount) {
            currentMenu = 0;
          }
        }
        else if(currentState == 3){
          currentSPSelector++;
          if(currentSPSelector >= 1){
            currentSPSelector = 0;
          }
        }
        stateController();
        break;
      case 'C':
        currentState--;
        if(currentState < 0){
          currentState = 0;
        }
        stateController();
        break;
      case 'D':
        currentState++;
        if(currentState > stateCount){
          currentState = 5;
        }
        stateController();
        break;
    }
    }

    
  }
}

void stateController(){
  if(currentState == 0)
  {
    displayDefault();
  }
  else if(currentState == 1)
  {
    displayMenu();
  }
  else if(currentState == 2)
  {
    displayDetail();
  }
  else if(currentState == 3)
  {
    setPointSelector();
  }
  else if(currentState == 4){
    displaySetPoint();
  }
  else{
    changeSetPoint();
  }
}
void displayDefault() {
  lcd.clear();
  currentSPSelector = 1;
  lcd.setCursor(0, 0);
  lcd.print("Pilih Sayur...");
  lcd.setCursor(0, 1);
  lcd.print("D untuk lanjut");
}

void displayMenu() {
  lcd.clear();
  if(currentMenu == 1){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("=>Sayur 1: ");
    lcd.setCursor(0, 1);
    lcd.print("  Sayur 2: ");
  }
  else if(currentMenu == 2){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Sayur 1: ");
    lcd.setCursor(0, 1);
    lcd.print("=>Sayur 2: ");
  }
  else if(currentMenu == 3){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("=>Sayur 3: ");
    lcd.setCursor(0, 1);
    lcd.print("  Sayur 4: ");
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Sayur 3: ");
    lcd.setCursor(0, 1);
    lcd.print("=>Sayur 4: ");
  }
  
  
  }

  void displayDetail() 
  {
    lcd.clear();
    if(currentMenu == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("pH S1 : " + String(sayur1_phValue));
      lcd.setCursor(0, 1);
      lcd.print("TDS S1 : " + String(sayur1_TDSValue));
    }
    else if(currentMenu == 2){
      lcd.setCursor(0, 0);
      lcd.print("pH S2 : " + String(sayur2_phValue));
      lcd.setCursor(0, 1);
      lcd.print("TDS S2 : " + String(sayur2_TDSValue));
    }
    else if(currentMenu == 3){
      lcd.setCursor(0, 0);
      lcd.print("pH S3 : "  + String(sayur3_phValue));
      lcd.setCursor(0, 1);
      lcd.print("TDS S3 : "  + String(sayur3_TDSValue));
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print("pH S4 : "  + String(sayur4_phValue));
      lcd.setCursor(0, 1);
      lcd.print("TDS S4 : "  + String(sayur4_TDSValue));
    }
  // lcd.print(currentMenu + 1);
  // lcd.setCursor(0, 1);
  // lcd.print(menuItems[currentMenu]);
  
}

  void setPointSelector(){
    lcd.clear();
    if(currentSPSelector == 1){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">SetPoint pH");
      lcd.setCursor(0, 1);
      lcd.print(" SetPoint TDS");
    }
    else{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" SetPoint pH");
      lcd.setCursor(0, 1);
      lcd.print(">SetPoint TDS");
    }
  }

  void displaySetPoint(){
    lcd.clear();
    if(currentSPSelector == 1){
      if(currentMenu == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S1");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur1_phSP));
      }
      else if(currentMenu == 2){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S2");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur2_phSP));
      }
      else if(currentMenu == 3){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S3");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur3_phSP));
      }
      else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S4");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur4_phSP));
      }
    }
    else{
      if(currentMenu == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S1");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur1_TDSSP));
      }
      else if(currentMenu == 2){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S2");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur2_TDSSP));
      }
      else if(currentMenu == 3){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S3");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur3_TDSSP));
      }
      else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S4");
        lcd.setCursor(0, 1);
        lcd.print(String(sayur4_TDSSP));
      }
    }
    
  }

  void changeSetPoint()
  {
    lcd.clear();
    if(currentSPSelector == 1){
      if(currentMenu == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S1");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
      else if(currentMenu == 2){
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S2");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
      else if(currentMenu == 3){
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S3");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
      else{
        lcd.setCursor(0, 0);
        lcd.print("Setpoint pH S4");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
    }
    else{
      if(currentMenu == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S1");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
      else if(currentMenu == 2){
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S2");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
      else if(currentMenu == 3){
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S3");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
      else{
        lcd.setCursor(0, 0);
        lcd.print("Setpoint TDS S4");
        lcd.setCursor(0, 1);
        lcd.print("__");
      }
    }
    
  }

  void saveText() 
  {
    lcd.clear();
    if(currentSPSelector == 1){
      if(currentMenu == 1){
        sayur1_phSP = atof(enteredText.c_str());
      }
      else if(currentMenu == 2){
        sayur2_phSP = atof(enteredText.c_str());
      }
      else if(currentMenu == 3){
        sayur3_phSP = atof(enteredText.c_str());
      }
      else{
        sayur4_phSP = atof(enteredText.c_str());
      }
    }
    else
    {
      if(currentMenu == 1){
        sayur1_TDSSP = atof(enteredText.c_str());
      }
      else if(currentMenu == 2){
        sayur2_TDSSP = atof(enteredText.c_str());
      }
      else if(currentMenu == 3){
        sayur3_TDSSP = atof(enteredText.c_str());
      }
      else{
        sayur4_TDSSP = atof(enteredText.c_str());
      }
    }
    lcd.print("Setpoint Updated:");
    lcd.setCursor(0, 1);
    lcd.print(enteredText);
    delay(1000);
    lcd.clear();
    enteredText = "";
    stateController();
}
