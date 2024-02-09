#include <Arduino.h>

// #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <esp8266-google-home-notifier.h>
#include <NetworkManager.h>
#include <APIManager.h>

NetworkManager nm;
GoogleHomeNotifier ghn;
APIManager apim(nm, ghn);
// APIManager apim;

// WiFiManager wm;

const char displayName[] = "Kitchen speaker";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // reset settings - wipe credentials for testing
  // wm.resetSettings();

  if (nm.autoConnect())
  {
    apim.setupApi();

    Serial.println("connecting to Google Home...");
    if (ghn.device(displayName, "en") != true)
    {
      Serial.println(ghn.getLastError());
      return;
    }
    ghn.notify("MUSICBOX READY");
    Serial.println("connecting to Google Home...");
  }
  else
  {
    Serial.println("Configportal running");
  }
}

void loop()
{
  nm.process();
  apim.handleClient();

  // put your main code here, to run repeatedly:
}