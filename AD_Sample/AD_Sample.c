#include "main.h"


s_counter_info g_counter;

int process_rdy = 0;
vu16 AD_Value_0[SAMPLE_NUM][CHANEL_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
vu16 AD_Value_1[SAMPLE_NUM][CHANEL_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
u16 After_filter[CHANEL_NUM]; //���������ƽ��ֵ֮��Ľ��


vu16 Detect_Buf[DETECTG_BUF_GROUP][DETECTG_BUF_SIZE];
s_buf AD_buff;




s_counter_env counter_env;

void counter_init (void)
{
	int i;
	S8 *p = (S8 *) &g_counter;
	for (i = 0; i < sizeof(s_counter_info); i++)
	{
		*(p++) = 0;
	}	
	
	memset ((void *)Detect_Buf, 0, sizeof(Detect_Buf));
	memset ((void *)After_filter, 0, sizeof(After_filter));
	memset ((void *)AD_Value_0, 0, sizeof(AD_Value_0));
	memset ((void *)AD_Value_1, 0, sizeof(AD_Value_1));
	
	COUNT_COMPLETE = 0;
	
	g_counter.AD_Value_p = AD_Value_0;
	g_counter.buf_index = 0;
	
	for (i = 0; i < CHANEL_NUM; i++){
		g_counter.ch[i].ad_min = 0xFFFF;
		g_counter.ch[i].ad_max = 0;
	}
}


void counter_reset (void)
{
	g_counter.total_count = 0;
	g_counter.pre_count = 0;
	g_counter.total_reject = 0;
	CHANEL_INIT(0);
	CHANEL_INIT(1);
	CHANEL_INIT(2);
	CHANEL_INIT(3);
	CHANEL_INIT(4);
	CHANEL_INIT(5);
	CHANEL_INIT(6);
	CHANEL_INIT(7);
	CHANEL_INIT(8);
	CHANEL_INIT(9);
	CHANEL_INIT(10);
	CHANEL_INIT(11);
	stop_vibrate ();
	COUNT_COMPLETE = 0;//Ӧ��
	PRE_COUNT_FLAG = 1;
	g_counter.counter_step = 0;
}

void AD_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE); 
	//PA0/1/2/3 ��Ϊģ��ͨ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//PB0/1 ��Ϊģ��ͨ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PC0/1/2/3/4/5 ��Ϊģ��ͨ����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;				 //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOG.15
	PEout(3) = 1;
	PEout(4) = 1;
	PEout(5) = 1;
	PEout(6) = 1;
}


void ADC1_Configuration(void)
{
	#define SAMPLE_TIME ADC_SampleTime_28Cycles5// ADC_SampleTime_7Cycles5 
	ADC_InitTypeDef ADC_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE ); //ʹ��ADC1ͨ��ʱ�ӣ������ܽ�ʱ��

	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_DeInit(ADC1); //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode =ENABLE; //ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = CHANEL_NUM; //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���


	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	//ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, CH0, 1, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH1, 2, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH2, 3, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH3, 4, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH4, 5, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH5, 6, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH6, 7, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH7, 8, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH8, 9, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH9, 10, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH10, 11, SAMPLE_TIME );
	ADC_RegularChannelConfig(ADC1, CH11, 12, SAMPLE_TIME );

	// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
	ADC_DMACmd(ADC1, ENABLE);
	
	//����ģ�⿴�Ź�
	ADC_AnalogWatchdogThresholdsConfig(ADC1,0xfff,0);
	ADC_AnalogWatchdogCmd(ADC1,ADC_AnalogWatchdog_AllRegEnable);
	ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);//����ģ�⿴�Ź��ж�

	//ʹ��ADC�ж�
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = ADC1_2_INT_PREEM;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = ADC1_2_INT_SUB;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_Init(&NVIC_InitStructure);  
	
	ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1

	ADC_ResetCalibration(ADC1); //��λָ����ADC1��У׼�Ĵ���

	while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�


	ADC_StartCalibration(ADC1); //��ʼָ��ADC1��У׼״̬

	while(ADC_GetCalibrationStatus(ADC1)); //��ȡָ��ADC1��У׼����,����״̬��ȴ�
}


