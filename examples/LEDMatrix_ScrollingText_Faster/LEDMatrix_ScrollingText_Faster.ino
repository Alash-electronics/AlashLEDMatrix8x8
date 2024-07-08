/*
 * Этот код предназначен для управления светодиодной матрицей 8x8, подключенной через SPI, с использованием библиотеки AlashLEDMatrix8x8. 
 * Он инициализирует матрицу, устанавливает яркость и прокручивает текст по дисплею. 
 * Функции nextChar, nextCol, и writeCol используются для управления прокруткой текста и отрисовки символов. 
 * В loop вызывается функция marquee, которая отвечает за обновление дисплея.
*/
#include <AlashLEDMatrix8x8.hpp>

// Установите пин Chip Select (CS) для светодиодной матрицы
const uint8_t CS_PIN = 9;
// Количество подключаемых модулей
const uint8_t NUM_SEGMENTS = 8;
// Ширина всего дисплея
const uint16_t DISPLAY_WIDTH = NUM_SEGMENTS * 8;

// Инициализация AlashLEDMatrix8x8
AlashLEDMatrix8x8 ledMatrix(NUM_SEGMENTS, CS_PIN, AlashLEDMatrix8x8::INVERT_SEGMENT_X | AlashLEDMatrix8x8::INVERT_Y);

// Задержка прокрутки в миллисекундах
const uint16_t SCROLL_DELAY = 30;
uint64_t marqueeDelayTimestamp = 0;

