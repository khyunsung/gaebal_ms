#include "define.h"
#include "variable.h"
#include "prototype.h"

//28335�� 32bit machine������ 16bit(1word) ó����. �ܺ� peripheral�� 16bit
//char 16bit, int 16bit, long 16bit
//���� ������ ��� PT�� �ɸ��� ���� ������. 3��4���� ������, 3��3���� ��������(HIMAP-BCS�� ��� �������� ������)
//Ia, Ib, Ic, Io�� ��� �ִ� 100[A], Va, Vb, Vc, Vo�� ��� �ִ� 380[V]
//������ 36�����̸�, A/D���� 3������ �Ѳ����� 12�� �����ִ� �����
void main(void) 
{
	// H/W �ʱ�ȭ �� ����....
	// �Ʒ� ���� �Լ��� H/W ������ ���� �� ���� ����

	cpu_setup();         // DSP setup�� ���� ���� TI guide�� ����
	lcd_setup();	     // LCD ��Ʈ�ѷ��� ����
	interrupt_control(); // ���ͷ�Ʈ ���

	// ������ system setup �� ��������
	booting_setting_check();

	// Enable Global interrupt INTM
	EINT;	// ���⼭���� ���ͷ�Ʈ Ȱ�� ȭ

	// ��¥ main �Լ�
	real_main();
}

void real_main(void)
{
	unsigned int i;
	unsigned int j;
//	unsigned int temp;

	menu_init();

	for(;;)
	{	
		//relay
		if(SAMPLE.ending)	
		{
			PROTECTIVE_RELAY();
		}

		// key
		if(TIMER.key > 80)	{key_drive();}

		// lcd
		if(TIMER.lcd > 200)	{menu_drive();}//300

		// �⺻���� �� ����,����
		if(TIMER.measurement > 4)
		{
			if(DISPLAY.switching == 0)	{measure_display();}
			else												{measure2_display();}
		}

		// AD ���ͷ�Ʈ���� 1�ʰ� ���°��� �����Ǿ��ٰ� �˷����� ȣ��
		if(DISPLAY.Power_Up == 0xaaaa)	{power_update();}

		// 20ms ���� ������� �����
		if(HARMONICS.timer > 20)	{harmonics();}

//-------- manager ���
		// ���������� ����Ÿ�� ���� �����ε�....
		if(MANAGER.rx_status == 1)
		{
			// ���̺� �������ų� �˼� ���� ������ 2�ʰ� �������� ������ ���� �Ϸ�(MANAGER.rx_status == 2)�� �ȵǸ�
			// �ø��� ���� ������ �ʱ�ȭ
			if(MANAGER.rx_timeout > 2000)
			{
				MANAGER.rx_count = 0;	// �Է� ���� ī���� �ʱ�ȭ
				MANAGER.rx_status = 0; // �ø��� ���� �÷��� �ʱ�ȭ
			}
		}

		// �ϴ� ������ ������ �Է��� �Ϸ�� ����
		else if(MANAGER.rx_status == 2)
		{
			// �� ù����Ʈ ��� �˻�
			// header �̻��ϸ� pc�� nak �۽�
			if(MANAGER.rx_buffer[0] != '#')	{serial_ok_nak_send(0x01);}

			// �ι�° id �˻��ϴµ� 0 �Ǵ� ADDRESS.address�� ������ ���� ������ ������ nak
			// id �̻�
			else if((MANAGER.rx_buffer[1] != 0) && (MANAGER.rx_buffer[1] != ADDRESS.address))	{serial_ok_nak_send(0x02);}

			// �ϴ� ����� ���� ���
			// �ϴ� ����
			else
			{
				// ��ü �ø��� �������� ������ �Ǵ��� ���� ���� ���� ���� crc ���� ���Ѵ�.
				// crc ���
				j = COMM_CRC(MANAGER.rx_buffer, MANAGER.rx_length - 2);

				// ���������� ���� ���� crc ��������Ʈ
				i = MANAGER.rx_buffer[MANAGER.rx_length - 2];
				i <<= 8;
				// ���������� ���� ���� crc ��������Ʈ�� or �ϸ� crc �� ����
				i |= MANAGER.rx_buffer[MANAGER.rx_length - 1];

				// �Էµ� crc ���� ����� crc���� ������ �������� �����ϴٶ�� �Ǵ�
				if(i == j)	{manager_handling();}
				// ������ �ҷ�. nak
				else				{serial_ok_nak_send(0x03);}
			}

			MANAGER.rx_count = 0;
			MANAGER.rx_status = 0;
		}
//-------- manager ��� END

//-------- wave ó��
		if((WAVE.post_count == 5400) && (WAVE.post_start == 0x1234))	{wave_save_process();}
//-------- wave ó�� END

//-------- tcs/ccs
//		if(SUPERVISION.mode == 0xaaaa)
//		{
//			if(SUPERVISION.monitor_update)
//			{
//				SUPERVISION.monitor_update = 0; // �÷��� �ʱ�ȭ
//
//				SUPERVISION.monitoring[0] /= 720; // 1�ʵ��� �� ���
//				supervision_relay(0); // tcs ����
//
//				SUPERVISION.monitoring[1] /= 720; // 1�ʵ��� �� ���
//				supervision_relay(1);	//ccs ����
//			}
//		}
//-------- tcs/ccs END

//-------- event ����
		// di/do on/off �̺�Ʈ�� ���⼭ �Ѳ����� ����
		// 1ms ���ͷ�Ʈ �ȿ��� �ּ����� ���۸� �ϰ� ������ ����
		// ������ ������ �ִ� 1ms ���� �߻��ϹǷ� ���������� �ǹ̾���
		if(EVENT.di_off & 0x0000ffff)	{event_direct_save(&EVENT.di_off);}
		if(EVENT.di_on & 0x0000ffff)	{event_direct_save(&EVENT.di_on);}

//		if(SYSTEM.do_status != SYSTEM.do_status_backup)	// do ���°� �ٲ��
//		{
//			temp = SYSTEM.do_status_backup ^ SYSTEM.do_status;	// Ʋ���� �� ���͸�
//			for(i = 0; i < 9; i++)
//			{
//				if(temp & DO_ON_BIT[i])	// Ʋ������?
//				{
//					if(SYSTEM.do_status & DO_ON_BIT[i])	// close? ��Ʈ�� 1
//					{
//						EVENT.do_on |= ON_BIT[i];
//					}
//					else	// open
//					{
//						EVENT.do_off |= ON_BIT[i];
//					}
//				}
//				//-------- DO display, Wave ����, COMM�� (DO display ����� ���� ����)
//				if(SYSTEM.do_status & DO_ON_BIT[i])
//				{
//					DIGITAL_OUTPUT.do_status |= ON_BIT[i]; // DIGITAL_OUTPUT.do_status - DO display ���� ����
//				}
//				else
//				{
//					DIGITAL_OUTPUT.do_status &= OFF_BIT[i];
//				}
//				//-------- DO display, Wave ����, COMM�� END
//			}
//			SYSTEM.do_status_backup = SYSTEM.do_status;
//		}
//		// ������ �з��� ������� �̺�Ʈ ����
//		if(EVENT.do_off & 0x0000ffff)	{event_direct_save(&EVENT.do_off);}
//		if(EVENT.do_on & 0x0000ffff)	{event_direct_save(&EVENT.do_on);}
//-------- event ���� END

//-------- LED�� ǥ���� data 1�ʸ��� üũ
		if(TIMER.led > 700)	{
			led_handling();
			modbus_comm_card_check();
			SCI_Port_Err_Check();
		}
		*LED_CS = SYSTEM.led_on; // �ֱ������� led���� ������ ������ led�� �����°� ó�� ���� (latch ȸ�ΰ� ����), 1ms�� ���ġ ����
//-------- LED�� ǥ���� data 1�ʸ��� üũ END

//-------- ���� rtc �ð� �о����
		if(TIME.update != 0xffff)
		{
			if(TIME.milisecond > 0)
			{
				rtc_handling();
				TIME.milisecond = 0;
			}
		}
//-------- ���� rtc �ð� �о���� END

		// cb open �Ǵ� cb close �� 500ms �Ѿ������� ��������
		// cb trip �� ������
		if(SYSTEM.do_control & 0x0008)
		{
			if((RELAY_STATUS.pickup == 0) && (RELAY_STATUS.operation_realtime == 0))
			{
				// cb trip ����
				//cb open�� ����ϰų� Ÿ�̸� �Ѿ������
				if((DIGITAL_INPUT.di_status & 0x0002) || (TIMER.cb_open > 500))
				{
					// cb trip ����
					SYSTEM.do_control &= ~0x0008;
				}
			}
		}
		//������ �� cb close�� latch �˻����� ����
		//cb close pulse
		if(LOCAL_CONTROL.mode == 0xaaaa)
		{
			//cb close �� ���
			if(SYSTEM.do_control & 0x0020)
			{
				// cb close ����
				if(TIMER.cb_close > 500)
				{
					// cb close ����
					SYSTEM.do_control &= ~0x0020;
				}
			}
		}

//-------- RUNNING HOUR METER
		Cal_RHour();
//-------- RUNNING HOUR METER END

//-------- HIMIX RS-485 �۽�
		if(HIMIX.timer > 4)	{himix_drive();}
//-------- HIMIX RS-485 �۽� END

//-------- remote ��� ����ϴ� ��쿡�� ȣ��
		if(COMM.use)	{comm_drive();}
//-------- remote ��� ����ϴ� ��쿡�� ȣ�� END
	}
}