U16 detect_chanel_index = 0xFFFF;//���ͨ������
U16 chanel_pos_index = 0;	//ͨ������������λ������	
U16 ADC_sync_signal = 0; //ADCת������ͬ���ź�
U16 ADC1_irq_cycle = 0;
U16 ADC1_process_time = 0;
//ADC�жϷ�����
void ADC1_2_IRQHandler(void)
{   
	//U16 temp;
	unsigned long long tick_old;
	tick_old = get_tim5_ticks();
	refresh_adc1_cycle ();
///////////////////////////////////////////////////////////////////////////////
	if (ADC_GetITStatus(ADC1, ADC_IT_AWD) != RESET){//���۹���ʱ������
		detect_chanel_index = CHANEL_NUM - (DMA_GetCurrDataCounter (DMA1_Channel1) % CHANEL_NUM);
		ADC_ClearFlag(ADC1, ADC_FLAG_AWD);
		ADC_ClearITPendingBit(ADC1, ADC_IT_AWD); 
	}else{
		chanel_pos_index++; //����������һ������������
		if (chanel_pos_index < CHANEL_SENSOR_NUM){
		}else{
			chanel_pos_index = 0;
		}
		WRITE_SENSOR_ADDR(chanel_pos_index);//����������һ������������
		if (AD_buff.buffer_en == 1){
			AD_buff.buffer[AD_buff.buffer_index] = g_counter.AD_Value_p[ADC_sync_signal][my_env.watch_ch];
			AD_buff.buffer_index++;
			if (AD_buff.buffer_index >= AD_BUFF_SIZE){
				AD_buff.buffer_index = 0;
				AD_buff.buffer_en = 0;
				OSQPost(debug_msg, (void *) 0x55);//������Ϣ
			}
		}
		ADC_sync_signal++;
		if ( ADC_sync_signal < SAMPLE_NUM){
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		}//else{
		//	chanel_pos_index = 0;
		//}
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);      //���ADCx���жϴ�����λ
	}
////////////////////////////////////////////////////////////////////
	ADC1_process_time = get_tim5_ticks () - tick_old + 2;  	
}


void AD1_DMA_Configuration(void)
{

	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ʹ��DMA����
	DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value_0; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	DMA_InitStructure.DMA_BufferSize = SAMPLE_NUM * CHANEL_NUM; //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// DMA_Mode_Normal; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC,ENABLE); //��������ж�
     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = DMA1_1_INT_PREEM;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = DMA1_1_INT_SUB;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_Init(&NVIC_InitStructure);   

}
int counter_process_state;
void counter_process (void);
//============================================
//��������:DMA1_Channel1_IRQHandler
//��������:DMA�ж� ��AD�ɼ�ֵƽ���˲�
//����:��
//���:��
//============================================

#if (SAMPLE_NUM == 8)
	#define GET_STD_AD_V(AD,BUF,C,S)  {\
		AD[C] = BUF[0][C] + BUF[1][C] + BUF[2][C] + BUF[3][C] + \
				BUF[4][C] + BUF[5][C] + BUF[6][C] + BUF[7][C]; \
		 AD[C] /= S; \
		if (AD[C] > g_counter.ch[C].ad_max){ \
			g_counter.ch[C].ad_max = AD[C]; \
		} \
		if (AD[C] < g_counter.ch[C].ad_min){ \
			g_counter.ch[C].ad_min = AD[C]; \
		} \
		if (process_rdy != process_rdy_old) { \
			g_counter.ch[C].std_v += AD[C] / (PROCESS_RDY - 1); \
		}\
		if ((process_rdy + 1) == PROCESS_RDY){ \
			g_counter.ch[C].std_up_v = g_counter.ch[C].std_v - STD_UP_V_OFFSET; \
			g_counter.ch[C].std_down_v = g_counter.ch[C].std_v - STD_DOWN_V_OFFSET; \
		} \
	}
