#include <Conceptinetics.h>
#include <FastLED.h>

#define DMX_START_CHANNEL 200
#define DMX_SLAVE_CHANNELS 14

#define NUM_LEDS_CLOCK 344
#define NUM_LEDS_IC 60
#define NUM_LEDS_GARDENER 60
#define NUM_LEDS_OFFICE 60
#define NUM_LEDS_CLOTHES NUM_LEDS_IC + NUM_LEDS_GARDENER + NUM_LEDS_OFFICE

#define DATA_PIN_CLOTHES 10
#define DATA_PIN_CLOCK 9

#define SHIFT 12

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
  uint8_t ch2 = dmx_slave.getChannelValue(1);
  uint8_t ch3 = dmx_slave.getChannelValue(2);
  uint8_t r = dmx_slave.getChannelValue(3);
  uint8_t g = dmx_slave.getChannelValue(4);
  uint8_t b = dmx_slave.getChannelValue(5);

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
  light_ic();
  light_gardener();
  light_office();
}

void light_ic() {
  uint8_t r = dmx_slave.getChannelValue(6);
  uint8_t g = dmx_slave.getChannelValue(7);
  uint8_t b = dmx_slave.getChannelValue(8);
  for (int i = 0; i < NUM_LEDS_IC; i++) {
    clothes_leds[i] = CRGB(r, g, b);
  }
}

void light_gardener() {
  uint8_t r = dmx_slave.getChannelValue(9);
  uint8_t g = dmx_slave.getChannelValue(10);
  uint8_t b = dmx_slave.getChannelValue(11);
  for (int i = NUM_LEDS_IC; i < NUM_LEDS_IC + NUM_LEDS_GARDENER; i++) {
    clothes_leds[i] = CRGB(r, g, b);
  }
}

void light_office() {
  uint8_t r = dmx_slave.getChannelValue(12);
  uint8_t g = dmx_slave.getChannelValue(13);
  uint8_t b = dmx_slave.getChannelValue(14);
  for (int i = NUM_LEDS_IC + NUM_LEDS_GARDENER; i < NUM_LEDS_IC + NUM_LEDS_GARDENER + NUM_LEDS_OFFICE; i++) {
    clothes_leds[i] = CRGB(r, g, b);
  }
}
