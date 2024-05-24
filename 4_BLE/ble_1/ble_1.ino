#include <ArduinoBLE.h>

BLEService ledService("e628f80f-77ca-4cd7-a930-efb37e826937");  // BLE LED Service
BLEService acelService("6282a2a1-5f99-430e-abda-ba09b255bdd4");
BLEByteCharacteristic switchCharacteristic("163e6b0d-caad-4a54-98be-c98e8beae724", BLERead | BLEWrite);
BLEByteCharacteristic acelChar("68f6b451-210d-4dda-9dea-bd8ead4bc544", BLERead | BLENotify);
BLEDescriptor acelDes("0x2901", "Aceleracion");

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");
    while (1)
      ;
  }

  BLE.setLocalName("ESP32Chesus");

  BLE.setAdvertisedService(ledService);
  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);
  BLE.addService(ledService);

  BLE.setAdvertisedService(acelService);
  acelChar.addDescriptor(acelDes);
  acelService.addCharacteristic(acelChar);
  BLE.addService(acelService);

  switchCharacteristic.writeValue(0);

  BLE.advertise();
  Serial.println("BLE LED Peripheral");
}

void loop() {
  static bool registrandoAcel = false;

  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    while (central.connected()) {
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value() == 0) {
          Serial.println("Led on");
          registrandoAcel = true;
        } else {
          Serial.println("Led off");
          registrandoAcel = false;
        }
      }
      if (registrandoAcel) {
        acelChar.writeValue(random(0, 100));
        delay(500);
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}