// 3�� ������ 1�ʿ� �ѹ��� ������
// 1�� ������ �� 333ms �ð� ������ ����
// crc 1ms �ѹ��� 56��
void himix_drive(void)
{
	// ���� ����
	if(HIMIX.index == 0)
	{
		HIMIX.tx_buffer[0] = 0x7e;
		HIMIX.tx_buffer[1] = 0x30;
		HIMIX.tx_buffer[2] = 0x31;
		
		HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Va];
		
		HIMIX.buffer_index = 3;
		++HIMIX.index;
		
		HIMIX.number_start = 0;
		
		HIMIX.crc_count = 0;
		
		HIMIX.tx_buffer[39] = 0;
		HIMIX.tx_buffer[40] = 0;
		HIMIX.tx_buffer[41] = 0;
		HIMIX.tx_buffer[42] = 0;
		HIMIX.tx_buffer[43] = 0;
		HIMIX.tx_buffer[44] = 0;
		HIMIX.tx_buffer[45] = 0;
		HIMIX.tx_buffer[46] = 0;
		HIMIX.tx_buffer[47] = 0;
		HIMIX.tx_buffer[48] = 0;
		HIMIX.tx_buffer[49] = 0;
		HIMIX.tx_buffer[50] = 0;
		HIMIX.tx_buffer[51] = 0;
		HIMIX.tx_buffer[52] = 0;
		HIMIX.tx_buffer[53] = 0;
		HIMIX.tx_buffer[54] = 0;
		HIMIX.tx_buffer[55] = 0;
		HIMIX.tx_buffer[56] = 0;
	}
	
	// ���� ����
	else if(HIMIX.index == 37)
	{
		HIMIX.tx_buffer[0] = 0x7e;
		HIMIX.tx_buffer[1] = 0x30;
		HIMIX.tx_buffer[2] = 0x32;
		
		HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Ia] * 10;
		
		HIMIX.buffer_index = 3;
		++HIMIX.index;
		
		HIMIX.number_start = 0;
		
		HIMIX.crc_count = 0;
	}
	
	// ����,���� �ֻ���
	else if((HIMIX.index == 1)  || (HIMIX.index == 10) || (HIMIX.index == 19) || (HIMIX.index == 28) || (HIMIX.index == 38) || (HIMIX.index == 47) || (HIMIX.index == 56) || (HIMIX.index == 65))
	{
		// �ֻ���
		HIMIX.temp16 = HIMIX.temp32 / 100000000;
		
		if(HIMIX.temp16 == 0)
		HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
		
		else
		{
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
			HIMIX.number_start = 1;
		}
		
		HIMIX.temp32 %= 100000000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� �ι���
	else if((HIMIX.index == 2)  || (HIMIX.index == 11) || (HIMIX.index == 20) || (HIMIX.index == 29) || (HIMIX.index == 39) || (HIMIX.index == 48) || (HIMIX.index == 57) || (HIMIX.index == 66))
	{
		//�ι�°
		HIMIX.temp16 = HIMIX.temp32 / 10000000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 10000000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� ������
	else if((HIMIX.index == 3)  || (HIMIX.index == 12) || (HIMIX.index == 21) || (HIMIX.index == 30) || (HIMIX.index == 40) || (HIMIX.index == 49) || (HIMIX.index == 58) || (HIMIX.index == 67))
	{
		//����°
		HIMIX.temp16 = HIMIX.temp32 / 1000000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 1000000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� �׹���
	else if((HIMIX.index == 4)  || (HIMIX.index == 13) || (HIMIX.index == 22) || (HIMIX.index == 31) || (HIMIX.index == 41) || (HIMIX.index == 50) || (HIMIX.index == 59) || (HIMIX.index == 68))
	{
		//�׹�°
		HIMIX.temp16 = HIMIX.temp32 / 100000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 100000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� �ټ�����
	else if((HIMIX.index == 5)  || (HIMIX.index == 14) || (HIMIX.index == 23) || (HIMIX.index == 32) || (HIMIX.index == 42) || (HIMIX.index == 51) || (HIMIX.index == 60) || (HIMIX.index == 69))
	{
		//�ټ���°
		HIMIX.temp16 = HIMIX.temp32 / 10000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 10000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� ��������
	else if((HIMIX.index == 6)  || (HIMIX.index == 15) || (HIMIX.index == 24) || (HIMIX.index == 33) || (HIMIX.index == 43) || (HIMIX.index == 52) || (HIMIX.index == 61) || (HIMIX.index == 70))
	{
		//������°
		HIMIX.temp16 = HIMIX.temp32 / 1000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 1000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� �ϰ�����
	else if((HIMIX.index == 7)  || (HIMIX.index == 16) || (HIMIX.index == 25) || (HIMIX.index == 34) || (HIMIX.index == 44) || (HIMIX.index == 53) || (HIMIX.index == 62) || (HIMIX.index == 71))
	{
		//�ϰ���°
		HIMIX.temp16 = HIMIX.temp32 / 100;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 100;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� ��������
	else if((HIMIX.index == 8)  || (HIMIX.index == 17) || (HIMIX.index == 26) || (HIMIX.index == 35) || (HIMIX.index == 45) || (HIMIX.index == 54) || (HIMIX.index == 63) || (HIMIX.index == 72))
	{
		//������°
		HIMIX.temp16 = HIMIX.temp32 / 10;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
			}
		}
		
		HIMIX.temp32 %= 10;
		
		if((HIMIX.index == 45) || (HIMIX.index == 54) || (HIMIX.index == 63) || (HIMIX.index == 72))
		{
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
		}
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ����,���� ��ȩ����
	else if((HIMIX.index == 9)  || (HIMIX.index == 18) || (HIMIX.index == 27) || (HIMIX.index == 36) || (HIMIX.index == 46) || (HIMIX.index == 55) || (HIMIX.index == 64) || (HIMIX.index == 73))
	{
		if(HIMIX.index == 9)
		{
			//��ȩ��°
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
			
			HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Vb];
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 18)
		{
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
			
			HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Vc];
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 27)
		{
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
			
			HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Vn];
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 36)
		{
			if(HIMIX.crc_count == 0)
			{
				// ����� ������ ��ȣ
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
				HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
				
				HIMIX.crc[0] = 0;
				HIMIX.crc[1] = 0;
				
				HIMIX.crc_count = 1;
			}
			
			//for(i=1;i<56;i++)
			//himix_crc(localTxBufB[i]);
	
			himix_crc(HIMIX.tx_buffer[HIMIX.crc_count]);
			
			++HIMIX.crc_count;
			
			if(HIMIX.crc_count == 56)
			{
				//�߻�
				//485 driver Ȱ��
				HIMIX_SEND;
				// tx interrupt Ȱ��
				*ScicRegs_SCICTL2 |= 0x0001;
				
				// tx intrrupt Ȱ��ȭ �� ���� �ѹ� �����
				HIMIX.tx_count = 1;
				*ScicRegs_SCITXBUF = HIMIX.tx_buffer[0];
				
				++HIMIX.index;
			}
		}
			
		else if(HIMIX.index == 46)
		{
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			
			HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Ib] * 10;
						
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 55)
		{
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			
			HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[Ic] * 10;
						
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 64)
		{
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			
			HIMIX.temp32 = (unsigned long)DISPLAY.rms_value[In] * 10;
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}	
		
		else if(HIMIX.index == 73)
		{
			if(HIMIX.crc_count == 0)
			{
				// ����� ������ ��ȣ
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
				HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
				
				HIMIX.crc[0] = 0;
				HIMIX.crc[1] = 0;
				
				HIMIX.crc_count = 1;
			}
			
			//for(i=1;i<56;i++)
			//himix_crc(localTxBufB[i]);
	
			himix_crc(HIMIX.tx_buffer[HIMIX.crc_count]);
			
			++HIMIX.crc_count;
			
			if(HIMIX.crc_count == 56)
			{
				//�߻�
				++HIMIX.index;
			}
		}	
	}
	
	
	// ���� ����
	else if(HIMIX.index == 74)
	{
		HIMIX.tx_buffer[0] = 0x7e;
		HIMIX.tx_buffer[1] = 0x30;
		HIMIX.tx_buffer[2] = 0x33;
		
		if(DISPLAY.p3 < 0)
		{
			HIMIX.minus_flag = 1;			
			HIMIX.temp32 = (unsigned long)(DISPLAY.p3 * -10);
		}
		
		else
		{
			HIMIX.minus_flag = 0;
			HIMIX.temp32 = (unsigned long)(DISPLAY.p3 * 10);
		}
		
		HIMIX.buffer_index = 3;		
		++HIMIX.index;
		
		HIMIX.number_start = 0;
		
		HIMIX.crc_count = 0;
	}
	
	// ���� �ֻ���
	else if((HIMIX.index == 75)  || (HIMIX.index == 84)  || (HIMIX.index == 93) || (HIMIX.index == 102) || (HIMIX.index == 111) || (HIMIX.index == 120))
	{
		// �ֻ���
		HIMIX.temp16 = HIMIX.temp32 / 100000000;
		
		if(HIMIX.temp16 == 0)
		HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
		
		else
		{
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
			HIMIX.number_start = 1;
		}
		
		HIMIX.temp32 %= 100000000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� �ι���
	else if((HIMIX.index == 76)  || (HIMIX.index == 85)  || (HIMIX.index == 94) || (HIMIX.index == 103) || (HIMIX.index == 112) || (HIMIX.index == 121))
	{
		//�ι�°
		HIMIX.temp16 = HIMIX.temp32 / 10000000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;				
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 10000000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� ������
	else if((HIMIX.index == 77)  || (HIMIX.index == 86)  || (HIMIX.index == 95) || (HIMIX.index == 104) || (HIMIX.index == 113) || (HIMIX.index == 122))
	{
		//����°
		HIMIX.temp16 = HIMIX.temp32 / 1000000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;				
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 1000000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� �׹���
	else if((HIMIX.index == 78)  || (HIMIX.index == 87)  || (HIMIX.index == 96) || (HIMIX.index == 105) || (HIMIX.index == 114) || (HIMIX.index == 123))
	{
		//�׹�°
		HIMIX.temp16 = HIMIX.temp32 / 100000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 100000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� �ټ�����
	else if((HIMIX.index == 79)  || (HIMIX.index == 88)  || (HIMIX.index == 97) || (HIMIX.index == 106) || (HIMIX.index == 115) || (HIMIX.index == 124))
	{
		//�ټ���°
		HIMIX.temp16 = HIMIX.temp32 / 10000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 10000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� ��������
	else if((HIMIX.index == 80)  || (HIMIX.index == 89)  || (HIMIX.index == 98) || (HIMIX.index == 107) || (HIMIX.index == 116) || (HIMIX.index == 125))
	{
		//������°
		HIMIX.temp16 = HIMIX.temp32 / 1000;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 1000;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� �ϰ�����
	else if((HIMIX.index == 81)  || (HIMIX.index == 90)  || (HIMIX.index == 99) || (HIMIX.index == 108) || (HIMIX.index == 117) || (HIMIX.index == 126))
	{
		//�ϰ���°
		HIMIX.temp16 = HIMIX.temp32 / 100;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 100;
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� ��������
	else if((HIMIX.index == 82)  || (HIMIX.index == 91)  || (HIMIX.index == 100) || (HIMIX.index == 109) || (HIMIX.index == 118) || (HIMIX.index == 127))
	{
		//������°
		HIMIX.temp16 = HIMIX.temp32 / 10;
		
		if(HIMIX.number_start)
		HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
		
		else
		{
			if(HIMIX.temp16 == 0)
			HIMIX.tx_buffer[HIMIX.buffer_index] = 0;
			
			else
			{
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp16];
				HIMIX.number_start = 1;
				
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
					HIMIX.minus_flag = 0;
				}
			}
		}
		
		HIMIX.temp32 %= 10;
		
		if((HIMIX.index == 82) || (HIMIX.index == 91) || (HIMIX.index == 118)|| (HIMIX.index == 127))
		{
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
		}
		
		++HIMIX.buffer_index;
		++HIMIX.index;
	}
	
	// ���� ��ȩ����
	else if((HIMIX.index == 83)  || (HIMIX.index == 92)  || (HIMIX.index == 101) || (HIMIX.index == 110) || (HIMIX.index == 119) || (HIMIX.index == 128))
	{		
		if(HIMIX.index == 83)
		{
			//��ȩ��°
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
		
			if(HIMIX.minus_flag)
			{
				HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
				HIMIX.minus_flag = 0;
			}
		
			if(DISPLAY.q3 < 0)
			{
				HIMIX.minus_flag = 1;			
				HIMIX.temp32 = (unsigned long)(DISPLAY.q3 * -10);
			}
		
			else
			{
				HIMIX.minus_flag = 0;
				HIMIX.temp32 = (unsigned long)(DISPLAY.q3 * 10);
			}
			
			HIMIX.number_start = 0;
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 92)
		{
			//��ȩ��°
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
		
			if(HIMIX.minus_flag)
			{
				HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
				HIMIX.minus_flag = 0;
			}
			
			
			if(ACCUMULATION.energy_p < 0)
			{
				HIMIX.minus_flag = 1;			
				HIMIX.temp32 = (unsigned long)(ACCUMULATION.energy_p * -1);
			}
		
			else
			{
				HIMIX.minus_flag = 0;
				HIMIX.temp32 = (unsigned long)ACCUMULATION.energy_p;
			}
			
			HIMIX.number_start = 0;
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 101)
		{
			//��ȩ��°
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
		
			if(HIMIX.minus_flag)
			{
				HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
				HIMIX.minus_flag = 0;
			}
			
			
			if(ACCUMULATION.energy_q < 0)
			{
				HIMIX.minus_flag = 1;			
				HIMIX.temp32 = (unsigned long)(ACCUMULATION.energy_q * -1);
			}
		
			else
			{
				HIMIX.minus_flag = 0;
				HIMIX.temp32 = (unsigned long)ACCUMULATION.energy_q;
			}
			
			HIMIX.number_start = 0;
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 110)
		{
			//��ȩ��°
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			HIMIX.tx_buffer[HIMIX.buffer_index] |= 0x80;
		
			if(HIMIX.minus_flag)
			{
				HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
				HIMIX.minus_flag = 0;
			}
			
			HIMIX.minus_flag = 0;
			HIMIX.temp32 = (unsigned long)(MEASUREMENT.frequency * 10);
			
			HIMIX.number_start = 0;
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 119)
		{
			//��ȩ��°
			// ����� ������ ��ȣ
			HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			
		
			if(HIMIX.minus_flag)
			{
				HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
				HIMIX.minus_flag = 0;
			}
			
			if(DISPLAY.pf3 < 0)
			{
				HIMIX.minus_flag = 1;			
				HIMIX.temp32 = (unsigned long)(DISPLAY.pf3 * -10);
			}
		
			else
			{
				HIMIX.minus_flag = 0;
				HIMIX.temp32 = (unsigned long)(DISPLAY.pf3 * 10);
			}
			
			HIMIX.number_start = 0;
			
			++HIMIX.buffer_index;
			++HIMIX.index;
		}
		
		else if(HIMIX.index == 128)
		{
			if(HIMIX.crc_count == 0)
			{
				//��ȩ��°
				// ����� ������ ��ȣ
				HIMIX.tx_buffer[HIMIX.buffer_index] = himix_number[HIMIX.temp32];
			
		
				if(HIMIX.minus_flag)
				{
					HIMIX.tx_buffer[HIMIX.buffer_index - 1] = 0x40;
					HIMIX.minus_flag = 0;
				}
			
				HIMIX.crc[0] = 0;
				HIMIX.crc[1] = 0;
				
				HIMIX.crc_count = 1;
			}
			
			//for(i=1;i<56;i++)
			//himix_crc(localTxBufB[i]);
	
			himix_crc(HIMIX.tx_buffer[HIMIX.crc_count]);
			
			++HIMIX.crc_count;
			
			if(HIMIX.crc_count == 56)
			{
				//�߻�
				
				
				HIMIX.index = 0;
			}
		}
	}
	HIMIX.timer = 0;
}


void himix_crc(unsigned int ar_data)
{
	unsigned int k;
	unsigned char CRC_BL,CRC_BH;

	CRC_BL = 0;

	// xor conversion
	for(k=0;k<8;k++)
	{       
		if(((ar_data >> k) & 0x01) != ((HIMIX.crc[1] >> k) & 0x01))
		{
		  CRC_BL += 0x01 << k;
		}
	}

	CRC_BH = CRC_High[CRC_BL];   

	HIMIX.crc[1] = 0;

	// xor conversion
	for(k = 0; k < 8; k++)
	{       
		if(((CRC_BH >> k) & 0x01) != ((HIMIX.crc[0] >> k) & 0x01))
		{
		  HIMIX.crc[1]+=0x01 << k;
		}
	}

	HIMIX.crc[0] = CRC_Low[CRC_BL];
}

// float�� 8��Ʈ fram �Ǵ� �ø��� ���� ó���� �� ��� �а� ����
// *ar_value   - ���� ����� ������ �ּ�
// *ar_address - destination �ּ� 
// ar_write - �б�/���� ���� 
void float_to_8bit_fram(void *ar_value, unsigned int *ar_address, unsigned int ar_write)
{
	// *ar_value �� ����Ű�� �ּҿ� ����� ���� �Ӽ��� �츮�� float���� �˰� ����
	// �ٵ� ������ ����ȯ �ؼ� ����Ʈ������ �ɰ��� �ϴµ� �̸��� cpu�� ����ȯ�� raw data �״�� �ɰ���� �Ѵ�.
	// �̰� �����ͷ� ó���ؾ� �ϴµ� �ּҰ��� unsigned long ������ �����Ǿ� ���� - 0x200000 ~ 0x21FFFF
	// �� ������ ���� �ʴ� void �����ͷ� �� �Լ��� ������ �ϰ�, �� �Լ����� ������ raw ������ �� �� �ְ� �ּ� ������ ���ش�
	unsigned long *point_long;
	unsigned int temp;
	
	// ar_value�� �ּҸ� point_long ������ ������ �����Ͽ� ������ �ϰ� �Ѵ�.
	point_long = ar_value;
	
	// *ar_address �� ������ �� ���� write �� ���
	if(ar_write)
	{
		// ��¶�ų� ����Ʈ ������ �װ� ����Ʈ�� �ɰ��� *ar_address �� ������ �� ������ 4��
		*ar_address = (*point_long >> 24) & 0x00ff;        // �ֻ��� ����Ʈ
		*(ar_address + 1) = (*point_long >> 16) & 0x00ff;  // ������ ����Ʈ
		*(ar_address + 2) = (*point_long >> 8) & 0x00ff;   // ������ ����Ʈ
		*(ar_address + 3) = *point_long & 0x00ff;          // ������ ����Ʈ
	}
	
	// *ar_address �� ������ �� �� ���� �װ� ����Ʈ ���� �о� *ar_value�� ������ �� ���� ������ ���. ���� �ý��ۿ����� fram �ۿ� ������ ����
	else
	{
		
		*point_long = *ar_address & 0x00ff; // *ar_address ù��° �о��
		*point_long <<= 24; // �ֻ��� ����Ʈ�� shift
		
		temp = *(ar_address + 1) & 0x00ff;  // *ar_address �ι�° �о��
		*point_long |= (unsigned long)(temp) << 16; // ������ ����Ʈ�� shift
		
		temp = *(ar_address + 2) & 0x00ff; // *ar_address ����° �о��
		*point_long |= (unsigned long)(temp) << 8; // ������ ����Ʈ�� shift
		
		temp = *(ar_address + 3) & 0x00ff;  // *ar_address �׹�° �о��
		*point_long |= (unsigned long)temp; // ������ ����Ʈ�� shift
	}
}

// ar_write - �б�/���� ���� 
void float_to_integer(float ar_value, unsigned int *ar_address, float scale)
{
	unsigned long l_temp;
	
	// ar_value�� �ּҸ� point_long ������ ������ �����Ͽ� ������ �ϰ� �Ѵ�.
	l_temp = (unsigned long)(ar_value * scale);
	
	*ar_address =       (l_temp >> 24) & 0x00ff;  // �ֻ��� ����Ʈ
	*(ar_address + 1) = (l_temp >> 16) & 0x00ff;  // ������ ����Ʈ
	*(ar_address + 2) = (l_temp >> 8) & 0x00ff;   // ������ ����Ʈ
	*(ar_address + 3) =  l_temp & 0x00ff;         // ������ ����Ʈ
}

void float_to_integer2(float ar_value, unsigned int *ar_address, float scale)
{
	unsigned long l_temp;
	
	// ar_value�� �ּҸ� point_long ������ ������ �����Ͽ� ������ �ϰ� �Ѵ�.
	l_temp = (unsigned long)(ar_value * scale);
	
	*ar_address = (l_temp >> 8) & 0x00ff;   // �ֻ��� ����Ʈ
	*(ar_address + 1) =  l_temp & 0x00ff;   // ������ ����Ʈ
}
	
// raw data�� �����ϴ� ��� �����غ���
// tcs/ccs ����
// ar_index - ����� tcs, ccs ����
//            0-tcs, 1-ccs
// do ����κ� ���� �� confirm
//void supervision_relay(unsigned int ar_index)
//{
//	// ������ ������ �۾�����
//	if(SUPERVISION.monitoring[ar_index] < SUPERVISION.pickup[ar_index])
//	{
//		// ������ pickup
//		if(SUPERVISION.status[ar_index] == RELAY_NORMAL)
//		SUPERVISION.status[ar_index] = RELAY_DETECT;
//		
//		// pickup
//		else if(SUPERVISION.status[ar_index] == RELAY_DETECT)
//		{
//			//ī���� ����
//			++SUPERVISION.pickup_count[ar_index];
//			
//			// ������ ���۽ð��̻�Ǹ�
//			if(SUPERVISION.pickup_count[ar_index] > SUPERVISION.time[ar_index])
//			{
//				// do ����
//				//86�� �ϴ� �����
//				SYSTEM.do_control &= 0xff9f;
//				SYSTEM.do_control |= SUPERVISION.do_output[ar_index]; // ������ do ���� ��Ʈ ��
//				
//				SUPERVISION.do_output_off[ar_index] = SUPERVISION.do_output[ar_index];
//							
//				SUPERVISION.status[ar_index] = RELAY_PICKUP;
//				
//				
//				// event				
//			}
//		}
//				
//		else
//		{
//			SUPERVISION.status[ar_index] = RELAY_NORMAL;
//			SUPERVISION.pickup_count[ar_index] = 0;
//					
//			// do ����
//			do_release(&SUPERVISION.do_output_off[ar_index]);
//			//SYSTEM.do_control &= DIGITAL_OUTPUT.property;
//		}
//	}
//}

// ��] "TDD(Total Demand Distortion)�� ���� ���� �ִ��� �װ��� ���ϸ� ��� ���ϴ°�����"
//��]   THD[%] = {����������/�⺻������}*100 = {root(I2^2+I3^2+,,,I50^2)/I1}*100
//
//       TDD[%] = {����������/�⺻������(15~30�а� ������ ���� �ִ�ġ)}*100 �Դϴ�.
//
//        ���� "1219511"���� ���Ŀ� ���� ����� �½��ϴ�.
//
// 
//
//��] "������ ���� �� ������ ������ ���̿� ������ ���⼳�� �ǿ����� �ִ��� �ñ��մϴ�"
//
//��] ������������ ���Ͽ��� �߻��ϴ� ������������ ���Ͽ� �߻��ϸ� �������Ǵ����� ����մϴ�.
//
//      ���� ���Ͽ��� �߻��ϴ� ������������ ���� ���⼳�� ��ġ�� ������ ��κ��Դϴ�.
//
//      ��������������� ���� ������⵿����, ��������������� ���� OCGR ������ ���� ��ǥ��������.^^

// ������ ���
void harmonics(void)
{
	// Ia sample backup 
	if(HARMONICS.index == 0)
	{
		// display �������� �̸�
		if(DISPLAY.rms_value[Ia] < DISPLAY_CURRENT_MIN)
		{
			HARMONICS.ia[0] = 0;
			HARMONICS.ia[1] = 0;
			HARMONICS.ia[2] = 0;
			HARMONICS.ia[3] = 0;
			HARMONICS.ia[4] = 0;
			HARMONICS.ia[5] = 0;
			
			HARMONICS.index = 16;
		}
		else
		harmonic_sample_backup(0); // Ia 36���� ����
	}
	
	
	// Ia �⺻�� real ���� ���
	else if(HARMONICS.index == 1)
	{		
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_1st_cos);
	}
	
	// Ia �⺻�� imag ���� ���
	else if(HARMONICS.index == 2)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_1st_sin);
	}
	
	// Ia �⺻�� rms
	else if(HARMONICS.index == 3)
	{
		HARMONICS.base = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));
	}
	
	// Ia 3���� real ���� ���
	else if(HARMONICS.index == 4)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_3rd_cos);
	}
	
	// Ia 3���� imag ���� ���
	else if(HARMONICS.index == 5)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_3rd_sin);
	}
	
	// Ia 3���� rms
	else if(HARMONICS.index == 6)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

	  // �⺻�� ��� ���� ���
	  HARMONICS.ia[0] = HARMONICS.float_temp / HARMONICS.base;

		// TDD/THD �̸����
		HARMONICS.ftemp[0] = HARMONICS.ia[0] * HARMONICS.ia[0];

		// �⺻�� ��� %�� ȯ��
		HARMONICS.ia[0] *= 100;
	}
	
	// Ia 5���� real ���� ���
	else if(HARMONICS.index == 7)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_5th_cos);
	}
	
	// Ia 5���� imag ���� ���
	else if(HARMONICS.index == 8)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_5th_sin);
	}
	
	// Ia 5���� rms
	else if(HARMONICS.index == 9)
	{
		// 3���� �ּ� ����
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ia[1] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[1] = HARMONICS.ia[1] * HARMONICS.ia[1];

		HARMONICS.ia[1] *= 100;
	}
	
	// Ia 7���� real ���� ���  -> ���� ���� ����
	else if(HARMONICS.index == 10)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_7th_cos);
	}
	
	// Ia 7���� imag ���� ���
	else if(HARMONICS.index == 11)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_7th_sin);
	}
	
	// Ia 7���� rms
	else if(HARMONICS.index == 12)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ia[2] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[2] = HARMONICS.ia[2] * HARMONICS.ia[2];

		HARMONICS.ia[2] *= 100;
	}
	
	// Ia 9���� real ���� ���
	else if(HARMONICS.index == 13)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_9th_cos);
	}
	
	// Ia 9���� imag ���� ���
	else if(HARMONICS.index == 14)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_9th_sin);
	}
	
	// Ia 9�� rms
	else if(HARMONICS.index == 15)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ia[3] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[3] = HARMONICS.ia[3] * HARMONICS.ia[3];

		HARMONICS.ia[3] *= 100;
	}
	
	// ���� 11���� �䱸 �� ��κп� ���ó�� �߰���
	// �ε��� �þ���� ������ ���⸸ �ϴ°Ŵ� ���� �� ����
	
	// Ia THD/TDD  5us
	else if(HARMONICS.index == 16)
	{
		HARMONICS.float_temp = sqrt(HARMONICS.ftemp[0] + HARMONICS.ftemp[1] + HARMONICS.ftemp[2] + HARMONICS.ftemp[3]);

		HARMONICS.ia[4] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ia[5] = HARMONICS.float_temp / HARMONICS.ia_max;

		HARMONICS.ia[4] *= 100;
		HARMONICS.ia[5] *= 100;

		if(HARMONICS.base > HARMONICS.ia_max_save)
		HARMONICS.ia_max_save = HARMONICS.base;
	}
	
	// Ib sample backup
	else if(HARMONICS.index == 17)
	{
		//2.5us
		// display �������� �̸�
		if(DISPLAY.rms_value[Ib] < DISPLAY_CURRENT_MIN)
		{
			HARMONICS.ib[0] = 0;
			HARMONICS.ib[1] = 0;
			HARMONICS.ib[2] = 0;
			HARMONICS.ib[3] = 0;
			HARMONICS.ib[4] = 0;
			HARMONICS.ib[5] = 0;
			
			HARMONICS.index = 33;
		}
		else
		harmonic_sample_backup(1);
	}
	
	// Ib �⺻�� real ���� ���
	else if(HARMONICS.index == 18)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_1st_cos);
	}
	
	// Ib �⺻�� imag ���� ���
	else if(HARMONICS.index == 19)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_1st_sin);
	}
	
	// Ib �⺻�� rms
	else if(HARMONICS.index == 20)
	{
		HARMONICS.base = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));
	}
	
	// Ib 3���� real ���� ���
	else if(HARMONICS.index == 21)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_3rd_cos);
	}
	
	// Ib 3���� imag ���� ���
	else if(HARMONICS.index == 22)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_3rd_sin);
	}
	
	// Ib 3���� rms
	else if(HARMONICS.index == 23)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));
	    
		HARMONICS.ib[0] = HARMONICS.float_temp / HARMONICS.base;
		
		HARMONICS.ftemp[0] = HARMONICS.ib[0] * HARMONICS.ib[0];
		
		HARMONICS.ib[0] *= 100;
	}
	
	// Ib 5���� real ���� ���
	else if(HARMONICS.index == 24)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_5th_cos);
	}
	
	// Ib 5���� imag ���� ���
	else if(HARMONICS.index == 25)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_5th_sin);
	}
	
	// Ib 5���� rms
	else if(HARMONICS.index == 26)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ib[1] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[1] = HARMONICS.ib[1] * HARMONICS.ib[1];

		HARMONICS.ib[1] *= 100;
	}
	
	// Ib 7���� real ���� ���
	else if(HARMONICS.index == 27)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_7th_cos);
	}
	
	// Ib 7���� imag ���� ���
	else if(HARMONICS.index == 28)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_7th_sin);
	}
	
	// Ib 7���� rms
	else if(HARMONICS.index == 29)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ib[2] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[2] = HARMONICS.ib[2] * HARMONICS.ib[2];

		HARMONICS.ib[2] *= 100;
	}
	
	// Ib 9���� real ���� ���
	else if(HARMONICS.index == 30)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_9th_cos);
	}
	
	// Ib 9���� imag ���� ���
	else if(HARMONICS.index == 31)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_9th_sin);
	}
	
	// Ib 9���� rms
	else if(HARMONICS.index == 32)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ib[3] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[3] = HARMONICS.ib[3] * HARMONICS.ib[3];

		HARMONICS.ib[3] *= 100;
	}

	// ���� 11���� �䱸 �� ��κп� ���ó�� �߰���
	// �ε��� �þ���� ������ ���⸸ �ϴ°Ŵ� ���� �� ����

	// Ib THD/TDD
	else if(HARMONICS.index == 33)
	{
		HARMONICS.float_temp = sqrt(HARMONICS.ftemp[0] + HARMONICS.ftemp[1] + HARMONICS.ftemp[2] + HARMONICS.ftemp[3]);
		
		HARMONICS.ib[4] = HARMONICS.float_temp / HARMONICS.base;
		
		HARMONICS.ib[5] = HARMONICS.float_temp / HARMONICS.ib_max;
		
		HARMONICS.ib[4] *= 100;
		HARMONICS.ib[5] *= 100;
		
		if(HARMONICS.base > HARMONICS.ib_max_save)
		HARMONICS.ib_max_save = HARMONICS.base;
	}
	
	// Ic sample backup
	else if(HARMONICS.index == 34)
	{
		//2.5us
		if(DISPLAY.rms_value[Ic] < DISPLAY_CURRENT_MIN)
		{
			HARMONICS.ic[0] = 0;
			HARMONICS.ic[1] = 0;
			HARMONICS.ic[2] = 0;
			HARMONICS.ic[3] = 0;
			HARMONICS.ic[4] = 0;
			HARMONICS.ic[5] = 0;
			
			HARMONICS.index = 51;
		}
		else
		harmonic_sample_backup(2);
	}
	
	// Ic �⺻�� real ���� ���
	else if(HARMONICS.index == 35)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_1st_cos);
	}
	
	// Ic �⺻�� imag ���� ���
	else if(HARMONICS.index == 36)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_1st_sin);
	}
	
	// Ic �⺻�� rms
	else if(HARMONICS.index == 37)
	{
		HARMONICS.base = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));
	}
	
	// Ic 3���� real ���� ���
	else if(HARMONICS.index == 38)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_3rd_cos);
	}
	
	// Ic 3���� imag ���� ���
	else if(HARMONICS.index == 39)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_3rd_sin);
	}
	
	// Ic 3���� rms
	else if(HARMONICS.index == 40)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ic[0] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[0] = HARMONICS.ic[0] * HARMONICS.ic[0];

		HARMONICS.ic[0] *= 100;
	}
	
	// Ic 5���� real ���� ���
	else if(HARMONICS.index == 41)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_5th_cos);
	}
	
	// Ic 5���� imag ���� ���
	else if(HARMONICS.index == 42)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_5th_sin);
	}
	
	// Ic 5���� rms
	else if(HARMONICS.index == 43)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ic[1] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[1] = HARMONICS.ic[1] * HARMONICS.ic[1];

		HARMONICS.ic[1] *= 100;
	}
	
	// Ic 7���� real ���� ���
	else if(HARMONICS.index == 44)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_7th_cos);
	}
	
	// Ic 7���� imag ���� ���
	else if(HARMONICS.index == 45)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_7th_sin);
	}
	
	// Ic 7���� rms
	else if(HARMONICS.index == 46)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ic[2] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[2] = HARMONICS.ic[2] * HARMONICS.ic[2];

		HARMONICS.ic[2] *= 100;
	}
	
	// Ic 9���� real ���� ���
	else if(HARMONICS.index == 47)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.real, harmonics_9th_cos);
	}
	
	// Ic 9�� imag
	else if(HARMONICS.index == 48)
	{
		//8us
		harmonic_real_imag_calculation(&HARMONICS.imag, harmonics_9th_sin);
	}
	
	// Ic 9�� rms
	else if(HARMONICS.index == 49)
	{
		HARMONICS.float_temp = sqrt((HARMONICS.real * HARMONICS.real) + (HARMONICS.imag * HARMONICS.imag));

		HARMONICS.ic[3] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ftemp[3] = HARMONICS.ic[3] * HARMONICS.ic[3];

		HARMONICS.ic[3] *= 100;
	}
	
	// Ic THD/TDD
	else if(HARMONICS.index == 50)
	{
		HARMONICS.float_temp = sqrt(HARMONICS.ftemp[0] + HARMONICS.ftemp[1] + HARMONICS.ftemp[2] + HARMONICS.ftemp[3]);

		HARMONICS.ic[4] = HARMONICS.float_temp / HARMONICS.base;

		HARMONICS.ic[5] = HARMONICS.float_temp / HARMONICS.ic_max;

		HARMONICS.ic[4] *= 100;
		HARMONICS.ic[5] *= 100;

		if(HARMONICS.base > HARMONICS.ic_max_save)
		HARMONICS.ic_max_save = HARMONICS.base;
	}
	
	//Ia,Ib,Ic max
	else
	{
		++HARMONICS.timer_15min;
		
		//about 15min
		if(HARMONICS.timer_15min == 900)
		{
			//���� �ִ� �� ��ü
			HARMONICS.ia_max = HARMONICS.ia_max_save;
			HARMONICS.ib_max = HARMONICS.ib_max_save;
			HARMONICS.ic_max = HARMONICS.ic_max_save;
			
			HARMONICS.ia_max_save = 0;
			HARMONICS.ib_max_save = 0;
			HARMONICS.ic_max_save = 0;
			
			HARMONICS.timer_15min = 0;
		}
	}
	
	++HARMONICS.index;

	if(HARMONICS.index > 51)
	HARMONICS.index = 0;
	
	HARMONICS.timer = 0;
}


