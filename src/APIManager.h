#pragma once

#include <WebServer.h>
#include <NetworkManager.h>
#include <ArduinoJson.h>
#include <esp8266-google-home-notifier.h>

class APIManager // begin declaration of the class
{

public:                                                      // begin public section
    APIManager();                                            // constructor
    APIManager(NetworkManager &nm, GoogleHomeNotifier &ghn); // constructor

    void setupApi();
    void handleClient();

private: // begin private section
         // int itsAge; // member variable
         // char *string;
         // WiFiManager wm;
    void getHeartbeat();
    void getNetStatus();
    void postPlaySong();
    NetworkManager *_nm;
    GoogleHomeNotifier *_ghn;
};