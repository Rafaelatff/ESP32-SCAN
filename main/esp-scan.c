#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h" // replaces the #include "tcpip_adapter.h"
#include <string.h> // to use 'memset'

#define MAXIMUM_AP 20

static esp_err_t init_wifi(void){
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT(); // macro default

    esp_netif_init();
    esp_event_loop_create_default();
    nvs_flash_init();
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_storage(WIFI_STORAGE_FLASH);
    esp_wifi_start();

    printf("WiFi initialization completed.");
    return ESP_OK;
}

static void wifi_scan(void){
    uint16_t number = MAXIMUM_AP;
    wifi_ap_record_t ap_info[MAXIMUM_AP];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    wifi_scan_config_t scan_config = {
        .ssid = 0,
        .bssid = 0,
        .channel = 0,
        .show_hidden = true 
    };
    //ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true)); // in case I want to pass the scan_config
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    printf("Total APs scanned = %u\n\n", ap_count);
    printf("               SSID               |  CHANNEL  |  RSSI  |  MAC  \n");
    for (int i = 0; (i < MAXIMUM_AP) && (i < ap_count); i++) {
        printf(" %32s |   %5d   |  %4d  | ", ap_info[i].ssid, ap_info[i].primary, ap_info[i].rssi);
        for (int j = 0; j < 6; j++) {
            printf("%02x", ap_info[i].bssid[j]);
            if (j < 5) {
                printf(":");
            }
        }
        printf("\n");
    }

}

void app_main(void)
{
    ESP_ERROR_CHECK(init_wifi());

    while(1){
        vTaskDelay(3000/ portTICK_PERIOD_MS);
        wifi_scan();
    }
}
