void drawPorcent(byte porcent){
  //TODO: Optimize this code 
  byte i=1;
  int aDibujar=(8*porcent)/10;
  lcd.setCursor(0,1);

  if(aDibujar<5)
  {
    switch(aDibujar){
    case 0:
      break;
    case 1:
      lcd.write((uint8_t)0);
      break;
    case 2:
      lcd.write(1);
      break;
    case 3:
      lcd.write(2);
      break;
    case 4:
      lcd.write(3);
      break;
    }
  }
  while(aDibujar>=5){
    if(aDibujar>=5)
    {
      lcd.write(4);
      aDibujar-=5;
    }
    if(aDibujar<5)
    {
      switch(aDibujar){
      case 0:
        break;
      case 1:
        lcd.write((uint8_t)0);
        break;
      case 2:
        lcd.write(1);
        break;
      case 3:
        lcd.write(2);
        break;
      case 4:
        lcd.write(3);
        break;
      }
    }
  }
}
void cls(){
  lcd.clear();
  lcd.setCursor(0,0);
}

void printTime(unsigned long minutos, unsigned long aTiempo){
  //minutes
  if((minutos-aTiempo/60000)<10)
  {
    lcd.print("0");
    lcd.print(minutos-aTiempo/60000);
  }
  else
  {
    lcd.print(minutos-aTiempo/60000);
  }
  lcd.print(":");
  //seconds
  if((59-((aTiempo/1000)%60))<10)
  {
    lcd.print("0");
    lcd.print(59-((aTiempo/1000)%60));
  }
  else
  {
    lcd.print(59-((aTiempo/1000)%60));
  }
  lcd.print(":");
  //this not mach with real time, is just a effect, it says 999 because millis%1000 sometimes give 0 LOL
  lcd.print(999-(millis()%1000));
}

void printTimeDom(unsigned long aTiempo, boolean showMillis){
  //minutes
  if((aTiempo/60000)<10)
  {
    lcd.print("0");
    lcd.print(aTiempo/60000);
  }
  else
  {
    lcd.print(aTiempo/60000);
  }
  lcd.print(":");
  //seconds
  if(((aTiempo/1000)%60)<10)
  {
    lcd.print("0");
    lcd.print((aTiempo/1000)%60);
  }
  else
  {
    lcd.print((aTiempo/1000)%60);
  }
  if(showMillis){
    lcd.print(":");
    //this not mach with real time, is just a effect, it says 999 because millis%1000 sometimes give 0 LOL
      lcd.print(999-millis()%1000);

  }
}


void startGameCount(){
  cls();
  lcd.setCursor(1,0);
  lcd.print("Ready to Begin");
  lcd.setCursor(0,1);
  lcd.print(".Aperte um Botao.");
  keypad.waitForKey();//if you press a button game start

  cls();
  lcd.setCursor(1,0);
  lcd.print("Starting Game");
  for(int i = 5; i > 0 ; i--){ // START COUNT GAME INIT
    lcd.setCursor(5,1);
    tone(tonepin,2000,100);
    lcd.print("IN ");
    lcd.print(i);
    delay(1000);
  }
  cls();
}

void checkArrows(byte i,byte maxx ){

  if(i==0){
    lcd.setCursor(15,1);
    lcd.write(6); 
  }
  if(i==maxx){  
    lcd.setCursor(15,0);
    lcd.write(5);
  }
  if(i>0 && i<maxx){
    lcd.setCursor(15,1);
    lcd.write(6);
    lcd.setCursor(15,0);
    lcd.write(5);  
  }
}

void activateMosfet(){

  //lcd.print("Mosfet ON!");
  digitalWrite(mosfet, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(MOSFET_TIME);   // wait for 4 second
  //lcd.print("Mosfet OFF!");
  digitalWrite(mosfet, LOW);

}