// ������ ����� ���� �̸� �����͸� �����
// ar_channel - ����� ���� ä�� ����
// 0-Ia, 1-Ib, 2-Ic
void harmonic_sample_backup(unsigned int ar_channel)
{
	HARMONICS.sample[0] = SAMPLE.pre_36_buffer[ar_channel][0];
	HARMONICS.sample[1] = SAMPLE.pre_36_buffer[ar_channel][1];
	HARMONICS.sample[2] = SAMPLE.pre_36_buffer[ar_channel][2];
	HARMONICS.sample[3] = SAMPLE.pre_36_buffer[ar_channel][3];
	HARMONICS.sample[4] = SAMPLE.pre_36_buffer[ar_channel][4];
	HARMONICS.sample[5] = SAMPLE.pre_36_buffer[ar_channel][5];
	HARMONICS.sample[6] = SAMPLE.pre_36_buffer[ar_channel][6];
	HARMONICS.sample[7] = SAMPLE.pre_36_buffer[ar_channel][7];
	HARMONICS.sample[8] = SAMPLE.pre_36_buffer[ar_channel][8];
	HARMONICS.sample[9] = SAMPLE.pre_36_buffer[ar_channel][9];
	HARMONICS.sample[10] = SAMPLE.pre_36_buffer[ar_channel][10];
	HARMONICS.sample[11] = SAMPLE.pre_36_buffer[ar_channel][11];
	HARMONICS.sample[12] = SAMPLE.pre_36_buffer[ar_channel][12];
	HARMONICS.sample[13] = SAMPLE.pre_36_buffer[ar_channel][13];
	HARMONICS.sample[14] = SAMPLE.pre_36_buffer[ar_channel][14];
	HARMONICS.sample[15] = SAMPLE.pre_36_buffer[ar_channel][15];
	HARMONICS.sample[16] = SAMPLE.pre_36_buffer[ar_channel][16];
	HARMONICS.sample[17] = SAMPLE.pre_36_buffer[ar_channel][17];
	HARMONICS.sample[18] = SAMPLE.pre_36_buffer[ar_channel][18];
	HARMONICS.sample[19] = SAMPLE.pre_36_buffer[ar_channel][19];
	HARMONICS.sample[20] = SAMPLE.pre_36_buffer[ar_channel][20];
	HARMONICS.sample[21] = SAMPLE.pre_36_buffer[ar_channel][21];
	HARMONICS.sample[22] = SAMPLE.pre_36_buffer[ar_channel][22];
	HARMONICS.sample[23] = SAMPLE.pre_36_buffer[ar_channel][23];
	HARMONICS.sample[24] = SAMPLE.pre_36_buffer[ar_channel][24];
	HARMONICS.sample[25] = SAMPLE.pre_36_buffer[ar_channel][25];
	HARMONICS.sample[26] = SAMPLE.pre_36_buffer[ar_channel][26];
	HARMONICS.sample[27] = SAMPLE.pre_36_buffer[ar_channel][27];
	HARMONICS.sample[28] = SAMPLE.pre_36_buffer[ar_channel][28];
	HARMONICS.sample[29] = SAMPLE.pre_36_buffer[ar_channel][29];
	HARMONICS.sample[30] = SAMPLE.pre_36_buffer[ar_channel][30];
	HARMONICS.sample[31] = SAMPLE.pre_36_buffer[ar_channel][31];
	HARMONICS.sample[32] = SAMPLE.pre_36_buffer[ar_channel][32];
	HARMONICS.sample[33] = SAMPLE.pre_36_buffer[ar_channel][33];
	HARMONICS.sample[34] = SAMPLE.pre_36_buffer[ar_channel][34];
	HARMONICS.sample[35] = SAMPLE.pre_36_buffer[ar_channel][35];
}

