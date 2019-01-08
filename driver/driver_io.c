#include "main.h"


void drive_io_init (void)
{
	
	
}

//�ⲿ�ж���0���жϷ�����
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0); //����ж���0�����־λ
}
//�ⲿ�ж���1���жϷ�����
void EXTI1_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line1); //����ж���1�����־λ
}
//�ⲿ�ж���2���жϷ�����
void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2); //����ж���2�����־λ
}
//�ⲿ�ж���3���жϷ�����
void EXTI3_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line3); //����ж���3�����־λ
}

//�ⲿ�ж���6 7 8���жϷ�����
void EXTI9_5_IRQHandler(void)
{
	if (PCin(6) == 0){
	}else if (PCin(7) == 0){
	}else if (PAin(8) == 0){
	}
	EXTI_ClearITPendingBit(EXTI_Line6 | EXTI_Line7 | EXTI_Line8); //����ж���6�����־λ
}
//�ⲿ�ж���11���жϷ�����
void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line11); //����ж���11�����־λ
}

























