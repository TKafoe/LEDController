#include <Conceptinetics.h>
#include <FastLED.h>

#define DMX_START_CHANNEL 100
#define DMX_SLAVE_CHANNELS 6

#define NUM_LEDS_CLOCK 344
#define NUM_LEDS_IC 60
#define NUM_LEDS_GARDENER 60
#define NUM_LEDS_OFFICE 60
#define NUM_LEDS_CLOTHES NUM_LEDS_IC + NUM_LEDS_GARDENER + NUM_LEDS_OFFICE

#define DATA_PIN_CLOTHES 10
#define DATA_PIN_CLOCK 9

#define SHIFT 20

unsigned long long t = millis();

DMX_Slave dmx_slave(DMX_SLAVE_CHANNELS);
CRGB clock_leds[NUM_LEDS_CLOCK];
CRGB clothes_leds[NUM_LEDS_CLOTHES];

void setup() {
  dmx_slave.enable();
  dmx_slave.setStartAddress(DMX_START_CHANNEL);

  FastLED.addLeds<NEOPIXEL, DATA_PIN_CLOCK>(clock_leds, NUM_LEDS_CLOCK);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_CLOTHES>(clothes_leds, NUM_LEDS_CLOTHES);
}

void loop() {
  set_clock();
  set_workers();
  FastLED.show();
  delay(100);
}

void set_clock() {
  uint8_t ch2 = dmx_slave.getChannelValue(2);
  uint8_t ch3 = dmx_slave.getChannelValue(3);
  uint8_t r = dmx_slave.getChannelValue(4);
  uint8_t g = dmx_slave.getChannelValue(5);
  uint8_t b = dmx_slave.getChannelValue(6);

  int start = ((float)ch2 / (float) 255) * NUM_LEDS_CLOCK;
  int nd = ((float)ch3 / (float) 255) * NUM_LEDS_CLOCK;


  for (int i = 0; i < NUM_LEDS_CLOCK; i++) {
    int i_shifted = i + SHIFT;
    i_shifted %= NUM_LEDS_CLOCK;

    if (nd > start) {
      if (i_shifted >= start && i_shifted <= nd) {
        clock_leds[i] = CRGB(r, g, b);
      } else {
        clock_leds[i] = CRGB::Black;
      }
    } else {
      if (i_shifted >= nd && i_shifted <= start) {
        clock_leds[i] = CRGB::Black;
      } else {
        clock_leds[i] = CRGB(r, g, b);
      }
    } 
  }
  return;
}

void set_workers() {
  uint8_t ch1 = dmx_slave.getChannelValue(1);

  switch (ch1) {
  case 0: {
    light_ic(false);
    light_gardener(false);
    light_office(false);
    break;
  }
  case 1: {
    light_ic(true);
    light_gardener(false);
    light_office(false);
    break;
  }
  case 2: {
    light_ic(false);
    light_gardener(true);
    light_office(false);
    break;
  }
  case 3:
  default: {
    light_ic(false);
    light_gardener(false);
    light_office(true);
  }
  }
}

void light_gardener(bool on) {
  for (int i = NUM_LEDS_IC; i < NUM_LEDS_IC + NUM_LEDS_GARDENER; i++) {
    if (on) {
      clothes_leds[i] = CRGB::Red;
    } else {
      clothes_leds[i] = CRGB::Black;
    }
  }
}

void light_ic(bool on) {
  for (int i = 0; i < NUM_LEDS_IC; i++) {
    if (on) {
      clothes_leds[i] = CRGB::Blue;
    } else {
      clothes_leds[i] = CRGB::Black;
    }
  }
}

void light_office(bool on) {
  for (int i = NUM_LEDS_IC + NUM_LEDS_GARDENER; i < NUM_LEDS_IC + NUM_LEDS_GARDENER + NUM_LEDS_OFFICE; i++) {
    if (on) {
      clothes_leds[i] = CRGB::Green;
    } else {
      clothes_leds[i] = CRGB::Black;
    }
  }
}
