#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "GPS_Air530.h"
#include "GPS_Air530Z.h"

#define RF_FREQUENCY 868000000 // Hz
#define TX_OUTPUT_POWER 5      // dBm
#define LORA_BANDWIDTH 0       // 125 kHz
#define LORA_SPREADING_FACTOR 7
#define LORA_CODINGRATE 1      // 4/5
#define LORA_PREAMBLE_LENGTH 8
#define LORA_SYMBOL_TIMEOUT 0
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false

#define LED_PIN_TX GPIO8
#define LED_PIN_RX GPIO9  

#define BUFFER_SIZE 30

static RadioEvents_t RadioEvents;

uint8_t txpacket[BUFFER_SIZE];
uint8_t rxpacket[BUFFER_SIZE];

Air530ZClass GPS;

void OnTxDone(void);
void OnTxTimeout(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

typedef enum {
    LOWPOWER,
    RX,
    TX
} States_t;

States_t state;
unsigned long lastSendTime = 0;

void setup() {
    Serial.begin(115200);
    GPS.begin();
    pinMode(LED_PIN_TX, OUTPUT);
    pinMode(LED_PIN_RX, OUTPUT);

    digitalWrite(LED_PIN_TX, HIGH);  // Turn the LED on
    digitalWrite(LED_PIN_RX, HIGH);  // Turn the LED on
    delay(2000);                  // Wait for 1 second
    digitalWrite(LED_PIN_TX, LOW);   // Turn the LED off
    digitalWrite(LED_PIN_RX, LOW);   // Turn the LED off
    delay(2000); 
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
                      0, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    Radio.Rx(0);  // Set continuous RX mode
    state = TX;   // Start in TX to send first packet
}

void loop() {
    switch (state) {
        case TX: {
          delay(1000);
          uint32_t starttime = millis();
          while ((millis() - starttime) < 1000) {
              while (GPS.available() > 0) {
                GPS.encode(GPS.read());
              }
            }
            float latitude = GPS.location.lat();  // Scoped within the case
            float longitude = GPS.location.lng(); 
            if (latitude != 0 && longitude != 0) { // Check for valid GPS data
                for (int i = 0; i < 4; i++) {
                    digitalWrite(LED_PIN_TX, HIGH); // Turn the LED on
                    delay(200);                     // Wait for 0.2 seconds
                    digitalWrite(LED_PIN_TX, LOW);  // Turn the LED off
                    delay(200);  
                }
                sprintf((char*)txpacket, "%.6f,%.6f", latitude, longitude);
                Serial.printf("Sending packet: %s\n", txpacket);
                Radio.Send(txpacket, strlen((char*)txpacket));
                lastSendTime = millis();
                state = LOWPOWER; // Wait for TX to complete
            } else {
                digitalWrite(LED_PIN_TX, HIGH); // Turn the LED on
                delay(1000);                   // Wait for 1 second
                digitalWrite(LED_PIN_TX, LOW); // Turn the LED off
                delay(1000);  
            }
            break;
        }
        case RX:
            // Reception is handled in OnRxDone
            break;
        case LOWPOWER:
            if (millis() - lastSendTime > 5000) { // 5 seconds delay
                state = TX; // Send next packet after 5 seconds
            }
            break;
    }
    Radio.IrqProcess(); // Handle LoRa events
}



void OnTxDone(void) {
    Serial.println("TX complete, switching to RX mode");
    Radio.Rx(0);  // Return to RX mode after sending
}

void OnTxTimeout(void) {
    Serial.println("TX timeout, retrying...");
    state = TX;
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
    memcpy(rxpacket, payload, size);
    rxpacket[size] = '\0';
    Serial.print("Received packet: ");
    Serial.println((char*)rxpacket);
    digitalWrite(LED_PIN_RX, HIGH);  // Turn the LED on
    delay(1000);  
    state = TX; // Switch back to TX after processing RX
}
