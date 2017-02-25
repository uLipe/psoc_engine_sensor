/**
 * @brief engine analog front end inteface file
 */
#include <project.h>
#include "event_queue.h"
#include "engine_afe.h"
#include "fix_fft.h"
#include "fix_sqrt.h"

/** define the samples buffer size [words]*/
#define ENGINE_SAMPLE_BUFFER_SIZE   256
/** define the buffer lines avaialble */
#define ENGINE_SAMPLE_BUFFER_LINES  2

/** define the fft length */
#define ENGINE_FFT_LEN              9     
#define ENGINE_FFT_SIZ              256   


/** defines the afe sample rate */
#define ENGINE_SAMPLE_RATE          16000
#define SCALE_FREQ                  ((ENGINE_SAMPLE_RATE/2)/(ENGINE_FFT_SIZ/2))
#define ENGINE_IDX_TO_FREQ(x)       (x * SCALE_FREQ)
#define ENGINE_FREQ_TO_IDX(x)       (x / SCALE_FREQ)
#define ENGINE_THRESHOLD            20

#define ENGINE_BASE_FREQ            4000 /* KHz*/
#define ENGINE_SCALE_FACTOR         10

/**
 * static variables 
 */
static int16_t engine_sample_buffer[ENGINE_SAMPLE_BUFFER_LINES][ENGINE_SAMPLE_BUFFER_SIZE]={0};
static int16_t engine_sample_fft_buffer[2 * ENGINE_SAMPLE_BUFFER_SIZE] = {0};
static int engine_buffer_index = 0;
static int engine_current_speed = 0;
static uint32_t engine_speed_frequency = 0;
static int engine_buffer_available = 0;
/**
 * private functions 
 */


/**
 * @brief signals the DMA engine completed its task
 */
static void engine_dma_isr(void)
{
    /* halts the sampler */
    engine_sensor_adc_Stop();
    event_queue_put(KDMA_EVENT);
}

/**
 * @brief gets the idx which has the highest value in buffer 
 */
static uint32_t engine_gets_highest_value_idx(int16_t *buf, uint32_t len) 
{
    uint32_t ret = 0;
    uint32_t i = 0;
    int16_t val = buf[0];
    
    for(i = 0 ; i < len; i++){
        if(val < buf[i]) {
            val = buf[i];
            ret = i;
        }
    }
    return(ret);
}


/**
 * public functions 
 */
int engine_afe_init(void)
{
    int ret = 0;
        
    /* turn on the voltage reference */
    engine_sensor_ref_Start();
    
    /* turn on the voltage reference buffer */
    engine_vref_buf_Start();
    
    /* turn on the system amplifier */
    engine_sensor_pga_Start();
    
    /* set the dma interrupt function */
    engine_sensor_transfer_SetInterruptCallback((cydma_callback_t)&engine_dma_isr);
    
    /* set the dma initial buffer */
    /* we call this trick in Brazil: "Gambiarra" 
     * the cypress code generator seems to have a bug, generating like: xx_xx_SAR_CHAN_RESULTy where
     * y is the channel number, but this causes undeclared value compilation error, so the workaround is to take
     * the base address and add a offset, since I need of channel 0 this is not needed
     */
    engine_sensor_transfer_Start((void *)engine_sensor_adc_cy_psoc4_sar_1__SAR_CHAN_RESULT00, &engine_sample_buffer[engine_buffer_index]);
    
    /* prepare instance of fft */
    //arm_cfft_radix2_init_q15(&fft_instance,ENGINE_SAMPLE_BUFFER_SIZE,0,1);
    
    CyIntEnable(CYDMA_INTR_NUMBER);
    
    /* start the adc with continous sampling enabled */
    engine_sensor_adc_Start();
    engine_sensor_adc_StartConvert();
    
    return(ret);
}

int engine_afe_get_rpm(void)
{
    return(engine_current_speed);
}


void engine_afe_main(int event)
{
    system_event_t ev = (system_event_t)event;
    switch(ev) {
        case KDMA_EVENT:
            /* dma signaled, swap buffers and restart the adc */
            engine_buffer_index = (engine_buffer_index + 1) & (ENGINE_SAMPLE_BUFFER_LINES - 1);
            engine_buffer_available = (engine_buffer_index ^ (ENGINE_SAMPLE_BUFFER_LINES - 1)) & (ENGINE_SAMPLE_BUFFER_LINES - 1);
            memcpy(&engine_sample_fft_buffer,&engine_sample_buffer[engine_buffer_available][0],sizeof(engine_sample_fft_buffer)/2);  
            engine_sensor_transfer_Start((void *)engine_sensor_adc_cy_psoc4_sar_1__SAR_CHAN_RESULT00, &engine_sample_buffer[engine_buffer_index][0]);
            engine_sensor_adc_Start();
            event_queue_put(KENGINE_CALCULATE);
        break;
        
        case KENGINE_CALCULATE:
        {
            int i;
            /* calculate the frequency bins using the obtained buffer */
            (void)fix_fftr(&engine_sample_fft_buffer[0], ENGINE_FFT_LEN,0);
            
            /* compute mag_val since this is a complex fft */
            for( i = 0 ; i < ( 1 << (ENGINE_FFT_LEN - 1)); i++) {
                engine_sample_fft_buffer[i] =                                                                 \
                    (int16_t)fix_sqrt((uint32_t)(engine_sample_fft_buffer[i] * engine_sample_fft_buffer[i]   +\
                                                 engine_sample_fft_buffer[i + ( 1 << (ENGINE_FFT_LEN - 1)) ] *\
                                                 engine_sample_fft_buffer[i + ( 1 << (ENGINE_FFT_LEN - 1)) ]  \
                                       ));
            }   
            
            engine_speed_frequency = ENGINE_IDX_TO_FREQ(engine_gets_highest_value_idx(&engine_sample_fft_buffer[1],
                                                       (ENGINE_FFT_SIZ/2) - 1));
                       
            if(engine_sample_fft_buffer[ENGINE_FREQ_TO_IDX(engine_speed_frequency)] < ENGINE_THRESHOLD) {
                engine_current_speed = 0;            
            } else {
                engine_current_speed = (engine_speed_frequency - ENGINE_BASE_FREQ) * ENGINE_SCALE_FACTOR;
            }
            
            if(engine_current_speed < 0) engine_current_speed = 0;
            
            /* notify fresh rpm value to system */
            event_queue_put(KRPM_READY_EVENT);
        }
        break;
        
        
        case KRPM_READY_EVENT:
        /* not used for while */
        break;
    }
    
}
