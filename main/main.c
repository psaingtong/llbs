 #include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lora.h"

#include "timer_u32.h"

void task_tx(void *p){
    for(;;) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("packet sent...\n");

    }
    vTaskDelay(1);
}

void app_main()
{
   #if defined(CONFIG_IDF_TARGET_ESP32)
    printf("ESP32 processor, ");
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
    printf("ESP32-S2 processor, ");
#else
    printf("ESP32-??? processor, ");
#endif

#if defined(CONFIG_ESP_TIMER_IMPL_FRC2)
    printf("FRC2\n");
#elif defined(CONFIG_ESP_TIMER_IMPL_TG0_LAC)
    printf("TG0_LAC\n");
#else
    printf("SYSTIMER\n");
#endif
   lora_init();
   lora_set_frequency(923e6);
   lora_enable_crc();
   xTaskCreate(&task_tx, "task_tx", 2048, NULL, 5, NULL);
}
