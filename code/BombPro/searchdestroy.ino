void search(){
  cls();
  digitalWrite(REDLED, HIGH); 
  digitalWrite(GREENLED, HIGH);   
  //SETUP INITIAL TIME 
  int minutos = GAMEMINUTES-1;
  unsigned long iTime=millis(); //  initialTime in millisec 
  unsigned long aTime;
  //var='o';

  //Starting Game Code
  while(1){  // this is the important code, is a little messy but works good.
    //Code for led blinking
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 50)
    {
      digitalWrite(GREENLED, LOW);  
    }
    if(timeCalcVar >= 90 && timeCalcVar <= 130)
    {    
      digitalWrite(GREENLED, HIGH);  
    }

    lcd.setCursor(0,0);
    lcd.print("TIEMPO de JUEGO");
    aTime=millis()- iTime;
    lcd.setCursor(3,1);

    //PRINT TIME ON LCD

    printTime(minutos, aTime);

    //###########################CHECKINGS##################

    //Check If Game End
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)
    {
      lcd.clear();
      while(1){
        lcd.print("FIN DEL TIEMPO!");
        lcd.setCursor(0,1);
        lcd.print("DEFENSORES WIN ");  

        digitalWrite(mosfet, HIGH);
        delay(300);
        digitalWrite(mosfet, LOW);
        delay(1000);
        digitalWrite(mosfet, HIGH);
        delay(300);
        digitalWrite(mosfet, LOW);
        delay(1000);
        digitalWrite(mosfet, HIGH);
        delay(300);
        digitalWrite(mosfet, LOW);
        delay(1000);
        digitalWrite(mosfet, HIGH);
        delay(200);
        digitalWrite(mosfet, LOW);
        delay(100);
        digitalWrite(mosfet, HIGH);
        delay(200);
        digitalWrite(mosfet, LOW);
        delay(100);


        for(int i = 1000; i>200; i--){
          if(soundEnable)tone(tonepin,i);
          delay(5);
        }
        noTone(tonepin);
        delay(5000);
        cls();
        menuPrincipal();
      }
    }
    //Serial.println(keypad.getKey());
    //USED IN PASSWORD GAME 
    if('d' == keypad.getKey() && passwordEnable){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ARMANDO BOMBA");
      delay(1000);//a little delay to think in the password
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Enter Code");

      setCode();// we need to set the comparation variable first it writes on enteredText[]

      //then compare :D

      if(comparePassword()){
        destroy();
      }        
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Code Error!");
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(500);
      cls();
    }
    //Check If Is Activating
    while(defuseando && !passwordEnable)
    {
      digitalWrite(GREENLED, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" ARMANDO BOMBA");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando)
      {
        keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 40)
        {
          digitalWrite(REDLED, LOW);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 520)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, LOW);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, HIGH);
          destroy();// jump to the next gamemode
        }
      }
      cls();
      digitalWrite(REDLED, HIGH);  

    }
  }
}

void destroy(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" BOMBA ARMADA");
  delay(1000);
  int minutos=BOMBMINUTES-1;
  unsigned long iTime=millis();
  unsigned long aTime;
  int largoTono = 50;

  //MAIN LOOP
  while(1){
    
    //If you fail disarm. 
    if(endGame){
      explodeSplash();
    }

    //Led Blink

    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 40)
    {
      digitalWrite(REDLED, LOW);  
      if(soundEnable)tone(tonepin,tonoActivada,largoTono);
    }
    if(timeCalcVar >= 180 && timeCalcVar <= 220){
      digitalWrite(REDLED, HIGH);  
    }
    //Sound 
    aTime= millis()- iTime;
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 245 && timeCalcVar <= 255 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 495 && timeCalcVar <= 510 && minutos-aTime/60000<4 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 745 && timeCalcVar <= 760 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if( minutos-aTime/60000==0 && 59-((aTime/1000)%60) < 10)largoTono = 300;

    lcd.setCursor(0,0);
    lcd.print(" DETONACAO EM ");
    //Passed Time
   
    lcd.setCursor(3,1);

    ////////HERE ARE THE TWO OPTIONS THAT ENDS THE GAME///////////

    ////TIME PASED AWAY AND THE BOMB EXPLODES
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)// Check if game ends
    {
      explodeSplash();
    }
    //print time

    printTime(minutos, aTime);

    //// SECOND OPTION: YOU PRESS DISARMING BUTTON  

    //IF IS A PASSWORD GAME 

    if('d' == keypad.getKey() && passwordEnable){

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("DESARMANDO BOMBA");
      delay(1000);//a little delay to think in the password

      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Enter Code");

      setCode();// we need to set the compare variable first

      //then compare :D

      if(comparePassword()){
        disarmedSplash();
      }        
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Code Error!");
      if(soundEnable)tone(tonepin,errorTone,200);
      delay(500);
      cls();
    }

    if(defuseando && !passwordEnable)// disarming bomb
    {
      lcd.clear();
      digitalWrite(REDLED, HIGH);  
      lcd.setCursor(0,0);
      lcd.print(" DESARMANDO ");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis();
      while(defuseando)
      {
        keypad.getKey();
        //check if game time runs out during the disabling
        aTime= millis()- iTime;
        if((minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0) || minutos-aTime/60000>4000000000){ 
          endGame = true;
        }
        timeCalcVar=(millis()- xTime)%1000;
        if(timeCalcVar>= 0 && timeCalcVar <= 20)
        {
          digitalWrite(GREENLED, LOW);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(GREENLED, HIGH);  
        }
        unsigned long seconds=(millis()- xTime);
        percent= seconds/(ACTIVATESECONDS*10);
        drawPorcent(percent);  

        //BOMB DISARMED GAME OVER
        if(percent >= 100)
        {
          disarmedSplash();   
        }
      }
      digitalWrite(REDLED, HIGH); 
      digitalWrite(GREENLED, HIGH);
      cls();
    }
  }
}
