int start()
{
  but = 0;
  if(point != 11)
  {
    myScreen.background(255, 255, 255);
    myScreen.text("START", 50, 1);
    /*if(err)
    {
      myScreen.text("DEVICE ERRROR", 0, 20);
      delay(5000);
      return 1;
    }
    else*/
      myScreen.text("INIT...", 0, 20);
    delay(100);
  }
  point = 11;

  w_temp[0] = 25; w_temp[1] = 25; w_temp[2] = 0; w_temp[3] = 25; //zmiana granic
  if(temp_chceck()) //sprawdzanie temp
  {
    return 1;
  }
  myScreen.text("[||         ]", 0, 40);
  
  //włączenie pompy
  
  w_temp[0] = 20; w_temp[2] = 5; w_temp[3] = 25; //zmiana granic
  if(temp_chceck()) //sprawdzanie temp
  {
    return 1;
  }
  myScreen.text("[||||       ]", 0, 40);
  
  for (POT0_Dn = 0; POT0_Dn < 63; POT0_Dn++) //właczenie d peltiera na 25%
  {
    myScreen.text("B.PEL -> 25%", 0, 60); //wyświetl aktualny proces
    DigitalPotWrite(POT0_SEL , 255 - POT0_Dn);
    delay(load);
  }
  myScreen.stroke(255, 255, 255);
  myScreen.text("B.PEL -> 25% P", 0, 60);
  myScreen.stroke(0, 0, 0);
  
  w_temp[0] = 30; w_temp[2] = 5; w_temp[3] = 5; //zmiana granic
  
  if(temp_chceck()) //sprawdzanie temp
  {
    return 1;
  }
  myScreen.text("[||||||     ]", 0, 40); //wyświetl postęp

  for (POT1_Dn = 0; POT1_Dn < 38; POT1_Dn++) //właczenie m peltiera na 15%
  {
    myScreen.text("S.PEL -> 15%", 0, 60); //wyświetl aktualny proces
    DigitalPotWrite(POT1_SEL , 255 - POT1_Dn);
    delay(load);
  }
  myScreen.stroke(255, 255, 255);
  myScreen.text("S.PEL -> 15%", 0, 60);
  myScreen.stroke(0, 0, 0);
  //właczenie wentylatora
  
  w_temp[0] = 30; w_temp[2] = 5; w_temp[3] = 5; //zmiana granic
  if(temp_chceck()) //sprawdzanie temp
  {
    return 1;
  }
  myScreen.text("[|||||||||  ]", 0, 40); //wyświetl postęp
  
  // właczenie d peltiera na 75%
  
  w_temp[0] = 30; w_temp[2] = 5; w_temp[3] = 5; //zmiana granic
  if(temp_chceck()) //sprawdzanie temp
  {
    return 1;
  }
  myScreen.text("[|||||||||||]", 0, 40); //wyświetl postęp

  
    //przykład
  for(POT0_Dn; POT0_Dn < 256; POT0_Dn++)
  {
    DigitalPotWrite(POT0_SEL, 255 - POT0_Dn);
    if(POT0_Dn%10 == 0)
    {
      POT1_Dn = POT1_Dn + 5;
      DigitalPotWrite(POT1_SEL, 255 - POT1_Dn);
    }
    //delay(load);
  }
  myScreen.text("INIT... DONE", 0, 20); //wyświetl postęp
  delay(5000);
  return 1;
}




void mDelay( int ms) {
  mDelay(1);
  while( ms-- ) {
    delay(1);
    
    mstick++;
    if( mstick > 79 ) mstick=0;
    Serial.println(mstick);
  }
}
