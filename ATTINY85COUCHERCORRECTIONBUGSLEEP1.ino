#include <avr/sleep.h>

// This library contains functions to set various low-power 
// states for the ATmega328

#include <DS1302.h>

#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int pinLed = 1;////PB1
volatile int f_wdt = 0;

// Init the DS1302
//DS1302 rtc(2, 3, 4);
// INVERSE  JAUNE VERT NOIR FIL JAUNE !!!!!!!!!!!!!!!!!!!!!!
DS1302 rtc(2, 4, 3);
int address = 0; //Address to first EEPROM cell.

  byte numbers[49][4] = {
    //jan fev 1 14 21 28
    { 8,54, 17, 05 },
    { 8,50, 17, 15 },
    { 8,44, 17, 26 },
    { 8,35, 17, 37 },
    { 8,20, 17, 55 },
    { 8,8, 18, 7 },
    { 7,55, 18, 20 },
    { 7,41, 18, 32 },
    
    //mars avril 1 14 21 28
    { 7,24, 18, 45 },
    { 7,8, 18, 57 },
    { 6,53, 19, 8 },
    { 6,37, 19, 20 },
    { 6,15, 19, 36 },
    { 6,0, 19, 47},
    { 5,46, 19, 59 },
    { 5,32, 20, 10 },
    //mai juin 1 14 21 28
    { 5,16, 20, 24 },
    { 5,5, 20, 34 },
    { 4,56, 20, 44 },
    { 4,49, 20, 53 },
    { 4,42, 21, 3 },
    { 4,40, 21, 8 },
    { 4,40, 21, 10 },
    { 4,43, 21, 10 },
    //juillet aout 1 14 21 28
    { 4,50, 21, 7 },
    { 4,57, 21, 2 },
    { 5,06, 20, 54 },
    { 5,15, 20, 45 },
    { 5,30, 20, 29 },
    { 5,41, 20, 16 },
    { 5,51, 20, 2 },
    { 6,02, 19, 47 },
    //sept octobre 1 14 21 28
    { 6,17, 19, 25 },
    { 6,28, 19, 10 },
    { 6,39, 18, 54 },
    { 6,50, 18, 38 },
    { 7,4, 18, 18 },
    { 7,16, 18,3 },
    { 7,27, 17, 49 },
    { 7,39, 17, 36 },
    //nov decembre 1 14 21 28
    { 7,56, 17, 18 },
    { 8,8, 17, 8 },
    { 8,19, 17, 00 },
    { 8,30, 16, 54 },
    { 8,41, 16, 49 },
    { 8,48, 16, 48 },
    { 8,53, 16, 51 },
    { 8,55, 16, 55 },
    //CORRECTION BUG
    { 8,55, 16, 55 }

    
  };
  
int result = 0;
int semaine= 0;
int mois= 0;
//int heurelever;
//int minutelever;
int heurecoucher;
int minutecoucher;
float heurecourante;


void setup(void) {
   //Serial.begin(9600);
   pinMode(pinLed,OUTPUT);
  setup_watchdog(9); // approximately 8 seconds sleep
  
  // memset( numbers, 0, sizeof(numbers) ); //Clear testing array.
 //EEPROM.get( address, numbers );  //Read back array data.
   //rtc.halt(false);
  rtc.writeProtect(true);
  //rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
  //rtc.setTime(18,15, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(02, 01, 2017);   // Set the date to August 6th, 2010



}

void loop(void) {
  if (f_wdt==4) {  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
f_wdt=0;       // reset flag



    
// CODE TO BE EXECUTED PERIODICALLY
//pinMode(8, OUTPUT);
//digitalWrite(8, HIGH);
 //delay(1000);              // wait for a second
 //digitalWrite(8, LOW); 
 //buffer=rtc.getTimeStr();
 //Serial.println(rtc.getTimeStr());
 Time t;
//char stime[17];
 t = rtc.getTime();
 //String Sday = rtc.getDOWStr();
//sprintf(stime, " %d:%d:%d ", t.hour, t.min, t.sec);
//Serial.print("oooo ");
//Serial.print("oooo ");
//Serial.print("oooo ");
//Serial.print(t.hour);
//Serial.println(t.min);
//Serial.println(t.sec);
//Serial.print(t.hour);
//Serial.println(t.min);
//Serial.println(t.sec);
//Serial.println(t.date);
//Serial.println(t.mon);
//Serial.println(t.year);
//Serial.println("000000000");


semaine=((int) t.date/7);
mois=(t.mon-1)*4+semaine;

//memset( numbers, 0, sizeof(numbers) ); //Clear testing array.
 //EEPROM.get( address, numbers );  //Read back array data.





//Serial.println(hourMinuteToHour(10,20));
//Serial.println("______________");
//heurelever=numbers[(t.mon-1)*4+semaine][0];
//minutelever=numbers[(t.mon-1)*4+semaine][1];
heurecoucher=numbers[(t.mon-1)*4+semaine][2];
minutecoucher=numbers[(t.mon-1)*4+semaine][3];

if( hourMinuteToHour(t.hour,t.min) > hourMinuteToHour(heurecoucher, minutecoucher) && hourMinuteToHour(t.hour,t.min) <  hourMinuteToHour(23, 59))
{
    //Serial.println("light init on");
    //lightOn();
    pinMode(pinLed,OUTPUT);
    digitalWrite(pinLed,HIGH);  
   
//digitalWrite(8, HIGH);
  }
  
 
  else{
    //Serial.println("light init off");

  //pinMode(pinLed,OUTPUT);
    //digitalWrite(pinLed,HIGH);  
    
    digitalWrite(pinLed, LOW); 

      pinMode(pinLed,INPUT); // set all used port to intput to save power
system_sleep();
//pinMode(pinLed,OUTPUT); // set all ports into state before sleep
       //digitalWrite(pinLed,LOW); 
       //pinMode(pinLed, INPUT); 
    
    //lightOff();
  }
//Serial.println(heurelever);
//Serial.println(minutelever);
//Serial.println(heurecoucher);
//Serial.println(minutecoucher);

//Serial.println(rtc.getDOWStr());
//Serial.print(rtc.getDateStr());
// sprintf(rtc.getTimeStr(), " %d:%d:%d ", t.hour, t.min, t.sec);


}

  system_sleep();
 
}



// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {
 
  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
 // WDTCR |= _BV(WDTIE);// ATTINY13 seulement
  WDTCR |= _BV(WDIE);// ATTINY85 seulement
}
  
// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
   //f_wdt=1;  // set global flag
  //
  f_wdt++;  // set global flag
}

float hourMinuteToHour(int hour, int minute){
  //return hour + minute/60.0f;
return hour%24 + minute/60.0f;
}







 
