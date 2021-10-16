#include <Conceptinetics.h>
#include <FastLED.h>

#define DMX_START_CHANNEL 100
#define DMX_SLAVE_CHANNELS 5

#define NUM_LEDS 14
#define DATA_PIN 9

DMX_Slave dmx_slave(DMX_SLAVE_CHANNELS);
CRGB leds[NUM_LEDS];

void setup() {
    dmx_slave.enable();
    dmx_slave.setStartAddress(DMX_START_CHANNEL);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    uint8_t ch1 = dmx_slave.getChannelValue(1);
    uint8_t ch2 = dmx_slave.getChannelValue(2);
    uint8_t r = dmx_slave.getChannelValue(3);
    uint8_t g = dmx_slave.getChannelValue(4);
    uint8_t b = dmx_slave.getChannelValue(5);
    uint8_t start = ((float) ch1 / 255) * NUM_LEDS;
    uint8_t nd = ((float) ch2 / 255) * NUM_LEDS;

    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (nd < start) {
        if (i >= start || i <= nd) {
          leds[i] = CRGB(r, g, b);
        } else {
          leds[i] = CRGB::Black;
        } 
      } else { 
        if (i >= start && i <= nd) {
          leds[i] = CRGB(r, g, b);
        } else {
          leds[i] = CRGB::Black;
        } 
      }
    }
    FastLED.show();

    delay(100);
}
    
