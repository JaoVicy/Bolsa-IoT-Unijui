/**
* GBTRACKER
* Demonstrativo de Rastreador usando LoRa
* Gerson Battisti
*/
// For a connection via I2C using the Arduino Wire include:
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include "images.h"
//#include "boards.h"
#include "OLEDDisplayUi.h"
#include "gps.h"
#include "lorawan.h"


#define I2C_SDA                     21
#define I2C_SCL                     22
#define DHT_SENSOR_PIN  25 // ESP32 pin GIOP25 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT22
#define BUTTON_PIN                  38

SSD1306Wire display(0x3c, I2C_SDA, I2C_SCL);
OLEDDisplayUi ui     ( &display );

#include <DHT.h>


DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// Variaveis Globais

float LatInt=0;
float LatDec=0;
int LatOri=0;

float LonInt=0;
float LonDec=0;
int LonOri=0;

float Altitude=0;
int Sat=0;
float Temp=0;
float Humi=0;



void msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state)
{
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(128, 0, String(millis()));
}

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // draw an xbm image.
    // Please note that everything that should be transitioned
    // needs to be drawn relative to x and y
    display->drawXbm(x + 30, y + 0, UNIJUI_Logo_width, UNIJUI_Logo_height, UNIJUI_Logo_bits);
}

void drawFrameGPS(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // draw an xbm image.
    // Please note that everything that should be transitioned
    // needs to be drawn relative to x and y
    display->setFont(ArialMT_Plain_10);
    display->drawString( x + 0, 0,  "LAT : "+ String(LatInt)+ String(LatDec)+ String(char(LatOri)));

    display->setFont(ArialMT_Plain_10);
    display->drawString(  x + 0, 20, "LGT : "+ String(LonInt)+ String(LonDec)+ String(char(LonOri)));
    
    display->setFont(ArialMT_Plain_10);
    display->drawString(  x + 0, 40, "ALT : "+ String(Altitude) + "m");

    display->drawXbm( x + 100, 0, SATELLITE_IMAGE_WIDTH, SATELLITE_IMAGE_HEIGHT, SATELLITE_IMAGE);
    display->setFont(ArialMT_Plain_10);
    display->drawString(  x + 120, 0, String(Sat));
}

void drawFrameUNIJUI_H_LOGO(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // draw an xbm image.
    // Please note that everything that should be transitioned
    // needs to be drawn relative to x and y
    display->drawXbm( x + 4, 10, UNIJUI_H_width, UNIJUI_H_height, UNIJUI_H_Logo);
}

void drawFrameHumidity(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // draw an xbm image.
    // Please note that everything that should be transitioned
    // needs to be drawn relative to x and y
    display->setFont(ArialMT_Plain_24);
    display->drawString( x + 10, 10, String(Humi));
    display->drawXbm( x + 80, 10, humidity_icon_width, humidity_icon_height, humidity_icon);
}

void drawFrameTemperature(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // draw an xbm image.
    // Please note that everything that should be transitioned
    // needs to be drawn relative to x and y
    display->setFont(ArialMT_Plain_24);
    display->drawString( x + 10, 10, String(Temp));
    display->drawXbm( x + 80, 10, temperature_icon_width, temperature_icon_height, temperature_icon);
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
    // Besides the default fonts there will be a program to convert TrueType fonts into this format
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(0 + x, 10 + y, "Arial 10");

    display->setFont(ArialMT_Plain_16);
    display->drawString(0 + x, 20 + y, "Arial 16");

    display->setFont(ArialMT_Plain_24);
    display->drawString(0 + x, 34 + y, "Arial 24");
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Text alignment demo
    display->setFont(ArialMT_Plain_10);

    // The coordinates define the left starting point of the text
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0 + x, 11 + y, "Left aligned (0,10)");

    // The coordinates define the center of the text
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64 + x, 22 + y, "Center aligned (64,22)");

    // The coordinates define the right end of the text
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    display->drawString(128 + x, 33 + y, "Right aligned (128,33)");
}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Demo for drawStringMaxWidth:
    // with the third parameter you can define the width after which words will be wrapped.
    // Currently only spaces and "-" are allowed for wrapping
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawStringMaxWidth(0 + x, 10 + y, 128, "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore.");
}
/*
void drawFrame5(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_16);
    display->drawString(0 + x, 10 + y, "Humi: " + String(dht_sensor.readHumidity()));

    display->setFont(ArialMT_Plain_16);
    display->drawString(0 + x, 30 + y, "Temp: " + String(dht_sensor.readTemperature()));

}
*/
// This array keeps function pointers to all frames
// frames are the single views that slide in
//FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4, drawFrame5 };
FrameCallback frames[] = { drawFrameUNIJUI_H_LOGO, drawFrameTemperature , drawFrameHumidity, drawFrameGPS};

