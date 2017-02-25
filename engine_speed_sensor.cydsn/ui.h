/**
 * @brief user interface of engine sensor
 */
    
#ifndef __UI_H
#define __UI_H

/** uart rpm measure packet format  */
typedef struct {
    uint16_t rpm_sample;
    uint32_t timestamp;
}measure_pack_t;
    
/**
 * @brief initialize ui interface 
 */
void ui_init(void);

/**
 * @brief ui mainloop
 */
void ui_main(int event);
    
#endif