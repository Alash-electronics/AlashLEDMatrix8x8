# AlashLEDMatrix8x8

## Функции
- Может управлять более чем 8 сегментами (ограничено только памятью)
- Запись на дисплей контролируется программным обеспечением
- Гораздо быстрее, поскольку используется аппаратное обеспечение [SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface) с программным SS.
- Может использовать внешнюю память или самораспределенный буфер
- (Необязательно) поддержка библиотеки Adafruit_GFX:
  - по умолчанию эта функция **ОТКЛЮЧЕНА**,
  - добавьте `#define USE_ADAFRUIT_GFX` в заголовок, в строке 27, **или**
  - используйте `-DUSE_ADAFTUIT_GFX` (для опытных пользователей).

## Выбор контакта
Для каждого сегмента дисплея требуется 16 бит, и все они могут быть сдвинуты одновременно.  Чтобы ускорить переводы, мы используем аппаратный SPI вместо программного.

Таким образом, штифты зафиксированы:
- MOSI подключен к DIN,
- SCK подключен к CLK,
- MISO нельзя использовать (кроме другого устройства SPI),
- SS использовать нельзя (мы не используем аппаратный вывод).

Пользователь должен выбрать, какой контакт использовать для программного SS, но **не** использовать какие-либо аппаратные контакты SPI. Пожалуйста, проверьте номера контактов, соответствующие вашей [аппаратной платформе]

Рекомендуемые контакты для Arduino Uno:
- DIN подключен к 11
- CLK подключен к 13
- CS подключен к 9