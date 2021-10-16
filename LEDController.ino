#include <Conceptinetics.h>
#include <FastLED.h>

#define DMX_START_CHANNEL 100
#define DMX_SLAVE_CHANNELS 6

#define NUM_LEDS_CLOCK 14
#define NUM_LEDS_IC 14
#define NUM_LEDS_GARDENER 14
#define NUM_LEDS_OFFICE 14

#define DATA_PIN_CLOCK 9
#define DATA_PIN_IC 9
#define DATA_PIN_GARDENER 9
#define DATA_PIN_OFFICE 9

DMX_Slave dmx_slave(DMX_SLAVE_CHANNELS);
CRGB clock_leds[NUM_LEDS_CLOCK];
CRGB ic_leds[NUM_LEDS_IC];
CRGB office_leds[NUM_LEDS_OFFICE];
CRGB gardener_leds[NUM_LEDS_GARDENER];

void setup() {
  dmx_slave.enable();
  dmx_slave.setStartAddress(DMX_START_CHANNEL);

  FastLED.addLeds<NEOPIXEL, DATA_PIN_CLOCK>(clock_leds, NUM_LEDS_CLOCK);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_IC>(ic_leds, NUM_LEDS_IC);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_GARDENER>(gardener_leds,
                                               NUM_LEDS_GARDENER);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_OFFICE>(office_leds, NUM_LEDS_OFFICE);
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

  uint8_t start = ((float)ch2 / 255) * NUM_LEDS_CLOCK;
  uint8_t nd = ((float)ch3 / 255) * NUM_LEDS_CLOCK;

  for (uint8_t i = 0; i < NUM_LEDS_CLOCK; i++) {
    if (nd < start) {
      if (i >= start || i <= nd) {
        clock_leds[i] = CRGB(r, g, b);
      } else {
        clock_leds[i] = CRGB::Black;
      }
    } else {
      if (i >= start && i <= nd) {
        clock_leds[i] = CRGB(r, g, b);
      } else {
        clock_leds[i] = CRGB::Black;
      }
    }
  }
  return;
}

void set_workers() {
  uint8_t ch1 = dmx_slave.getChannelValue(1);

  switch (ch1) {
  case 0: {
    light_ic(true);
    light_gardener(false);
    light_office(false);
    break;
  }
  case 1: {
    light_ic(false);
    light_gardener(true);
    light_office(false);
    break;
  }
  case 2:
  default: {
    light_ic(false);
    light_gardener(false);
    light_office(true);
  }
  }
}

void light_gardener(bool on) {
  for (int i = 0; i < NUM_LEDS_GARDENER; i++) {
    if (on) {
      gardener_leds[i] = CRGB::Red;
    } else {
      gardener_leds[i] = CRGB::Black;
    }
  }
}

void light_ic(bool on) {
  for (int i = 0; i < NUM_LEDS_IC; i++) {
    if (on) {
      ic_leds[i] = CRGB::Blue;
    } else {
      ic_leds[i] = CRGB::Black;
    }
  }
}

void light_office(bool on) {
  for (int i = 0; i < NUM_LEDS_OFFICE; i++) {
    if (on) {
      office_leds[i] = CRGB::Green;
    } else {
      office_leds[i] = CRGB::Black;
    }
  }
}