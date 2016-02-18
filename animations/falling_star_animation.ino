#include <FastLED.h>

/*
 * basic settings
 */
 
#define LED_PIN     6
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    240

/*
 * animation settings
 */

#define BRIGHTNESS  255
#define NUMBER_STARS 10
#define MIN_LENGTH 10
#define MAX_LENGTH 25
#define MAX_SPEED 20

/*
 * basic animation initialization
 */

long interval[NUMBER_STARS - 1];
long next_step[NUMBER_STARS - 1];

CRGB leds[NUM_LEDS];

    struct falling_star {
    int index;
    int length_star;
    long speed_star;
    CRGB color; 
  }; 

  int length_star;
  int j = 0;
  falling_star falling_stars[NUMBER_STARS - 1];
  int k = 0;
  int l = 0;
  int i = 0;

void setup() {
  delay(3000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
}

void loop()
{
  long currentTime = millis();
   if (random8() < NUMBER_STARS) {
     char r = random8(); 
     char g = random8();
     char b = random8();
     length_star = random8(MIN_LENGTH,MAX_LENGTH);
     falling_stars[k].color = CRGB( r, g, b);
     falling_stars[k].index = 0;
     falling_stars[k].length_star = length_star;
     falling_stars[k].speed_star = 1000 / (length_star * random8(4, MAX_SPEED));
     if (k == NUMBER_STARS - 1) k = 0;
     else k++;
  }
 for ( i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB( 0, 0, 0);
  } 
  for (l = 0; l < NUMBER_STARS; l++) {
   next_step[l] = Falling_Star(currentTime, l);
  }
   FastLED.show();
}

long Falling_Star(long currentMillis, int star_number) {
  if (currentMillis > interval[star_number]) {
    if (qadd8(falling_stars[star_number].index, falling_stars[star_number].length_star)-2 > NUM_LEDS) {
      falling_stars[star_number].length_star--;
    }
    for (i = 0; i < falling_stars[star_number].length_star; i++) {
    leds[qadd8(falling_stars[star_number].index,  i)-2] = falling_stars[star_number].color;
    leds[qadd8(falling_stars[star_number].index,  i)-2].nscale8_video( (i*(i >> 1)) );
    }
    falling_stars[star_number].index++;
    interval[star_number] = (currentMillis + falling_stars[star_number].speed_star);
}
return interval[star_number];
}

