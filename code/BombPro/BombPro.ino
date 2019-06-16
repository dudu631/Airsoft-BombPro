#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

const byte ROWS = 4;
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {3, 2, 4, 5}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


char enteredText[8];
char password[8];
int key=-1;
char lastKey;
char var;
boolean passwordEnable=false;


char BT_RIGHT = '4';
char BT_UP = 'a';
char BT_DOWN = 'b';
char BT_LEFT = '6';
char BT_SEL = 'd';   
char BT_CANCEL = 'c';
char BT_DEFUSER = 'x';   // not implemented

//leds

const int REDLED = 9;
const int GREENLED = 11;

boolean mosfetEnable = false;
const int mosfet = 9;
//IS VERY IMPORTANT THAT YOU TEST THIS TIME. BY DEFAULT IS IN 1 SEC. THAT IS NOT TOO MUCH. SO TEST IT!
const int MOSFET_TIME = 15000;

//TIME INTS
int GAMEHOURS = 0;
int GAMEMINUTES = 45;
int BOMBMINUTES = 4;
int ACTIVATESECONDS = 5;

boolean endGame = false;

boolean sdStatus = false; //search and destroy game enable used in config
boolean saStatus = false; //same but SAbotaghe
boolean doStatus = false; //for DEmolition
boolean start = true;
boolean defuseando;
boolean cancelando;
// SOUND TONES
boolean soundEnable = true;
int tonepin = 8; 
int tonoPitido = 3000;
int tonoAlarma1 = 700;
int tonoAlarma2 = 2600;
int tonoActivada = 1330;
int errorTone = 100;

unsigned long iTime;
unsigned long timeCalcVar;
unsigned long redTime;
unsigned long greenTime;
unsigned long iZoneTime;
byte team=0;

void setup(){
  lcd.begin(16,2); 
  lcd.backlight();
  Serial.begin(9600);
  //  lcd.init();                      
  //  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print(" R E B O R N");
  lcd.setCursor(1,1);
  lcd.print(" A I R S O F T");
  keypad.setHoldTime(50);
  keypad.setDebounceTime(50);
  keypad.addEventListener(keypadEvent);
  delay(3000); 
  pinMode(GREENLED, OUTPUT);     
  pinMode(REDLED, OUTPUT); 
  pinMode(mosfet, OUTPUT);  
  // 
  byte bar1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
  };
  byte bar2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
  };
  byte bar3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
  };
  byte bar4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
  };
  byte bar5[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };
  byte up[8] = {
    B00000,
    B00100,
    B01110,
    B11111,
    B11111,
    B00000,
    B00000,
  };

  byte down[8] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000,
  };
  lcd.createChar(0,bar1);
  lcd.createChar(1,bar2);
  lcd.createChar(2,bar3);
  lcd.createChar(3,bar4);
  lcd.createChar(4,bar5);
  lcd.createChar(5,up);
  lcd.createChar(6,down);
}

void loop(){
  menuPrincipal();
}
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){

      }
    break;
    case RELEASED:
      switch (key){
         case 'd': defuseando= false;
         Serial.println("d Releases");
         break;
         case 'c': cancelando=false;
         Serial.println("c Releases");
         break;
      }
    break;
    case HOLD:
      switch (key){
        case 'd': defuseando= true;
        Serial.println("d hold");
        break;
        case 'c': cancelando=true;
        Serial.println("c hold");
        break;
      }
    break;
  }
}

void disarmedSplash(){
  endGame = false;
  digitalWrite(REDLED, LOW); 
  digitalWrite(GREENLED, LOW);
  if(sdStatus || saStatus){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BOMBA DESARMADA");
    lcd.setCursor(0,1);
    lcd.print(" PARABENS ");
    digitalWrite(GREENLED, LOW);  
    delay(5000);
    digitalWrite(GREENLED, HIGH); 
  }
  //end code
  lcd.clear();
  lcd.print("Jogar outra vez?");
  lcd.setCursor(0,1);
  lcd.print("A: SIM  B: NAO");
  digitalWrite(REDLED, HIGH);  
  digitalWrite(GREENLED, HIGH); 
  while(1)
  {
    var = keypad.waitForKey();
    if(var == 'a' ){
      tone(tonepin,2400,30);
      //
      if(sdStatus){
        startGameCount();
        search();
      }
      if(saStatus){
        saStatus=true;
        startGameCount();
        start=true; //
        sabotage();
      }
    }  
    if(var == 'b' ){
      tone(tonepin,2400,30);
      menuPrincipal();
      break;
    }  
  } 
}

void explodeSplash(){
  digitalWrite(REDLED, HIGH);  
  digitalWrite(GREENLED, HIGH); 
  cls();
  delay(100);
  endGame = false;
  lcd.setCursor(1,0);
  lcd.print("TERRORISTAS WIN");
  lcd.setCursor(0,1);
  lcd.print("  FIM DE JOGO");
  for(int i = 200; i>0; i--)// 
  {
    tone(tonepin,i);
    delay(20);
  }
  noTone(tonepin);
  if(mosfetEnable){
    activateMosfet(); 
  }
  delay(5000);
  cls();

  //end code
  lcd.print("Jogar outra vez?");
  lcd.setCursor(0,1);
  lcd.print("A: SIM  B: NAO");
  while(1)
  {
    var = keypad.waitForKey();
    if(var == 'a' ){
      tone(tonepin,2400,30);
      //
      if(sdStatus){
        startGameCount();
        search();
      }
      if(saStatus){
        saStatus=true;
        startGameCount();
        start=true; //
        sabotage();
      }
    }  
    if(var == 'b' ){
      tone(tonepin,2400,30);
      menuPrincipal();

      break;
    }  
  } 
}
