#include "LoRaWan_APP.h"
#include "Arduino.h"

#ifndef LoraWan_RGB
#define LoraWan_RGB 0
#endif

#define RF_FREQUENCY                                868000000 // Hz
#define TX_OUTPUT_POWER                             5        // dBm
#define LORA_BANDWIDTH                              0         // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false

#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 30 // Define the payload size here

char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;
void OnTxDone(void);
void OnTxTimeout(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

typedef enum {
    LOWPOWER,
    RX,
    TX
} States_t;

int16_t txNumber;
States_t state;
bool sleepMode = false;
int16_t Rssi, rxSize;

void setup() {
    Serial.begin(115200);

    txNumber = 0;
    Rssi = 0;

    RadioEvents.TxDone = OnTxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxDone = OnRxDone;

    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);
    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);
    state = RX;
}

void loop() {
    switch (state) {
        case TX:
            delay(1000);
            strcpy(txpacket, "ACK");
            turnOnRGB(COLOR_SEND, 0);
            Serial.printf("\r\nsending packet \"%s\", length %d\r\n", txpacket, strlen(txpacket));

            Radio.Send((uint8_t *)txpacket, strlen(txpacket));
            state = LOWPOWER;
            break;
        case RX:
            Serial.println("into RX mode");
            Radio.Rx(0);
            state = LOWPOWER;
            break;
        case LOWPOWER:
            lowPowerHandler();
            break;
        default:
            break;
    }
    Radio.IrqProcess();
}

void OnTxDone(void) {
    Serial.print("TX done......");
    turnOffRGB();
    state = RX;
}

void OnTxTimeout(void) {
    Radio.Sleep();
    Serial.print("TX Timeout......");
    state = RX;
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
    Rssi = rssi;
    rxSize = size;
    memcpy(rxpacket, payload, size);
    rxpacket[size] = '\0';
    turnOnRGB(COLOR_RECEIVED, 0);
    Radio.Sleep();

    Serial.printf("\r\nreceived packet \"%s\" with Rssi %d, length %d\r\n", rxpacket, Rssi, rxSize);
    Serial.println("wait to send next packet");

    state = TX;
}
