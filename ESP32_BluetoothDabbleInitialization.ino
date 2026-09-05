#include <DabbleESP32.h> // Forked DabbleESP32 Library for Classic Bluetooth Support & Removal of SoftwareSerial for ESP built-in HardwareSerial
#include <Abstracted_Functions.h>

#if !SOC_BT_SUPPORTED || !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth not supported, or Bluetooth/BlueDroid Host is not enabled
#endif

// For non-blocking bluetooth ghost connection check
unsigned long previousTimeStamp = 0;
const unsigned long msTimeout = 30000;

void setup() {
  Serial.begin(115200); // Typical ESP32 Baud Rate
  delay(1000);
  Dabble.begin("ESP32_Connect");  // Initalize Dabble BluetoothSerial Configuration for Classic Bluetooth
  Serial.println(esp_Bluetooth_MAC());
  Serial.println("Bluetooth is ready. Connect using Dabble app.");
}

void loop() {
  Dabble.processInput();  // Dabble App's incoming data requires processing before it is usable

  if (Terminal.available()) { // Executes only if there is an incoming data
    previousTimeStamp = millis();
    String message = Terminal.readString(); // save msg to local String variable
    Serial.print("Received from phone: ");
    Serial.println(message);
    Terminal.println("ESP32: Message received - " + message); // ESP32 replies to Dabble Terminal app with the same msg
  }

  if(GamePad.isUpPressed()) { // Experimental
    Serial.println("Up Button is Pressed");
  }

  // Check if Bluetooth is still connected
  if (Dabble.isAppConnected()) { 
    if (millis() - previousTimeStamp >= msTimeout) {
      Serial.println("Ghost Connection detected! Rebooting ESP32...");
      delay(100);
      /*
        Restart ESP because the original Dabble Library is restricted to AVR Boards
        and forked Dabble library is limited, causing problems, such as not being able to reconnect.
      */
      ESP.restart(); 
    }
  } else {
    previousTimeStamp = millis();
  }
}