/*
 * Этот код управляет светодиодной матрицей 8x8 с использованием библиотеки AlashLEDMatrix8x8 и драйвера MAX7219. 
 * В setup настраивается яркость, предел сканирования и декодирование BCD. 
 * В loop отображается время работы в секундах и текст "- HELP -". 
 * Код включает комментарии для каждого шага, поясняя назначение каждой строки и действия.
*/
#include <AlashLEDMatrix8x8.hpp>

// Определение пина Chip Select (CS) для светодиодной матрицы (Не используйте пины SS или MISO Arduino!)
const uint8_t CS_PIN_MATRIX = 9;

const int NUM_DRIVERS = 1; // Каждый драйвер MAX7219 может управлять восемью 7-сегментными дисплеями.

// Создание экземпляра класса AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(NUM_DRIVERS, CS_PIN_MATRIX);

void setup() {
  // Инициализация дисплея
  ledMatrix.setEnabled(true);
  ledMatrix.setIntensity(2);  // Установка яркости: 0 = минимум, 15 = максимум
  ledMatrix.setScanLimit(7);  // Установка предела сканирования: 0-7 показывает 1-8 цифр
  ledMatrix.setDecode(0xFF);  // Включение декодирования "BCD Type B" для всех цифр
}

void loop() {
  // Отображение времени работы в секундах на одну секунду
  unsigned long startTime = millis(); // Получение текущего времени
  byte digit; // Переменная для хранения текущей цифры
  do {
    unsigned long remainingTime = millis(); // Получение оставшегося времени
    for (digit = 0; digit < 8; digit++) {
      // Установка цифр на дисплее в обратном порядке
      ledMatrix.setDigit(digit, remainingTime % 10, digit == 3); // Установка значения цифры
      remainingTime /= 10; // Сдвиг на следующую цифру
    }
    ledMatrix.display(); // Отображение текущего состояния матрицы
    delay(10); // Задержка для плавного отображения
  }
  while (millis() - startTime < 1000); // Повторять, пока не пройдет 1 секунда

  // Отображение текста "- HELP -" на одну секунду
  ledMatrix.setDigit(7, AlashLEDMatrix8x8::BCD_DASH); // Установка символа "-"
  ledMatrix.setDigit(6, AlashLEDMatrix8x8::BCD_BLANK); // Пустое место
  ledMatrix.setDigit(5, AlashLEDMatrix8x8::BCD_H); // Буква "H"
  ledMatrix.setDigit(4, AlashLEDMatrix8x8::BCD_E); // Буква "E"
  ledMatrix.setDigit(3, AlashLEDMatrix8x8::BCD_L); // Буква "L"
  ledMatrix.setDigit(2, AlashLEDMatrix8x8::BCD_P); // Буква "P"
  ledMatrix.setDigit(1, AlashLEDMatrix8x8::BCD_BLANK); // Пустое место
  ledMatrix.setDigit(0, AlashLEDMatrix8x8::BCD_DASH); // Установка символа "-"
  ledMatrix.display(); // Отображение текста на матрице
  delay(1000); // Задержка 1 секунда
}