#endif
#if (SAMPLE_NUM == 16)	
	#define GET_STD_AD_V(AD,BUF,C,S)  {\
		AD[C] = BUF[0][C] + BUF[1][C] + BUF[2][C] + BUF[3][C] + \
				BUF[4][C] + BUF[5][C] + BUF[6][C] + BUF[7][C] + \
				BUF[8][C] + BUF[9][C] + BUF[10][C] + BUF[11][C] + \
				BUF[12][C] + BUF[13][C] + BUF[14][C] + BUF[15][C]; \
		 AD[C] /= S; \
		if (AD[C] > g_counter.ch[C].ad_max){ \
			g_counter.ch[C].ad_max = AD[C]; \
		} \
		if (AD[C] < g_counter.ch[C].ad_min){ \
			g_counter.ch[C].ad_min = AD[C]; \
		} \
		if (process_rdy != process_rdy_old) { \
			g_counter.ch[C].std_v += AD[C] / (PROCESS_RDY - 1); \
		} \
		if ((process_rdy + 1) == PROCESS_RDY){ \
			g_counter.ch[C].std_up_v = g_counter.ch[C].std_v - STD_UP_V_OFFSET; \
			g_counter.ch[C].std_down_v = g_counter.ch[C].std_v - STD_DOWN_V_OFFSET; \
		} \
	}
#endif
	
u16 dma_irq_cycle = 0;

void DMA1_Channel1_IRQHandler(void)
{     
	static int process_rdy_old = 0;
	unsigned long long tick_old;
	tick_old = get_tim5_ticks();
	refresh_dma1_cycle (); //��ͳ��DMA�ж�����
/////////////////////////////////////////////////////////////////////////////////
//	u8 count;
	if(DMA_GetITStatus(DMA1_IT_TC1)){
		DMA_ClearITPendingBit(DMA1_IT_GL1); //���ȫ���жϱ�־
		if (process_rdy < PROCESS_RDY){
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			//process_rdy++;
			ADC_sync_signal = 0;//ͬ���ź�����
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 0, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 1, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 2, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 3, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 4, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 5, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 6, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 7, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 8, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 9, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 10, SAMPLE_NUM);
			GET_STD_AD_V (After_filter, g_counter.AD_Value_p, 11, SAMPLE_NUM);
			if ((process_rdy + 1) == PROCESS_RDY){
				process_rdy++;
			}else{
				process_rdy_old = process_rdy;
			}
		}else{
			counter_process ();
		}
	} 
//////////////////////////////////////////////////////////////////////
	counter_process_time = get_tim5_ticks () - tick_old + 2;  	
}


#if (SAMPLE_NUM == 8)
	#define AD_FILTER(AD,BUF,C,S)  {\
		AD[C] = BUF[0][C] + BUF[1][C] + BUF[2][C] + BUF[3][C] + \
				BUF[4][C] + BUF[5][C] + BUF[6][C] + BUF[7][C]; \
		 AD[C] /= S; \
		if (AD[C] > g_counter.ch[C].ad_max){ \
			g_counter.ch[C].ad_max = AD[C]; \
		} \
		if (AD[C] < g_counter.ch[C].ad_min){ \
			g_counter.ch[C].ad_min = AD[C]; \
		} \
	}
#endif
#if (SAMPLE_NUM == 16)	
	#define AD_FILTER(AD,BUF,C,S)  {\
		AD[C] = BUF[0][C] + BUF[1][C] + BUF[2][C] + BUF[3][C] + \
				BUF[4][C] + BUF[5][C] + BUF[6][C] + BUF[7][C] + \
				BUF[8][C] + BUF[9][C] + BUF[10][C] + BUF[11][C] + \
				BUF[12][C] + BUF[13][C] + BUF[14][C] + BUF[15][C]; \
		 AD[C] /= S; \
		if (AD[C] > g_counter.ch[C].ad_max){ \
			g_counter.ch[C].ad_max = AD[C]; \
		} \
		if (AD[C] < g_counter.ch[C].ad_min){ \
			g_counter.ch[C].ad_min = AD[C]; \
		} \
	}
#endif

	
void pause_vibrate (void)
{
	VIBRATE_SWITCH = 1;
}
	