// Шрифт, хранящийся в программе
static const uint8_t font[515] PROGMEM = {
  2,0b00000000,0b00000000,                                  /* 032 =   */
  2,0b01101111,0b01101111,                                  /* 033 = ! */
  3,0b00000011,0b00000000,0b00000011,                       /* 034 = " */
  5,0b00010100,0b01111111,0b00010100,0b01111111,0b00010100, /* 035 = # */
  5,0b00100100,0b00101010,0b01111111,0b00101010,0b00010010, /* 036 = $ */
  5,0b00100011,0b00010011,0b00001000,0b01100100,0b01100010, /* 037 = % */
  5,0b00110100,0b01001010,0b01001010,0b00110100,0b01010000, /* 038 = & */
  1,0b00000011,                                             /* 039 = ' */
  3,0b00011100,0b00100010,0b01000001,                       /* 040 = ( */
  3,0b01000001,0b00100010,0b00011100,                       /* 041 = ) */
  3,0b00000101,0b00000010,0b00000101,                       /* 042 = * */
  5,0b00001000,0b00001000,0b00111110,0b00001000,0b00001000, /* 043 = + */
  2,0b11100000,0b01100000,                                  /* 044 = , */
  5,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000, /* 045 = - */
  2,0b01100000,0b01100000,                                  /* 046 = . */
  5,0b01000000,0b00110000,0b00001000,0b00000110,0b00000001, /* 047 = / */
  5,0b00111110,0b01010001,0b01001001,0b01000101,0b00111110, /* 048 = 0 */
  3,0b01000010,0b01111111,0b01000000,                       /* 049 = 1 */
  5,0b01000010,0b01100001,0b01010001,0b01001001,0b01000110, /* 050 = 2 */
  5,0b00100001,0b01000001,0b01000101,0b01001011,0b00110001, /* 051 = 3 */
  5,0b00011000,0b00010100,0b00010010,0b01111111,0b00010000, /* 052 = 4 */
  5,0b00100111,0b01000101,0b01000101,0b01000101,0b00111001, /* 053 = 5 */
  5,0b00111100,0b01001010,0b01001001,0b01001001,0b00110000, /* 054 = 6 */
  5,0b00000001,0b00000001,0b01111001,0b00000101,0b00000011, /* 055 = 7 */
  5,0b00110110,0b01001001,0b01001001,0b01001001,0b00110110, /* 056 = 8 */
  5,0b00000110,0b01001001,0b01001001,0b00101001,0b00011110, /* 057 = 9 */
  2,0b00110110,0b00110110,                                  /* 058 = : */
  2,0b01110110,0b00110110,                                  /* 059 = ; */
  4,0b00001000,0b00010100,0b00100010,0b01000001,            /* 060 = < */
  5,0b00010100,0b00010100,0b00010100,0b00010100,0b00010100, /* 061 = = */
  4,0b01000001,0b00100010,0b00010100,0b00001000,            /* 062 = > */
  5,0b00000010,0b00000001,0b01010001,0b00001001,0b00000110, /* 063 = ? */
  5,0b00111110,0b01000001,0b01011101,0b01010101,0b01011110, /* 064 = @ */
  5,0b01111110,0b00001001,0b00001001,0b00001001,0b01111110, /* 065 = A */
  5,0b01111111,0b01001001,0b01001001,0b01001001,0b00110110, /* 066 = B */
  5,0b00111110,0b01000001,0b01000001,0b01000001,0b00100010, /* 067 = C */
  5,0b01111111,0b01000001,0b01000001,0b01000001,0b00111110, /* 068 = D */
  5,0b01111111,0b01001001,0b01001001,0b01001001,0b01000001, /* 069 = E */
  5,0b01111111,0b00001001,0b00001001,0b00001001,0b00000001, /* 070 = F */
  5,0b00111110,0b01000001,0b01001001,0b01001001,0b01111010, /* 071 = G */
  5,0b01111111,0b00001000,0b00001000,0b00001000,0b01111111, /* 072 = H */
  5,0b01000001,0b01000001,0b01111111,0b01000001,0b01000001, /* 073 = I */
  5,0b00100000,0b01000001,0b01000001,0b00111111,0b00000001, /* 074 = J */
  5,0b01111111,0b00001000,0b00010100,0b00100010,0b01000001, /* 075 = K */
  5,0b01111111,0b01000000,0b01000000,0b01000000,0b01000000, /* 076 = L */
  5,0b01111111,0b00000010,0b00000100,0b00000010,0b01111111, /* 077 = M */
  5,0b01111111,0b00000110,0b00001000,0b00110000,0b01111111, /* 078 = N */
  5,0b00111110,0b01000001,0b01000001,0b01000001,0b00111110, /* 079 = O */
  5,0b01111111,0b00010001,0b00010001,0b00010001,0b00001110, /* 080 = P */
  5,0b00111110,0b01000001,0b01010001,0b00100001,0b01011110, /* 081 = Q */
  5,0b01111111,0b00001001,0b00011001,0b00101001,0b01000110, /* 082 = R */
  5,0b00100110,0b01001001,0b01001001,0b01001001,0b00110010, /* 083 = S */
  5,0b00000001,0b00000001,0b01111111,0b00000001,0b00000001, /* 084 = T */
  5,0b00111111,0b01000000,0b01000000,0b01000000,0b00111111, /* 085 = U */
  5,0b00011111,0b00100000,0b01000000,0b00100000,0b00011111, /* 086 = V */
  5,0b00111111,0b01000000,0b00110000,0b01000000,0b00111111, /* 087 = W */
  5,0b01100011,0b00010100,0b00001000,0b00010100,0b01100011, /* 088 = X */
  5,0b00000111,0b00001000,0b01110000,0b00001000,0b00000111, /* 089 = Y */
  5,0b01100001,0b01010001,0b01001001,0b01000101,0b01000011, /* 090 = Z */
  3,0b01111111,0b01000001,0b01000001,                       /* 091 = [ */
  5,0b00000001,0b00000110,0b00001000,0b00110000,0b01000000, /* 092 = \ */
  3,0b01000001,0b01000001,0b01111111,                       /* 093 = ] */
  5,0b00000100,0b00000010,0b00000001,0b00000010,0b00000100, /* 094 = ^ */
  5,0b01000000,0b01000000,0b01000000,0b01000000,0b01000000, /* 095 = _ */
  1,0b00000011,                                             /* 096 = ' */
  5,0b00100000,0b01010100,0b01010100,0b01010100,0b01111000, /* 097 = a */
  5,0b01111111,0b00101000,0b01000100,0b01000100,0b00111000, /* 098 = b */
  5,0b00111000,0b01000100,0b01000100,0b01000100,0b00101000, /* 099 = c */
  5,0b00111000,0b01000100,0b01000100,0b00101000,0b01111111, /* 100 = d */
  5,0b00111000,0b01010100,0b01010100,0b01010100,0b00011000, /* 101 = e */
  5,0b00000100,0b01111110,0b00000101,0b00000001,0b00000010, /* 102 = f */
  5,0b00011000,0b10100100,0b10100100,0b10100100,0b01111100, /* 103 = g */
  5,0b01111111,0b00000100,0b00000100,0b00000100,0b01111000, /* 104 = h */
  3,0b01000100,0b01111101,0b01000000,                       /* 105 = i */
  4,0b01000000,0b10000000,0b10000100,0b01111101,            /* 106 = j */
  5,0b01111111,0b00010000,0b00010000,0b00101000,0b01000100, /* 107 = k */
  3,0b01000001,0b01111111,0b01000000,                       /* 108 = l */
  5,0b01111100,0b00000100,0b01111100,0b00000100,0b01111000, /* 109 = m */
  5,0b01111100,0b00001000,0b00000100,0b00000100,0b01111000, /* 110 = n */
  5,0b00111000,0b01000100,0b01000100,0b01000100,0b00111000, /* 111 = o */
  5,0b11111100,0b00100100,0b00100100,0b00100100,0b00011000, /* 112 = p */
  5,0b00011000,0b00100100,0b00100100,0b00100100,0b11111100, /* 113 = q */
  5,0b01111100,0b00001000,0b00000100,0b00000100,0b00001000, /* 114 = r */
  5,0b01001000,0b01010100,0b01010100,0b01010100,0b00100000, /* 115 = s */
  5,0b00000100,0b00111110,0b01000100,0b01000000,0b00100000, /* 116 = t */
  5,0b00111100,0b01000000,0b01000000,0b00100000,0b01111100, /* 117 = u */
  5,0b00011100,0b00100000,0b01000000,0b00100000,0b00011100, /* 118 = v */
  5,0b00111100,0b01000000,0b00110000,0b01000000,0b00111100, /* 119 = w */
  5,0b01000100,0b00101000,0b00010000,0b00101000,0b01000100, /* 120 = x */
  5,0b00000100,0b01001000,0b00110000,0b00001000,0b00000100, /* 121 = y */
  5,0b01000100,0b01100100,0b01010100,0b01001100,0b01000100, /* 122 = z */
  3,0b00001000,0b00110110,0b01000001,                       /* 123 = { */
  1,0b01111111,                                             /* 124 = | */
  3,0b01000001,0b00110110,0b00001000,                       /* 125 = } */
  5,0b00011000,0b00000100,0b00001000,0b00010000,0b00001100  /* 126 = ~ */
};

