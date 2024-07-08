/*
   Этот код демонстрирует использование светодиодной матрицы 8x8 с прокруткой изображений в различных направлениях.
   В функции setup инициализируется матрица и устанавливается её яркость. В функции loop отображается шаблон "шеврон",
   после чего выполняется прокрутка изображения в четырех направлениях: вниз, влево, вверх и вправо.
*/

#include <AlashLEDMatrix8x8.hpp>

// Определение пина Chip Select (CS) для светодиодной матрицы
const uint8_t MATRIX_CS_PIN = 9;
// Указание количества модулей, соединенных последовательно
const int NUM_MODULES = 4;
// Ширина матрицы
const int MATRIX_WIDTH = NUM_MODULES * 8;

// Создание экземпляра класса AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(NUM_MODULES, MATRIX_CS_PIN);

void setup() {
  Serial.begin(115200); // Инициализация последовательного соединения для вывода данных

  ledMatrix.setEnabled(true); // Включение матрицы
  ledMatrix.setIntensity(3); // Установка яркости матрицы
}

// Определение шаблона "шеврон" для отображения
const uint8_t chevron[8] = {0x81, 0xC3, 0x66, 0x3C, 0x18, 0, 0, 0};

// Функция для отображения шаблона "шеврон" на матрице
void drawChevron() {
  for (int i = 0; i < 8 * ledMatrix.getSegments(); i++) {
    ledMatrix.setColumn(i, chevron[i % 8]);
  }
}

// Определение направлений прокрутки
const AlashLEDMatrix8x8::scrollDirection SCROLL_DIRECTIONS[4] = {
  AlashLEDMatrix8x8::scrollDirection::scrollDown,
  AlashLEDMatrix8x8::scrollDirection::scrollLeft,
  AlashLEDMatrix8x8::scrollDirection::scrollUp,
  AlashLEDMatrix8x8::scrollDirection::scrollRight,
};

void loop() {
  drawChevron(); // Отображение шаблона "шеврон"

  // Цикл для прокрутки в разных направлениях
  for (auto direction : SCROLL_DIRECTIONS) {
    int steps = (direction == AlashLEDMatrix8x8::scrollDirection::scrollLeft || direction == AlashLEDMatrix8x8::scrollDirection::scrollRight) ? 8 * ledMatrix.getSegments() : 4;
    for (int i = 0; i < steps; i++) {
      ledMatrix.scroll(direction, true); // Прокрутка матрицы
      ledMatrix.display(); // Обновление отображения
      delay(50); // Задержка для плавности анимации
    }
  }
}
