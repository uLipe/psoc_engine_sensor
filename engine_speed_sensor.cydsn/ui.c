/**
 * @brief user interface of engine sensor
 */
#include <project.h>
#include <stdint.h>
#include <stdlib.h>
#include "engine_afe.h"
#include "event_queue.h"
#include "ui.h"

static uint8_t ui_busy = 0;
static measure_pack_t pack = {0,0};
char result_buffer[64] = {0};


/**
 * @brief uart TX packet sent callback
 */

void ui_init(void)
{
    engine_sensor_uart_Start();
    engine_sensor_uart_Enable();    
}

void ui_main(int event)
{
    system_event_t ev = (system_event_t) event;
    
    switch(ev) {
        case KRPM_READY_EVENT:
            pack.rpm_sample = (uint16_t) engine_afe_get_rpm();
            
            sprintf(&result_buffer[0], "[MEASURED]: %d(RPM) - [at TIMESTAMP]: %d(ms)\n\r", pack.rpm_sample, pack.timestamp);   
             
            if(ui_busy == 0) {
                /* dispatch new packet to uart if uart is free
                 * if not drop measure since RPM is periodic  
                 */
                pack.timestamp++;
                engine_sensor_uart_SpiUartPutArray((uint8_t *)&result_buffer, strlen(result_buffer));
                ui_busy = 1;
            }
        
            break;
        
        case KENGINE_PACKET_SENT:
            ui_busy = 0;
            break;
    
    }
    
    
    if(ui_busy != 0){
        if(engine_sensor_uart_SpiUartGetTxBufferSize() == 0) {
            /* packet sent, frees the uart */
            event_queue_put(KENGINE_PACKET_SENT);
        }
    }
}