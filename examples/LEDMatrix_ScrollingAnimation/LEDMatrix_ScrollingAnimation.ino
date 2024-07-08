/*
 * Этот код предназначен для управления светодиодной матрицей 8x8, подключенной через SPI, 
 * с использованием библиотеки AlashLEDMatrix8x8. Он инициализирует матрицу, устанавливает яркость, 
 * и последовательно зажигает и гасит каждый пиксель, создавая анимацию.
*/
#include <AlashLEDMatrix8x8.hpp>

// Определяем пин ChipSelect для светодиодной матрицы (не используйте пины SS или MISO на Arduino!)
const uint8_t CHIP_SELECT_PIN = 9;

// Количество подключаемых сегментов 8x8
const int MATRIX_SEGMENTS = 1;
const int MATRIX_WIDTH = MATRIX_SEGMENTS * 8;

// Экземпляр класса AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(MATRIX_SEGMENTS, CHIP_SELECT_PIN);

void setup() {
    // Инициализация дисплея
    ledMatrix.setEnabled(true);
    ledMatrix.setIntensity(10); // 0 = низкая яркость, 10 = высокая яркость
}

int currentX = 0, currentY = 0; // начальная позиция верхний левый угол
bool ledState = true; // начальное состояние светодиода включено

void loop() {
    // Переключаем текущий пиксель в буфере кадра
    ledMatrix.setPixel(currentX, currentY, ledState);

    // Переходим к следующему пикселю
    if (currentX++ >= MATRIX_WIDTH) {
        // Возвращаемся влево
        currentX = 0;
        // Начинаем новую строку
        if (currentY++ >= 8) {
            currentY = 0;  // нужно вернуться к началу
            ledState = !ledState; // переключаем состояние светодиода
        }
    }
    // Сбрасываем буфер кадра
    ledMatrix.display();
    delay(10);
}
