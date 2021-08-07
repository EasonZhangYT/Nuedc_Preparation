
//#include "spi.h"
//#include "lcd.h"
//#include "delay.h"
//#include "AD1292.h"
//#include "FIFOQUEUE.h"
//#include "arm_math.h"
//#include "timer.h"
//#include "Rate.h"
//#include "arm_fir_example_f32.h"
#include "bsp.h"
#include "AD1292.h"

extern SPI_HandleTypeDef hspi;
float32_t Value_measure;
uint8_t ads1292r_data_buff[9] = {0};
uint32_t sample_pro = 0;
uint32_t sample_now = 0;
//struct FifoQueue Queue;
//float32_t Process_Data[1512];
float32_t value_pro = 0;
float32_t value_now = 0;
float32_t value_next = 0;
uint32_t result;
uint8_t con = 0;
uint16_t tim1;
uint16_t tim1_record;
uint16_t tim2;
uint16_t i=0;
float32_t filter_result[1000]={0};
float32_t filter_Highpass[1000]={0};
float32_t filter_Lowpass[1000]={0};
uint8_t flag_filter_begin=0;
uint32_t counter_zhongduan=0;
uint32_t Medium_Data[1000]={0};

uint8_t Flag_HALF_Full=0;
uint8_t Flag_Store;
float32_t ban_data[1000] ={0};
float32_t Half_data[500] ={0};
float32_t Full_data[500] ={0};

float32_t Process_Data[2048];
float32_t Store_Data_1[512];
float32_t Store_Data_2[512];
float32_t Get_Data[512];
//extern WM_HWIN Display_xinRate;
void AD1292_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOA_CLK_ENABLE();	
	__HAL_RCC_GPIOB_CLK_ENABLE();	
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	
	GPIO_Initure.Mode			= GPIO_MODE_OUTPUT_PP,  //�������
	GPIO_Initure.Pull			= GPIO_NOPULL,          //��
	GPIO_Initure.Speed		= GPIO_SPEED_FREQ_LOW,
	
	GPIO_Initure.Pin			= ADS1292R_PWDN_PIN;
	HAL_GPIO_Init(ADS1292R_PWDN_PORT,&GPIO_Initure);
	GPIO_Initure.Pin			= ADS1292R_START_PIN;
	HAL_GPIO_Init(ADS1292R_START_PORT,&GPIO_Initure);
	
	GPIO_Initure.Pin			= ADS1292R_CS_PIN;
	GPIO_Initure.Pull			= GPIO_PULLUP,          //����
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH,    	//����
	HAL_GPIO_Init(ADS1292R_CS_PORT,&GPIO_Initure);
	
	GPIO_Initure.Pull			= GPIO_PULLUP;
	GPIO_Initure.Mode			= GPIO_MODE_IT_FALLING;  //�½�������
	GPIO_Initure.Pin			= ADS1292R_ADC_RDY_PIN;
	HAL_GPIO_Init(ADS1292R_ADC_RDY_PORT,&GPIO_Initure);
	

	
	AD1292_PowerOnInit();
	
}	


uint8_t device_id=0x00;


/**ADS1292R�ϵ縴λ **/
void AD1292_PowerOnInit(void)
{
	
	char cBuf[64];
	
	//printf("poweron");
//	LCD_Clear(LGRAYBLUE);
//	LCD_ShowString(10,40,260,32,32,"power on"); 
	
	ADS1292R_CS_H;
	ADS1292R_START_H;
	ADS1292R_PWDN_H;
	bsp_DelayMS(10);
	
	ADS1292R_PWDN_L;//�������ģʽ
	bsp_DelayMS(10);
	ADS1292R_PWDN_H;//�˳�����ģʽ
	bsp_DelayMS(1000);//�ȴ��ȶ�
	ADS1292R_PWDN_L;//������λ����
	bsp_DelayUS(10);
	ADS1292R_PWDN_H;
	bsp_DelayMS(100);//�ȴ��ȶ������Կ�ʼʹ��ADS1292R
	

	ADS1292R_CMD(ADS1292R_SDATAC);//����ֹͣ������ȡ��������
	bsp_DelayMS(1);
	
	while(device_id!=0x73)       //ʶ��оƬ�ͺţ�1292rΪ0x73
	{
		device_id = ADS1292R_REG(ADS1292R_RREG|ADS1292R_ID,0X00);
		bsp_DelayMS(200);
		sprintf(cBuf,"ID: %LX",device_id);
//		LCD_ShowString(10,90,200,16,16,cBuf);	
	}

//	LCD_ShowString(10,110,240,16,16,"ADS1292R Detected");	
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_CONFIG2,    0XE0);	//????????
	bsp_DelayMS(10);//??????????
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_CONFIG1,    0X02);	//???????500SPS
	//ADS1292R_REG(ADS1292R_WREG|ADS1292R_CONFIG1,    0X00);	//???????125SPS
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_LOFF,       0XF0);
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_CH1SET,     0X00);
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_CH2SET,     0x60);
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_RLD_SENS,   0x30);
	//	ADS1292R_REG(ADS1292R_WREG|ADS1292R_RLD_SENS,   0x3C);	//????2??????
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_LOFF_SENS,  0x3F);
	//  ADS1292R_REG(ADS1292R_WREG|LOFF_STAT,  0X00);
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_RESP1,      0xDE);
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_RESP2,      0x07);
	ADS1292R_REG(ADS1292R_WREG|ADS1292R_GPIO,       0x0C);
}

