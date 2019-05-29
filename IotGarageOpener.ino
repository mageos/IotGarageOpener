#include <ESP8266WiFi.h>
#include <FS.h>
#include <GDBStub.h>
#include <ArduinoJson.h>
#include <Ticker.h>
#include "HttpServer.h"
#include "Led.h"
#include "Button.h"
#include "Thermometer.h"
#include "Scheduler.h"

void handleManualButton();

Button manualButton(D2, handleManualButton);
Thermometer thermometer(A0);
Led green(D6);
Led red(D7);
WebServer server;

long lastReport = 0;

void reportStatus()
{    
    auto currentReport = millis();

    if (currentReport - lastReport < 5000)
    {
        return;
    }

    Serial.printf("Last Temperature is %f C or %f F.  Averaged %f C (%f F)\n",
             thermometer.lastReadingC(),
             thermometer.lastReadingF(),
             thermometer.averagedC(),
             thermometer.averagedF());

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    lastReport = currentReport;   
}

void initializeWifi()
{
    green.off();

    File settings = SPIFFS.open("/priv.settings", "r");

    StaticJsonDocument<200> doc;

    deserializeJson(doc, settings);    

    const char* ssid = doc["ssid"];
    const char* key = doc["key"];

    settings.close();

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.hostname("Arduino");

    WiFi.begin(ssid, key);    

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        red.toggle();
    }
    Serial.println("");
    Serial.println("WiFi connected");
}

Runable* actions[] = {&server, &red, &green, &manualButton, &thermometer};

void setup()
{
    Serial.begin(115200);
    gdbstub_init();
    delay(250);

    if (!SPIFFS.begin())
    {
        //_led.blink(125,5);
    }    

    initializeWifi();
    
    server.initialize(handleManualButton);

    pinMode(A0, INPUT);

    green.on();
    red.off();
}

void loop()
{   
    for (int i=0; i < 5; i++)
    {
        actions[i]->run();
    }    

    reportStatus();

    yield();
}

void handleManualButton()
{
    green.toggle();
    green.blink(100, 5);
}