#include <stdio.h>
#include <stdlib.h>
#include "esp32cam.h"
#include "i2c.h"

#define device_addr 0x52  //���豸��ַ��	ESP32-Cam��ͨѶ��ַ
#define light_data  0x11  //���Ĵ�����ַ��	���ò�������ȡ�uint8_t brightness��(0~255)

//��ESP32-CamΪ����ʶ����ʱ��
//��ַ	����
#define face_data   0x01  //���Ĵ�����ַ��	��ȡ�������ݡ�int16_t  x,y,w,h����������ʱ������ȫΪ0��


//��ESP32-CamΪ��ɫʶ����ʱ��
//��ַ	����
#define color1_data 0x00	//���Ĵ�����ַ����ȡ��ɫ0���ݣ���ȡ�������ݸ�ʽΪ��int16_t  x,y,w,h������ʶ��ʱ������ȫΪ0��

#define color2_data 0x01	//���Ĵ�����ַ����ȡ��ɫ1���ݣ���ȡ�������ݸ�ʽΪ��int16_t  x,y,w,h������ʶ��ʱ������ȫΪ0��

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
	//��������ʼ�����豸�������Σ���ʾ��ʼ�����
	for(int i=2;i>0;i--){
		cam1.brightness=100;
    HAL_I2C_Master_Transmit(&hi2c1, device_addr, &cam1.brightness, 1, 0xFFFF);
		cam1.brightness=0;
    HAL_I2C_Master_Transmit(&hi2c1, device_addr, &cam1.brightness, 1, 0xFFFF);
	}
}