void ADS1292R_Work(void)
{
	//OLED_PrintfString(0,2,"ADS1292R Working");
//	LCD_ShowString(10,140,200,16,16,"ADS1292R Working");	
	ADS1292R_CMD(ADS1292R_RDATAC);//����������ȡ���ݵ�����
	ADS1292R_START_H;
//	QueueInit(&Queue);
	
//	HAL_NVIC_SetPriority(EXTI15_10_IRQn,1,1);   
//	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);   //ʹ���ж�  	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn,1,1);   
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);   //ʹ���ж�  		
}
void ADS1292R_Halt(void)
{
	//OLED_PrintfString(0,2,"ADS1292R Halt");
	ADS1292R_START_L;
	ADS1292R_CMD(ADS1292R_SDATAC);
//	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

//void EXTI15_10_IRQHandler(void)
//{
//    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);  //�����жϴ����ú���
//}
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(ADS1292R_ADC_RDY_PIN);  //�����жϴ����ú���
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t dataBuf;
	ADS1292R_CS_L;
	HAL_SPI_TransmitReceive(&hspi, temp1292r, ads1292r_data_buff, 9, 10);
	ADS1292R_CS_H;
	dataBuf = data_han2();//��������ƴ�ӺͲ�������
//	Queuein(&Queue,dataBuf);//������
//	printf("databuf:%d\r\n",dataBuf);
//	printf("%d\n",dataBuf);
	
	if(counter_zhongduan<512)
	{
//		Data_Store();//1000������
		Store_Data_1[counter_zhongduan]=dataBuf;
		counter_zhongduan++;
		
		if(counter_zhongduan == 512){
				flag_filter_begin=2;
				Flag_HALF_Full=1;//��
		}
	}
	else if(counter_zhongduan>511)
	{  
//		Data_Store();//1000������
		Store_Data_2[counter_zhongduan-512]=dataBuf;
		counter_zhongduan++;
		
		if(counter_zhongduan==1024)
		{
			flag_filter_begin=2;
			counter_zhongduan=0;
			Flag_HALF_Full=2;//ȫ��	
		}
 }
//		for(int k=0;k<1000;k++)
//		{
//		
//		printf("%f\r\n",Process_Data[k]);
//		
//		}
	

}
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	uint32_t dataBuf;
//  ADS1292R_CS_L;
//	HAL_SPI_TransmitReceive(&SPI5_Handler, temp1292r, ads1292r_data_buff, 9, 10);
//	ADS1292R_CS_H;
//	dataBuf = data_han2();//��������ƴ�ӺͲ�������
//	Queuein(&Queue,dataBuf);//������
////	printf("%d\r\n",dataBuf);
//   counter_zhongduan++;
//	if(counter_zhongduan==500)
//	{
//		counter_zhongduan=0;
//		flag_filter_begin=2;
//		Flag_Store = Flag_Store + 1;
//		if(Flag_Store == 2) Flag_Store = 0;
//	}

//}

//	 Data_Filter_HighPass();
//	 printf("over\r\n");
//	Data_Filter_HD();//�˲�
//	Data_Filter_Medium();
//	Heart_Rate_Cal();//��������


