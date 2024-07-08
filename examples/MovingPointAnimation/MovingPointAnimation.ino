/*
 * Этот код создает анимацию движущейся точки на светодиодной матрице, используя функцию прокрутки из библиотеки AlashLEDMatrix8x8. 
 * Точка движется вверх, вниз, влево и вправо, создавая визуальный эффект прокрутки. В функции setup инициализируется матрица и 
 * устанавливается её яркость. В функции loop точка прокручивается по матрице в заданных направлениях, отображая движение.
*/
#include <AlashLEDMatrix8x8.hpp>

// Определяем пин Chip Select (CS) для светодиодной матрицы. Не используйте пины SS или MISO вашего Arduino!
// Другие пины - это специфические пины SPI для Arduino (MOSI=DIN, SCK=CLK светодиодной матрицы), см. https://www.arduino.cc/en/Reference/SPI
const uint8_t MATRIX_CS_PIN = 9;

// Количество 8x8 сегментов, которые вы подключаете
const int NUM_SEGMENTS = 4;
const int MATRIX_WIDTH = NUM_SEGMENTS * 8;

// Экземпляр класса AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(NUM_SEGMENTS, MATRIX_CS_PIN);

void setup() {
    // Инициализация дисплея
    ledMatrix.setEnabled(true);
    ledMatrix.setIntensity(2); // 0 = низкая яркость, 10 = высокая яркость
}

const int ANIMATION_DELAY = 200;
int position = 0, step = 1, direction = 0, counter = 0;

void loop() {
    switch(direction) {
        case 0:
            ledMatrix.scroll(AlashLEDMatrix8x8::scrollDirection::scrollDown);
            ledMatrix.setPixel(position, 0, true);
            break;
        case 1:
            ledMatrix.scroll(AlashLEDMatrix8x8::scrollDirection::scrollUp);
            ledMatrix.setPixel(position, 7, true);
            break;
        case 2:
            ledMatrix.scroll(AlashLEDMatrix8x8::scrollDirection::scrollLeft);
            ledMatrix.setPixel(7, position, true);
            break;
        case 3:
            ledMatrix.scroll(AlashLEDMatrix8x8::scrollDirection::scrollRight);
            ledMatrix.setPixel(0, position, true);
            break;
    }

    // Отображение содержимого буфера кадра
    ledMatrix.display();

    // Увеличение/сброс счетчика эффекта
    if (counter++ > 50) { // после 50 циклов
        if (++direction > 3) // переключаемся на следующий эффект
            direction = 0;

        // Сброс счетчика и значений пикселя
        counter = 0;
        position = 0;
        step = 1;

        // Очистка буфера для более чистого отображения примера
        ledMatrix.clear();
    }

    // Движение пикселя вверх и вниз
    position += step;
    if (position == 7)
        step = -1;
    else if (position == 0)
        step = 1;

    delay(ANIMATION_DELAY);
}