void harmonic_real_imag_calculation(float *ar_temp, float const *ar_table)
{
	*ar_temp = 0;
	
	*ar_temp += (float)(HARMONICS.sample[0] * ar_table[0]);
	*ar_temp += (float)(HARMONICS.sample[1] * ar_table[1]);
	*ar_temp += (float)(HARMONICS.sample[2] * ar_table[2]);
	*ar_temp += (float)(HARMONICS.sample[3] * ar_table[3]);
	*ar_temp += (float)(HARMONICS.sample[4] * ar_table[4]);
	*ar_temp += (float)(HARMONICS.sample[5] * ar_table[5]);
	*ar_temp += (float)(HARMONICS.sample[6] * ar_table[6]);
	*ar_temp += (float)(HARMONICS.sample[7] * ar_table[7]);
	*ar_temp += (float)(HARMONICS.sample[8] * ar_table[8]);
	*ar_temp += (float)(HARMONICS.sample[9] * ar_table[9]);
	*ar_temp += (float)(HARMONICS.sample[10] * ar_table[10]);
	*ar_temp += (float)(HARMONICS.sample[11] * ar_table[11]);
	*ar_temp += (float)(HARMONICS.sample[12] * ar_table[12]);
	*ar_temp += (float)(HARMONICS.sample[13] * ar_table[13]);
	*ar_temp += (float)(HARMONICS.sample[14] * ar_table[14]);
	*ar_temp += (float)(HARMONICS.sample[15] * ar_table[15]);
	*ar_temp += (float)(HARMONICS.sample[16] * ar_table[16]);
	*ar_temp += (float)(HARMONICS.sample[17] * ar_table[17]);
	*ar_temp += (float)(HARMONICS.sample[18] * ar_table[18]);
	*ar_temp += (float)(HARMONICS.sample[19] * ar_table[19]);
	*ar_temp += (float)(HARMONICS.sample[20] * ar_table[20]);
	*ar_temp += (float)(HARMONICS.sample[21] * ar_table[21]);
	*ar_temp += (float)(HARMONICS.sample[22] * ar_table[22]);
	*ar_temp += (float)(HARMONICS.sample[23] * ar_table[23]);
	*ar_temp += (float)(HARMONICS.sample[24] * ar_table[24]);
	*ar_temp += (float)(HARMONICS.sample[25] * ar_table[25]);
	*ar_temp += (float)(HARMONICS.sample[26] * ar_table[26]);
	*ar_temp += (float)(HARMONICS.sample[27] * ar_table[27]);
	*ar_temp += (float)(HARMONICS.sample[28] * ar_table[28]);
	*ar_temp += (float)(HARMONICS.sample[29] * ar_table[29]);
	*ar_temp += (float)(HARMONICS.sample[30] * ar_table[30]);
	*ar_temp += (float)(HARMONICS.sample[31] * ar_table[31]);
	*ar_temp += (float)(HARMONICS.sample[32] * ar_table[32]);
	*ar_temp += (float)(HARMONICS.sample[33] * ar_table[33]);
	*ar_temp += (float)(HARMONICS.sample[34] * ar_table[34]);
	*ar_temp += (float)(HARMONICS.sample[35] * ar_table[35]);
}

