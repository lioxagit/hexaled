#include <EnableInterrupt.h>
#include <Adafruit_NeoPixel.h>

#define SERIAL_PORT_SPEED 57600
#define RC_NUM_CHANNELS  4

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3

#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1
#define RC_CH3_INPUT  A2
#define RC_CH4_INPUT  A3

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(28, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(28, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(28, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_4 = Adafruit_NeoPixel(28, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_5 = Adafruit_NeoPixel(28, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_6 = Adafruit_NeoPixel(28, 7, NEO_GRB + NEO_KHZ800);

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];
unsigned int mode=0,blink_mode=0,blink_mode6=0,brightness=255,case1=0;
uint32_t none,red,green,blue,yellow,i,i1,LEDr=0 ;
unsigned int array_case6[26] = {0, 17, 1, 16, 2, 15, 3, 14, 4, 13 , 5, 12, 18, 24, 6, 11, 19, 23, 7, 10, 20, 22, 8, 9, 21, 21};


void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

// Fill the dots one after the other with a color
void colorClear1() {
  for(uint16_t i=0; i<24; i++) {
    strip_1.setPixelColor(i, 0);
  }
strip_1.show();
}
void colorClear2() {
  for(uint16_t i=0; i<24; i++) {
    strip_2.setPixelColor(i, 0);
  }
strip_2.show();
}
void colorClear3() {
  for(uint16_t i=0; i<24; i++) {
    strip_3.setPixelColor(i, 0);
  }
strip_3.show();
}
void colorClear4() {
  for(uint16_t i=0; i<24; i++) {
    strip_4.setPixelColor(i, 0);
  }
strip_4.show();
}
void colorClear5() {
  for(uint16_t i=0; i<24; i++) {
    strip_5.setPixelColor(i, 0);
  }
strip_5.show();
}
void colorClear6() {
  for(uint16_t i=0; i<24; i++) {
    strip_6.setPixelColor(i, 0);
  }
strip_6.show();
}


void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }


  
void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_INPUT, INPUT);


  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);


  strip_1.begin();
  strip_1.setBrightness(brightness);
  strip_1.show(); // Initialize all pixels to 'off'

  none = strip_1.Color(0, 0, 0);  // none
  red = strip_1.Color(255, 0, 0);  // Red
  green = strip_1.Color(0, 255, 0); // Green
  blue = strip_1.Color(0, 0, 255); // Blue
  yellow = strip_1.Color(255, 255, 0); // Yellow


  strip_2.begin();
  strip_2.setBrightness(brightness);
  strip_2.show(); // Initialize all pixels to 'off'

  none = strip_2.Color(0, 0, 0);  // none
  red = strip_2.Color(255, 0, 0);  // Red
  green = strip_2.Color(0, 255, 0); // Green
  blue = strip_2.Color(0, 0, 255); // Blue
  yellow = strip_2.Color(255, 255, 0); // Yellow


  strip_3.begin();
  strip_3.setBrightness(brightness);
  strip_3.show(); // Initialize all pixels to 'off'

  none = strip_3.Color(0, 0, 0);  // none
  red = strip_3.Color(255, 0, 0);  // Red
  green = strip_3.Color(0, 255, 0); // Green
  blue = strip_3.Color(0, 0, 255); // Blue
  yellow = strip_3.Color(255, 255, 0); // Yellow

  strip_4.begin();
  strip_4.setBrightness(brightness);
  strip_4.show(); // Initialize all pixels to 'off'

  none = strip_4.Color(0, 0, 0);  // none
  red = strip_4.Color(255, 0, 0);  // Red
  green = strip_4.Color(0, 255, 0); // Green
  blue = strip_4.Color(0, 0, 255); // Blue
  yellow = strip_4.Color(255, 255, 0); // Yellow
  
  strip_5.begin();
  strip_5.setBrightness(brightness);
  strip_5.show(); // Initialize all pixels to 'off'

  none = strip_5.Color(0, 0, 0);  // none
  red = strip_5.Color(255, 0, 0);  // Red
  green = strip_5.Color(0, 255, 0); // Green
  blue = strip_5.Color(0, 0, 255); // Blue
  yellow = strip_5.Color(255, 255, 0); // Yellow

  strip_6.begin();
  strip_6.setBrightness(brightness);
  strip_6.show(); // Initialize all pixels to 'off'

  none = strip_6.Color(0, 0, 0);  // none
  red = strip_6.Color(255, 0, 0);  // Red
  green = strip_6.Color(0, 255, 0); // Green
  blue = strip_6.Color(0, 0, 255); // Blue
  yellow = strip_6.Color(255, 255, 0); // Yellow
}

