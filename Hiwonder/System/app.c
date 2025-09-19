/**
 * @file app.c
 * @author Lu Yongping (Lucas@hiwonder.com)
 * @brief 主应用逻辑(main appilication logic)
 * @version 0.1
 * @date 2023-05-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "cmsis_os2.h"
#include "led.h"
#include "lwmem_porting.h"
#include "global.h"
#include "global.h"
#include "adc.h"
#include "u8g2_porting.h"
#include "packet_reports.h"
#include "packet_handle.h"
#include "serial_servo.h"
#include "rgb_spi.h"
#include "esp32cam.h"

/* 蜂鸣器	的频率(the frequency of buzzer) */
#define BUZZER_FREQ				 1300

void buzzers_init(void);
void buttons_init(void);
void leds_init(void);
void motors_init(void);
void serial_servo_init(void);
void pwm_servos_init(void);
void chassis_init(void);


void button_event_callback(ButtonObjectTypeDef *button,  ButtonEventIDEnum event)
{
    if(button == buttons[0]) { /* 按键1的事件(the event of button1)  */
        if(event == BUTTON_EVENT_CLICK) {	//若为单击(if it is a single click)
            buzzer_didi(buzzers[0], BUZZER_FREQ, 100, 100, 3);	//蜂鸣器响2声(the buzzer sounds twice)
			static uint8_t led_ctl = 0;
			switch(led_ctl)
			{
				case 0:
					led_off(leds[0]);	//LED灭(LED off)
					led_ctl++;
					break;
				case 1:
					led_on(leds[0]);	//LED亮(LED on)
					led_ctl++;
					break;
				case 2:
					led_flash(leds[0],200,200,0);	//LED闪烁（灭200ms，亮200ms）(LED flashing (on for 200ms, and off for 200ms))
					led_ctl = 0;
					break;
				default:
					led_ctl = 0;
					break;
			}
        }
    }
	if(button == buttons[1]) { /* 按键2的事件(the event of button2)  */
         if(event == BUTTON_EVENT_DOUBLE_CLICK) {	//若为双击(if it is double click)
            buzzer_didi(buzzers[0], BUZZER_FREQ, 100, 100, 3);	//蜂鸣器响3声(the buzzer sounds three times)
        }
    }
}

void app_task_entry(void *argument)
{
    extern osTimerId_t led_timerHandle;

    leds_init();
    
    osTimerStart(led_timerHandle, LED_TASK_PERIOD);

    
    osDelay(1000); //延时1秒再亮(the LED lights up after a 1 second delay)
	  led_on(leds[0]);	 //led亮(LED lights up)
	  osDelay(3000);     //延时3秒再灭(the LED turns off after a 3 second delay)
	  led_off(leds[0]);	//LED灭(LED turns off)
	  osDelay(3000);   
	  led_flash(leds[0],200,200,0);	//LED闪烁（灭200ms，亮200ms）(LED flashing (on for 200ms, and off for 200ms))
	  osDelay(3000);  
	  led_off(leds[0]);	//LED灭(LED turns off)
    
    for(;;) {
      osDelay(1000);
    }
}


