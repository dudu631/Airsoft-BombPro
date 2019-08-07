//##################MENUS###############################

void menuPrincipal(){   //MAIN MENU

  digitalWrite(GREENLED, HIGH); 
 digitalWrite(REDLED, HIGH); 
  //Draw menu
  cls();//clear lcd and set cursor to 0,0
  int i=0;
  
  lcd.print(menu1[i]);
  lcd.setCursor(15,1);
  checkArrows(i,2);
  while(1){

    var = keypad.waitForKey();
    if(var == BT_UP && i>0){
      tone(tonepin,2400,30);
      i--;
      cls();
      lcd.print(menu1[i]);
      checkArrows(i,3);
      delay(100);
    }
    if(var == BT_DOWN && i<3){
      tone(tonepin,2400,30);
      i++;
      cls(); 
      lcd.print(menu1[i]);    
      checkArrows(i,3);
      delay(100);

    }

    if(var == BT_SEL){
      tone(tonepin,2400,30);
      cls();
      switch (i){

      case 0:
        sdStatus=true;
        configQuickGame();
        startGameCount();
        search();
        break;
      case 1: 
        saStatus=true;
        configQuickGame();
        startGameCount();
        sabotage();
        break;
      case 2:
        doStatus=true;
        configQuickGame();
        startGameCount();
        domination();
        break;
      case 3:
        config();
        break;
        
       
      }
    }
  }
}

void config(){
  //Draw menu
  lcd.clear();
  lcd.setCursor(0, 0);
  int i=0;
  char* menu2[]={
    "Game Config","OFF Time TEST", "RELE Test 3 sec.","...vazio..."}; // HERE YOU CAN ADD MORE ITEMS ON THE MENU
  delay(500);
  lcd.print(menu2[i]);
  checkArrows(i,3);

  while(1){
    var=keypad.waitForKey();
    if(var == BT_UP && i>0){
      tone(tonepin,2400,30);
      i--;
      lcd.clear();  
      lcd.print(menu2[i]);
      checkArrows(i,3);
      delay(50);

    }
    if(var == BT_DOWN && i<3){
      tone(tonepin,2400,30);
      i++;
      lcd.clear();  
      lcd.print(menu2[i]);
      checkArrows(i,3);
      delay(50);
    }
    if(var == BT_CANCEL){
      tone(tonepin,2400,30);
      menuPrincipal();
    }
    if(var == BT_SEL){
      tone(tonepin,2400,30);
      lcd.clear();
      switch (i){

      case 0:
        //gameConfigMenu
        lcd.print("No config menu!");
        delay(2000);
        config();
        break;

      case 1:
        //final time test menu
        lcd.print("Final time sound");

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


        config();
        break;

      case 2:
      //test rele menu
        cls();
        lcd.print("RELE ON!");
        digitalWrite(mosfet, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(3000);   // wait for 3 second
        cls();
        lcd.print("RELE OFF!");
        digitalWrite(mosfet, LOW);
        delay(2000);
        config();
        break;        

      }
    }
  }
}

void configQuickGame(){

  cls();
  //GAME TIME
  if(sdStatus || doStatus || saStatus){
    lcd.print("Game Time:");
    lcd.setCursor(0,1);
    checkArrows(1,2);
    delay(400);

    while(1){


      lcd.setCursor(0,1);  
      lcd.print(GAMEMINUTES);  
      lcd.print("   Minutos");

      var = keypad.waitForKey();

      if(var == 'a' && GAMEMINUTES<180){
        tone(tonepin,2400,30);
        GAMEMINUTES++;
        delay(50);
      }
      if(var == 'b' && GAMEMINUTES>1){
        tone(tonepin,2400,30);
        GAMEMINUTES--;
        delay(50);
      }
      if(var == 'c') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        menuPrincipal();
      } 
      if(var == 'd') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        break;
      }        
    }
    tone(tonepin,2400,30);
    cls();
  }
  //BOMB TIME
  if(sdStatus || saStatus){
    lcd.print("Bomb Time:");
    lcd.setCursor(0,1);
    checkArrows(1,2);
    delay(400);

    while(1){
      lcd.setCursor(0,1);  
      lcd.print(BOMBMINUTES);  
      lcd.print(" Minutos");
      var = keypad.waitForKey();


      if(var == 'b' && BOMBMINUTES>1){
        tone(tonepin,2400,30);
        BOMBMINUTES--;
        delay(50);
      }
      if(var == 'a' && BOMBMINUTES<20){
        tone(tonepin,2400,30);
        BOMBMINUTES++;
        delay(50);
      }
      if(var == 'c') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        menuPrincipal();
      } 
      if(var == 'd') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        break;
      }          
    }
    tone(tonepin,2400,30);
  }
  cls();
  //ARMING TIME
  if(sdStatus || doStatus || saStatus){
    lcd.print("Arm time:");
    lcd.setCursor(0,1);
    checkArrows(1,2);
    delay(400);

    while(1){
      lcd.setCursor(0,1);  
      lcd.print(ACTIVATESECONDS);  
      lcd.print(" segundos");
      var = keypad.waitForKey();
      
      if(var == 'b' && ACTIVATESECONDS>5){
        tone(tonepin,2400,30);
        ACTIVATESECONDS--;
        delay(50);
      }   
      if(var == 'a' && ACTIVATESECONDS<30){
        ACTIVATESECONDS++;
        tone(tonepin,2400,30);
        delay(50);
      }
      if(var == 'c') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        menuPrincipal();
      } 
      if(var == 'd') // Cancel or Back Button :')
      {
        tone(tonepin,2400,30);
        break;
      }     
    }
    tone(tonepin,2400,30);
    ACTIVATESECONDS-=1; // Just a fix

  }
  //Want sound??
  if(sdStatus || saStatus || doStatus){
    cls();
  lcd.print("Ativar som?");
  lcd.setCursor(0,1);
  lcd.print("A: SIM  B: NAO");


    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        soundEnable=true;
        tone(tonepin,2400,30);
        break;
      }  

      if(var == 'b' ){
        soundEnable=false;
        tone(tonepin,2400,30);
        break;
      }  
    }
  } 
  //Activate Mosfet at Terrorist game ends??? Boom!

  if(sdStatus || saStatus){
    cls();
    lcd.print("Ativar Rele?");
    lcd.setCursor(0,1);
    lcd.print("A: SIM  B: NO");
    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        mosfetEnable=true;
        tone(tonepin,2400,30);
        break;
      }  
      if(var == 'b' ){
        mosfetEnable=false;
        tone(tonepin,2400,30);
        break;
      }  
    } 
  }
  //You Want a password enable-disable game?
  if(sdStatus || saStatus){
    cls();
    lcd.print("Colocar Senha?");
    lcd.setCursor(0,1);
    lcd.print("A: SIM  B: NAO");

    while(1)
    {
      var = keypad.waitForKey();
      if(var == 'a' ){
        tone(tonepin,2400,30);
        setNewPass();
        passwordEnable = true;
        break;
      }  
      if(var == 'b' ){
        tone(tonepin,2400,30);
        passwordEnable = false;
        break;
      }  
    } 
    tone(tonepin,2400,30);
  }  
  //Continue the game :D
}
