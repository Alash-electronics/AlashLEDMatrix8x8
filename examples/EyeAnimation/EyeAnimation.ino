#include <AlashLEDMatrix8x8.hpp>

// Определяем пин Chip Select (CS) для светодиодной матрицы
const uint8_t LEDMATRIX_CS_PIN = 9;

// Количество сегментов 8x8, подключенных друг к другу
const int LEDMATRIX_SEGMENTS = 1;

// Экземпляр класса AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

// Массивы для хранения данных глаз
byte eyesCenter[8] = {
  0b00111100,
  0b01000010,
  0b01000010,
  0b01000010,
  0b01011010,
  0b01011010,
  0b01000010,
  0b00111100
};

byte eyesLeft[8] = {
  0b00111100,
  0b01000010,
  0b01000010,
  0b01000010,
  0b01110010,
  0b01110010,
  0b01000010,
  0b00111100
};

byte eyesRight[8] = {
  0b00111100,
  0b01000010,
  0b01000010,
  0b01000010,
  0b01001110,
  0b01001110,
  0b01000010,
  0b00111100
};

byte eyesDown[8] = {
  0b00000000,
  0b00111100,
  0b01000010,
  0b01000010,
  0b01000010,
  0b01000010,
  0b01011010,
  0b00111100
};

byte eyesUp[8] = {
  0b00111100,
  0b01000010,
  0b01011010,
  0b01011010,
  0b01000010,
  0b01000010,
  0b01000010,
  0b00111100
};

byte eyesAngry[8] = {
  0b01000000,
  0b01100000,
  0b01010000,
  0b01001000,
  0b01010100,
  0b01011010,
  0b01000010,
  0b00111100
};

void setup() {
  // Инициализация дисплея
  ledMatrix.setEnabled(true);
  ledMatrix.setIntensity(2); // Установка яркости (0 - минимальная, 15 - максимальная)
}

void loop() {
  // Показываем глаза, смотрящие прямо
  drawSprite(eyesCenter, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

  // Показываем глаза, смотрящие налево
  drawSprite(eyesLeft, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

  // Показываем глаза, смотрящие направо
  drawSprite(eyesRight, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

  // Показываем глаза, смотрящие прямо
  drawSprite(eyesCenter, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

  // Показываем глаза, смотрящие направо
  drawSprite(eyesDown, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

  // Показываем глаза, смотрящие прямо
  drawSprite(eyesCenter, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

  // Показываем глаза, смотрящие направо
  drawSprite(eyesUp, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

    // Показываем глаза, смотрящие прямо
  drawSprite(eyesCenter, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);

    // Показываем глаза, смотрящие направо
  drawSprite(eyesAngry, 0, 0, 8, 8);
  ledMatrix.display();
  delay(500);
}

// Функция для рисования спрайта на дисплее
void drawSprite(byte* sprite, int x, int y, int width, int height) {
  byte mask = B10000000;
  for (int iy = 0; iy < height; iy++) {
    for (int ix = 0; ix < width; ix++) {
      ledMatrix.setPixel(x + ix, y + iy, (sprite[iy] & mask) != 0);
      mask >>= 1;
    }
    mask = B10000000;
  }
}
