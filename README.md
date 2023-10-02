# LEDController
The Arduino software that is used to control the LED strips included in the "The Cycle of Light" Glow project.

The code is used on an Arduino Uno using the [CTC-DRA-10-1 DMX Shield](http://www.cqrobot.wiki/index.php/DMX_Shield_for_Arduino_SKU:_AngelDFR0260US) in Slave Mode.

This code does not include the Midi-triggering Ableton file.
## Instructions

Please set the data pins and number of LED's per connected strip accordingly before flashing the code.
By default the start channel is set to `200`. This can easily be changed in the code.

### Channels in use (relative to START_CHANNEL):

| Channel | Purpose                                                                               |
|---------|---------------------------------------------------------------------------------------|
| 1       | Sets where (fraction) the LED's of the clock should start to light up.                          |
| 2       | Sets where (fraction) the LED's of the clock should stop to light up.                              |
| 3       | Sets the "R" component of the RGB color of the Clock.                                 |
| 4       | Sets the "G" component of the RGB color of the Clock.                                 |
| 5       | Sets the "B" component of the RGB color of the Clock.                                 |
| 6       | Sets the "R" component of the RGB color of the IC clothes.                                 |
| 7       | Sets the "G" component of the RGB color of the IC clothes.                                 |
| 8       | Sets the "B" component of the RGB color of the IC clothes.                                 |
| 9       | Sets the "R" component of the RGB color of the Gardener clothes.                                 |
| 10       | Sets the "G" component of the RGB color of the Gardener clothes.                                 |
| 11       | Sets the "B" component of the RGB color of the Gardener clothes.                                 |
| 12       | Sets the "R" component of the RGB color of the Office worker clothes.                                 |
| 13       | Sets the "G" component of the RGB color of the Office worker clothes.                                 |
| 14       | Sets the "B" component of the RGB color of the Office worker clothes.                                 |

If Channel 1 > Channel 2 the LED's will "loop" back to the start and light up until the value of Channel 2 (fraction).
