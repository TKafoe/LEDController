# LEDController
The Arduino software that is used to control the LED strips included in the "The Cycle of Light" Glow project.

The code is used on an Arduino Uno using the [CTC-DRA-10-1 DMX Shield](http://www.cqrobot.wiki/index.php/DMX_Shield_for_Arduino_SKU:_AngelDFR0260US) in Slave Mode.
## Instructions

Please set the data pins and number of LED's per connected strip accordingly before flashing the code.
By default the start channel is set to `100`. This can easily be changed in the code.

### Channels in use (relative to START_CHANNEL):

| Channel | Purpose                                                                               |
|---------|---------------------------------------------------------------------------------------|
| 1       | Sets what worker to light up. 0 for IC, 1 for Gardener, anything else for Office worker |
| 2       | Sets where (fraction) the LED's should start to light up.                          |
| 3       | Sets where (fraction) the LED's should stop to light up.                              |
| 4       | Sets the "R" component of the RGB color of the Clock.                                 |
| 5       | Sets the "G" component of the RGB color of the Clock.                                 |
| 6       | Sets the "B" component of the RGB color of the Clock.                                 |

If Channel 2 > Channel 3 the LED's will "loop" back to the start and light up until the value of Channel 3 (fraction).
