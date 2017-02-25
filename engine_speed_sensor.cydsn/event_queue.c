/**
 * @brief event queue interface file
 */
#include <project.h>
#include "event_queue.h"

/**
 * private variables 
 */
static int put_index = 0;
static int get_index = 0;
static int noof_elements = 0;
static system_event_t event_queue[EVENT_QUEUE_LEN] = {KNO_EVENT};


/**
 * public functions 
 */
int event_queue_init(void)
{
   /* not needed */
   return 0;
}
system_event_t event_queue_peek(void)
{
    uint8_t isr_key = CyEnterCriticalSection();
    system_event_t ret = (noof_elements == 0)? KNO_EVENT : event_queue[get_index];
    CyExitCriticalSection(isr_key);
    return(ret);
}
system_event_t event_queue_get(void)
{
    system_event_t ret = (noof_elements == 0)? KNO_EVENT : event_queue[get_index];
    if(ret != KNO_EVENT) {
        uint8_t isr_key = CyEnterCriticalSection();
        get_index = (get_index + 1) % EVENT_QUEUE_LEN;
        noof_elements--;
        CyExitCriticalSection(isr_key);
    }
    return(ret);
}
int event_queue_put(system_event_t ev)
{
    int ret = 0;
    
    if(noof_elements < EVENT_QUEUE_LEN) {
        /* send event to the most back position of queue */
        uint8_t isr_key = CyEnterCriticalSection();
        event_queue[put_index] = ev;
        put_index = (put_index + 1) % EVENT_QUEUE_LEN;
        noof_elements++;
        CyExitCriticalSection(isr_key);
    } else {
        /* event queue full */
        ret = -1;
    }
    
    return(ret);    
}