#include <Abstracted_Functions.h>

String esp_Bluetooth_MAC() {
  uint8_t bt_MAC_Address[6]; // Hold Calculated 6 bytes Bluetooth MAC Address
  if(esp_read_mac(bt_MAC_Address, ESP_MAC_BT) == ESP_OK) {
    char temp_btMAC[40]; // Temporary hold Bluetooth MAC Address with description
    snprintf(temp_btMAC, sizeof(temp_btMAC), "ESP BT MAC-Address: %02X:%02X:%02X:%02X:%02X:%02X", bt_MAC_Address[0], bt_MAC_Address[1], bt_MAC_Address[2], bt_MAC_Address[3], bt_MAC_Address[4], bt_MAC_Address[5]);
    return String(temp_btMAC);
  }
  return "ERROR";
}