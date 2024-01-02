# ESP32-SCAN

Repositorie created to guide me during the WiFi studies with ESP32 board. This code explains how to use the ESP32 to work as a beacon that read all the SSID's, RSSI's and MAC addresses of Access Points within a certain range.

During my studies I learned that the new versions for the ESPNOW libaries doesn't have suport for the RSSI reading anymore (a few codes on internet showed lines that read of the RSSI was possible. The same for ChatGPT). So I stop using the ESPNOW protocol and start learning the usual way of coding WiFi (using the tcpip protocol and others).

Also, during this code creation, I discovered that some old codes were replaced, such `tcpip_adapter_init()`, that was replaced by `esp_netif_init()`. You can check more info by reading the [TCP/IP Adapter Migration Guide](https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/api-reference/network/tcpip_adapter_migration.html).

The creating of this code was aided by the Espressif examples and also the [API Guides » Wi-Fi Driver](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html).

# WiFi Scan code

## WiFi Init

## Scan code

## Results

The final code, presented the following results:

![image](https://github.com/Rafaelatff/ESP32-SCAN/assets/58916022/b556e7c5-c8dd-4b39-a766-66d9c206aa83)