//  0,  1,  2,  3,   4,   5,  6,  7,  8,  9
// Ia, Ib, Ic, In, In2, ZCT, Va, Vb, Vc, Vn
void measure_display(void) //����, ���� ��
{
	DISPLAY.rms_value_sum[DISPLAY.index] += MEASUREMENT.rms_value[DISPLAY.index];
	if(DISPLAY.sum_count == 49)	// 50�� �����Ǿ��� ���
	{
		DISPLAY.rms_value_temp[DISPLAY.index] = DISPLAY.rms_value_sum[DISPLAY.index] / 50.;	// 50�� ��հ� ���
		if((DISPLAY.index > 5) && (DISPLAY.index < 10)) //���� ä��(6,7,8,9)
		{
			if(DISPLAY.rms_value_temp[DISPLAY.index] < DISPLAY_VOLTAGE_MIN)	{DISPLAY.rms_value_temp[DISPLAY.index] = 0;} //���� ä�� ���� ���ΰ� (1.9V)
		}
		else if(DISPLAY.index < 4) //���� ä��(0,1,2,3)
		{
			if(DISPLAY.rms_value_temp[DISPLAY.index] < DISPLAY_CURRENT_MIN)	{DISPLAY.rms_value_temp[DISPLAY.index] = 0;} //���� ä�� ���� ���ΰ� (0.03A)
		}
		else if(DISPLAY.index == 5)
		{
			if(DISPLAY.rms_value_temp[DISPLAY.index] < DISPLAY_Io_MIN)	{DISPLAY.rms_value_temp[DISPLAY.index] = 0;} //���� ���� ä�� ���� ���ΰ� (0.2mA)
		}

		DISPLAY.rms_value[DISPLAY.index] = DISPLAY.rms_value_temp[DISPLAY.index] * DISPLAY.multipllier[DISPLAY.index]; // CT(PT) ratio ������ //���� ����,���� display ��
		DISPLAY.rms_Iavg_value = ((DISPLAY.rms_value[0] + DISPLAY.rms_value[1] + DISPLAY.rms_value[2]) / 3.0); //���� ���� ��� display ��
		DISPLAY.rms_Vavg_value = ((DISPLAY.rms_value[6] + DISPLAY.rms_value[7] + DISPLAY.rms_value[8]) / 3.0); //���� ���� ��� display ��

//	DISPLAY.V1_value = MEASUREMENT.V1_value * CPT.pt_ratio; // PT ratio ������
//	DISPLAY.V2_value = MEASUREMENT.V2_value * CPT.pt_ratio; // PT ratio ������
		if(MEASUREMENT.V1_value < 2) //���� ä�� ���� ���ΰ� (2V) // ������ 2V �̳����� ����... ���� ���е� ���� �ʿ�
		{
			DISPLAY.V1_value = 0; //���� ���� ���� display ��
		}
		else 
		{
			DISPLAY.V1_value = MEASUREMENT.V1_value * CPT.pt_ratio; // PT ratio ������ //���� ���� ���� display ��
		}
		if(MEASUREMENT.V2_value < 2) //���� ä�� ���� ���ΰ� (2V)
		{
			DISPLAY.V2_value = 0; //���� ���� ���� display ��
		}
		else 
		{
			DISPLAY.V2_value = MEASUREMENT.V2_value * CPT.pt_ratio; // PT ratio ������ //���� ���� ���� display ��
		}

		if(MEASUREMENT.I1_value < 0.03) //���� ä�� ���� ���ΰ� (0.03A) // ������ �̳����� ����... ���� ���е� ���� �ʿ�
		{
			DISPLAY.I1_value = 0; //���� ���� ���� display ��
		}
		else 
		{
			DISPLAY.I1_value = MEASUREMENT.I1_value * CPT.ct_ratio; // CT ratio ������ //���� ���� ���� display ��
		}
		if(MEASUREMENT.I2_value < 0.03) //���� ä�� ���� ���ΰ� (0.03A)
		{
			DISPLAY.I2_value = 0; //���� ���� ���� display ��
		}
		else 
		{
			DISPLAY.I2_value = MEASUREMENT.I2_value * CPT.ct_ratio; // CT ratio ������ //���� ���� ���� display ��
		}
		
		if(DISPLAY.index == 9)	// ����� �������к��� Ŭ������ MRAM�� ����(���� ��ġ ���� �ʿ�)
		{
			if(DISPLAY.rms_value[9] > DISPLAY.vo_max)
			{
				DISPLAY.vo_max = (unsigned long)DISPLAY.rms_value[9];

				//MRAM ����
				*(MRAM_Vo_MAX1) = (DISPLAY.vo_max >> 16) & 0xffff;
				*(MRAM_Vo_MAX2) = DISPLAY.vo_max & 0xffff;
			}
		}

		DISPLAY.rms_value_sum[DISPLAY.index] = 0;
	}
	++DISPLAY.index;
	if(DISPLAY.index == 10)
	{
		DISPLAY.index = 0;
		++DISPLAY.sum_count;				
		if(DISPLAY.sum_count == 50)	{DISPLAY.sum_count = 0;}
		DISPLAY.switching = 0x0001;	//measure_display(), measure_display2() �����ư��� ����϶�� �����ϴ�  flag
	}
}		

