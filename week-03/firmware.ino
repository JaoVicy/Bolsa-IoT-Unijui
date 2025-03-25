/*
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

// Configurações OTAA - Substitua com seus dados!
const char *appEui = "0000000000000000";
const char *appKey = "aa58dd2d23b9391b977f785e4dca437c";
const char *devEui = "e120b09cad629058";

// Pinagem T-Beam v1 (NÃO ALTERAR)
const lmic_pinmap lmic_pins = {
    .nss = 18, .rxtx = LMIC_UNUSED_PIN, .rst = 23,
    .dio = {26, 33, 32} // DIO0=26, DIO1=33, DIO2=32
};

void os_getArtEui(u1_t* buf) { memcpy(buf, appEui, 8); }
void os_getDevEui(u1_t* buf) { memcpy(buf, devEui, 8); }
void os_getDevKey(u1_t* buf) { memcpy(buf, appKey, 16); }

void onEvent(ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            LMIC_setLinkCheckMode(0);
            // Configuração pós-join otimizada
            LMIC.datarate = DR_SF7;
            LMIC.txpow = 14;
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE"));
            break;
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println(F("Iniciando T-Beam v1.0 (915 MHz)..."));

    os_init();
    LMIC_reset();
    
    // Ajustes críticos
    LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);
    LMIC_setAdrMode(1);

    // Configuração de canais para Brasil (915 MHz)
    // Formato definitivo para MCCI LMIC v4.x
    LMIC_setupChannel(0, 915200000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(1, 915400000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(2, 915600000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(3, 915800000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(4, 916000000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(5, 916200000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(6, 916400000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);
    LMIC_setupChannel(7, 916600000, DR_RANGE_MAP(DR_SF10, DR_SF7), 0);

    // Configuração de potência definitiva
    LMIC.txpow = 14; // 14 dBm

    // Configuração de região US915
    for (int i = 8; i < 72; i++) {
        LMIC_disableChannel(i); // Desativa todos os canais extras
    }
    LMIC_enableChannel(0); // Ativa apenas os 8 canais principais

    LMIC_startJoining();
}

void loop() {
    os_runloop_once();
    delay(10);
}
*/