void start_vibrate (void)
{
	if (g_counter.pre_count < g_counter.set_count){
		OPEN_DOOR(0);
		OPEN_DOOR(1);
		OPEN_DOOR(2);
		OPEN_DOOR(3);
		OPEN_DOOR(4);
		OPEN_DOOR(5);
		OPEN_DOOR(6);
		OPEN_DOOR(7);
		OPEN_DOOR(8);
		OPEN_DOOR(9);
		OPEN_DOOR(10);
		OPEN_DOOR(11);
		g_counter.total_count = g_counter.pre_count;
		g_counter.pre_count = 0;
		g_counter.counter_state = NORMAL_COUNT;
	}else{
		g_counter.total_count = g_counter.pre_count;
		g_counter.pre_count = 0;
		if (g_counter.total_count > g_counter.set_count){//����
			REJECT_FLAG = 0;//�޳���־
		}
		COUNT_COMPLETE = 0;
		g_counter.counter_state = PRE_COUNT;
	}
	VIBRATE_SWITCH = 0;
}	
void stop_vibrate (void)
{
	VIBRATE_SWITCH = 1;
}


int AD_Sample_init (void)
{
	AD_GPIO_Configuration ();
	AD1_DMA_Configuration ();
	ADC1_Configuration ();
	ENABLE_SENSOR ();
	DMA_Cmd(DMA1_Channel1, ENABLE); //����DMAͨ��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	return 0;
}

void AD_Start_Sample (u32 _memBaseAddr)
{
	ADC_sync_signal = 0;//AD �ź����� ����ͬ��
	/* Write to DMA1 Channel4 CMAR */
	DMA1_Channel1->CMAR = _memBaseAddr;
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



int save_detect_data (U16 _ch, U16 * _index, U16 _ad_value)
{		
	if (_ch == my_env.watch_ch){
		if ((*_index) < DETECTG_BUF_SIZE){
			Detect_Buf[g_counter.buf_index][*_index] = _ad_value;
			(*_index)++;
			return 0;
		}else{
			return 1;
		}
	}
	return 0;
}

#define CASE_CH(CH) case CH: if (DOOR_##CH == 1){ \
	if (g_counter.door_close_delay_para == 0){ \
		DOOR_##CH = 0; \
	}else { \
		_ch->door_close_delay = g_counter.door_close_delay_para;/*С���Źر���ʱ*/ \
	} \
	if (_ch->interval.data_hl < g_counter.min_interval.data_hl){/*С���Źر�ʱ���̫С*/  \
		REJECT_FLAG = 0; \
	} \
	_ch->close_interval.data_hl = _ch->interval.data_hl; \
} \
break

