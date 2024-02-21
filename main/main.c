#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lora.h"
#include "timer_u32.h"
#include "math.h"
#include <inttypes.h>

/**
void task_tx(void *p)
{
   for(;;) {
      vTaskDelay(pdMS_TO_TICKS(5000));
      lora_send_packet((uint8_t*)"Hello", 5);
      printf("packet sent...\n");
   }
}
*/

uint8_t buf[32];
void task_tx(void *p){
        //int x;
    lora_send_packet((uint8_t*) "HELLO" , 5);
    for(;;) {
      lora_receive();    // put into receive mode
      while(lora_received()) {
        //x = lora_receive_packet(buf, sizeof(buf));
        //buf[x] = 0;
        //printf("Received: %s\n", buf);
        //vTaskDelay(pdMS_TO_TICKS(5000));
        
        lora_send_packet((uint8_t*) buf , sizeof(buf));
        //printf("Sent------------\n");
          

        lora_receive();
      }
      vTaskDelay(1);
   }
}

/**
//uint8_t buf[32];
uint64_t t0, t1;
uint64_t t01, t02, t03, t04, t05, t06;
uint32_t t00, t11;

void task_tx(void *p){
    lora_send_packet((uint8_t*)"S1", 2);
    //int x;
   for(;;) {
    
      //t01 = timer_u32();
      //printf("Time 01  %lld tick \n",t01);
       
    lora_receive();    // put into receive mode
      //2523
      //t02 = timer_u32();
      //printf("Time 02  %lld tick \n",t02);

      while(lora_received()) {
        //lora_received();
        //2208
        //TickType_t nowTick0 = xTaskGetTickCount();
        //printf("Time 1 " "%"PRIu32 " tick \n",nowTick0);
        //t0 = timer_u32() -t1 - 10084376 - 2208 -2523 - 2523 - 22 ;
        t0 = timer_u32() - t1;
        t01 = timer_u32();
        printf("Time 0  %.3f ns - -    %lld tick   \n",timer_delta_ns(t01),t0);
        //t0 = timer_u32() - t1;
        //printf("Time Diff  %lld tick \n",t0);
        //printf("Time 0  %.3f ns\n",timer_delta_ns(t0));
        //x = lora_receive_packet(buf, sizeof(buf));
        //buf[x] = 0;
        //printf("Received: %s\n", buf);
          
        vTaskDelay(pdMS_TO_TICKS(5000));
         //79995590 
         //TickType_t nowTick = xTaskGetTickCount();
         //printf("Time 1 " "%"PRIu32 " tick \n",nowTick);
          
        lora_send_packet((uint8_t*)"S1", 2);  //10084376
          
         
         t1 = timer_u32();
         //printf("Time 1  %lld tick \n",t1);
         printf("Time 1  %.3f ns\n",timer_delta_ns(t1));
         
         lora_receive();
      }
      //t0 = timer_u32();
      //t03 = timer_u32();
      //printf("Time 03  %lld tick \n",t03);
      vTaskDelay(1); //36620- 70000
      //t11 = timer_u32() - t00;
      //printf("Time diff111  %lld tick \n",t0);
      //t04 = timer_u32();
      //printf("Time 04  %lld tick \n",t04);
      //printf("Time 03-04  %lld tick \n",t04-t03);

      ///////////timer_u32(); // 11 tick
    
  
   

   }
}
**/
/**
void task_tx(void *p){
    lora_send_packet((uint8_t*)"S1", 2);
    for(;;) {
        lora_receive();    // put into receive mode
        while(lora_received()) {
            int rssi = lora_packet_rssi();
            printf("RSSI Received: %d\n", rssi);
            float distance1 = pow(10,((rssi - (-71))/(10.0*2.0)));
            printf("Distance  %.3lf m\n",distance1);
            float distance2 = pow(10,(2));
            printf("Distance  %.3lf m\n",distance2);
            vTaskDelay(pdMS_TO_TICKS(3000));
            lora_receive();
        }
         vTaskDelay(1);
    }
}
*/
//float x1, y1, x2, y2, distance;
//distance = sqrt( (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) );
//printf("Distance between (%0.2f, %0.2f) and (%0.2f, %0.2f) is %
// 1,2  5,4  3,8

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
   lora_set_tx_power(16);
   lora_set_bandwidth(125000);
   lora_set_spreading_factor(7);
   lora_set_coding_rate(5);
   lora_set_frequency(9232e5);
   //lora_set_sync_word(0xF7);
   //lora_enable_crc();
   
   xTaskCreate(&task_tx, "task_tx", 2048, NULL, 2, NULL);
}