static const uint16_t font_index[95] PROGMEM = {
  0,3,6,10,16,22,28,34,36,40,44,48,54,57,63,66,72,78,82,88,94,
  100,106,112,118,124,130,133,136,141,147,152,158,164,170,176,
  182,188,194,200,206,212,218,224,230,236,242,248,254,260,266,
  272,278,284,290,296,302,308,314,320,324,330,334,340,346,348,
  354,360,366,372,378,384,390,396,400,405,411,415,421,427,433,
  439,445,451,457,463,469,475,481,487,493,499,503,505,509
};

// Текст для прокрутки
char text[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_'abcdefghijklmnopqrstuvwxyz{|}~";
uint16_t textIndex = 0;
uint8_t colIndex = 0;
uint16_t scrollWhitespace = 0;

void nextChar() {
  if (text[++textIndex] == '\0') {
    textIndex = 0;
    scrollWhitespace = DISPLAY_WIDTH;
  }
}

void nextCol(uint8_t width) {
  if (++colIndex == width) {
    scrollWhitespace = 2;
    colIndex = 0;
    nextChar();
  }  
}

void writeCol() {
  if (scrollWhitespace > 0) {
    scrollWhitespace--;
    return;
  }
  
  uint8_t ascii = text[textIndex] - 32;
  uint16_t idx = pgm_read_word(&(font_index[ascii]));
  uint8_t width = pgm_read_byte(&(font[idx]));
  uint8_t column = pgm_read_byte(&(font[colIndex + idx + 1]));
  
  ledMatrix.setColumn(DISPLAY_WIDTH - 1, column);
  nextCol(width);
}

void marquee() {
  if (millis() < 1) marqueeDelayTimestamp = 0;
  if (millis() < marqueeDelayTimestamp) return;
    
  marqueeDelayTimestamp = millis() + SCROLL_DELAY;
  ledMatrix.scroll(AlashLEDMatrix8x8::scrollDirection::scrollLeft);
  writeCol();
  ledMatrix.display();
}

void setup() {
  ledMatrix.setEnabled(true);
  ledMatrix.setIntensity(0);
}

void loop() {
  marquee();
}