int count_piece(s_chanel_info * _ch, U16 ad_value, U16 _ch_id)
{
	int r_code = 0;
	switch(_ch->process_step)
	{ 
/*Ԥ���ӳ�,��ʼ��ֵ*/
		case 0: {
			
			_ch->wave_down_flag = 0;
			_ch->wave_up_flag = 0;
			_ch->ad_value_min = AD_MAX_V;
			_ch->ad_value_min_temp = AD_MAX_V;
			
			//_ch->std_down_v = STD_DOWN_V;
			//_ch->std_up_v = STD_UP_V;
			
			_ch->cur_count = 0;
			_ch->piece_in = 0;
			_ch->piece_out = 1;
			_ch->piece_stay_t = 0;
			_ch->piece_stay_t_min = 0;
			_ch->piece_stay_t_max = 0;
			_ch->sample_index = 0;
			
			_ch->process_step = 6;
			_ch->state = CH_IDLE;
			_ch->interval_ticks = get_tim5_ticks ();
			_ch->max_interval.data_hl = 0;
			_ch->max_size.data_hl = 0;
			_ch->min_interval.data_hl = 0xFFFFFFFF;
			_ch->min_size.data_hl = 0xFFFFFFFF;
			
			break;
		}
		case 6:{ /*��ȡ��ֵ��ο�ֵ�Աȼ��仯�Ĳ���ִ��*/	//read in ad value ADSAMPNUM times 
			
			if (ad_value < _ch->std_down_v){
				r_code = save_detect_data (_ch_id, &_ch->sample_index, ad_value);
				_ch->state = CH_BUSY;
				_ch->wave_down_flag++;
			}else{
				_ch->wave_down_flag = 0;
				_ch->sample_index = 0;
				_ch->state = CH_IDLE;
			}
			
			if (_ch->wave_down_flag > WAVE_DOWN){
				_ch->wave_down_flag = 0;
				_ch->ad_value_min_temp = ad_value;
				_ch->piece_in = 1;
				_ch->piece_out = 0;
				_ch->size_ticks = get_tim5_ticks ();
				_ch->interval.data_hl = _ch->size_ticks - _ch->interval_ticks;
				if (_ch->interval.data_hl > _ch->max_interval.data_hl ){
					if ( _ch->max_interval.data_hl > 0){
						_ch->max_interval.data_hl = _ch->interval.data_hl;
					}else{
						_ch->max_interval.data_hl = 1;//ͨ����һ������
					}
				}else if (_ch->interval.data_hl < _ch->min_interval.data_hl){
					_ch->min_interval.data_hl = _ch->interval.data_hl;
				}
				
				_ch->process_step = 16;
			}else{
			}
			
			break;
		} 
		case 16:{	/*ȷ����Сֵ,���λ���*/					//read in ad value ADSAMPNUM times 
			
			r_code = save_detect_data (_ch_id, &_ch->sample_index, ad_value);
			
			if (ad_value < _ch->ad_value_min_temp){
				_ch->ad_value_min_temp = ad_value;
				_ch->wave_up_flag = 0;
			}else if (ad_value > _ch->ad_value_min_temp + WAVE_UP_V){
				_ch->wave_up_flag++;
			}
			
			if (_ch->wave_up_flag > WAVE_UP){//�����˲��Ⱥ�
				_ch->ad_value_min = _ch->ad_value_min_temp;
				_ch->ad_value_min_temp = AD_MAX_V;
				_ch->wave_up_flag = 0;
				_ch->process_step = 31;
			}
			
			break;
		}
		case 31:{		/*�ж��Ƿ���ο�ֵ��ͬ�����,ȷ��������ֵ,���λָ����ο�ֵ*/				//ad0 value get
			
			r_code = save_detect_data (_ch_id, &_ch->sample_index, ad_value);
			
			if (ad_value >= _ch->std_up_v){
				_ch->wave_up_flag++;
			}
			
			if (_ch->wave_up_flag > WAVE_UP){
				_ch->piece_in = 0;
				_ch->piece_out = 1;
				
				_ch->interval_ticks = get_tim5_ticks ();
				_ch->size.data_hl = _ch->interval_ticks - _ch->size_ticks;
				if (_ch->size.data_hl > _ch->max_size.data_hl){
					_ch->max_size.data_hl = _ch->size.data_hl;
				}else if (_ch->size.data_hl < _ch->min_size.data_hl){
					_ch->min_size.data_hl = _ch->size.data_hl;
				}
				
				if (_ch->size.data_hl > g_counter.max_size.data_hl){ //�����趨����
					REJECT_FLAG = 0;//�޳���־
				}else if (_ch->size.data_hl < g_counter.min_size.data_hl){//�����趨����
					REJECT_FLAG = 0;//�޳���־
				}
				//����
				_ch->cur_count++;
				if (g_counter.counter_state == NORMAL_COUNT){//��������
					PRE_COUNT_FLAG = 1;
					g_counter.total_count++;
					if (g_counter.total_count >= g_counter.set_count){//�ﵽ�趨�ļ�����
						COUNT_COMPLETE = 0;//�������,��PLC�ź�
						g_counter.counter_state = PRE_COUNT;
						_ch->cur_count = 0;
						if (g_counter.total_count > g_counter.set_count){//����
							REJECT_FLAG = 0;//�޳���־
						}
					}
				}else if (g_counter.counter_state == PRE_COUNT){//��ʼԤ��
					g_counter.pre_count++;
					if (g_counter.pre_count >= g_counter.pre_set_count){//�ﵽ�趨��Ԥ��
						pause_vibrate();
						_ch->cur_count = 0;
					}
					PRE_COUNT_FLAG = 0;
					switch (_ch_id){
						CASE_CH(0);
						CASE_CH(1);
						CASE_CH(2);
						CASE_CH(3);
						CASE_CH(4);
						CASE_CH(5);
						CASE_CH(6);
						CASE_CH(7);
						CASE_CH(8);
						CASE_CH(9);
						CASE_CH(10);
						CASE_CH(11);
						default:break;
					}
				}
				
				_ch->process_step = 6;
				_ch->sample_size = _ch->sample_index;
				_ch->state = CH_DATA_RDY;
				_ch->sample_index = 0;
				_ch->wave_up_flag = 0;
			}
			break;
		}
	}
	return r_code;
}