// how many frames are there?
int frameCount = 4;

// Overlays are statically drawn on top of a frame eg. a clock
//OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;

bool autoTransition = false;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting");
  Serial1.begin(9600, SERIAL_8N1, SERIAL1_RX, SERIAL1_TX);
  //SPI pin mapping ESP32 (LILYGO Board V1.1)
  SPI.begin(5, 19, 27, 18);
  //initBoard();

/*
  #ifdef VCC_ENABLE
    // For Pinoccio Scout boards
    pinMode(VCC_ENABLE, OUTPUT);
    digitalWrite(VCC_ENABLE, HIGH);
    delay(1000);
  #endif
  
  
*/
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  #ifdef LED_PIN
    pinMode(LED_PIN, OUTPUT);
  #endif


    // The ESP is capable of rendering 60fps in 80Mhz mode
    // but that won't give you much time for anything else
    // run it in 160Mhz mode or just set it to 30 fps
    ui.setTargetFPS(30);
    // Customize the active and inactive symbol
    // ui.setActiveSymbol(activeSymbol);
    // ui.setInactiveSymbol(inactiveSymbol);

    // You can change this to
    // TOP, LEFT, BOTTOM, RIGHT
    ui.setIndicatorPosition(BOTTOM);

    // Defines where the first frame is located in the bar.
    ui.setIndicatorDirection(LEFT_RIGHT);

    // You can change the transition that is used
    // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
    ui.setFrameAnimation(SLIDE_LEFT);

    // Add frames
    ui.setFrames(frames, frameCount);

    // Add overlays
    //ui.setOverlays(overlays, overlaysCount);
    
    // Disable AutoTransition
    // ui.disableAutoTransition();

    // Initialising the UI will init the display too.
    ui.init();

    display.flipScreenVertically(); 

// Start temp sensor
 // dht_sensor.begin();
  

  
  // Reset the MAC state. Session and pending data transfers will be discarded.
  //LMIC_reset();

  //Set FS for RX2 (SF9 = TTN,TTS EU)
  LMIC.dn2Dr = DR_SF9;

  Serial.println("LMIC");
  //Serial.println(CFG_au915);
  
  beginPower();
//beginDisplay();
  // Start GPS
  //setupGPS();
   delay(3000);

  // Start LoRa
//  setupLoRa();
  // LMIC init
  os_init();


  // Start job (sending automatically starts OTAA too)
  do_send(&sendjob);
    


}

void loop()
{
  //if ()
 

 
  os_runloop_once();
  ui.update();

  
/*
  if (join_success == true) {

    int remainingTimeBudget = ui.update();

    if (remainingTimeBudget > 0) {
        // You can do some work here
        // Don't do stuff if you are below your
        // time budget.
        delay(remainingTimeBudget);
    }

    read_sentence = Serial1.readStringUntil(13); //13 = return (ASCII)
    read_sentence.trim();

    if (read_sentence.startsWith("$GPGGA")) {
       
      Serial.println(read_sentence);

      String gps_lat = sentence_sep(read_sentence, 2); //Latitude in degrees & minutes
      String gps_lon = sentence_sep(read_sentence, 4); //Longitude in degrees & minutes
      String gps_sat = sentence_sep(read_sentence, 7);
      String gps_hgt = sentence_sep(read_sentence, 9);
      String gps_lat_o = sentence_sep(read_sentence, 3);  //Orientation (N or S)
      String gps_lon_o = sentence_sep(read_sentence, 5); //Orientation (E or W)
      
      Sat = gps_sat.toInt();
      if (Sat > 0) {
        //Latitude = convert_gps_coord(gps_lat.toFloat(), gps_lat_o);
        //Longitude = convert_gps_coord(gps_lon.toFloat(), gps_lon_o);

        LatInt = gps_lat.substring(0, gps_lat.indexOf(".")).toFloat();
        LatDec = gps_lat.substring(gps_lat.indexOf(".")+1,gps_lat.indexOf(".")+6).toFloat();
        LatOri = (int) gps_lat_o[0];

        LonInt = gps_lon.substring(0, gps_lon.indexOf(".")).toFloat();
        LonDec = gps_lon.substring(gps_lon.indexOf(".")+1,gps_lon.indexOf(".")+6).toFloat();
        LonOri = (int) gps_lon_o[0];

        Altitude = gps_hgt.toFloat();
    
        Temp = dht_sensor.readTemperature();
        Humi = dht_sensor.readHumidity();
        Serial.print("LATInt: ");
        Serial.print(LatInt);
        Serial.print(" LATDec: ");
        Serial.print(LatDec);
        Serial.print(" LATOri: ");
        Serial.print(gps_lon_o);
        
        Serial.print(" ALT: ");
        Serial.print(Altitude);
        Serial.print(" SAT: ");
        Serial.println(Sat);
        Serial.print(" Temp: ");
        Serial.println(Temp);
        Serial.print(" Humi: ");
        Serial.println(Humi);

        generate_payload(LatInt, LatDec, LatOri, LonInt, LonDec, LonOri, Altitude, Sat, Temp, Humi);
    }
    }
  }   */
}

