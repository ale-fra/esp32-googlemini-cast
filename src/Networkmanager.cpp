#include <NetworkManager.h>

// constructor of NetworkManager,
NetworkManager::NetworkManager()
{
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    wm.setConfigPortalBlocking(false);
    wm.setConfigPortalTimeout(60);
    // automatically connect using saved credentials if they exist
    // If connection fails it starts an access point with the specified name
    wm.setConnectTimeout(500);
    wm.setConnectRetries(50);

    unsigned long previousMillis = 0;
    unsigned long interval = 30000;
}

// definition of Meow method
// returns: void
// parameters: None
// action: Prints "meow" to screen
void NetworkManager::resetSetting()
{
    wm.resetSettings();
    ESP.restart();
}

void NetworkManager::setHostname(String hostname)
{
    wm.setHostname(hostname);
}

void NetworkManager::process()
{
    wm.process();
    unsigned long currentMillis = millis();
    // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval))
    {
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        WiFi.disconnect();
        WiFi.reconnect();
        previousMillis = currentMillis;
    }
}

bool NetworkManager::autoConnect()
{
    bool connected = wm.autoConnect("AutoConnectAP");
    if (connected)
    {
        Serial.println("connected...yeey :)");
        wm.setHostname("esp32");
    }
    return connected;
}

String NetworkManager::getSSID()
{
    return wm.getWiFiSSID();
}
