#include "main.h"

//U16 RS485_FrameEndFlag;

void uart1_send_data (int ch)
{
    //USART1->SR;  //USART_GetFlagStatus(USART1, USART_FLAG_TC) �����һ���ַ�����ʧ�ܵ�����
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	if(ch == '\n'){
		USART_SendData(USART1, '\r');
		my_env.roll_count++;
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
    //һ��һ�������ַ�
    USART_SendData(USART1, (unsigned char) ch);
    //�ȴ��������
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}

void uart1_puts(const char *s)
{
	while (*s) {
		uart1_send_data(*s++);
	}
}

void uart1_dma_config (void)
{
}
//����1 DMA��ʽ�����ж�  
void DMA1_Channel4_IRQHandler(void)  
{
	if(DMA_GetITStatus(DMA1_IT_TC4)){
		//�����־λ  
		DMA_ClearFlag(DMA1_FLAG_TC4);//���ͨ��4������ɱ�־
		DMA_ClearITPendingBit(DMA1_IT_GL4); //���ȫ���жϱ�־ 
		USART_DMACmd(USART1,USART_DMAReq_Tx, DISABLE); //DISABLE����1��DMA����  
		DMA_Cmd(DMA1_Channel4, DISABLE);  
	}
} 

void start_uart1_dma (u32 _memBaseAddr, U16 _size)
{
	/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
	/* Write to DMA1 Channel4 CMAR */
	DMA1_Channel4->CMAR = _memBaseAddr;
	DMA_SetCurrDataCounter (DMA1_Channel4, _size);
	DMA_Cmd(DMA1_Channel4, ENABLE);  
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����   
}

void start_uart3_dma (u32 _memBaseAddr, U16 _size)
{
	/*--------------------------- DMAy Channelx CMAR Configuration ----------------*/
	/* Write to DMA1 Channel2 CMAR */
	DMA1_Channel2->CMAR = _memBaseAddr;
	DMA_SetCurrDataCounter (DMA1_Channel2, _size);
	DMA_Cmd(DMA1_Channel2, ENABLE);  
	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����   
}
void uart1_init (void)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART1_RX_INT_PREEM;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART1_RX_INT_SUB;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = UART1_BOUND_RATE;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж� 
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE); //�������ڿ����ж� 
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	
	uart1_dma_config ();

}


void stop_uart1_receive (void)
{
    DMA_Cmd(DMA1_Channel5,DISABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, DISABLE); //�������ڿ����ж� 
}
void start_uart1_receive (void)
{        
	//���ô������ݳ���  
	memset (cmd_analyze.rec_buf, 0, CMD_BUF_LEN);
    DMA_Cmd(DMA1_Channel5,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel5, CMD_BUF_LEN);  
    DMA_Cmd(DMA1_Channel5,ENABLE);
	USART_ITConfig(USART1,USART_IT_IDLE, ENABLE); //�������ڿ����ж� 
}


#if EN_USART1_RX   //���ʹ���˽���
//����1�����ж�     
void USART1_IRQHandler(void)                                 
{     
    uint32_t temp = 0;    
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  
    {  
      temp = USART1->SR;  
      temp = USART1->DR; //��USART_IT_IDLE��־  
			if (my_env.tty){
				fill_rec_buf(temp);
			}else if (temp == ' '){
				my_env.tty_ctr++;
				if (my_env.tty_ctr > 5){
					my_env.tty = 1;
				}
			}else{
				my_env.tty_ctr = 0;
			}
    }else{
        temp = USART1->SR;  
        temp = USART1->DR; //��USART_IT_IDLE��־  
	}
} 

#endif

//����3 DMA��ʽ�����ж�  
void DMA1_Channel2_IRQHandler(void)  
{  
	if(DMA_GetITStatus(DMA1_IT_TC2)){
		//�����־λ  
		DMA_ClearFlag(DMA1_FLAG_TC2);//���ͨ��4������ɱ�־
		DMA_ClearITPendingBit(DMA1_IT_GL2); //���ȫ���жϱ�־ 
		USART_DMACmd(USART3,USART_DMAReq_Tx, DISABLE); //DISABLE����1��DMA����  
		DMA_Cmd(DMA1_Channel2, DISABLE);  
	}
} 
void uart3_dma_config (void)
{
}

void uart3_init (void)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART1ʱ��
  
	//USART3_TX   GPIOB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB10
   
	//USART3_RX	  GPIOB11��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB11

	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = UART3_RX_INT_PREEM;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = UART3_RX_INT_SUB;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = UART3_BOUND_RATE;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 
	
	uart3_dma_config ();
}

#if EN_USART3_RX   //���ʹ���˽���
unsigned char uart3_rec_buf[UART3_BUF_LEN];
U16 uart3_rec_count = 0;
void USART3_IRQHandler(void)                	//����3�жϷ������
{
	__IO u8 Res;
	//Res = USART1->SR;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
	#if (MODBUS_RTU_USE_UART == 3)
		TIM_SetCounter(TIM7,0);//�����յ�һ���µ��ֽڣ�����ʱ��7��λΪ0�����¼�ʱ���൱��ι����
		TIM_Cmd(TIM7,ENABLE);//��ʼ��ʱ
	#endif
		uart3_rec_buf[uart3_rec_count++] = USART_ReceiveData(USART3);	//��ȡ���յ�������
	}else{
		Res = USART_ReceiveData(USART3);	//��ȡ���յ�������
	}
} 
#endif











