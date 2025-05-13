#include <SparkFun_Ublox_Arduino_Library.h>

#define SERIAL1_RX 34 // GPS_TX -> 34
#define SERIAL1_TX 12 // 12 -> GPS_RX

SFE_UBLOX_GPS NEO6GPS;

void setupGPS()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial is open now");
  Serial1.begin(9600, SERIAL_8N1, SERIAL1_RX, SERIAL1_TX);
  delay(300);

  do {
    if (NEO6GPS.begin(Serial1)) {
      Serial.println("GPS connection ok");
      NEO6GPS.setUART1Output(COM_TYPE_NMEA);
      NEO6GPS.saveConfiguration();
      Serial.println("Enable NMEA");
      NEO6GPS.disableNMEAMessage(UBX_NMEA_GLL, COM_PORT_UART1);
      NEO6GPS.disableNMEAMessage(UBX_NMEA_GSA, COM_PORT_UART1);
      NEO6GPS.disableNMEAMessage(UBX_NMEA_GSV, COM_PORT_UART1);
      NEO6GPS.disableNMEAMessage(UBX_NMEA_VTG, COM_PORT_UART1);
      NEO6GPS.disableNMEAMessage(UBX_NMEA_RMC, COM_PORT_UART1);
      NEO6GPS.enableNMEAMessage(UBX_NMEA_GGA, COM_PORT_UART1);
      NEO6GPS.saveConfiguration();
      Serial.println("NMEA-GGA enabled!");
      break;
    }
    delay(1000);
  } while(1);
}

String sentence_sep(String input, int index) {
  int finder = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = input.length() - 1;

  for (int i = 0; i <= maxIndex && finder <= index; i++) {
    if (input.charAt(i) == ',' || i == maxIndex) {
      finder++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return finder > index ? input.substring(strIndex[0], strIndex[1]) : "";
}

float convert_gps_coord(float deg_min, String orientation) {
  double gps_min = fmod((double)deg_min, 100.0);
  int gps_deg = deg_min / 100;
  double dec_deg = gps_deg + ( gps_min / 60 );
  if (orientation == "W" || orientation == "S") {
    dec_deg = 0 - dec_deg;
  }
  return dec_deg;
}


