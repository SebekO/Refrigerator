/*
Created by:
Sebastian Owarzany
Technical Physics
Faculty of Physics and Applied Computer Science
AGH University of Science and Technology
https://github.com/SebekO
*/
#include <TFT.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "board_settings.h"

void setup()
{
  SPI.begin(); //inicjalizacja SPI
  myScreen.begin(); //wlacz wyswietlacz
  ads.begin(); //inicjalizacja ADCI
  // ads.setGain(GAIN_ONE);   // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  
  //deklaracja wyjsc:
  pinMode(CS_PIN, OUTPUT); //potencjomentr
  pinMode(start_button_pin, INPUT);
  pinMode(stop_button_pin, INPUT);
  pinMode(start_signal_pin, OUTPUT);
  pinMode(stop_signal_pin, OUTPUT);
  pinMode(status_power_pin, INPUT);
  pinMode(status_own_pin, OUTPUT);
  digitalWrite(start_signal_pin, LOW);
  digitalWrite(stop_signal_pin, LOW);
  digitalWrite(status_own_pin, HIGH);
  
  myScreen.setTextSize(txtsize); //ustaw czcionke
  myScreen.background(255, 255, 255); //ustaw kolor tla
  myScreen.stroke(0, 0, 0); //ustaw kolor liter
  s[0] = 247; //stopnie
  
  if((digitalRead(status_power_pin)) == 0){
    myScreen.background(255, 255, 255);
    myScreen.stroke(255, 0, 0);
    myScreen.text("BLAD ", 0, 1); 
    myScreen.text("KONTROLERA", 0, 20);
    myScreen.text("ZASILANIA!!!", 0, 40);
    myScreen.stroke(0, 0, 0);
    screen_position = -1;
    delay(1000);
  }
  else{
    //inicjalizacja ekranu startowego:
    myScreen.text("T_o:", 0, 1);
    myScreen.text(s, 138, 1);
    myScreen.text("C", 149, 1);
    myScreen.text("T_b:", 0, 26);
    myScreen.text(s, 138, 26);
    myScreen.text("C", 149, 26);
    myScreen.text("START", 0, 110);
    myScreen.stroke(255, 0, 0);
    myScreen.text("STOP", 112, 110);
    myScreen.stroke(0, 0, 0);
  }
}

void loop()
{
//  if((digitalRead(status_power_pin)) == 0){
//    if(screen_position != -1){
//      myScreen.background(255, 255, 255);
//      myScreen.stroke(255, 0, 0);
//      myScreen.text("BLAD ", 0, 1); 
//      myScreen.text("KONTROLERA", 0, 20);
//      myScreen.text("ZASILANIA!!!", 0, 40);
//      myScreen.stroke(0, 0, 0);
//      delay(1000);
//    }
//    screen_position = -1;    
//  }
//  else{
//    pomiar();
//    if( digitalRead(start_button_pin) ){
//      start_dev();
//    }
//    if( digitalRead(stop_button_pin) ){
//      stop_dev();
//    }
//  }
  start_dev();
  delay(1000);
  stop_dev();
  delay(1000);
}

void stop_dev()
{
  myScreen.background(255, 255, 255);
  myScreen.text("STOP", 50, 1);
  myScreen.text("INIT", 0, 20);
  delay(1000);
  
  DigitalPotWrite(BOTH_POT_SEL, BOTH_POT_Dn);
  
  myScreen.text("INIT.", 0, 20);
  delay(1000);
  myScreen.text("INIT..", 0, 20);
  delay(1000);
  myScreen.text("INIT...", 0, 20);
  delay(1000);
  myScreen.text("DEV STOPPED", 0, 40);
  
  if(digitalRead(start_signal_pin)){
    digitalWrite(start_signal_pin, LOW);
  }
  digitalWrite(stop_signal_pin, HIGH);
  delay(5000);
  
  screen_position = -2;
  myScreen.background(255, 255, 255);
}

void start_dev()
{
  myScreen.background(255, 255, 255);
  myScreen.text("START", 50, 1);
  myScreen.text("INIT", 0, 20);
  myScreen.stroke(255, 0, 0);
  myScreen.text("STOP", 112, 110);
  myScreen.stroke(0, 0, 0);
  delay(1000);
  
  if(digitalRead(stop_signal_pin)){
    digitalWrite(stop_signal_pin, LOW);
  }
  digitalWrite(start_signal_pin, HIGH);
  
//  if( digitalRead(stop_button_pin) ){
//    digitalWrite(start_signal_pin, LOW);
//    stop_dev();
//  }
  POT0_Dn = 128;
  POT1_Dn = 128;
  
  myScreen.text("INIT.", 0, 20);
  DigitalPotWrite(POT0_SEL, POT0_Dn);
  delay(load);
  myScreen.text("INIT..", 0, 20);
  DigitalPotWrite(POT1_SEL,POT1_Dn);
  delay(load);
  myScreen.text("INIT...", 0, 20);
  delay(1000); 
  myScreen.text("DEV STARTED", 0, 40);
  delay(5000);
  
  screen_position = 1;
  myScreen.background(255, 255, 255);
}

void pomiar()
{
  int16_t adc0, adc1;
  
  if(screen_position != 0){
    myScreen.background(255, 255, 255);
    myScreen.text("T_o:", 0, 1);
    myScreen.text(printout1, 50, 1);
    myScreen.text(s, 138, 1);
    myScreen.text("C", 149, 1);
    myScreen.text("T_b:", 0, 26);
    myScreen.text(printout2, 50, 26);
    myScreen.text(s, 138, 26);
    myScreen.text("C", 149, 26);
    myScreen.text("START", 0, 110);
    myScreen.stroke(255, 0, 0);
    myScreen.text("STOP", 112, 110);
    myScreen.stroke(0, 0, 0);
  }
  
  screen_position = 0;
  
  adc0 = ads.readADC_SingleEnded(0); //odczyt z termopary O
  digit1 = map(adc0, 0, 1023 , Tmin, Tmax);
  if(digit1_tmp != digit1)
  {
    myScreen.stroke(255, 255, 255);
    myScreen.text(printout1, 50, 1);
    String elapsedVar1 = String(digit1);
    elapsedVar1.toCharArray(printout1,5);
    myScreen.stroke(0, 0 ,0);
    myScreen.text(printout1, 50, 1);
  }
  adc0 = ads.readADC_SingleEnded(0); 
  digit1_tmp = map(adc0, 0, 1023 , Tmin, Tmax);
  
  adc1 = ads.readADC_SingleEnded(1); //odczyt z termopary B
  digit2 = map(adc1, 0, 1023 , Tmin, Tmax);
  if(digit2_tmp != digit2)
  {
    myScreen.stroke(255, 255, 255);
    myScreen.text(printout2, 50, 26);
    String elapsedVar2 = String(digit2);
    elapsedVar2.toCharArray(printout2,5);
    myScreen.stroke(0, 0 ,0);
    myScreen.text(printout2, 50, 26);  
  }
  adc1 = ads.readADC_SingleEnded(1);
  digit2_tmp = map(adc1, 0, 1023 , Tmin, Tmax);
}

void DigitalPotWrite(int cmd, int val)
{
  // constrain input value within 0 - 255
  val = constrain(val, 0, 255);
  // set the CS pin to low to select the chip:
  digitalWrite(CS_PIN, LOW);
  // send the command and value via SPI:
  SPI.transfer(cmd);
  SPI.transfer(val);
  // Set the CS pin high to execute the command:
  digitalWrite(CS_PIN, HIGH);
}
  
