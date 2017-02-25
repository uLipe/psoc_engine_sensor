/**
 * @brief event queue interface file
 */

#ifndef __EVENT_QUEUE_H
#define __EVENT_QUEUE_H

/** system event list */
typedef enum {
    KNO_EVENT=0,
    KDMA_EVENT,
    KRPM_READY_EVENT,
    KSYS_INIT_EVENT,
    KENGINE_CALCULATE,
    KENGINE_COMM_BUSY,
    KENGINE_PACKET_SENT,
}system_event_t;


/** define the system event queue length */
#define EVENT_QUEUE_LEN 64

/**
 * @brief inits the event queue 
 */
int event_queue_init(void);

/**
 * @brief  look at head of queue but not remove the event
 */
system_event_t event_queue_peek(void);

/**
 * @brief removes the event on the head of queue
 */
system_event_t event_queue_get(void);

/**
 * @brief put a system event on tail of queue
 */
int event_queue_put(system_event_t ev);    
    
#endif