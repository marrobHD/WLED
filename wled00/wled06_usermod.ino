//starts Dallas Temp service on boot
void userSetup()
{
// Start the DS18B20 sensor
  sensors.begin(); 
}
    
//gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{

}

void userLoop()
{
  temptimer = millis();
  
// Timer to publishe new temperature every 60 seconds
  if (temptimer - lastMeasure > 60000) {
    lastMeasure = temptimer;
    
//Check if MQTT Connected, otherwise it will crash the 8266
    if (mqtt != nullptr){
      sensors.requestTemperatures();

//Gets prefered temperature scale based on selection in definitions section
      #ifdef Celsius
      float board_temperature = sensors.getTempCByIndex(0);
      #else
      float board_temperature = sensors.getTempFByIndex(0);
      #endif

//Create character string populated with user defined device topic from the UI, and the read temperature. Then publish to MQTT server.
      char subuf[38];
      strcpy(subuf, mqttDeviceTopic);
      strcat(subuf, "/temperature");
      mqtt->publish(subuf, 0, true, String(board_temperature).c_str());
    return;}
  return;}
return;
}


// /*
//  * This file allows you to add own functionality to WLED more easily
//  * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
//  * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in wled01_eeprom.h)
//  * bytes 2400+ are currently ununsed, but might be used for future wled features
//  */

// //Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)

// //gets called once at boot. Do all initialization that doesn't depend on network here
// void userSetup()
// {
  
// }

// //gets called every time WiFi is (re-)connected. Initialize own network interfaces here
// void userConnected()
// {

// }

// //loop. You can use "if (WLED_CONNECTED)" to check for successful connection
// void userLoop()
// {
  
// }