/* Gera o payload passando o valor de latitude decimal separado 
 *  Exemplo: Latitude 1234.5678 W
 *  Gera: latInt = 1234, latDec = 5678, latOri = W
 */
void generate_payload(double latInt, double latDec, int latOri, double lonInt, double lonDec, int lonOri, int alt, int sat, double temp, double humi) {
  uint16_t LatIntBinary = latInt;
  uint32_t LatDecBinary = latDec;
  uint8_t LatOriBinary = latOri;

  uint16_t LonIntBinary = lonInt;
  uint32_t LonDecBinary = lonDec;
  uint8_t LonOriBinary = lonOri;

  uint16_t TempBinary = temp * 100;
  uint16_t HumiBinary = humi * 100;

  uint8_t payload[21];

  payload[0] = ( LatIntBinary >> 8 ) & 0xFF;
  payload[1] = LatIntBinary & 0xFF;
  payload[2] = ( LatDecBinary >> 24 ) & 0xFF;
  payload[3] = ( LatDecBinary >> 16 ) & 0xFF;
  payload[4] = ( LatDecBinary >> 8 ) & 0xFF;
  payload[5] = LatDecBinary & 0xFF;

  payload[6] = LatOriBinary & 0xFF;

  payload[7] = ( LonIntBinary >> 8 ) & 0xFF;
  payload[8] = LonIntBinary & 0xFF;
  payload[9] = ( LonDecBinary >> 24 ) & 0xFF;
  payload[10] = ( LonDecBinary >> 16 ) & 0xFF;  
  payload[11] = ( LonDecBinary >> 8 ) & 0xFF;
  payload[12] = LonDecBinary & 0xFF;

  payload[13] = LonOriBinary & 0xFF;

  payload[14] = ( alt >> 8 ) & 0xFF;
  payload[15] = alt & 0xFF;

  payload[16] = sat & 0xFF;

  payload[17] = ( TempBinary >> 8 ) & 0xFF;
  payload[18] = TempBinary & 0xFF;

  payload[19] = ( HumiBinary >> 8 ) & 0xFF;
  payload[20] = HumiBinary & 0xFF;

  int i = 0;
  while (i < sizeof(payload)) {
    tx_payload[i] = payload[i];
    i++;
  }
}

/*

    // if user presses button for more than 3 secs, discard our network prefs and reboot (FIXME, use a debounce lib instead of this boilerplate)
    static bool wasPressed = false;
    static uint32_t minPressMs;  // what tick should we call this press long enough
    if (!digitalRead(BUTTON_PIN)) {
        if (!wasPressed) {
            // just started a new press
            Serial.println("pressing");
            wasPressed = true;
            minPressMs = millis() + 3000;
        }
    } else if (wasPressed) {
        // we just did a release
        ui.nextFrame();
        wasPressed = false;
        if (millis() > minPressMs) {
            if (autoTransition) {
                ui.disableAutoTransition();
                autoTransition = false;
            } else {
                ui.enableAutoTransition();
                autoTransition = true;
            }
  
        }
    }
    }
*/




