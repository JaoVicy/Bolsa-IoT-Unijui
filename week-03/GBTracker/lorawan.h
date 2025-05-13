/***************************************************************************************************
   Copyright (c) 2023 Gerson Battisti
   GBTracker - LoRaWan Demo Tracker
 ***************************************************************************************************/

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <LoRaBoards.h>

String read_sentence;
uint8_t tx_payload[21];

boolean join_success = false;
//
// For normal use, we require that you edit the sketch to replace FILLMEIN
// with values assigned by the TTN console. However, for regression tests,
// we want to be able to compile these scripts. The regression tests define
// COMPILE_REGRESSION_TEST, and in that case we define FILLMEIN to a non-
// working but innocuous value.
//
#ifdef COMPILE_REGRESSION_TEST
# define FILLMEIN 0
#else
# warning "You must replace the values marked FILLMEIN with real values from the TTN control panel!"
# define FILLMEIN (#dont edit this, edit the lines that use FILLMEIN)
#endif

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
//74 50 81 c1 1c 0a 77 4b           Chirp

//47 CB AF 6D F4 24 8B 9D 

//LilyGo Demo
static const u1_t PROGMEM APPEUI[8] = {0x53,0x45,0x97,0xb8,0xeb,0x35,0xba,0xb4};

//static const u1_t PROGMEM APPEUI[8] = {0x4b,0x77,0x0a,0x1c,0xc1,0x81,0x50,0x74};
//static const u1_t PROGMEM APPEUI[8] = { 0x47,0xcb,0xaf,0x6d,0xf4,0x24,0x8b,0x9d };
void os_getArtEui (u1_t* buf) {
  memcpy_P(buf, APPEUI, 8);
}

// This should also be in little endian format, see above.
//LilyGo Demo
static const u1_t PROGMEM DEVEUI[8] = {0x53,0x45,0x97,0xb8,0xeb,0x35,0xba,0xb4};

//static const u1_t PROGMEM DEVEUI[8] = {0x4b,0x77,0x0a,0x1c,0xc1,0x81,0x50,0x74};
//static const u1_t PROGMEM DEVEUI[8] = { 0x47,0xcb,0xaf,0x6d,0xf4,0x24,0x8b,0x9d };
void os_getDevEui (u1_t* buf) {
  memcpy_P(buf, DEVEUI, 8);
}
//0xa2,0x7e,0xfc,0x95,0x90,0x12,0x3f,0x02,0xb7,0x24,0xfc,0x51,0x64,0x5f,0x1c,0x2e
// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from ttnctl can be copied as-is.

//LilyGo Demo
static const u1_t PROGMEM APPKEY[16] = {0x1f,0x9b,0x21,0x82,0x34,0x71,0x94,0x61,0x83,0x8f,0x11,0xcb,0x35,0xdc,0x3c,0x00};

//1f9b218234719461838f11cb35dc3c00

//static const u1_t PROGMEM APPKEY[16] = {0xa2,0x7e,0xfc,0x95,0x90,0x12,0x3f,0x02,0xb7,0x24,0xfc,0x51,0x64,0x5f,0x1c,0x2e};




void os_getDevKey (u1_t* buf) {
  memcpy_P(buf, APPKEY, 16);
}

static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 60;

//LoRa pin mapping ESP32 (LILYGO Board V1.1)
/*const lmic_pinmap lmic_pins = {
  .nss = 18,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 23,  //23
  .dio = {26, 33, 32},
}; */
const lmic_pinmap lmic_pins = {
    .nss =  RADIO_CS_PIN,
    .rxtx = LMIC_UNUSED_PIN,
    .rst =  RADIO_RST_PIN,
    .dio = {RADIO_DIO0_PIN, RADIO_DIO1_PIN, RADIO_DIO2_PIN}
};

void setupLoRa(){

// LMIC init
  Serial.print("Iniciando LoRa ...");
  //Serial.print(os_init_ex (lmic_pins));
  os_init();
}

  
void printHex2(unsigned v) {
  v &= 0xff;
  if (v < 16)
    Serial.print('0');
  Serial.print(v, HEX);
}

void do_send(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    // Prepare upstream data transmission at the next possible time.

    Serial.print("Payload: ");
    int x = 0;
    while (x < sizeof(tx_payload)) {
      printHex2(tx_payload[x]);
      Serial.print(" ");
      x++;
    }
    Serial.println();

    LMIC_setTxData2(1, tx_payload, sizeof(tx_payload), 0);
    Serial.println(F("Packet queued"));
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      {
        u4_t netid = 0;
        devaddr_t devaddr = 0;
        u1_t nwkKey[16];
        u1_t artKey[16];
        LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);
        Serial.print("netid: ");
        Serial.println(netid, DEC);
        Serial.print("devaddr: ");
        Serial.println(devaddr, HEX);
        Serial.print("AppSKey: ");
        for (size_t i = 0; i < sizeof(artKey); ++i) {
          if (i != 0)
            Serial.print("-");
          printHex2(artKey[i]);
        }
        Serial.println("");
        Serial.print("NwkSKey: ");
        for (size_t i = 0; i < sizeof(nwkKey); ++i) {
          if (i != 0)
            Serial.print("-");
          printHex2(nwkKey[i]);
        }
        Serial.println();
        join_success = true;
      }
      // Disable link check validation (automatically enabled
      // during join, but because slow data rates change max TX
      // size, we don't use it in this example.
      LMIC_setLinkCheckMode(0);
      break;
    /*
      || This event is defined but not used in the code. No
      || point in wasting codespace on it.
      ||
      || case EV_RFU1:
      ||     Serial.println(F("EV_RFU1"));
      ||     break;
    */
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      break;
    case EV_TXCOMPLETE:

      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      if (LMIC.txrxFlags & TXRX_ACK)
        Serial.println(F("Received ack"));
      if (LMIC.dataLen) {
        Serial.print(F("Received "));
        Serial.print(LMIC.dataLen);
        Serial.println(F(" bytes of payload"));
      }
      // Schedule next transmission
      os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
      break;
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    /*
      || This event is defined but not used in the code. No
      || point in wasting codespace on it.
      ||
      || case EV_SCAN_FOUND:
      ||    Serial.println(F("EV_SCAN_FOUND"));
      ||    break;
    */
    case EV_TXSTART:
      Serial.println(F("EV_TXSTART"));
      break;
    case EV_TXCANCELED:
      Serial.println(F("EV_TXCANCELED"));
      break;
    case EV_RXSTART:
      /* do not print anything -- it wrecks timing */
      break;
    case EV_JOIN_TXCOMPLETE:
      Serial.println(F("EV_JOIN_TXCOMPLETE: no JoinAccept"));
      break;

    default:
      Serial.print(F("Unknown event: "));
      Serial.println((unsigned) ev);
      break;
  }
}

