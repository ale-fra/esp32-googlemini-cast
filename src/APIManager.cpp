#include <APIManager.h>

WebServer server(80);

APIManager::APIManager()
{
}

APIManager::APIManager(NetworkManager &nm, GoogleHomeNotifier &ghn) : _nm(&nm), _ghn(&ghn)
{
}

void APIManager::setupApi()
{
    server.on("/heartbeat", [&]
              { getHeartbeat(); });
    server.on("/getNetStatus", [&]
              { getNetStatus(); });
    // // server.on("/updateNet", HTTP_POST, handlePost);
    // server.on("/factoryReset", HTTP_POST, factoryReset);
    server.on("/play", HTTP_POST, [&]
              { postPlaySong(); });

    // start server
    server.begin();
}

void APIManager::handleClient()
{
    server.handleClient();
}

void APIManager::getNetStatus()
{
    Serial.println("[DEBUG] WIFI_INFO DEBUG");
    JsonDocument doc;
    doc["status"] = "200";
    doc["description"] = "success";
    doc["SSID"] = _nm->getSSID();
    doc["description"] = "success";
    doc["IP"] = (String)WiFi.localIP();
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
}

void APIManager::getHeartbeat()
{
    JsonDocument doc;
    Serial.println("[DEBUG] Create Heatbeat");
    doc["status"] = "200";
    doc["description"] = "success";
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
}

// void factoryReset()
// {
//   JsonDocument doc;

//   Serial.println("[DEBUG] Factory reset device");
//   doc["status"] = "200";
//   doc["description"] = "success, device restarting";
//   String response;
//   serializeJson(doc, response);
//   server.send(200, "application/json", response);
//   sleep(250);
//   nm.resetSetting();
// }

void APIManager::postPlaySong()
{
    JsonDocument doc;

    // String mp3URL = "http://" + ip.toString() + "/shared/a_ram_sam_sam.mp3";
    String mp3URL = "http://192.168.68.56/shared/a_ram_sam_sam.mp3";
    if (_ghn->play(mp3URL.c_str()) != true)
    {
        Serial.println(_ghn->getLastError());
        return;
    }
    Serial.println("Done.");

    Serial.println("[DEBUG] play song");
    doc["status"] = "200";
    doc["description"] = "success";
    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
}
