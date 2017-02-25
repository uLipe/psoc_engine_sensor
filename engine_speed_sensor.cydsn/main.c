/**
 * @brief engine speed sensor main application file 
 */
#include <stdbool.h>
#include "event_queue.h"
#include "engine_afe.h"
#include "project.h"
#include "ui.h"

/**
 * @brief main loop application 
 */
int main(void)
{   
    bool should_run  = true;
    system_event_t global_ev;
    
    CyGlobalIntDisable;
    
    /* init application event manager */
    event_queue_init();
    
    /* inits the engine sensor analog front end engine */
    engine_afe_init();
    
    /* inits the comm interface, a uart in 115200 bps 8N1 */
    ui_init();
    
    /* enable global interrupts */
    CyGlobalIntEnable;
    
    for(;should_run != false;) {
        /* each loop, gets the system generated events 
         * eg.: interrupts signals, process completeds
         * and broadcast to all sub applications, each
         * app do programmed actions based on events arrived
         */
        global_ev = event_queue_get();
        
        engine_afe_main(global_ev);
        ui_main(global_ev);
    }
    return 0;
}

