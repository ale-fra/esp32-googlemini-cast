#pragma once
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

class NetworkManager // begin declaration of the class
{
public:               // begin public section
    NetworkManager(); // constructor
    // NetworkManager(const NetworkManager &copy_from);            // copy constructor
    // NetworkManager &operator=(const NetworkManager &copy_from); // copy assignment

    // int GetAge() const;   // accessor function
    // void SetAge(int age); // accessor function
    void resetSetting();
    bool autoConnect();
    void process();
    void setHostname(String hostname);
    String getSSID();

private: // begin private section
    // int itsAge; // member variable
    // char *string;
    WiFiManager wm;
    unsigned long previousMillis;
    unsigned long interval;
};