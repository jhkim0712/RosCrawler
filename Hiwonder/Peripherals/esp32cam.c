#include <stdio.h>
#include <stdlib.h>
#include "esp32cam.h"
#include "i2c.h"

#define device_addr 0x52  //（设备地址）	ESP32-Cam的通讯地址
#define light_data  0x11  //（寄存器地址）	设置补光灯亮度【uint8_t brightness】(0~255)

//当ESP32-Cam为人脸识别功能时：
//地址	作用
#define face_data   0x01  //（寄存器地址）	读取人脸数据【int16_t  x,y,w,h】（无人脸时，数据全为0）


//当ESP32-Cam为颜色识别功能时：
//地址	作用
#define color1_data 0x00	//（寄存器地址）读取颜色0数据，读取到的数据格式为【int16_t  x,y,w,h】（无识别到时，数据全为0）

#define color2_data 0x01	//（寄存器地址）读取颜色1数据，读取到的数据格式为【int16_t  x,y,w,h】（无识别到时，数据全为0）

struct esp32camobject{
  int16_t  face_data_raw[4];
	int16_t  color0_data_raw[4];
	int16_t  color1_data_raw[4];
	uint8_t  brightness;
};
	
struct esp32camobject cam1;

void esp32cam_init(){
  MX_I2C1_Init();
	cam1.brightness=0;
	memset((void *)cam1.color0_data_raw, 0 ,4*sizeof(int16_t));
	memset((void *)cam1.color1_data_raw, 0 ,4*sizeof(int16_t));
	memset((void *)cam1.face_data_raw, 0 ,4*sizeof(int16_t));
	//让正常初始化的设备闪灯两次，以示初始化完成
	for(int i=2;i>0;i--){
		cam1.brightness=100;
    HAL_I2C_Master_Transmit(&hi2c1, device_addr, &cam1.brightness, 1, 0xFFFF);
		cam1.brightness=0;
    HAL_I2C_Master_Transmit(&hi2c1, device_addr, &cam1.brightness, 1, 0xFFFF);
	}
}
