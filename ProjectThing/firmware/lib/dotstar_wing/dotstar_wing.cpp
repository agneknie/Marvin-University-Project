// Adafruit_DotStarMatrix example for single DotStar LED matrix.
// Scrolls 'Adafruit' across the matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <Fonts/TomThumb.h>
#include <dotstar_wing.h>

#if defined(ESP8266)
  #define DATAPIN    13
  #define CLOCKPIN   14
#elif defined(__AVR_ATmega328P__)
  #define DATAPIN    2
  #define CLOCKPIN   4
#elif defined(ARDUINO_NRF52832_FEATHER)
  #define DATAPIN    7
  #define CLOCKPIN   16
#elif defined(TEENSYDUINO)
  #define DATAPIN    9
  #define CLOCKPIN   5
#elif defined(ARDUINO_ARCH_WICED)
  #define DATAPIN    PA4
  #define CLOCKPIN   PB5
#elif defined(ARDUINO_FEATHER_ESP32) // hardware spi on feather huzzah32
  #define DATAPIN    MOSI
  #define CLOCKPIN   SCK
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
  #define DATAPIN    27
  #define CLOCKPIN   13
#else // // 32u4, M0, M4, esp32-s2, nrf52840 and 328p
  #define DATAPIN    11
  #define CLOCKPIN   13
#endif

#define SHIFTDELAY 100
#define BRIGHTNESS 20

// MATRIX DECLARATION:
// Parameter 1 = width of DotStar matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   DS_MATRIX_TOP, DS_MATRIX_BOTTOM, DS_MATRIX_LEFT, DS_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     DS_MATRIX_TOP + DS_MATRIX_LEFT for the top-left corner.
//   DS_MATRIX_ROWS, DS_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   DS_MATRIX_PROGRESSIVE, DS_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type:
//   DOTSTAR_BRG  Pixels are wired for BRG bitstream (most DotStar items)
//   DOTSTAR_GBR  Pixels are wired for GBR bitstream (some older DotStars)
//   DOTSTAR_BGR  Pixels are wired for BGR bitstream (APA102-2020 DotStars)

bool state_on = true;

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
                                  12, 6, DATAPIN, CLOCKPIN,
                                  DS_MATRIX_BOTTOM     + DS_MATRIX_LEFT +
                                  DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                  DOTSTAR_BGR);

const uint16_t primaryColors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

const uint16_t adaColors[] = {
  matrix.Color(255, 0, 0),   //A red
  matrix.Color(255, 125, 0), //D orange
  matrix.Color(200, 255, 0), //A yellowish
  matrix.Color(0, 255, 0),   //F green
  matrix.Color(0, 255, 225), //R blue
  matrix.Color(150, 0, 255), //U purple
  matrix.Color(255, 0, 220), //I pink
  matrix.Color(255, 65, 0),  //T reddish
  matrix.Color(255, 220, 0)  //! orange/yellow
};

char adafruit[] = "MARVIN!!!";

void dotstar_wing_setup() {
  Serial.begin(115200);
 
  // uncomment to have wait
  //while (!Serial) delay(500); 

  Serial.println("\nDotstar Matrix Wing");
  matrix.begin();
  matrix.setFont(&TomThumb);
  matrix.setTextWrap(false);
  matrix.setBrightness(BRIGHTNESS);

  for (byte i = 0; i < 3; i++) {
    matrix.fillScreen(primaryColors[i]);
    matrix.show();
    delay(500);
  }
  dotstar_wing_show_text();
}

int x = matrix.width();
int pass = 0;
int red = 128, green = 160, blue = 192;

int loopIteration = 0;                  // iterator for up slicing main loop
const int LOOP_ROLLOVER = 300000;       // how many loops per action sequence
int TICK_DO_MATRIX = 1000;              // do matrix display

void dotstar_wing_loop() {
  if(!state_on) return;
  if(loopIteration == TICK_DO_MATRIX)   // redisplay the matrix
    dotstar_wing_show_colour();
  if(loopIteration++ == LOOP_ROLLOVER)  // roll over
    loopIteration = 0;
}

void dotstar_wing_show_text() {
  for(int iter = 0; iter < strlen(adafruit) * 5; iter++) {
    matrix.fillScreen(0);
    if(state_on) {
      matrix.setCursor(x, 5);
      for (byte i = 0; i < strlen(adafruit); i++) {
        matrix.setTextColor(adaColors[i]); // set the color
        matrix.print(adafruit[i]);         // write the letter
      }

      if(--x < -50) x = matrix.width();
    }
    matrix.show();
    delay(SHIFTDELAY);
  }
}

void dotstar_wing_show_colour() {
  if(! state_on) return;

  bool ascending = true;
  for(int b = 20; b <= 170 && b >= 20;  ) {
    matrix.setBrightness(b);
    matrix.fillScreen(matrix.Color(red, green, blue));
    matrix.show();
    if(ascending)
      b++;
    else
      b--;
    if(b == 170)
      ascending = false;
    else if(b < 20)
      break;
    delay(SHIFTDELAY / 10);
  }
  matrix.fillScreen(0);
  matrix.show();
  yield();
}

// toggle the dotstar matrix
void dotstar_wing_on()  { state_on = true; }
void dotstar_wing_off() { state_on = false; }
bool dotstar_wing_state_on() { return state_on; }
