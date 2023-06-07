/*///////////////////////////////////////////////////////////////////////////////
FILENAME   : scrolling_colors.ino
AUTHOR     : Brian Denton <denton_brian_david@lilly.com>
DATE       : 2023-06-02
PROJECT    : 
DESCRIPTION: 
///////////////////////////////////////////////////////////////////////////////*/

#include <FastLED.h>
#include "FastLED_RGBW.h"

#define NUM_LEDS    300
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB

#define OUT1_PIN 8
#define BLOCK_SIZE 5

#define ALL CRGBW(255,255,255,255)
#define BLUE CRGBW(0,0,255,0)
#define FORESTGREEN CRGBW(34,139,34,0)
#define PURPLE CRGBW(128,0,128,0)
#define RED CRGBW(255,0,0,0)
#define WHITE CRGBW(0,0,0,255)
#define YELLOW CRGBW(255,255,51,255)

// TODO: Define multiple led strips
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

int runs = 1;
int run_counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup");

  FastLED.addLeds<LED_TYPE, OUT1_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
}

void scroll_colors(CRGBW *leds, CRGBW color1, CRGBW color2, int delay, int rounds){

  int led_index = 0;
  int offset = 0;
  int increment = 1;
  int color_code = 0;
  int counter = 0;
  
  for(int round = 0; round<rounds; round++){
  
    FastLED.clear();
  
    for(int i=0; i<NUM_LEDS; i++){
      
      led_index = (i + offset) % NUM_LEDS;
      color_code = (i/BLOCK_SIZE % 2 == 0);
      
      //Serial.println(led_index);
      
      if(color_code == 0){
        leds[led_index] = BLUE;
      }else{
        leds[led_index] = WHITE;
      }
    }
    
    if(offset<0 || offset>=NUM_LEDS){
      increment = -increment;
      counter++;
    }
    
    offset += increment;
    
    FastLED.show();
    FastLED.delay(delay);

  }
  
}

void loop(){  

  while(run_counter < runs){
    scroll_colors(leds, BLUE, WHITE, 10, 1000);
    run_counter++;
  }
  
  FastLED.clear();
  FastLED.show();
}

// END OF FILE