// ����
void measure2_display(void)
{
	//1.5us 
	//for(temp = 0; temp < 6; temp++)
	//DISPLAY.angle[temp] = 0.0;
	
	//200ns
	DISPLAY.angle[0] = 0.0;
	DISPLAY.angle[1] = 0.0;
	DISPLAY.angle[2] = 0.0;
	DISPLAY.angle[3] = 0.0;
	DISPLAY.angle[4] = 0.0;
	DISPLAY.angle[5] = 0.0;
	DISPLAY.angle[6] = 0.0;
	DISPLAY.angle[7] = 0.0;
	
	if(DISPLAY.rms_value[Va])	{DISPLAY.angle[0] = MEASUREMENT.angle[Va];}
	if(DISPLAY.rms_value[Vb])	{DISPLAY.angle[1] = MEASUREMENT.angle[Vb];}
	if(DISPLAY.rms_value[Vc])	{DISPLAY.angle[2] = MEASUREMENT.angle[Vc];}
	if(DISPLAY.rms_value[Vc])	{DISPLAY.angle[3] = MEASUREMENT.angle[Vn];}
	if(DISPLAY.rms_value[Ia])	{DISPLAY.angle[4] = MEASUREMENT.angle[Ia];}
	if(DISPLAY.rms_value[Ib])	{DISPLAY.angle[5] = MEASUREMENT.angle[Ib];}
	if(DISPLAY.rms_value[Ic])	{DISPLAY.angle[6] = MEASUREMENT.angle[Ic];}
	if(CORE.gr_select == NCT_SELECT)
	{
		if(DISPLAY.rms_value[In])	{DISPLAY.angle[7] = MEASUREMENT.angle[In];}
	}
	else
	{
		if(DISPLAY.rms_value[Is])	{DISPLAY.angle[7] = MEASUREMENT.angle[Is];}
	}
	
	// ���ͷ�Ʈ������ �������� ����ϰ� ������
	// ������ ���̴� ���� degree�� ȯ���Ŵ
	DISPLAY.angle[0] *= 57.29577951;  // 180/PI = 57.29577951
	DISPLAY.angle[1] *= 57.29577951;
	DISPLAY.angle[2] *= 57.29577951;
	DISPLAY.angle[3] *= 57.29577951;
	DISPLAY.angle[4] *= 57.29577951;
	DISPLAY.angle[5] *= 57.29577951;
	DISPLAY.angle[6] *= 57.29577951;
	DISPLAY.angle[7] *= 57.29577951;
	
	//Vbc
	DISPLAY.angle[1] -= DISPLAY.angle[0];
	if(DISPLAY.angle[1] < 0)	{DISPLAY.angle[1] += 360;}
	//Vca
	DISPLAY.angle[2] -= DISPLAY.angle[0];
	if(DISPLAY.angle[2] < 0)	{DISPLAY.angle[2] += 360;}
	//Vn
	DISPLAY.angle[3] -= DISPLAY.angle[0];
	if(DISPLAY.angle[3] < 0)	{DISPLAY.angle[3] += 360;}
	//Ia
	DISPLAY.angle[4] -= DISPLAY.angle[0];
	if(DISPLAY.angle[4] < 0)	{DISPLAY.angle[4] += 360;}
	//Ib
	DISPLAY.angle[5] -= DISPLAY.angle[0];
	if(DISPLAY.angle[5] < 0)	{DISPLAY.angle[5] += 360;}
	//Ic
	DISPLAY.angle[6] -= DISPLAY.angle[0];
	if(DISPLAY.angle[6] < 0)	{DISPLAY.angle[6] += 360;}
	//In or Is
	DISPLAY.angle[7] -= DISPLAY.angle[0];
	if(DISPLAY.angle[7] < 0)	{DISPLAY.angle[7] += 360;}
	//Vab�� ������ 0��
	DISPLAY.angle[0] = 0;

	DISPLAY.switching = 0x0000;
	TIMER.measurement = 0;
}


