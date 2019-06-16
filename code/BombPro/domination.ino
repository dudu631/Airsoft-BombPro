void domination(){

  //SETUP INITIAL TIME 
  int minutos = GAMEMINUTES-1;
  boolean showGameTime=true;
  unsigned long a;
  unsigned long iTime=millis(); //  initialTime in millisec 
  unsigned long aTime;
  redTime=0;
  greenTime=0;

  int largoTono = 50;
// 0 = neutral, 1 = green team, 2 = red team
  a=millis();
  //Starting Game Code
  while(1)  // this is the important code, is a little messy but works good.
  {
    keypad.getKey();
    aTime=millis()- iTime;
    //Code for led blinking
    timeCalcVar=(millis()- iTime)%1000;
    if(timeCalcVar >= 0 && timeCalcVar <= 40)
    {
      if(team==1)digitalWrite(GREENLED, LOW);  
      if(team==2)digitalWrite(REDLED, LOW);  
    }
    if(timeCalcVar >= 50 && timeCalcVar <= 100)
    {    
      if(team==1)digitalWrite(GREENLED, HIGH);  
      if(team==2)digitalWrite(REDLED, HIGH);
    }
    // Sound!!! same as Destroy 
    if(timeCalcVar >= 0 && timeCalcVar <= 40 && soundEnable)tone(tonepin,tonoActivada,largoTono);

    if(timeCalcVar >= 245 && timeCalcVar <= 255 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 495 && timeCalcVar <= 510 && minutos-aTime/60000<4 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    if(timeCalcVar >= 745 && timeCalcVar <= 760 && minutos-aTime/60000<2 && soundEnable)tone(tonepin,tonoActivada,largoTono);
    //Help to count 3 secs
    if(a+2000<millis()){
      a=millis();   
      showGameTime=!showGameTime;
      cls();
    }
    //THE NEXT TO METHODS SHOW "GAME TIME" AND "CONTROLED ZONE TIME" IT SHOWS 2 AND 2 SEC EACH

    if(showGameTime){ //THE SECOND IS /2
      lcd.setCursor(3,0);
      lcd.print("GAME TIME");
      lcd.setCursor(3,1);
      printTime(minutos, aTime);
    }
    else if (!showGameTime){

      lcd.setCursor(2,0);
      if(team == 0)lcd.print("NEUTRAL ZONE");
      if(team == 1)lcd.print(" GREEN ZONE");
      if(team == 2)lcd.print("  RED ZONE");

      if(team>0){
        lcd.setCursor(3,1);
        printTimeDom(millis()-iZoneTime,true);
      }
    }

    //###########################CHECKINGS##################

    //Check If Game End
    if(minutos-aTime/60000==0 && 59-((aTime/1000)%60)==0)
    {
      gameOver();
    }

    //Check If IS neutral
    while((defuseando || cancelando) && team > 0)
    {
      cls();
      if(team>0)lcd.print("NEUTRALIZING...");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando || cancelando)
      {
         keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 20)
        {
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, HIGH);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          delay(1000);
          
          if(team==1){ 
            greenTime+=millis()-iZoneTime;
            iZoneTime=0; 

          }
          if(team==2){ 
            redTime+=millis()-iZoneTime;
            iZoneTime=0; 
          }
          team=0;
          break;
        }
      }
      cls();
    }

//Capturing red

    while(defuseando && team == 0 )
    {
      cls();
      if(team==0)lcd.print(" CAPTURING ZONE");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(defuseando)
      {
        keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 20)
        {
          digitalWrite(REDLED, LOW);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(REDLED, HIGH);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, HIGH);
          team=2;
          iZoneTime=millis();
          delay(1000);
          break;
        }
      }
      cls();
      digitalWrite(REDLED, HIGH);
    }

    //getting to green zone
    while(cancelando && team == 0 )
    {
      cls();
      if(team==0)lcd.print(" CAPTURING ZONE");
      lcd.setCursor(0,1);
      unsigned int percent=0;
      unsigned long xTime=millis(); //start disabling time
      while(cancelando)
      {
         keypad.getKey();
        timeCalcVar = (millis()- xTime)%1000;

        if( timeCalcVar >= 0 && timeCalcVar <= 20)
        {
          digitalWrite(GREENLED, LOW);  
          if(soundEnable)tone(tonepin,tonoAlarma1,200);
        }
        if(timeCalcVar >= 480 && timeCalcVar <= 500)
        {
          if(soundEnable)tone(tonepin,tonoAlarma2,200);
          digitalWrite(GREENLED, HIGH);
        }

        unsigned long seconds= millis() - xTime;
        percent = (seconds)/(ACTIVATESECONDS*10);
        drawPorcent(percent);

        if(percent >= 100)
        {
          digitalWrite(GREENLED, HIGH);
          team=1;
          iZoneTime=millis();
          delay(1000);
          break;
        }
      }
      cls();
      digitalWrite(GREENLED, HIGH);  
    }
  }
}

void gameOver(){

  if(team==1)greenTime+=millis()-iZoneTime;
  if(team==2)redTime+=millis()-iZoneTime;
  
  while(!isPressed(BT_SEL)){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("TIME OVER!");
    lcd.setCursor(0,1);

    //check who team win the base
    if(greenTime>redTime){
      //greenteam wins
      lcd.print(" GREEN TEAM WIN ");
    }
    else{
      //redteam wins 
      lcd.print(" RED TEAM WIN ");
    }
    delay(3000);
    cls();
    lcd.print("Red Time:");
    lcd.setCursor(5,1);
    printTimeDom(redTime,false);
    delay(3000);
    cls();
    lcd.print("Green Time:");
    lcd.setCursor(5,1);
    printTimeDom(greenTime,false);
    delay(3000);
  }
  lcd.print("Jogar Novamente?");
  lcd.setCursor(0,1);
  lcd.print("A: Sim  B: Nao");
  while(1)
  {
    var = keypad.waitForKey();
    if(var == 'a' ){
      tone(tonepin,2400,30);
      search();
      break;
    }  
    if(var == 'b' ){
      tone(tonepin,2400,30);
      menuPrincipal();
      break;
    }  
  } 
}
