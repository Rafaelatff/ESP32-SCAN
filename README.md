# ESP32-SCAN

Repositorie created to guide me during the WiFi studies with ESP32 board. This code explains how to use the ESP32 to work as a beacon that read all the SSID's, RSSI's and MAC addresses of Access Points within a certain range.

During my studies I learned that the new versions for the ESPNOW libaries doesn't have suport for the RSSI reading anymore (a few codes on internet showed lines that read of the RSSI was possible. The same for ChatGPT). So I stop using the ESPNOW protocol and start learning the usual way of coding WiFi (using the tcpip protocol and others).

Also, during this code creation, I discovered that some old codes were replaced, such `tcpip_adapter_init()`, that was replaced by `esp_netif_init()`. You can check more info by reading the [TCP/IP Adapter Migration Guide](https://docs.espressif.com/projects/esp-idf/en/v4.2/esp32/api-reference/network/tcpip_adapter_migration.html).

The creating of this code was aided by the Espressif examples and also the [API Guides » Wi-Fi Driver](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html).

# WiFi Scan code

## WiFi Init

I used the same WiFi init code (`static esp_err_t init_wifi(void)`) that I previous used in the [ESP32-WROOM-32-ESP-NOW](https://github.com/Rafaelatff/ESP32-WROOM-32-ESP-NOW) repositorie. Initialize the WiFi and configured the ESP32 board as Station Mode. 

* In STA mode (station mode) the ESP32 work as a client and can connect to a pre existing network (access point).
* In AP mode (access point mode), the ESP32 work as a WiFi access point.

## Scan code

Created a function named `static void wifi_scan(void)`. Every time it is called it performs a network scan.

Declared and zeroed a few variables to aid me. `MAXIMUM_AP` is defined as 20 and it is the maximum number that the ESP32 board can read of network.

```c
    uint16_t number = MAXIMUM_AP;  
    wifi_ap_record_t ap_info[MAXIMUM_AP];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));
```
Using the `esp_wifi_scan_start()` function (from `"esp_wifi.h"` library), I started the scan. There are two ways of sending the arguments to this function, being:

```c
wifi_scan_config_t scan_config = {
        .ssid = 0,
        .bssid = 0,
        .channel = 0,
        .show_hidden = true 
    };
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true)); // in case I want to pass the setted arguments in scan_config
```
or simply:
```c
esp_wifi_scan_start(NULL, true);
```
After that, I call the `esp_wifi_scan_get_ap_records` function and I send the parameter `number` (equal to MAXIMUM_AP = 20) and the variable that will keep the informations about found the networks (`ap_info`). Then I call the `esp_wifi_scan_get_ap_num` function to retrieve the number of networks found.

```c
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    printf("Total APs scanned = %u\n\n", ap_count);
```

To start printing the resuts, I started by printing a header:

```c
printf("               SSID               |  CHANNEL  |  RSSI  |  MAC  \n");
```

And then, to print the body, I consulted the `struct` for the `wifi_ap_record_t` type. See:

![image](https://github.com/Rafaelatff/ESP32-SCAN/assets/58916022/ebc4c179-1bff-4fe0-bc20-4563caf7326c)

Created a `for loop` to print all the networks reached (up to the MAXIMUM_AP = 20):
```c
for (int i = 0; (i < MAXIMUM_AP) && (i < ap_count); i++)
```
And inside its loop, for each index [i], that represents one found network, I printed, up to 32 characters (`%32s`) the SSID network name (`ap_info[i].ssid`). Then the channel network (`ap_info[i].primary`), and then the network RSSI (`ap_info[i].rssi`).

```c
printf(" %32s |   %5d   |  %4d  | ", ap_info[i].ssid, ap_info[i].primary, ap_info[i].rssi);
```

And to print the network MAC address, I used another `for loop`, to print the digits of the MAC address separed by `:`.

```c
for (int j = 0; j < 6; j++) {
            printf("%02x", ap_info[i].bssid[j]);
            if (j < 5) {
                printf(":");
            }
        }
printf("\n"); // to pull a line after entering the whole MAC address
```

## Remaing code

All the includes are in the code inside this repositorie and the `app_main` function is next:

```c
void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi());

    while(1){
        vTaskDelay(3000/ portTICK_PERIOD_MS);
        wifi_scan();
    }
}
```

## Results

The final code, presented the following results:

![image](https://github.com/Rafaelatff/ESP32-SCAN/assets/58916022/b556e7c5-c8dd-4b39-a766-66d9c206aa83)