uint8_t ADS1292R_REG(uint8_t cmd, uint8_t data)	//ֻ��һ������
{
	uint8_t rx_data =0x00;
	
	ADS1292R_CS_L;
	bsp_DelayUS(1);
	ADS1292R_SPI_RW(cmd);	//��дָ��
	ADS1292R_SPI_RW(0x00);	//��Ҫд�������ݣ�n+1����
	if((cmd&0x20)==0x20)	//�ж��Ƿ�Ϊ���Ĵ���ָ��
		rx_data = ADS1292R_SPI_RW(0X00);	//���ؼĴ���ֵ
	else
		rx_data = ADS1292R_SPI_RW(data);	//д����ֵ
	bsp_DelayUS(1);
	ADS1292R_CS_H;
	return rx_data;
}

uint8_t ADS1292R_SPI_RW(uint8_t data)
{
	uint8_t rx_data1 =0x00;
	char data_buff[64];
	//printf("%d",rx_data1);
	
	HAL_SPI_TransmitReceive(&hspi, &data, &rx_data1, 1, 10);
	//sprintf(data_buff,"%LX",rx_data1);
	//LCD_ShowString(0,0,200,16,16,data_buff);
	//printf("%d",rx_data1);
	bsp_DelayMS(10);
	return rx_data1;
}

//��ADS1292Rд��ָ��
void ADS1292R_CMD(uint8_t cmd)
{
	ADS1292R_CS_L;
	bsp_DelayUS(1);
	ADS1292R_SPI_RW(cmd);
	bsp_DelayUS(1);
	ADS1292R_CS_H;
}

uint8_t temp1292r[9] = {0};


void ADS1292R_ReadData(void)
{
	ADS1292R_CS_L;
	HAL_SPI_TransmitReceive(&hspi, temp1292r, ads1292r_data_buff, 9, 10);
	ADS1292R_CS_H;

	//printf("%x%x%x      ",ads1292r_data_buff[3],ads1292r_data_buff[4],ads1292r_data_buff[5]);
}

uint32_t data_han1(void)
{
	uint32_t temp0;
	uint32_t temp1 = 0x00;
	uint32_t temp2 = ads1292r_data_buff[3];
	uint32_t temp3 = ads1292r_data_buff[4];
	uint32_t temp4 = ads1292r_data_buff[5];
	temp0 = (uint32_t) (temp1<<24) | (uint32_t) (temp2<<16) | (uint32_t) (temp3<<8) | (uint32_t) (temp4<<0);
	if(temp0 > 0x7FFFFF)
	{
		temp0 = uhexTodec(temp0);
	}
	return temp0;
}

uint32_t data_han2(void)
{
	uint32_t temp0;
	uint32_t temp1 = 0x00;
	uint32_t temp2 = ads1292r_data_buff[6];
	uint32_t temp3 = ads1292r_data_buff[7];
	uint32_t temp4 = ads1292r_data_buff[8];
	temp0 = (uint32_t) (temp1<<24) | (uint32_t) (temp2<<16) | (uint32_t) (temp3<<8) | (uint32_t) (temp4<<0);
	if(temp0 > 0x7FFFFF)
	{
		temp0 = uhexTodec(temp0);
	}
	return temp0;
}
float32_t Data_Filter_DT(float32_t DT_data)
{
	uint32_t data;
	float a=0.44;
	if(sample_pro == 0)
	{
		sample_now = data_han2();
	}
	else
	{
		sample_pro = sample_now;
		data = data_han2();
		sample_now = a * data + (1 - a) * sample_pro;
	}
	return sample_now;
	
}

