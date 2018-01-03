#include <SBUS.h>
SBUS sbus(Serial);

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

uint32_t red,green,blue,i,i1 ;
unsigned int thr_delay,thr_led=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

//Define variables 

#define I2C_ADDR          0x3F        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;

int yaw=0,thr=0,pitch=0,roll=0;
unsigned int thr_speed=0; 
void setup()
{
  sbus.begin();
 // Serial.begin(115200);
 // Serial.println("SBUS Status");

    //Define the LCD as 16 column by 2 rows 
    lcd.begin (16,2);
    
    //Switch on the backlight
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    
    //goto first column (column 0) and first line (Line 0)
  //  lcd.setCursor(5,0);
    
    //Print at cursor Location
 //   lcd.print("HAPPY");
    
    //goto first column (column 0) and second line (line 1)
 //   lcd.setCursor(3,1);
 //   lcd.print("Halloween");
    

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
 
  
  digitalWrite(2, HIGH);       // sets the digital pin 13 on
  delay(1000);                  // waits for a second
  digitalWrite(2, LOW);        // sets the digital pin 13 off
  delay(1000);                  // waits for a second


  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  red = strip.Color(255, 0, 0);  // Red
  green = strip.Color(0, 255, 0); // Green
  blue = strip.Color(0, 0, 255); // Blue
}

void ColorSet (uint32_t c, uint32_t r_min, uint32_t r_max ) {

  for (i=r_min; i < r_max; i++ ) {
    strip.setPixelColor(i, c);
    };
    strip.show();
  }

// Fill the dots one after the other with a color
void colorClear() {
  for(uint16_t i=0; i<103; i++) {
    strip.setPixelColor(i, 0);
  }
strip.show();
}

// this is timer2, which triggers ever 1ms and processes the incoming SBUS datastream
ISR(TIMER2_COMPA_vect)
{
  sbus.process();
}



void loop()
{
 delay(5);
 roll=sbus.getNormalizedChannel(1);
 pitch=sbus.getNormalizedChannel(2);
 thr=sbus.getNormalizedChannel(3);
 yaw=sbus.getNormalizedChannel(4);

 
//  printSBUSStatus();
/* 
 lcd.setCursor(0,0);
 lcd.print(roll);
 lcd.setCursor(5,1);
 lcd.print(pitch);
*/
 lcd.setCursor(5,0);
 lcd.print(thr);

if ( -10 <= thr && thr <= 10) 
{
  for (i1=0; i1<13; i1++) {strip.setPixelColor(i1, green);}
  for (i1=13; i1<20; i1++) {strip.setPixelColor(i1, red);}
   strip.show();
   thr_led = 1;
}

if ( thr >= 11) 
{
  if (thr_delay <= 0)
      {
       thr_delay=(300-(thr*3))/10;
        if (thr_led == 1)
        {
         colorClear(); 
        }
        else
        {
         for (i1=0; i1<13; i1++) {
          strip.setPixelColor(i1, green);
          strip.show();      
        }
      }
      
      }
  thr_delay=thr_delay-1;
  
  /*
  for (i1=0; i1<13; i1++) {
    strip.setPixelColor(i1, green);
    strip.show();
      }
  delay(300-(thr*3));
  colorClear();
  delay(500-(thr*5));
  */
}

if ( thr <= -11 ) 
{
  thr=thr*(-1);
  for (i1=13; i1<20; i1++) {
    strip.setPixelColor(i1, red);
    strip.show();
  }
    delay(300-(thr*3));
    colorClear();
    delay(500-(thr*5));
}


 /*
 lcd.setCursor(0,1);
 lcd.print(sbus.getNormalizedChannel(4));
 lcd.setCursor(5,1);
 lcd.print(sbus.getNormalizedChannel(5));
 lcd.setCursor(10,1);
 lcd.print(sbus.getNormalizedChannel(12));
 */
/*
  if (sbus.getNormalizedChannel(3) > 0 )
  {digitalWrite(2, HIGH);}
  else 
  {digitalWrite(2, LOW);}
  
  if (sbus.getNormalizedChannel(3) < 0 )
  {digitalWrite(3, HIGH);}
    else 
  {digitalWrite(3, LOW);}
*/
/*
unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(4, ledState);
  }
  */
}

void printSBUSStatus()
{
  Serial.print("Ch1  ");
  Serial.println(sbus.getNormalizedChannel(1));
  Serial.print("Ch2  ");
  Serial.println(sbus.getNormalizedChannel(2));
  Serial.print("Ch3  ");
  Serial.println(sbus.getNormalizedChannel(3));
  Serial.print("Ch4  ");
  Serial.println(sbus.getNormalizedChannel(4));
  Serial.print("Ch5  ");
  Serial.println(sbus.getNormalizedChannel(5));
  Serial.print("Ch6  ");
  Serial.println(sbus.getNormalizedChannel(6));
  Serial.print("Ch7  ");
  Serial.println(sbus.getNormalizedChannel(7));
  Serial.print("Ch8  ");
  Serial.println(sbus.getNormalizedChannel(8));
  Serial.print("Ch9  ");
  Serial.println(sbus.getNormalizedChannel(9));
  Serial.print("Ch10 ");
  Serial.println(sbus.getNormalizedChannel(10));
  Serial.print("Ch11 ");
  Serial.println(sbus.getNormalizedChannel(11));
  Serial.print("Ch12 ");
  Serial.println(sbus.getNormalizedChannel(12));
  Serial.print("Ch13 ");
  Serial.println(sbus.getNormalizedChannel(13));
  Serial.print("Ch14 ");
  Serial.println(sbus.getNormalizedChannel(14));
  Serial.print("Ch15 ");
  Serial.println(sbus.getNormalizedChannel(15));
  Serial.print("Ch16 ");
  Serial.println(sbus.getNormalizedChannel(16));
  Serial.println();
  Serial.print("Failsafe: ");
  if (sbus.getFailsafeStatus() == SBUS_FAILSAFE_ACTIVE) {
    Serial.println("Active");
  }
  if (sbus.getFailsafeStatus() == SBUS_FAILSAFE_INACTIVE) {
    Serial.println("Not Active");
  }

  Serial.print("Data loss on connection: ");
  Serial.print(sbus.getFrameLoss());
  Serial.println("%");

  Serial.print("Frames: ");
  Serial.print(sbus.getGoodFrames());
  Serial.print(" / ");
  Serial.print(sbus.getLostFrames());
  Serial.print(" / ");
  Serial.println(sbus.getDecoderErrorFrames());

  Serial.print("Time diff: ");
 // Serial.println(millis() - sbus.getLastTime());
}
