/*
 * MiceoWave.c
 *
 *  Created on: Apr 9, 2020
 *      Author: M.Aboelsaoud
 */
#include "MiceoWave.h"
static uint_8 key;
/**************timer****************************************************************/
str_obj obg1;

gcfg_hal_timer_t hal_timer_obj=
{
	.ins_timer=TIMER_0,
	.freq=PRESCALER_256,
	.timer_fun=NORMAL_MODE,
};

static uint_8 num1 , num2; /*used to cary the entered numbers */
static uint_8 num_of_sec;
void counter_time();
static void microwave_time_fun()
{
	if(num_of_sec!=0)
	{
		num_of_sec--;	
	}
	else
	{
		MW_Stop();
	}
	
}

/**************timer*************************************************/


/********************************INTERUPt*************************/
gstr_ext_interrupt_config extenal_int_obg =
{
	.interrupt_level=ANY_CHANGE,
	.cb_fun_ptr=&MW__ON_Spot_Stop,
	.interrupt_number=INT_1,
};
/********************************INTERUPt*************************/
bool_t MW_Init_All(void)
{
	bool_t ret_val =E_TRUE;
	/*LCD*/
    Lcd_Init();
	LCD_Display_RowColumn(0,4,"TOSHIBA");
	LCD_Display_RowColumn(1,3,"MICROWAVE");
	/********************************INTERUPt*************************/
	//hal_ex_interrupt_Initi(&extenal_int_obg);
	/********************************INTERUPt*************************/
	
	/**************timer*************************************************/
	tmu_init(TIMER0 ,1);
	hal_init_timer(&hal_timer_obj, counter_time);
	/**************timer*************************************************/
	
	/*PortD configuration*/
	//GPIO_PortDirection(PORTD,PIN3,INPUT);
	
	GPIO_PortDirection(PORTA,PIN0,INPUT);
	GPIO_PortDirection(PORTA,PIN1,INPUT);
	GPIO_PortDirection(PORTA,PIN2,INPUT);
	GPIO_PortDirection(PORTA,PIN3,INPUT);
/*	GPIO_PortInit(PORTA,PIN0,1);
	GPIO_PortInit(PORTA,PIN1,1);
	GPIO_PortInit(PORTA,PIN2,1);
	GPIO_PortInit(PORTA,PIN3,1);*/
	GPIO_PortDirection(PORTA,PIN4,OUTPUT);
	GPIO_PortDirection(PORTA,PIN5,OUTPUT);
	GPIO_PortDirection(PORTA,PIN6,OUTPUT);
	GPIO_PortDirection(PORTA,PIN7,OUTPUT);
/*	GPIO_PortInit(PORTA,PIN4,0);
	GPIO_PortInit(PORTA,PIN5,0);
	GPIO_PortInit(PORTA,PIN6,0);
	GPIO_PortInit(PORTA,PIN7,0);*/
	
	SET_BIT(PORTA1,PIN6);
	//SET_BIT(PORTA1,PIN4);
	//SET_BIT(PORTA1,PIN7);
	//SET_BIT(PORTA1,PIN5);
	
	
	/*PortA configuration*/
	
	
	


	return ret_val;
}


bool_t MW_Start(void)
{
	bool_t ret_val =E_TRUE;
while((IS_BIT_CLEAR(PINA,PIN3)==0));
while((IS_BIT_CLEAR(PINA,PIN2)==0));
		Lcd_Clean();
		LCD_Display_RowColumn(0,0,"Enter the time:-");
		uint_8 i=0,j=1,k=6;
		for (i=0;i<2;i++)
		{
			key = KeyPad_getPressedKey();
			_delay_ms(200);
			/**************timer****************/
			if(i==0)
				num2=key;
			else
				num1=key;
				
			/**************timer****************/	
			
			LCD_goToRowColumn(j,k);
			_delay_ms(100);
			switch(key)
			{
				case 0:
				{
					Lcd_Display_Character('0');
					break;
				}
				case 1:
				{
					Lcd_Display_Character('1');
					break;
				}
				case 2:
				{
					Lcd_Display_Character('2');
					break;
				}
				case 3:
				{
					Lcd_Display_Character('3');
					break;
				}
				case 4:
				{
					Lcd_Display_Character('4');
					break;
				}
				case 5:
				{
					Lcd_Display_Character('5');
					break;
				}
				case 6:
				{
					Lcd_Display_Character('6');
					break;
				}
				case 7:
				{
					Lcd_Display_Character('7');
					break;
				}
				case 8:
				{
					Lcd_Display_Character('8');
					break;
				}
				case 9:
				{
					Lcd_Display_Character('9');
					break;
				}
				case'*':
				{
					LCD_Display_RowColumn(0,1,"ERROE MUST ENTER NUM");
					LCD_Display_RowColumn(1,0,"TRY RETRY... ");
					_delay_ms(1000);
				    MW_Start();
				  break;
				}
				case'#':
				{
					LCD_Display_RowColumn(0,1,"ERROE MUST ENTER NUM");
					LCD_Display_RowColumn(1,0,"TRY RETRY... ");
					_delay_ms(1000);
					MW_Start();
					break;
				}
			default:
			{
				LCD_Display_RowColumn(0,1,"ERROE MUST ENTER NUM");
				LCD_Display_RowColumn(1,0,"TRY RETRY... ");
				_delay_ms(1000);
				 MW_Start();
				/*key = KeyPad_getPressedKey();
				if(key=='#')
				{
					i=0;
					k=3;
				  MW_Start();
				}*/
				break;
			}
				
			}
			k++;
		}
	num_of_sec =((num1*60)+(num2*10*60));//*(4*(num1+num2));
		
/**************timer****************/
start_timer(microwave_time_fun, PERIODIC,100, &obg1);
/**************timer****************/
while((IS_BIT_CLEAR(PINA,PIN0)==0));

SET_BIT(PORTA1,PIN5);
SET_BIT(PORTA1,PIN4);
LCD_Display_RowColumn(0,0,"MICROWAVE IS ON");
LCD_Display_RowColumn(1,2,"PLEASE WAIT...");


	return ret_val;
}


bool_t MW_Stop(void)
{
	bool_t ret_val =E_TRUE;

	/**************timer****************/
	hal_deinit_timer(&hal_timer_obj);
	/**************timer****************/
	SET_BIT(PORTA1,PIN7);
	CLEAR_BIT(PORTA1,PIN5);
	CLEAR_BIT(PORTA1,PIN4);
	CLEAR_BIT(PORTA1,PIN6);
	LCD_Display_RowColumn(0,0,"MICROWAVE IS OFF");
	LCD_Display_RowColumn(1,2,"FINSH....");
	


	return ret_val;
}
bool_t MW__ON_Spot_Stop()
{
	CLEAR_BIT(PORTA1,PIN5);
	CLEAR_BIT(PORTA1,PIN4);
	CLEAR_BIT(PORTA1,PIN6);
	CLEAR_BIT(PORTA1,PIN7);
	LCD_Display_RowColumn(0,0,"MICROWAVE IS STOP");
	//LCD_Display_RowColumn(1,2,"FINSH");
	
}