/**
 * @brief engine analog front end inteface file
 */
#ifndef __ENGINE_AFE_H
#define __ENGINE_AFE_H
    
/**
 * @brief init the engine sensor analog front end
 */
int engine_afe_init(void);

/**
 * @brief gets the current calculated RPM measure 
 */
int engine_afe_get_rpm(void);

/**
 * @brief engine afe main process
 */
void engine_afe_main(int event);

       
#endif