// 1�ʿ� �ѹ��� ���°��
void power_update(void)
{
	float float_temp = 0.0;
	
	// ���ͷ�Ʈ���� �⺻���� ����� ��ħ
	// ���⿡  0.01342814 * PT�� 
	//         0.012207403 * CT �� ���� ��
	// real �� ���� �� calibration factor ������
	// S�� S��� ��������� ����
	
	// raw PQ
	// 1�ʰ� 720�� �����Ǿ����Ƿ�, ����� ����
	// 0.00138s * 720 = 1s
	MEASUREMENT.Pa_value /= 720;
	MEASUREMENT.Pb_value /= 720;
	MEASUREMENT.Pc_value /= 720;
	
	MEASUREMENT.Qa_value /= 720;
	MEASUREMENT.Qb_value /= 720;
	MEASUREMENT.Qc_value /= 720;
	
	// V �Ǵ� I�� 0�̸� power, pf 0���� ����� ���� �߰�
	// �⺻�� ����, ���� �ּҰ� �̸��̸� display�� 0���� �ϱ�����
	if((MEASUREMENT.rms_value[Va] < 0.475) || (MEASUREMENT.rms_value[Ia] < 0.0475))
	{
		MEASUREMENT.Pa_value = 0.0;
		
		MEASUREMENT.Qa_value = 0.0;
	}
	
	if((MEASUREMENT.rms_value[Vb] < 0.475) || (MEASUREMENT.rms_value[Ib] < 0.0475))
	{
		MEASUREMENT.Pb_value = 0.0;
		
		MEASUREMENT.Qb_value = 0.0;
	}
	
	if((MEASUREMENT.rms_value[Vc] < 0.475) || (MEASUREMENT.rms_value[Ic] < 0.0475))
	{
		MEASUREMENT.Pc_value = 0.0;
		
		MEASUREMENT.Qc_value = 0.0;
	}
	
		
	
	// real PQ	
	MEASUREMENT.Pa_value *= DISPLAY.p_multipllier[0];
	MEASUREMENT.Qa_value *= DISPLAY.p_multipllier[0];
		
	MEASUREMENT.Pb_value *= DISPLAY.p_multipllier[1];
	MEASUREMENT.Qb_value *= DISPLAY.p_multipllier[1];
	
	MEASUREMENT.Pc_value *= DISPLAY.p_multipllier[2];
	MEASUREMENT.Qc_value *= DISPLAY.p_multipllier[2];
	
	
	// P/Qa
	DISPLAY.power_p[0] = (MEASUREMENT.Pa_value * CALIBRATION.Power_Cos[0]) - (MEASUREMENT.Qa_value * CALIBRATION.Power_Sin[0]);	
	DISPLAY.power_q[0] = (MEASUREMENT.Pa_value * CALIBRATION.Power_Sin[0]) + (MEASUREMENT.Qa_value * CALIBRATION.Power_Cos[0]);
	DISPLAY.power_s[0] = sqrt((DISPLAY.power_p[0] * DISPLAY.power_p[0]) + (DISPLAY.power_q[0] * DISPLAY.power_q[0]));
	
	DISPLAY.power_p[1] = (MEASUREMENT.Pb_value * CALIBRATION.Power_Cos[1]) - (MEASUREMENT.Qb_value * CALIBRATION.Power_Sin[1]);	
	DISPLAY.power_q[1] = (MEASUREMENT.Pb_value * CALIBRATION.Power_Sin[1]) + (MEASUREMENT.Qb_value * CALIBRATION.Power_Cos[1]);
	DISPLAY.power_s[1] = sqrt((DISPLAY.power_p[1] * DISPLAY.power_p[1]) + (DISPLAY.power_q[1] * DISPLAY.power_q[1]));
	
	DISPLAY.power_p[2] = (MEASUREMENT.Pc_value * CALIBRATION.Power_Cos[2]) - (MEASUREMENT.Qc_value * CALIBRATION.Power_Sin[2]);	
	DISPLAY.power_q[2] = (MEASUREMENT.Pc_value * CALIBRATION.Power_Sin[2]) + (MEASUREMENT.Qc_value * CALIBRATION.Power_Cos[2]);
	DISPLAY.power_s[2] = sqrt((DISPLAY.power_p[2] * DISPLAY.power_p[2]) + (DISPLAY.power_q[2] * DISPLAY.power_q[2]));
	
	
		
	
//	rma_bac[rmas_bac_count] = DISPLAY.power_q[0];
//	
//	++rmas_bac_count;
//	if(rmas_bac_count == 500)
//	rmas_bac_count = 0;
	
	
//	// pf
//	for(i = 0; i < 3; i++)
//	{
//		// 1��и�
//		if((DISPLAY.power_p[i] >= 0) && (DISPLAY.power_q[i] < 0))
//		{
//			j = 0x5555;
//			
//			float_temp = -1.0;
//		}
//		
//		// 2��и�
//		else if((DISPLAY.power_p[i] < 0) && (DISPLAY.power_q[i] < 0))
//		{
//			j = 0xaaaa;
//			
//			float_temp = -1.0;
//		}
//			
//		// 3��и�
//		else if((DISPLAY.power_p[i] < 0) && (DISPLAY.power_q[i] >= 0))
//		{
//			j = 0xaaaa;
//			
//			float_temp = 1.0;
//		}
//			
//		// 4��и�
//		else if((DISPLAY.power_p[i] >= 0) && (DISPLAY.power_q[i] >= 0))
//		{
//			j = 0x5555;
//			
//			float_temp = 1.0;
//		}
//		
//		DISPLAY.pf[i] = DISPLAY.power_p[i] / DISPLAY.power_s[i];
//		
//		DISPLAY.pf[i] *= float_temp;
//		
//		//k = i << 1;		
//	}
	
	
	
	// 3�� P,Q, S
	DISPLAY.p3 = DISPLAY.power_p[0] + DISPLAY.power_p[1] + DISPLAY.power_p[2];
	DISPLAY.q3 = DISPLAY.power_q[0] + DISPLAY.power_q[1] + DISPLAY.power_q[2];
	//float_temp2 = sqrt((float_temp * float_temp) + (float_temp1 * float_temp1));
	
	float_temp = DISPLAY.power_s[0] + DISPLAY.power_s[1] + DISPLAY.power_s[2];
	
//	if(TRANSFORMER.pt_wiring == P3W3)
//	{		
		DISPLAY.p3 /= 1.732050807569;
		DISPLAY.q3 /= 1.732050807569;
		float_temp  /= 1.732050807569;
//	}
	
	
	
	DISPLAY.pf3 = DISPLAY.p3 / float_temp;
	
	
	

////	// 3pf
////	// 1��и�
//////	if((float_temp >= 0) && (float_temp1 < 0))
//////	{
//////		j = 0x5555;
//////			
//////		float_temp2 *= -1.0;
//////	}
//////		
//////	// 2��и�
//////	else if((float_temp < 0) && (float_temp1 < 0))
//////	{
//////		j = 0xaaaa;
//////			
//////		float_temp2 *= -1.0;
//////	}
//////			
//////	// 3��и�
//////	else if((float_temp < 0) && (float_temp1 >= 0))
//////	{
//////		j = 0xaaaa;		
//////	}
//////			
//////	// 4��и�
//////	else if((float_temp2 >= 0) && (float_temp3 >= 0))
//////	{
//////		j = 0x5555;		
//////	}
//////	
//////	FRAM_Access(&float_temp2, Pf, 2);
//////				
//////	FRAM_Access(&j, Pf_Dir , 0);
////	
////
	
	
	//PE
	if(DISPLAY.p3 != 0)
	{
		// ���� * �ð��� �ʷγ��� ��{1/(60��*60��)}
		float_temp = DISPLAY.p3 * 0.000277777;
		
		if(float_temp > 0)
		{
			ACCUMULATION.energy_p += float_temp;
			
			float_to_8bit_fram(&ACCUMULATION.energy_p, EP1, 1);
		}
	}
	
	//QE
	if(DISPLAY.q3 != 0)
	{
		// ���� * �ð��� �ʷγ��� ��{1/(60��*60��)}
		float_temp = DISPLAY.q3 * 0.000277777;
		
		if(float_temp > 0)
		{
			ACCUMULATION.energy_q += float_temp;
			
			float_to_8bit_fram(&ACCUMULATION.energy_q, EQ1, 1);
		}
	}


//
//	float_temp = 0;
//	// P
//	for(i = 0; i < 3; i++)
//	{		
//		// PE
//		if(DISPLAY.power_p[i] != 0)
//		{
//			// ���� * �ð��� �ʷγ��� ��{1/(60��*60��)}
//			PQE_buffer[i] = DISPLAY.power_p[i] * 0.000277777;
//			
//			if(PQE_buffer[i] > 0)
//			{
//				float_temp += PQE_buffer[i];
//				
//				//FRAM_Access((PEa + i), &float_temp1, 2);
//				
//				
//				
//				// float �Ѱ�ġ���� ũ��
//				if((float_temp1 - PQE_buffer[i]) > 9999999.0)
//				{
//					POWER.PE_Under[i] += PQE_buffer[i];
//					
//					// ���δ����� �Ѱ�ġ���� ������
//					if((float_temp1 - POWER.PE_Under[i]) <= 9999999.0)
//					{
//						float_temp1 += POWER.PE_Under[i];
//						
//						POWER.PE_Under[i] = 0.0;
//						
//						//10G ������ 0
//					    if(float_temp1 > 10000000000)
//					    float_temp1 = 0.0;
//					    
//					    FRAM_Access(&float_temp1, (PEa + i), 2);
//					}
//				}
//				
//				// �������̸�
//				else
//				{
//					PQE_buffer[i] += float_temp1;
//					
//					//10G ������ 0
//					if(PQE_buffer[i] > 10000000000)
//					PQE_buffer[i] = 0;
//					
//					FRAM_Access(&PQE_buffer[i], (PEa + i), 2);
//				}				
//			}			
//		}		
//	}
//	
//	// 3PE
//	//float_temp = PQE_buffer[0] + PQE_buffer[1] + PQE_buffer[2];
//	
//	if(float_temp > 0)
//	{
//		FRAM_Access(PE3p, &float_temp1, 2);
//		
//		float_temp2 = float_temp + float_temp1;
//		
//		// 10G ������ 0
//		if(float_temp2 > 10000000000)
//		float_temp = 0;
//		
//		FRAM_Access(&float_temp2, PE3p, 2);
//	}
//	
//	
//	float_temp = 0;
//	// Q
//	for(i = 0; i < 3; i++)
//	{		
//		// QE
//		if(Q_buffer[i] != 0)
//		{			
//			PQE_buffer[i] = Q_buffer[i] * 0.000277777;
//			
//			if(PQE_buffer[i] > 0)
//			{
//				float_temp += PQE_buffer[i];
//				
//				FRAM_Access((QEa + i), &float_temp1, 2);
//				
//				
//				
//				// float �Ѱ�ġ���� ũ��
//				if((float_temp1 - PQE_buffer[i]) > 9999999.0)
//				{
//					POWER.QE_Under[i] += PQE_buffer[i];
//					
//					// ���δ����� �Ѱ�ġ���� ������
//					if((float_temp1 - POWER.QE_Under[i]) <= 9999999.0)
//					{
//						float_temp1 += POWER.QE_Under[i];
//						
//						POWER.QE_Under[i] = 0.0;
//						
//						//10G ������ 0
//					    if(float_temp1 > 10000000000)
//					    float_temp1 = 0.0;
//					    
//					    FRAM_Access(&float_temp1, (QEa + i), 2);
//					}
//				}
//				
//				// �������̸�
//				else
//				{
//					PQE_buffer[i] += float_temp1;
//					
//					//10G ������ 0
//					if(PQE_buffer[i] > 10000000000)
//					PQE_buffer[i] = 0;
//					
//					FRAM_Access(&PQE_buffer[i], (QEa + i), 2);
//				}				
//			}			
//		}		
//	}
//	
//	// 3QE
//	//float_temp = PQE_buffer[0] + PQE_buffer[1] + PQE_buffer[2];	
//	
//	if(float_temp > 0)
//	{
//		FRAM_Access(QE3p, &float_temp1, 2);
//		
//		float_temp += float_temp1;
//		
//		// 10G ������ 0
//		if(float_temp > 10000000000)
//		float_temp = 0;
//		
//		FRAM_Access(&float_temp, QE3p, 2);
//	}
//	
//	
//	
	
	
	
	
	
	
	DISPLAY.Power_Up = 0;
}