void Data_Filter_HD(void)
{
	int N = 10;
	uint32_t sum_data=0;
	int counter;
	uint8_t full;
//	Data_Store();//��ȡ�����е�����
//	full = isFifoFull(&Queue);//�ж϶����Ƿ�Ϊ��
	if(full == 1)
	{
	
	for (counter = 0; counter <N; counter++)
	{
			sum_data = sum_data + Process_Data[counter];
	}
	result = sum_data/N;//�˲�
	sum_data=0;
	filter_result[i]=result;//��Ż���ƽ���˲����
//	result=Data_Filter_DT(result);
//	Fir_H(filter_result,filter_Highpass);		//��Ŵ�ͨ�˲����
	for(int j=0;j<512;j++)
	{
	
//	printf("%f\r\n",filter_Highpass[j]);
	
//	}
//	printf("%d\r\n",result);
	i++;
	if(i==512)
	{  
		i=0;
  
	}
	}

}
}
void Data_Filter_Medium(void)
{
	int N = 331;
	int i,j;
	uint32_t temp;
	int counter;
	uint8_t full;
	Data_Store();
//	full = isFifoFull(&Queue);
//	printf("full is:%d\r\n",full);
	if(full == 1)
	{
	for (counter = 0; counter <N; counter++)
	{
			Medium_Data[counter] = Process_Data[counter];
	}
	for (i = 0; i<331; i++)
	{
			for(j = 1; j<331-i; j++)
			{
				if(Medium_Data[i]<Medium_Data[i+j])
				{
					temp = Medium_Data[i+j];
					Medium_Data[i+j] = Medium_Data[i];
					Medium_Data[i] = temp;
				}
			}
	}
	result = Medium_Data[165];
//	printf("%d\r\n",result);
}

}
void Data_Store(void)
{
	int i;
//	get_processed_array(&Queue, Get_Data);
//	if(Flag_Store == 0)
//	{
//		for(i = 0; i<512; i++)
//		{
//			Store_Data_1[i] = Get_Data[i];
//		}
//	}
//	else if(Flag_Store == 1)
//	{
//		for(i=0; i<512; i++)
//		{
//			Store_Data_2[i + 512] = Get_Data[i];
//		}
//	}
}

void Heart_Rate_Cal(void)
{
	uint8_t full;
  float32_t  heart_rate=0.0;
	uint16_t x = 0;
	char rateBuf[64];
	for(i=0;i<1024;i++)
	{
		if(value_pro != value_now && value_now != value_next)
		{
		value_pro = value_now;
		}
		if(value_next != value_now)
		{
		value_now = value_next;
		}
		value_next = Process_Data[i];
	

		if((value_pro > value_now  )&& (value_next > value_now) &&( value_now  < Value_measure))
			
	{
			printf("Value_measure %f\r\n",Value_measure);
		printf("value_now: %f\r\n",value_now);
		con = con + 1;
//     printf("con:%d\r\n",con);
			if(con == 1)
			{
				tim1 = i;
			printf("tim1:%d",tim1);
			}
			if(con == 3)
			{
				tim2 = i;
				printf("tim2:%d",tim2);
				con = 0;
				if(tim2 > tim1)
					{
						x = tim2 - tim1;
						heart_rate = 60000 / x ;
						printf("rate is %f\r\n",heart_rate);
						sprintf(rateBuf,"RATE: %f",heart_rate);
//						EDIT_SetText(Display_xinRate,rateBuf);
						bsp_DelayMS(10);
//						LCD_ShowString(10,80,400,24,16,rateBuf);
						//con = 0;
						//return heart_rate;
					}
				if(tim2<tim1)
					{
						x = 1024 - tim1+ tim2;
						heart_rate = 60000 / x;
						printf("rate is %f\r\n",heart_rate);
						sprintf(rateBuf,"RATE: %f",heart_rate);
					
//						EDIT_SetText(Display_xinRate,rateBuf);
						bsp_DelayMS(10);
//						LCD_ShowString(10,80,400,24,16,rateBuf);
						//con = 0;
//						return heart_rate;
					}
				}
//		
//		
	//}
	}
	
}
}


int uhexTodec(uint32_t dataIn) 
{
		return (int)((0x00ffffff - dataIn) + 1);	//����ת����
}

void Data_Filter_HighPass()
{

  uint8_t full;

//	full = isFifoFull(&Queue);//�ж϶����Ƿ�Ϊ��
	
//	printf("full is %d\r\n",full);
//	if(full == 1)
//	{
//		Data_Store();//��ȡ�����е�����
		
//		Fir_H(Process_Data,filter_Highpass);
//		Fir_L(Process_Data,filter_Lowpass);
//		
//		for(i=0;i<512;i++)
//		{
//		
//		
//			printf("%f\r\n",	filter_Lowpass[i]);
//		
//		}
	
//		for(i=0;i<512;i++)
//		{
//		
//		printf("%f\r\n",filter_Bandpass[i]);
//		}
//		
//		printf("%d\r\n",Process_Data[0]);
	}



//}
