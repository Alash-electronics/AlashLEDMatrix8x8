# AlashLEDMatrix8x8

> 🌐 **English** | [Русский](README_ru.md)

Arduino library for driving chained 8x8 LED matrix modules (MAX7219-style, cascaded over SPI).

## Features

- Drives more than 8 segments in a chain (limited only by available RAM)
- Software-controlled frame buffer — build a frame, then push it to the display
- Fast: uses hardware [SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface) with a software-controlled SS pin
- Works with an external buffer or a self-allocated one
- Optional [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) support for shapes, text, and sprites:
  - disabled by default,
  - enable by adding `#define USE_ADAFRUIT_GFX` before including the header, **or**
  - pass `-DUSE_ADAFRUIT_GFX` as a build flag (advanced).

## Wiring

Each segment needs 16 bits, all shifted out together — hardware SPI is used instead of bit-banging for speed, which fixes three of the four SPI pins:

- MOSI → DIN
- SCK → CLK
- MISO is unused (unless you have another SPI device on the bus)
- Hardware SS is **not** used — you choose any digital pin for chip-select instead

Recommended pins for an Arduino Uno:

- DIN → 11
- CLK → 13
- CS → 9

## Usage

```cpp
#include <AlashLEDMatrix8x8.h>

#define NUM_SEGMENTS 4
#define CS_PIN 9

AlashLEDMatrix8x8 matrix(NUM_SEGMENTS, CS_PIN);

void setup() {
  matrix.setEnabled(true);
  matrix.setIntensity(8);   // 0..15
  matrix.setScanLimit(7);   // show all 8 rows
  matrix.clear();
  matrix.setPixel(0, 0, true);
  matrix.display();
}
```

Key methods: `setPixel(x, y, on)`, `setColumn(x, value)`, `setDigit(digit, value, dot)` for 7-segment mode, `scroll(direction, wrap)`, `clear()`, `display()`. When `USE_ADAFRUIT_GFX` is enabled, all `Adafruit_GFX` drawing primitives (`drawLine`, `drawCircle`, `print`, …) work directly on the matrix.

## Examples

* `EyeAnimation`, `MovingPointAnimation`, `ScrollingSpritesAnimation`, `WrappedScroll` — animation demos
* `LEDMatrix_ScrollingText_Faster`, `LEDMatrix_TextScroll`, `LEDMatrix_ScrollingAnimation` — scrolling text/graphics
* `LED-7segmentControl` — 7-segment digit mode

## Other Arduino libraries from Alash-electronics

[github.com/Alash-electronics](https://github.com/Alash-electronics)