void loop() {

  
 rc_read_values();
 if (rc_values[RC_CH1] >= 1000)  
 {
  ++mode;
  delay(300);
  }
 
  Serial.println(mode);
 
switch (mode) {
  case 0 :
  
          for (i1=0; i1<24; i1++) {strip_1.setPixelColor(i1, none);}
          for (i1=0; i1<24; i1++) {strip_2.setPixelColor(i1, none);}
          for (i1=0; i1<24; i1++) {strip_3.setPixelColor(i1, none);}
          for (i1=0; i1<24; i1++) {strip_4.setPixelColor(i1, none);}
          for (i1=0; i1<24; i1++) {strip_5.setPixelColor(i1, none);}
          for (i1=0; i1<24; i1++) {strip_6.setPixelColor(i1, none);}
          
          strip_1.show();
          strip_2.show();         
          strip_3.show();
          strip_4.show();
          strip_5.show();
          strip_6.show();
          
      
    break;

  case 1 :

          for (i1=0; i1<24; i1++) {strip_1.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_2.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_3.setPixelColor(i1, blue);}
          for (i1=0; i1<24; i1++) {strip_4.setPixelColor(i1, green);}
          for (i1=0; i1<24; i1++) {strip_5.setPixelColor(i1, green);}
          for (i1=0; i1<24; i1++) {strip_6.setPixelColor(i1, blue);}
          
          strip_1.show();
          strip_2.show();         
          strip_3.show();
          strip_4.show();
          strip_5.show();
          strip_6.show();
      
      break;

  case 2 :
    if (blink_mode == 0){
          for (i1=0; i1<24; i1++) {strip_1.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_2.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_3.setPixelColor(i1, blue);}
          for (i1=0; i1<24; i1++) {strip_4.setPixelColor(i1, green);}
          for (i1=0; i1<24; i1++) {strip_5.setPixelColor(i1, green);}
          for (i1=0; i1<24; i1++) {strip_6.setPixelColor(i1, blue);}
          
          strip_1.show();
          strip_2.show();         
          strip_3.show();
          strip_4.show();
          strip_5.show();
          strip_6.show();
      }
      else
      {
      colorClear1();
      colorClear2();
      colorClear3();
      colorClear4();
      colorClear5();
      colorClear6();
      
        }
      break;
  case 3 :
        for (i=0; i<2; i++) {
          for (i1=0; i1<24; i1++) {strip_1.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_2.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_4.setPixelColor(i1, green);}
          for (i1=0; i1<24; i1++) {strip_5.setPixelColor(i1, green);}
          
          strip_1.show();
          strip_2.show();         
          strip_4.show();
          strip_5.show();
        delay(100);
          colorClear1();
          colorClear2();
          colorClear3();
          colorClear4();
          colorClear5();
          colorClear6();
        delay(100);
        }

          for (i1=0; i1<24; i1++) {strip_3.setPixelColor(i1, blue);}
          for (i1=0; i1<24; i1++) {strip_6.setPixelColor(i1, blue);}
          strip_3.show();
          strip_6.show();
        delay(300);
        colorClear3();
        colorClear6();
          
    break;
    
    case 4 :
          
           switch (blink_mode6) {
          case 1 :
              for (i1=0; i1<17; i1++) {
                strip_2.setPixelColor(i1, none);
                if (i1 % 2 == 0 )
                {strip_2.setPixelColor(26-((i1/2)+1), none);}
                
                strip_1.setPixelColor(i1, red);
                if (i1 % 2 == 0 )
                {strip_1.setPixelColor(26-((i1/2)+1), red);}
              strip_1.show();
              strip_2.show();
              delay(10);
              }
          break;

          case 2 :
              for (i1=0; i1<17; i1++) {
                strip_1.setPixelColor(i1, none);
                 if (i1 % 2 == 0 )
                strip_1.setPixelColor(26-((i1/2)+1), none);
                
                strip_6.setPixelColor(i1, blue);
                strip_6.setPixelColor(26-((i1/2)+1), blue);
                
              strip_1.show();
              strip_6.show();
              delay(10);
              }
              
          break;
          case 3 :
              for (i1=0; i1<17; i1++) {
                strip_6.setPixelColor(i1, none);
                strip_6.setPixelColor(26-((i1/2)+1), none);
                
                strip_5.setPixelColor(i1, green);
                strip_5.setPixelColor(26-((i1/2)+1), green);
                
              strip_6.show();
              strip_5.show();
              delay(10);
              }
          break;
          case 4 :
              for (i1=0; i1<17; i1++) {
                strip_5.setPixelColor(i1, none);
                strip_5.setPixelColor(26-((i1/2)+1), none);
                
                strip_4.setPixelColor(i1, green);
                strip_4.setPixelColor(26-((i1/2)+1), green);
                
              strip_5.show();
              strip_4.show();
              delay(10);
              }
          break;
          case 5 :
              for (i1=0; i1<17; i1++) {
                strip_4.setPixelColor(i1, none);
                strip_4.setPixelColor(26-((i1/2)+1), none);
                
                strip_3.setPixelColor(i1, blue);
                strip_3.setPixelColor(26-((i1/2)+1), blue);
                
              strip_4.show();
              strip_3.show();
              delay(10);
              }
          break;
          case 6 :
              for (i1=0; i1<17; i1++) {
                strip_3.setPixelColor(i1, none);
                strip_3.setPixelColor(26-((i1/2)+1), none);
                
                strip_2.setPixelColor(i1, red);
                strip_2.setPixelColor(26-((i1/2)+1), red);
                
              strip_3.show();
              strip_2.show();
              delay(10);
              }
          break;
          
           }
    break;

   case 5 :
       if (blink_mode == 0){
      colorClear1();
      colorClear2();
      colorClear3();
      colorClear4();
      colorClear5();
      colorClear6();
      
        for (i=0; i<5; i++){
          for (i1=0; i1<24; i1++) {strip_1.setPixelColor(i1, red);}
          for (i1=0; i1<24; i1++) {strip_2.setPixelColor(i1, red);}
          
          strip_1.show();
          strip_2.show();         
      delay(20);
          
      colorClear1();
      colorClear2();
      delay(30);
        }
      }
      else
      {
      colorClear1();
      colorClear2();
      colorClear3();
      colorClear4();
      colorClear5();
      colorClear6();
      
        for (i=0; i<5; i++){

          for (i1=0; i1<24; i1++) {strip_4.setPixelColor(i1, blue);}
          for (i1=0; i1<24; i1++) {strip_5.setPixelColor(i1, blue);}
          
          strip_4.show();
          strip_5.show();         
      delay(20);
          
      colorClear4();
      colorClear5();
      delay(30);
        }
        }   
    break;
    
    case 6 :
      colorClear1();
      colorClear2();
      colorClear3();
      colorClear4();
      colorClear5();
      colorClear6();
      
          for (i=0; i<26; i++){
       
              strip_1.setPixelColor(array_case6[i], red);
              strip_2.setPixelColor(array_case6[i], red);
              strip_3.setPixelColor(array_case6[i], blue);
              strip_4.setPixelColor(array_case6[i], green);
              strip_5.setPixelColor(array_case6[i], green);
              strip_6.setPixelColor(array_case6[i], blue);
             
              strip_1.setPixelColor(array_case6[i], red);
              strip_2.setPixelColor(array_case6[i], red);
              strip_3.setPixelColor(array_case6[i], blue);
              strip_4.setPixelColor(array_case6[i], green);
              strip_5.setPixelColor(array_case6[i], green);
              strip_6.setPixelColor(array_case6[i], blue);
       delay(20);
          strip_1.show();
          strip_2.show();         
          strip_3.show();
          strip_4.show();
          strip_5.show();
          strip_6.show();

          }


          
          
      break;
      
  //default:
    //Serial.print(mode);
    
}

//Serial.println(blink_mode);
++blink_mode;
++blink_mode6;

if ( blink_mode >= 2 ) {blink_mode = 0;}
if ( blink_mode6 >= 7 ) {blink_mode6 = 1;}

if (mode >= 7 ) {mode = 0;}
delay(100);
}



