/*
 * Этот код создает анимацию движущегося спрайта на светодиодной матрице, используя библиотеку AlashLEDMatrix8x8. 
 * В функции setup инициализируется матрица и устанавливается её яркость. 
 * В функции loop спрайты последовательно отображаются на экране с заданной задержкой, создавая эффект анимации. 
 * Когда спрайт выходит за пределы экрана, его позиция сбрасывается для повторного показа.
*/
#include <AlashLEDMatrix8x8.hpp>

// Определяем пин Chip Select (CS) для светодиодной матрицы
// Другие пины - это специфические пины SPI для Arduino (MOSI=DIN, SCK=CLK светодиодной матрицы), см. https://www.arduino.cc/en/Reference/SPI
const uint8_t MATRIX_CS_PIN = 9;

// Количество 8x8 сегментов, которые вы подключаете
const int NUM_SEGMENTS = 4;
const int SEGMENT_WIDTH = 8;
const int MATRIX_WIDTH = NUM_SEGMENTS * SEGMENT_WIDTH;

// Экземпляр класса AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(NUM_SEGMENTS, MATRIX_CS_PIN);

void setup() {
  // Инициализация дисплея
  ledMatrix.setEnabled(true);
  ledMatrix.setIntensity(2); // 0 = низкая яркость, 15 = высокая яркость
}

int positionX = -SEGMENT_WIDTH; // начальная позиция за пределами слева
int positionY = 0;              // начальная позиция в верхнем левом углу
bool state = true;              // начальное состояние светодиода включено

// Массивы для хранения данных для различных спрайтов
byte spriteA[8] = { B00011000, B00100100, B00100100, B00011000, B01111110, B00011000, B00100100, B01000010 };
byte spriteB[8] = { B00011000, B00100100, B00100100, B00011010, B01111100, B00011000, B01100100, B00000010 };
byte spriteC[8] = { B00011000, B00100100, B00100100, B00011010, B00111100, B01011000, B00110100, B00000100 };
byte spriteD[8] = { B00011000, B00100100, B00100100, B00011010, B00111100, B01011000, B00011000, B00011000 };
byte spriteE[8] = { B00011000, B00100100, B00100100, B00011010, B00111100, B01011000, B00010100, B00010000 };
byte spriteF[8] = { B00011000, B00100100, B00100100, B00011000, B00111110, B01011000, B00010100, B00010100 };

const int ANIMATION_DELAY = 100;

void loop() {
  // Отображение каждого спрайта последовательно
  ledMatrix.clear();
  drawSprite((byte*)&spriteA, positionX++, 0, 8, 8);
  ledMatrix.display();
  delay(ANIMATION_DELAY);

  ledMatrix.clear();
  drawSprite((byte*)&spriteB, positionX++, 0, 8, 8);
  ledMatrix.display();
  delay(ANIMATION_DELAY);

  ledMatrix.clear();
  drawSprite((byte*)&spriteC, positionX++, 0, 8, 8);
  ledMatrix.display();
  delay(ANIMATION_DELAY);

  ledMatrix.clear();
  drawSprite((byte*)&spriteD, positionX++, 0, 8, 8);
  ledMatrix.display();
  delay(ANIMATION_DELAY);

  ledMatrix.clear();
  drawSprite((byte*)&spriteE, positionX++, 0, 8, 8);
  ledMatrix.display();
  delay(ANIMATION_DELAY);

  ledMatrix.clear();
  drawSprite((byte*)&spriteF, positionX++, 0, 8, 8);
  ledMatrix.display();
  delay(ANIMATION_DELAY);

  // Сброс позиции после того, как спрайт выйдет за пределы экрана
  if (positionX > MATRIX_WIDTH) 
    positionX = -SEGMENT_WIDTH;
}

// Функция для рисования спрайта на дисплее
void drawSprite(byte* sprite, int x, int y, int width, int height) {
  byte mask = B10000000;
  for (int iy = 0; iy < height; iy++) {
    for (int ix = 0; ix < width; ix++) {
      ledMatrix.setPixel(x + ix, y + iy, (bool)(sprite[iy] & mask));
      mask = mask >> 1;
    }
    mask = B10000000;
  }
}
