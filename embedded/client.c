#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <conf.h>

#define DIRA 0
#define PWMA 5

const char* ssid = WIFISSID;
const char* password = WIFIPASSWORD;
const char* websockets_server = WSSERVER;

using namespace websockets;

void onMessageCallback(WebsocketsMessage message) {
     analogWrite(PWMA, message.data().toInt());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    }
}

WebsocketsClient client;
void setup() {
    Serial.begin(115200);

    pinMode(DIRA, OUTPUT);
    pinMode(PWMA, OUTPUT);
    analogWrite(PWMA, 0);
    digitalWrite(DIRA, 1);

    WiFi.begin(ssid, password);

    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Setup Callbacks
    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);

    // Connect to server
    client.connect(websockets_server);
}

void loop() {
    client.poll();
}