////////////////////////////////////////////////////////////////////////////////

u16 counter_process_time = 0;
void counter_process (void)
{
	int r_code = 0;
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// process begin ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
	
	if (g_counter.buf_index == 0){
		g_counter.AD_Value_p = AD_Value_0;
		AD_Start_Sample ((u32) AD_Value_1);//�˲���Ϳ���ת��
		g_counter.buf_index++;
	}else {
		g_counter.AD_Value_p = AD_Value_1;
		AD_Start_Sample ((u32) AD_Value_0);//�˲���Ϳ���ת��
		g_counter.buf_index = 0;
	}

	AD_FILTER (After_filter, g_counter.AD_Value_p, 0, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 1, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 2, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 3, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 4, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 5, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 6, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 7, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 8, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 9, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 10, SAMPLE_NUM);
	AD_FILTER (After_filter, g_counter.AD_Value_p, 11, SAMPLE_NUM);

#if 1
	r_code += count_piece (&g_counter.ch[0], After_filter[0], 0);
	r_code += count_piece (&g_counter.ch[1], After_filter[1], 1);
	r_code += count_piece (&g_counter.ch[2], After_filter[2], 2);
	r_code += count_piece (&g_counter.ch[3], After_filter[3], 3);
	r_code += count_piece (&g_counter.ch[4], After_filter[4], 4);
	r_code += count_piece (&g_counter.ch[5], After_filter[5], 5);
	r_code += count_piece (&g_counter.ch[6], After_filter[6], 6);
	r_code += count_piece (&g_counter.ch[7], After_filter[7], 7);
	r_code += count_piece (&g_counter.ch[8], After_filter[8], 8);
	r_code += count_piece (&g_counter.ch[9], After_filter[9], 9);
	r_code += count_piece (&g_counter.ch[10], After_filter[10], 10);
	r_code += count_piece (&g_counter.ch[11], After_filter[11], 11);
#else //���´���ֻ�ڲ��Ե�ʱ���ã�����ʹ����������Ĵ���
	r_code += count_piece (&g_counter.ch[0], After_filter[0], 0);
	r_code += count_piece (&g_counter.ch[1], After_filter[0], 1);
	r_code += count_piece (&g_counter.ch[2], After_filter[0], 2);
	r_code += count_piece (&g_counter.ch[3], After_filter[0], 3);
	r_code += count_piece (&g_counter.ch[4], After_filter[0], 4);
	r_code += count_piece (&g_counter.ch[5], After_filter[0], 5);
	r_code += count_piece (&g_counter.ch[6], After_filter[0], 6);
	r_code += count_piece (&g_counter.ch[7], After_filter[0], 7);
	r_code += count_piece (&g_counter.ch[8], After_filter[0], 8);
	r_code += count_piece (&g_counter.ch[9], After_filter[0], 9);
	r_code += count_piece (&g_counter.ch[10], After_filter[0], 10);
	r_code += count_piece (&g_counter.ch[11], After_filter[0], 11);
#endif	

	if (my_env.print == 1){
		if (r_code != 0){
		}else if (g_counter.ch[my_env.watch_ch].state == CH_DATA_RDY){
			if (my_env.dma_state == 0){
				my_env.dma_state = 1;
				g_counter.buf_addr = (u32)&Detect_Buf[g_counter.buf_index][0];
				g_counter.buf_index++;
				g_counter.buf_index %= DETECTG_BUF_GROUP;
				OSQPost(debug_msg, (void *) 0x55);//������Ϣ
			}
		}
	}
	
	counter_process_state = r_code;
//////////////////////////////// process end /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
}