void Cal_RHour(void)
{
	if(RUNNING.op_count < 1000)	return;
	RUNNING.op_count = 0; //1�� ���� ����
        
	RUNNING.RunningHourCNT++; //1�� ī���� ����

	if(RUNNING.RunningHourCNT >= 0x15752A00)	{RUNNING.RunningHourCNT = 0;}	//100000�ð� ���� RESET! (3,600*100,000=360,000,000)

	//MRAM ����
	*(MRAM_RUNNING_HOUR1) = (RUNNING.RunningHourCNT >> 16) & 0xffff;
	*(MRAM_RUNNING_HOUR2) = RUNNING.RunningHourCNT & 0xffff;
}


// ����ϴ� ���ͷ�Ʈ ����
// �� �Լ��� H/W ������ ���� �� ���� ����
void interrupt_control(void)
{
	EALLOW;
	
	// *SysCtrlRegs_PCLKCR3 = 0x3300;
	
	// interrupt vector regist
	
	// sync�� ������ Ʋ������ ���� �߻�
	// 1.389ms timer
	//PieVectTable.TINT0 = &TINT0_ISR;
	
	// AD �ܺ� ���ͷ�Ʈ
	PieVectTable.XINT3 = &XINT3_ISR;
	
	// 1ms timer
	PieVectTable.XINT13 = &TINT1_ISR;
	
	// 20us timer
	//PieVectTable.TINT2 = &TINT2_ISR;
	
	// ���� serial ����
	PieVectTable.SCIRXINTB = &SCIRXB_ISR;
	
	// ���� serial �۽�
	PieVectTable.SCITXINTB = &SCITXINTB_ISR;
	
	// HIMIX serial �۽�
	PieVectTable.SCITXINTC = &SCITXINTC_ISR;
	
	// interrupt enable bit
	// timer 0
	//IER |= M_INT1;  
	// timer 1
	IER |= M_INT13;  
	
	// timer2
	//IER |= M_INT14;
	
	// Enable CPU INT9 for SCI-B
	IER |= M_INT9;
	
	// Enable CPU INT8 for SCI-C
	IER |= M_INT8;
	
	// ad �ܺ����ͷ�Ʈ
	IER |= M_INT12;
	
	// timer0
	//*PieCtrlRegs_PIEIER1 |= 0x0040;
	
	// Enable SCI-B RX, TX INT in the PIE: Group 9
	*PieCtrlRegs_PIEIER9 |= 0x0004;
	*PieCtrlRegs_PIEIER9 |= 0x0008;
	// PieCtrlRegs.PIEIER9.bit.INTx3 = 1;

	// Enable SCI-C TX INT in the PIE: Group 8
	*PieCtrlRegs_PIEIER8 |= 0x0020;
	
	// sci-c tx interrupt Ȱ��
	// *ScicRegs_SCICTL2 |= 0x0001;
	
	// ad �ܺ����ͷ�Ʈ
	*PieCtrlRegs_PIEIER12 |= 0x0001;
	
	EDIS;

	ERTM;
}

void modbus_comm_card_check(void)
{
	static unsigned char a = 0;
	static unsigned char cnt = 0;
	static unsigned int nic_reset_start = 0;
	unsigned char tmp;

	if(nic_reset_start == 1) {
		nic_reset_start = 2;
		NIC_RESET_ON;
	} else if(nic_reset_start >= 2) {
		nic_reset_start = 0;
		NIC_RESET_OFF;
	}

	if(cnt++ > 5) {
		cnt = 0;

		tmp = *COMM_2_MODBUS_RECV_CNT & 0xff;

		if(a == tmp) {
			nic_reset_start = 1;
			NIC_RESET_OFF;//���ī�� ���� (Active Low �޽���ȣ �߻�)
		}

		a = tmp;
	}
}

void SCI_Port_Err_Check(void)
{
	if((*ScibRegs_SCIRXST & 0x80)||(*ScicRegs_SCIRXST & 0x80)) {
		sci_setup();
	}
}
