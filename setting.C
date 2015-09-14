#include "define.h"
#include "extern_variable.h"
#include "extern_prototype.h"

// 설정값 flash 저장
// *ar_temp - 값이 저장된 전역변수
// *ar_address - 값을 저장할 flash 주소
// ar_wordcount - 저장할 word 단위 개수
// return - 저장 양호 여부
unsigned int setting_save(unsigned int *ar_temp, unsigned int *ar_address, unsigned int ar_wordcount)
{
	unsigned int crc;
	unsigned int i;
	
	crc = Setting_CRC(ar_temp, ar_wordcount); //crc 계산
	flash_sector_erase(ar_address); // 해당 섹터 지움
	for(i = 0; i < ar_wordcount; i++){flash_word_write((ar_address + i), *(ar_temp + i));} 	// 지정된 개수만 큼 flash에 저장
	flash_word_write((ar_address + i), crc); // crc 추가로 저장
	for(i = 0; i < ar_wordcount; i++) // 저장된 값 비교
	{
		if(*(ar_temp + i) != *(ar_address + i)) // 하나라도 틀리면 fail
		return(0);
	}
	
// 설정 값에 따른 이벤트 저장
//---------계전요소 설정 이벤트 저장
	if(ar_address == OCR50_1_USE)					{
		EVENT.relay_set |= OCR50_1_SET_EVENT;		event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == OCR50_2_USE)	{
		EVENT.relay_set |= OCR50_2_SET_EVENT;		event_direct_save(&EVENT.relay_set);
	} else if(ar_address == OCGR50_USE)		{
		EVENT.relay_set |= OCGR50_SET_EVENT;    event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == OCGR51_USE)		{
		EVENT.relay_set |= OCGR51_SET_EVENT;    event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == THR_USE)			{
		EVENT.relay_set |= THR_SET_EVENT;				event_direct_save(&EVENT.relay_set);
	} else if(ar_address == NSR_USE)			{
		EVENT.relay_set |= NSR_SET_EVENT;				event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == LR51_USE)			{
		EVENT.relay_set |= LR51_SET_EVENT;			event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == NCHR_USE)			{
		EVENT.relay_set |= NCHR_SET_EVENT;			event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == H50_USE)			{
		EVENT.relay_set |= H50_SET_EVENT;				event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == UCR_USE)			{
		EVENT.relay_set |= UCR_SET_EVENT;				event_direct_save(&EVENT.relay_set);
	}	else if(ar_address == DGR_USE)			{
		EVENT.relay_set |= DGR_SET_EVENT;				event_direct_save(&EVENT.relay_set);
	} else if(ar_address == SGR_USE)			{
		EVENT.relay_set |= SGR_SET_EVENT;				event_direct_save(&EVENT.relay_set);
	}
	
//---------시스템요소 설정 이벤트 저장
//	else if(ar_address == CT_PRIMARY)
//	EVENT.system_set |= CT_PT_SET_EVENT;
//	
//	else if(ar_address == DI_DEBOUNCE1)
//	{
//		if(EVENT.group_extra == 0)
//		EVENT.system_set |= DI_DEBOUNCE_EVENT;
//		else
//		EVENT.system_set |= DO_PROPERTY_EVENT;
//	}
//	
//	else if(ar_address == SUPERV_MODE)
//	EVENT.system_set |= SUPERVISION_SET_EVENT;
//	
//	else if(ar_address == PASSWORD1)
//	EVENT.system_set |= PASSWORD_SET_EVENT;
//		
//	else if(ar_address == COMM_ADDRESS)
//	EVENT.system_set |= COMM_SET_EVENT;
//	
//	else if(ar_address == LOCAL_CTRL_USE) //2015.02.24
//	EVENT.system_set |= L_CONTROL_SET_EVENT;
//	
//	else if(ar_address == OCR_PROPERTY)
//	EVENT.system_set |= OCR_MODE_SET_EVENT;
//---------시스템요소 설정 이벤트 저장 END	

	return(1);
}

// crc가 정상일 경우 사후처리
// *ar_address - flash 시작 주소
// 상기 주소를 가지고 설정 값이 어떤 것인지 판단
// 필요로 하는 내부변수에 반영함
void setting_post_handling(unsigned int *ar_address)
{
	unsigned int i;
	float float_temp1;
	float float_temp2;

	if(ar_address == PT_SECONDARY)
	{
		CPT.pt_primary = CPT.pt_primary_high & 0xffff;
		CPT.pt_primary <<= 16;
		CPT.pt_primary += (CPT.pt_primary_low & 0xffff);
		float_temp1 = (float)CPT.pt_primary;
		float_temp2 = (float)GPT.pt_secondary;
		CPT.pt_ratio = float_temp1 / float_temp2;

		float_temp2 = (float)GPT.pt_tertiary;
		CPT.gpt_ratio = float_temp1 / float_temp2;

//-------- display용 factor
		DISPLAY.multipllier[0] = CPT.ct_ratio;
		DISPLAY.multipllier[1] = CPT.ct_ratio;
		DISPLAY.multipllier[2] = CPT.ct_ratio;
		DISPLAY.multipllier[3] = CPT.nct_ratio;
		DISPLAY.multipllier[4] = CPT.nct_ratio;
		//ZCT
		DISPLAY.multipllier[5] = 133.33333333333333333333333333333; //외부 ZCT 비 = 200:1.5=133.33[mA]=0.13333[A]
		DISPLAY.multipllier[6] = CPT.pt_ratio;
		DISPLAY.multipllier[7] = CPT.pt_ratio;
		DISPLAY.multipllier[8] = CPT.pt_ratio;
		DISPLAY.multipllier[9] = CPT.gpt_ratio;
	}

	else if(ar_address == CT_PRIMARY)
	{
		if(CORE.rated_ct == CT_1A)
		{
			CPT.ct_ratio = (float)CPT.ct_primary;
			CPT.nct_ratio = (float)CPT.nct_primary;
		}
		else //CT_5A
		{
			CPT.ct_ratio = (float)CPT.ct_primary;
			CPT.nct_ratio = (float)CPT.nct_primary;
			CPT.ct_ratio /= 5.0;
			CPT.nct_ratio /= 5.0;
		}
		
		CPT.pt_primary = CPT.pt_primary_high & 0xffff;
		CPT.pt_primary <<= 16;
		CPT.pt_primary += (CPT.pt_primary_low & 0xffff);
		float_temp1 = (float)CPT.pt_primary;
		float_temp2 = (float)GPT.pt_secondary;
		CPT.pt_ratio = float_temp1 / float_temp2;

		float_temp2 = (float)GPT.pt_tertiary;
		CPT.gpt_ratio = float_temp1 / float_temp2;

//-------- display용 factor
		DISPLAY.multipllier[0] = CPT.ct_ratio;
		DISPLAY.multipllier[1] = CPT.ct_ratio;
		DISPLAY.multipllier[2] = CPT.ct_ratio;
		DISPLAY.multipllier[3] = CPT.nct_ratio;
		DISPLAY.multipllier[4] = CPT.nct_ratio;
		DISPLAY.multipllier[5] = 133.33333333333333333333333333333; //외부 ZCT 비 = 200:1.5=133.33[mA]=0.13333[A]
		DISPLAY.multipllier[6] = CPT.pt_ratio;
		DISPLAY.multipllier[7] = CPT.pt_ratio;
		DISPLAY.multipllier[8] = CPT.pt_ratio;
		DISPLAY.multipllier[9] = CPT.gpt_ratio;

		//누적값들 삭제
//		ACCUMULATION.energy_p = 0;
//		ACCUMULATION.energy_q = 0;
//		ACCUMULATION.energy_rp = 0;
//		ACCUMULATION.energy_rq = 0;
//		float_to_8bit_fram(&ACCUMULATION.energy_p, EP1, 1);
//		float_to_8bit_fram(&ACCUMULATION.energy_q, EQ1, 1);
//		float_to_8bit_fram(&ACCUMULATION.energy_rp, REP1, 1);
//		float_to_8bit_fram(&ACCUMULATION.energy_rq, REQ1, 1);
//		ACCUMULATION.vo_max = 0;						
//		float_to_8bit_fram(&ACCUMULATION.vo_max, VoMAX1, 1);
//		ACCUMULATION.io_max = 0;
//		float_to_8bit_fram(&ACCUMULATION.io_max, IoMAX1, 1);
	}

	else if(ar_address == MOD_ADDR)
	{
		
	}

	else if(ar_address == AUTO_DISP_MODE)
	{
		
	}

	else if(ar_address == PASSWORD1)
	{
		
	}

	else if(ar_address == LOCAL_CTRL_USE)
	{
		
	}

	else if(ar_address == DISP_3PHASE_USE)
	{
		
	}

	else if(ar_address == MODBUS_BAUDRATE)
	{
		
	}

	else if(ar_address == RATIO_66)
	{
		SET_66.RatioSet_66 = (float)(SET_66.ratio*0.01);
	}

//	else if(ar_address == DI_DEBOUNCE1)
//	{
//		for(i = 0; i < 8; i++)		
//		SYSTEM.di_debounce_timer[i] = DIGITAL_INPUT.debounce[i];
//		
//	}
		
//	else if(ar_address == SUPERV_MODE)
//	{		
//		SUPERVISION.time[0] = SUPERVISION.tcs_time;
//		
//		if(SUPERVISION.tcs_do_relay & (0x0001 << i))
//		SUPERVISION.do_output[0] |= DO_ON_BIT[i];
//		
//		
//		SUPERVISION.time[1] = SUPERVISION.ccs_time;
//		
//		if(SUPERVISION.ccs_do_relay & (0x0001 << i))
//		SUPERVISION.do_output[1] |= DO_ON_BIT[i];
//		
//		
//		SUPERVISION.status[0] = RELAY_NORMAL;
//		SUPERVISION.status[1] = RELAY_NORMAL;
//		
//		SUPERVISION.tcs_monitoring = 0;
//		SUPERVISION.ccs_monitoring = 0;
//		SUPERVISION.monitor_count  = 0;
//		SUPERVISION.monitor_update = 0;
//	}
		
//	else if(ar_address == COMM_ADDRESS)

//	else if(ar_address == OCR_PROPERTY)
//	{
//		SYSTEM_SET.ocr_di_mask = 0x0001 << SYSTEM_SET.di_number;
//	}
//	else if(ar_address == OCGR_DGR_SEL)
//	{
//		if(CORE.gr_select == ZCT_SELECT)
//		;
//		
//		else
//		{
//			if(SYSTEM_SET.ocgr_dgr == DGR_SELECT)
//			{
//				if(OCGR50.use)
//				{
//					OCGR50.use = 0;
//					setting_save(&OCGR50.use, OCGR50_USE, 5);
//				}
//				
//				if(OCGR51.use)
//				{
//					OCGR51.use = 0;
//					setting_save(&OCGR51.use, OCGR51_USE, 5);
//				}
//				
////			dsgr_load_check();
//			}
//			
//			else
//			{
////2015.02.24
//// DGR, SGR 확인 필요
////				if(DSGR.use)
////				{
////					DSGR.use = 0;
////					setting_save(&DSGR.current_set, DSGR_USE, 6);
////				}
////2015.02.24 END				
////				ocgr_load_check();
//			}
//		}
//	}
//	else if(ar_address == COMM_ADDRESS)
//	{
//		*COMM_2_ADDRESS = ADDRESS.address;
//		*COMM_2_BAUDRATE = COMM.baudrate;
//	}


	else if(ar_address == OCR50_1_USE)
	{
		if(CORE.rated_ct == CT_5A) {
			OCR50_1.Pickup_Threshold = (float)OCR50_1.current_set;
			OCR50_1.Pickup_Threshold *= 0.1;

			OCR50_1.Dropout_Threshold = (float)OCR50_1.current_set;
			OCR50_1.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		} else {
//			OCR50_1.Pickup_Threshold = (float)OCR50_1.current_set;
//			OCR50_1.Pickup_Threshold *= 0.1;
//
//			OCR50_1.Dropout_Threshold = (float)OCR50_1.current_set;
//			OCR50_1.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		}

		OCR50_1.op_status = RELAY_NORMAL;
		OCR50_1.Op_Ratio = 0.0;
		OCR50_1.Op_Phase = 0;
		OCR50_1.Op_Time = 0.0;

		OCR50_1.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(OCR50_1.do_relay & (0x0001 << i))
			OCR50_1.do_output |= DO_ON_BIT[i];
		}
		
		if(OCR50_1.mode == DEFINITE)
		{
			OCR50_1.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
			OCR50_1.delay_ms = OCR50_1.delay_time * 10; //10msec -> msec로 변환
			OCR50_1.delay_ms = OCR50_1.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_50;
		}
		else
		{
			OCR50_1.pickup_limit = INSTANT_PICKUP_LIMIT;
			OCR50_1.delay_ms = 40 - INSTANT_PICKUP_LIMIT - TOTAL_DELAY_50; //순시 목표 40msec
		}
//	OCR50_1.event_ready = OCR50_1_SET_EVENT;
//	OCR50_1.event_ready |= (unsigned long)(OCR50_1.mode << 8);
		
		RELAY_STATUS.pickup							&= ~F_OCR50_1; //계전요소 alarm ON
		RELAY_STATUS.operation_realtime	&= ~F_OCR50_1; //계전요소 현재 상태 변수
	}

	else if(ar_address == OCR50_2_USE)
	{
		if(CORE.rated_ct == CT_5A) {
			OCR50_2.Pickup_Threshold = (float)OCR50_2.current_set;
			OCR50_2.Pickup_Threshold *= 0.1;

			OCR50_2.Dropout_Threshold = (float)OCR50_2.current_set;
			OCR50_2.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		} else {
//			OCR50_2.Pickup_Threshold = (float)OCR50_2.current_set;
//			OCR50_2.Pickup_Threshold *= 0.1;
//
//			OCR50_2.Dropout_Threshold = (float)OCR50_2.current_set;
//			OCR50_2.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		}

		OCR50_2.op_status = RELAY_NORMAL;
		OCR50_2.Op_Ratio = 0.0;
		OCR50_2.Op_Phase = 0;
		OCR50_2.Op_Time = 0.0;

		OCR50_2.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(OCR50_2.do_relay & (0x0001 << i))
			OCR50_2.do_output |= DO_ON_BIT[i];
		}
		
		if(OCR50_2.mode == DEFINITE)
		{
			OCR50_2.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
			OCR50_2.delay_ms = OCR50_2.delay_time * 10; //10msec -> msec로 변환
			OCR50_2.delay_ms = OCR50_2.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_50;
		}
		else
		{
			OCR50_2.pickup_limit = INSTANT_PICKUP_LIMIT;
			OCR50_2.delay_ms = 40 - INSTANT_PICKUP_LIMIT - TOTAL_DELAY_50; //순시 목표 40msec
		}
//	OCR50_2.event_ready = OCR50_2_SET_EVENT;
//	OCR50_2.event_ready |= (unsigned long)(OCR50_2.mode << 8);
		
		RELAY_STATUS.pickup							&= ~F_OCR50_2; //계전요소 alarm ON
		RELAY_STATUS.operation_realtime	&= ~F_OCR50_2; //계전요소 현재 상태 변수
	}

	else if(ar_address == OCGR50_USE)
	{
		if(CORE.rated_ct == CT_5A) {
			OCGR50.Pickup_Threshold = (float)OCGR50.current_set;
			OCGR50.Pickup_Threshold *= 0.1;
	
			OCGR50.Dropout_Threshold = (float)OCGR50.current_set;
			OCGR50.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		} else {
//		OCGR50.Pickup_Threshold = (float)OCGR50.current_set;
//		OCGR50.Pickup_Threshold *= 0.1;
//
//		OCGR50.Dropout_Threshold = (float)OCGR50.current_set;
//		OCGR50.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		}

		OCGR50.op_status = RELAY_NORMAL;
		OCGR50.Op_Ratio = 0.0;
		OCGR50.Op_Phase = 0;
		OCGR50.Op_Time = 0.0;
		
		OCGR50.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(OCGR50.do_relay & (0x0001 << i))
			OCGR50.do_output |= DO_ON_BIT[i];
		}
		
		if(OCGR50.mode == DEFINITE)
		{
			OCGR50.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
			OCGR50.delay_ms = OCGR50.delay_time * 10; //10msec -> msec로 변환
			OCGR50.delay_ms = OCGR50.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_50;
		}
		else
		{
			OCGR50.pickup_limit = INSTANT_PICKUP_LIMIT;
			OCGR50.delay_ms = 40 - INSTANT_PICKUP_LIMIT - TOTAL_DELAY_50; //순시 목표 40msec
		}
//	OCGR50.event_ready = OCGR50_SET_EVENT;
//	OCGR50.event_ready |= (unsigned long)(OCGR50.mode << 8);
//	OCGR50.event_ready |= 0x00000008;
		
		RELAY_STATUS.pickup							&= ~F_OCGR50;
		RELAY_STATUS.operation_realtime	&= ~F_OCGR50;
	}

	else if(ar_address == OCGR51_USE)
	{
		if(CORE.rated_ct == CT_5A) {
			OCGR51.Pickup_Threshold = (float)OCGR51.current_set;
			OCGR51.Pickup_Threshold *= 0.01;
	
			OCGR51.Dropout_Threshold = (float)OCGR51.current_set;
			OCGR51.Dropout_Threshold *= 0.0097; // 0.0097 = 0.01 * 0.97
		} else {
//		OCGR51.Pickup_Threshold = (float)OCGR51.current_set;
//		OCGR51.Pickup_Threshold *= 0.01;
//
//		OCGR51.Dropout_Threshold = (float)OCGR51.current_set;
//		OCGR51.Dropout_Threshold *= 0.0097; // 0.0097 = 0.01 * 0.97
		}

		OCGR51.op_status = RELAY_NORMAL;
		OCGR51.Op_Ratio = 0.0;
		OCGR51.Op_Phase = 0;
		OCGR51.Op_Time = 0.0;
		
		OCGR51.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(OCGR51.do_relay & (0x0001 << i))
			OCGR51.do_output |= DO_ON_BIT[i];
		}

		OCGR51.pickup_limit = INVERSE_PICKUP_LIMIT;

//		OCGR51.event_ready = OCGR51_SET_EVENT;
//		OCGR51.event_ready |= (unsigned long)(OCGR51.mode << 8);
//		OCGR51.event_ready |= 0x00000008;
		
		RELAY_STATUS.pickup							&= ~F_OCGR51;
		RELAY_STATUS.operation_realtime	&= ~F_OCGR51;
	}

	else if(ar_address == THR_USE)
	{
		if(CORE.rated_ct == CT_5A) {
			THR.Pickup_Threshold = (float)THR.current_set;
			THR.Pickup_Threshold *= 0.1;
			
			THR.Dropout_Threshold = (float)THR.current_set;
			THR.Dropout_Threshold *= 0.0099; // 0.0099 = 0.01 * 0.99
		} else {
			THR.Pickup_Threshold = (float)THR.current_set;
			THR.Pickup_Threshold *= 0.01;
			
			THR.Dropout_Threshold = (float)THR.current_set;
			THR.Dropout_Threshold *= 0.0099; // 0.0099 = 0.01 * 0.99
		}
		THR.Cold_Time = (float)(THR.cold_limit * 0.1);
		THR.Hot_Time  = (float)(THR.hot_limit * 0.1);
		THR.Cold_Thau = (float)(THR.tau_limit * 0.1);

		THR.op_status = RELAY_NORMAL;
		THR.Op_Ratio = 0.0;
		THR.Op_Phase = 0;
		THR.Op_Time = 0.0;
		
		THR.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(THR.do_relay & (0x0001 << i))
			THR.do_output |= DO_ON_BIT[i];
		}
		
//	THR.event_ready = THR_SET_EVENT;
//	THR.event_ready |= (unsigned long)(THR.mode << 8);
//	THR.event_ready |= 0x00000008;
		
		RELAY_STATUS.pickup							&= ~F_THR;
		RELAY_STATUS.operation_realtime	&= ~F_THR;
	}

	else if(ar_address == NSR_USE)
	{
		NSR.Pickup_Threshold = (float)NSR.current_set;
		NSR.Pickup_Threshold *= 0.1;

		NSR.Dropout_Threshold = (float)NSR.current_set;
		NSR.Dropout_Threshold *= 0.097; // 0.097 = 0.1 * 0.97

		NSR.op_status = RELAY_NORMAL;
		NSR.Op_Ratio = 0.0;
		NSR.Op_Phase = 0;
		NSR.Op_Time = 0.0;

		NSR.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(NSR.do_relay & (0x0001 << i))
			NSR.do_output |= DO_ON_BIT[i];
		}

		NSR.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
		NSR.delay_ms = NSR.delay_time * 100; //100msec -> msec로 변환
		NSR.delay_ms = NSR.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_NSR;

//		NSR.event_ready = NSR_SET_EVENT;
//		NSR.event_ready |= 0x00000100;

		RELAY_STATUS.pickup							&= ~F_NSR;
		RELAY_STATUS.operation_realtime	&= ~F_NSR;
	}

	else if(ar_address == LR51_USE)
	{
//---------------- start current set
		if(CORE.rated_ct == CT_5A) {
			LR51.Pickup_Threshold_Start = (float)LR51.start_current_set;
			LR51.Pickup_Threshold_Start *= 0.1;
		} else {
//			LR51.Pickup_Threshold_Start = (float)LR51.start_current_set;
//			LR51.Pickup_Threshold_Start *= 0.01;
		}
		LR51.Start_Ratio_Set = LR51.Pickup_Threshold_Start / THR.Pickup_Threshold;

//---------------- start time set
		LR51.pickup_limit = DEFINITE_PICKUP_LIMIT;
		LR51.delay_sec_time = LR51.start_delay_time * 0.1; //100msec -> sec로 변환
		LR51.delay_ms_time = LR51.start_delay_time * 100; //100msec -> msec로 변환
		LR51.Start_OPLevel =((pow(LR51.Start_Ratio_Set, 2.0)-1)*LR51.delay_sec_time)/80.0;
		LR51.Reactor_Start_Time = LR51.start_delay_time * 2 * 100; //2배 * 100msec -> msec로 변환

//---------------- run current set
		if(CORE.rated_ct == CT_5A) {
			LR51.Pickup_Threshold = (float)LR51.current_set;
			LR51.Pickup_Threshold *= 0.1;
		} else {
//		LR51.Pickup_Threshold = (float)LR51.current_set;
//		LR51.Pickup_Threshold *= 0.01;
		}

//---------------- run time set
		LR51.delay_ms = LR51.delay_time * 100; //100msec -> msec로 변환
		LR51.delay_ms = LR51.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_51LR_2;

		LR51.op_status = RELAY_NORMAL;
		LR51.Reactor_Start_Flag = STATE_NO;
		LR51.Op_Ratio = 0.0;
		LR51.Op_Phase = 0;
		LR51.Op_Time = 0.0;

		LR51.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(LR51.do_relay & (0x0001 << i))
			LR51.do_output |= DO_ON_BIT[i];
		}

//	LR51.event_ready = THR_SET_EVENT;
//	LR51.event_ready |= (unsigned long)(LR51.mode << 8);
//	LR51.event_ready |= 0x00000008;

		RELAY_STATUS.pickup							&= ~F_51LR_TOO;
		RELAY_STATUS.pickup							&= ~F_51LR_ROCK;
		RELAY_STATUS.operation_realtime	&= ~F_51LR_TOO;
		RELAY_STATUS.operation_realtime	&= ~F_51LR_ROCK;
	}

	else if(ar_address == NCHR_USE)
	{
		NCHR.Allow_Time_Threshold = NCHR.allow_time_set*60000;
		NCHR.Trip_Number_Threshold = NCHR.trip_number_set;
		NCHR.Limit_Time_Threshold = NCHR.limit_time_set*60000;
		NCHR.Theta_D_Threshold = (float)NCHR.theta_d_set*0.01;

		NCHR.op_status = RELAY_NORMAL;
//		NCHR.Op_Ratio = 0.0;
//		NCHR.Op_Phase = 0;
//		NCHR.Op_Time = 0.0;

		NCHR.Start_RNum = 0;
		Relay_Off(NCHR.do_output); //먼저 기존의 릴레이를 OFF 시킨다 //동작 중에 설정 값을 바꿀 수 있는 계전 요소는 적용해야 함. 27,50H,66

		NCHR.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(NCHR.do_relay & (0x0001 << i))
			NCHR.do_output |= DO_ON_BIT[i];
		}
		
//	NCHR.event_ready = OCR50_1_SET_EVENT;
//	NCHR.event_ready |= (unsigned long)(NCHR.mode << 8);
		
		RELAY_STATUS.pickup							&= ~F_NCHR; //계전요소 alarm ON
		RELAY_STATUS.operation_realtime	&= ~F_NCHR; //계전요소 현재 상태 변수
	}

	else if(ar_address == H50_USE)
	{
		if(CORE.rated_ct == CT_5A) {
			H50.Pickup_Threshold = (float)H50.current_set;
			H50.Pickup_Threshold *= 0.1;

			H50.Dropout_Threshold = (float)H50.current_set;
			H50.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		} else {
//		H50.Pickup_Threshold = (float)H50.current_set;
//		H50.Pickup_Threshold *= 0.1;
//
//		H50.Dropout_Threshold = (float)H50.current_set;
//		H50.Dropout_Threshold *= 0.099; // 0.099 = 0.1 * 0.99
		}

		H50.op_status = RELAY_NORMAL;
		if(H50.use == DISABLE)	{H50.op_status = RELAY_TRIP;}
        	
		H50.Op_Ratio = 0.0;
		H50.Op_Phase = 0;
		H50.Op_Time = 0.0;

		H50.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(H50.do_relay & (0x0001 << i))
			H50.do_output |= DO_ON_BIT[i];
		}

		H50.pickup_limit = INSTANT_PICKUP_LIMIT;
		H50.delay_ms = 40 - INSTANT_PICKUP_LIMIT - TOTAL_DELAY_H50; //순시 목표 40msec

		H50.trip_flag = ON;

//	H50.event_ready = H50_SET_EVENT;
//	H50.event_ready |= (unsigned long)(H50.mode << 8);
//	H50.event_ready |= 0x00000008;

		RELAY_STATUS.pickup							&= ~F_H50;
		RELAY_STATUS.operation_realtime	&= ~F_H50;
	}

	else if(ar_address == UCR_USE)
	{
		UCR.Min_Pickup_Threshold = (float)UCR.min_current_set;
		UCR.Min_Pickup_Threshold *= 0.1;

		UCR.Max_Pickup_Threshold = (float)UCR.max_current_set;
		UCR.Max_Pickup_Threshold *= 0.1;

		UCR.RMS = 0.0;

		UCR.op_status = RELAY_NORMAL;
		UCR.Op_Ratio = 0.0;
		UCR.Op_Phase = 0;
		UCR.Op_Time = 0.0;

		UCR.do_output = 0;
		for(i = 0; i < 8; i++)
		{
			if(UCR.do_relay & (0x0001 << i))
			UCR.do_output |= DO_ON_BIT[i];
		}

		UCR.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
		UCR.delay_ms = UCR.delay_time * 100; //100msec -> msec로 변환
		UCR.delay_ms = UCR.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_UCR;

//		UCR.event_ready = UCR_SET_EVENT;
//		UCR.event_ready |= 0x00000100;

		RELAY_STATUS.pickup							&= ~F_UCR;
		RELAY_STATUS.operation_realtime	&= ~F_UCR;
	}

	else if(ar_address == DGR_USE)
	{
		if(CORE.gr_select == NCT_SELECT)
		{
			if(CORE.rated_ct == CT_5A) {
				DGR.Pickup_Threshold_Io = (float)DGR.current_set;
				DGR.Pickup_Threshold_Io *= 0.1;

				DGR.Dropout_Threshold_Io = (float)DGR.current_set;
				DGR.Dropout_Threshold_Io *= 0.097; // 0.097 = 0.1 * 0.97
			} else {
//			DGR.Pickup_Threshold_Io = (float)DGR.current_set;
//			DGR.Pickup_Threshold_Io *= 0.1;
//
//			DGR.Dropout_Threshold_Io = (float)DGR.current_set;
//			DGR.Dropout_Threshold_Io *= 0.097; // 0.097 = 0.1 * 0.97
			}
			
			DGR.Pickup_Threshold_Vo = (float)DGR.voltage_set;
			DGR.Pickup_Threshold_Vo *= 0.1;

			DGR.Dropout_Threshold_Vo = (float)DGR.voltage_set;
			DGR.Dropout_Threshold_Vo *= 0.097; // 0.097 = 0.1 * 0.97

			DGR.angle_low = (float)DGR.angle_set;
			DGR.angle_low -= 60.;

			if(DGR.angle_low < 0.)
			DGR.angle_low += 360;

			DGR.angle_high = (float)DGR.angle_set;
			DGR.angle_high += 60.;
//			DGR.Pickup_Threshold_Angle = DGR.angle_set;
			
			DGR.op_status = RELAY_NORMAL;
			DGR.Op_Ratio = 0.0;
			DGR.Op_Phase = 0;
			DGR.Op_Time = 0.0;
			DGR.Op_Angle = 0;
			
			DGR.do_output = 0;
			for(i = 0; i < 8; i++)
			{
				if(DGR.do_relay & (0x0001 << i))
				{
					DGR.do_output |= DO_ON_BIT[i];
				}
			}

			DGR.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
			DGR.delay_ms = DGR.delay_time * 100; //100msec -> msec로 변환
			DGR.delay_ms = DGR.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_67GD;

//		DGR.event_ready = DGR_SET_EVENT;
//		DGR.event_ready |= 0x00000100;
			
			RELAY_STATUS.pickup							&= ~F_DGR;
			RELAY_STATUS.operation_realtime	&= ~F_DGR;
		}
	}

	else if(ar_address == SGR_USE)
	{
		if(CORE.gr_select == ZCT_SELECT)
		{
			SGR.Pickup_Threshold_Io = (float)SGR.current_set;
			SGR.Pickup_Threshold_Io *= 0.1;
			
			SGR.Dropout_Threshold_Io = (float)SGR.current_set;
			SGR.Dropout_Threshold_Io *= 0.097; // 0.097 = 0.1 * 0.97
			
			SGR.Pickup_Threshold_Vo = (float)SGR.voltage_set;
			SGR.Pickup_Threshold_Vo *= 0.1;
			
			SGR.Dropout_Threshold_Vo = (float)SGR.voltage_set;
			SGR.Dropout_Threshold_Vo *= 0.097; // 0.097 = 0.1 * 0.97
			
			SGR.angle_low = (float)SGR.angle_set;
			SGR.angle_low -= 60.;
			
			if(SGR.angle_low < 0.)
			SGR.angle_low += 360;
			
			SGR.angle_high = (float)SGR.angle_set;
			SGR.angle_high += 60.;
//			SGR.Pickup_Threshold_Angle = SGR.angle_set;
			
			SGR.op_status = RELAY_NORMAL;
			SGR.Op_Ratio = 0.0;
			SGR.Op_Phase = 0;
			SGR.Op_Time = 0.0;
			SGR.Op_Angle = 0;
			
			SGR.do_output = 0;
			for(i = 0; i < 8; i++)
			{
				if(SGR.do_relay & (0x0001 << i))
				{
					SGR.do_output |= DO_ON_BIT[i];
				}
			}

			SGR.pickup_limit = DEFINITE_PICKUP_LIMIT;
			
			SGR.delay_ms = SGR.delay_time * 100; //100msec -> msec로 변환
			SGR.delay_ms = SGR.delay_ms - DEFINITE_PICKUP_LIMIT - TOTAL_DELAY_67GS;

//		SGR.event_ready = SGR_SET_EVENT;
//		SGR.event_ready |= 0x00000100;
			
			RELAY_STATUS.pickup							&= ~F_SGR;
			RELAY_STATUS.operation_realtime	&= ~F_SGR;
		}
	}
}

	
// flash read
// *ar_value - flash에서 읽은 설정 값 저장변수
// *ar_address - flash 지정 주소
// ar_wordcount - *ar_address 부터 읽을 word 단위 개수
// return - crc 에러 여부
unsigned int setting_load(unsigned int *ar_value, unsigned int ar_wordcount, unsigned int *ar_address)
{	
	unsigned int crc;
	unsigned int i;
	
	// flash read
	for(i = 0; i < ar_wordcount; i++)
	{
		*(ar_value + i) = *(ar_address + i);
	}
	
	//crc read
	i = *(ar_address + i);
	
	// 일단 crc 계산
	crc = Setting_CRC(ar_value, ar_wordcount);
	
	// crc fail
	if(crc != i)
	return(0);
	
	//crc가 정상일 경우 사후처리
	setting_post_handling(ar_address);
	
	return(1);
}

unsigned int Setting_CRC(unsigned int *ar_address, unsigned int ar_length)
{
	unsigned int temp = 0;
	unsigned int high, low;
	unsigned int crc_hi_temp = 0x00FF;
	unsigned int crc_lo_temp = 0x00FF;
	unsigned int i;
	
	for(i = 0; i < ar_length; i++)
	{	
		temp = *(ar_address + i);
		high = 0;
		low = 0;
		high = temp >> 8;
		low = 0x00ff & temp;
		
		// high
		temp = (crc_hi_temp ^ high);
		crc_hi_temp = (crc_lo_temp ^ CRC_High[temp]);
		crc_lo_temp = CRC_Low[temp];
		
		// low
		temp = (crc_hi_temp ^ low);
		crc_hi_temp = (crc_lo_temp ^ CRC_High[temp]);
		crc_lo_temp = CRC_Low[temp];
	}
	crc_hi_temp <<= 8;
	crc_hi_temp |= crc_lo_temp;
	return(crc_hi_temp);
}

// 이벤트 정보 업데이트, khs, 2015-04-01 오후 5:37:28
void event_info_update(void)
{
	// rollover 아님
	if(EVENT.rollover == 0)
	{
		//시작점 지정
		EVENT.view_start = (int)(EVENT.sp - 1);
		// 현재 보는 부분 지정
		EVENT.view_point = EVENT.view_start;
	}
	// rollover
	else
	{						
		if(EVENT.sp == 0)
		{
			EVENT.view_start = 99;
			EVENT.view_point = 99;
		}
		
		else
		{
			EVENT.view_start = (int)(EVENT.sp - 1);
			EVENT.view_point = EVENT.view_start;
		}
	}	
}

// 이벤트 저장
// *ar_event - 이벤트 저장 변수
void event_direct_save(unsigned long *ar_event)
{
	unsigned int temp;

	event_info_update();//khs, 2015-04-01 오후 5:38:07
	
	// 곱하기 18
	temp = EVENT.sp * 18;
	
	*(EVENT_YEAR + temp)     = TIME.year;  // 연
	*(EVENT_MONTH + temp)    = TIME.month; // 월
	*(EVENT_DAY + temp)      = TIME.day;   // 일
	*(EVENT_HOUR + temp)     = TIME.hour;  // 시
	*(EVENT_MINUTE + temp)   = TIME.minute; // 분
	*(EVENT_SECOND + temp)   = TIME.second; // 초
	*(EVENT_MS1 + temp)      = TIME.milisecond >> 8; //msec 상위바이트
	*(EVENT_MS2 + temp)      = TIME.milisecond;      // msec 하위바이트
	*(EVENT_INDEX1 + temp)   = (unsigned int)(*ar_event >> 24); // 넘겨받은 변수에 이미 index1,2,contents 가 들어있음
	*(EVENT_INDEX2 + temp)   = (unsigned int)(*ar_event >> 16);
	*(EVENT_CONTENT1 + temp) = (unsigned int)(*ar_event >> 8);
	*(EVENT_CONTENT2 + temp) = (unsigned int)*ar_event;
	
	// 넘겨받은 이벤트가 계전동작이면 추가정보를 기록해준다
	// 넘겨받은 것이 정말 계전동작 이벤트라면 넘겨주는 변수 주소는 EVENT.operation
	//if(EVENT.operation & 0x01000000)
	if(ar_event == &EVENT.operation)
	{
		*(EVENT_RATIO1 + temp)   = EVENT.ratio >> 8; // 동작치 배율
		*(EVENT_RATIO2 + temp)   = EVENT.ratio;		
		*(EVENT_OPTIME1 + temp)  = (unsigned int)(EVENT.optime >> 24); //동작시간
		*(EVENT_OPTIME2 + temp)  = (unsigned int)(EVENT.optime >> 16);
		*(EVENT_OPTIME3 + temp)  = (unsigned int)(EVENT.optime >> 8);
		*(EVENT_OPTIME4 + temp)  = (unsigned int)EVENT.optime;
	}
	
	// 이벤트 개수 증가
	++EVENT.sp;
	
	// 200개 다차면 rollover 플래그 셋하고 sp는 0으로 초기화
	if(EVENT.sp == 200)
	{
		EVENT.sp = 0;
		
		EVENT.rollover = 0xaa;
		*EVENT_ROLLOVER = 0xaa;
	}
	
	// fram에 저장
	*EVENT_SP = EVENT.sp;
	
	// 넘겨받은 이벤트 변수 index만 살리고 데이터 초기화
	*ar_event &= 0xff000000;

	event_info_update();//khs, 2015-04-01 오후 5:38:07	
}

// rtc 장치 drivng 함수
void rtc_handling(void)
{
	unsigned int temp[7];
	unsigned int temp16 = 0;
	
	// rtc write mode
	if(TIME.update == 0)
	{
		temp[0] = 0x02;
		i2c_write(0x68, 0x00, 1, temp);
		++TIME.update;
	}
	
	//rtc에 시간을 설정할 때
	else if(TIME.update == 1)
	{
		// decimal을 bcd로 변환하여 써줌
		
		// year
		temp16 = *TIME.buffer / 10;
		temp[6] = temp16;
		temp[6] <<= 4;
		temp16 = *TIME.buffer % 10;
		temp[6] |= temp16;
		
		//month
		temp16 = *(TIME.buffer + 1) / 10;
		temp[5] = temp16;
		temp[5] <<= 4;
		temp16 = *(TIME.buffer + 1) % 10;
		temp[5] |= temp16;
		
		//day
		temp16 = *(TIME.buffer + 2) / 10;
		temp[4] = temp16;
		temp[4] <<= 4;
		temp16 = *(TIME.buffer + 2) % 10;
		temp[4] |= temp16;
		
		//hour
		temp16 = *(TIME.buffer + 3) / 10;
		temp[2] = temp16;
		temp[2] <<= 4;
		temp16 = *(TIME.buffer + 3) % 10;
		temp[2] |= temp16;
		
		//minute
		temp16 = *(TIME.buffer + 4) / 10;
		temp[1] = temp16;
		temp[1] <<= 4;
		temp16 = *(TIME.buffer + 4) % 10;
		temp[1] |= temp16;
		
		//second
		temp16 = *(TIME.buffer + 5) / 10;
		temp[0] = temp16;
		temp[0] <<= 4;
		temp16 = *(TIME.buffer + 5) % 10;
		temp[0] |= temp16;
		
		i2c_write(0x68, 0x02, 7, temp);
		
		++TIME.update;
	}
	// rtc 내부 시간을 읽어올때  read mode로 전환
	else if(TIME.update == 2)
	{
		temp[0] = 0x01;		
		i2c_write(0x68, 0x00, 1, temp);
		++TIME.update;
	}
	// rtc read 동작
	else if(TIME.update == 3)
	{		
		i2c_read(0x68, 0x02, 7);
		++TIME.update;
	}
	// 읽어온 rtc 시간을 conversion & restart
	else if(TIME.update == 4)
	{	
		// i2c_read()에서 읽음완료 후 DSP 수신 FIFO(*I2caRegs_I2CDRR)에서 불러오면 읽기가 최종적으로 완료
		for(temp16 = 0; temp16 < 7; temp16++)
		temp[temp16] = *I2caRegs_I2CDRR;
		
		// RTC 내부는 BCD type으로 시간을 운용하므로 decimal 형태로 변환을 해준다
		// BCD 타입 - 자리수를 nibble 단위로 처리
		// 10월인 경우 - 0x10
		// 31일인 경우 - 0x31
		// year		
		TIME.year = (temp[6] >> 4) * 10;
		TIME.year += (temp[6] & 0x000f);
		
		//month
		TIME.month = (temp[5] >> 4) * 10;
		TIME.month += (temp[5] & 0x000f);
		
		//day
		TIME.day = (temp[4] >> 4) * 10;
		TIME.day += (temp[4] & 0x000f);
				
		//hour
		TIME.hour = (temp[2] >> 4) * 10;
		TIME.hour += (temp[2] & 0x000f);
		
		//minute
		TIME.minute = (temp[1] >> 4) * 10;
		TIME.minute += (temp[1] & 0x000f);
		
		//second
		TIME.second = (temp[0] >> 4) * 10;
		TIME.second += (temp[0] & 0x000f);
		
		//rtc start
		temp[0] = 0x00;
		i2c_write(0x68, 0x00, 1, temp);		
		
		TIME.update = 0xffff;	
	}	
}

void GPT_Default_Settings(void)
{
	GPT.pt_secondary = 110;
	GPT.pt_tertiary = 190;

	if(setting_save(&GPT.pt_secondary, PT_SECONDARY, 2))
	{
		setting_load(&GPT.pt_secondary, 2, PT_SECONDARY);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void CPT_Default_Settings(void)
{
	if(CORE.rated_ct == CT_5A)	{CPT.ct_primary = CT_5A_RATED; CPT.nct_primary = CT_5A_RATED;}
	else												{CPT.ct_primary = CT_1A_RATED; CPT.nct_primary = CT_1A_RATED;}
	
	if(GPT.pt_secondary == 100)			 {CPT.pt_primary_low = 0x86a0; CPT.pt_primary_high = 0x0001;} // 0x186a0 ->100000
	else if(GPT.pt_secondary == 110) {CPT.pt_primary_low = 0xadb0; CPT.pt_primary_high = 0x0001;} // 0x1adb0 ->110000
	else if(GPT.pt_secondary == 120) {CPT.pt_primary_low = 0xd4c0; CPT.pt_primary_high = 0x0001;} // 0x1d4c0 ->120000
	else if(GPT.pt_secondary == 190) {CPT.pt_primary_low = 0xe630; CPT.pt_primary_high = 0x0002;} // 0x2E630 ->190000
		
	if(CORE.rated_ct == CT_5A)	{CPT.rated_current = 50000;}
	else												{CPT.rated_current = 10000;}

	if(setting_save(&CPT.ct_primary, CT_PRIMARY, 5))
	{
		setting_load(&CPT.ct_primary, 5, CT_PRIMARY);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void ADDRESS_Default_Settings(void)
{
	ADDRESS.address = 254;

	if(setting_save(&ADDRESS.address, MOD_ADDR, 1))
	{
		setting_load(&ADDRESS.address, 1, MOD_ADDR);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void AUTO_DISPLAY_Default_Settings(void)
{
	AUTO_DISPLAY.mode = 0;

	if(setting_save(&AUTO_DISPLAY.mode, AUTO_DISP_MODE, 1))
	{
		setting_load(&AUTO_DISPLAY.mode, 1, AUTO_DISP_MODE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void PASSWORD_Default_Settings(void)
{
	PASSWORD.real = 1111;

	if(setting_save(&PASSWORD.real, PASSWORD1, 1))
	{
		setting_load(&PASSWORD.real, 1, PASSWORD1);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void LOCAL_CTRL_Default_Settings(void)
{
	LOCAL_CTRL.use = DISABLE;
	LOCAL_CTRL.close_time = 2;
	LOCAL_CTRL.open_time = 0;

	if(setting_save(&LOCAL_CTRL.use, LOCAL_CTRL_USE, 3))
	{
		setting_load(&LOCAL_CTRL.use, 3, LOCAL_CTRL_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void DSGR_ANGLE_Default_Settings(void)
{
	//default
	DSGR_ANGLE.dgr_angle = 0;
	DSGR_ANGLE.sgr_angle = 0;

	if(setting_save(&DSGR_ANGLE.dgr_angle, DGR_ANGLE_COMP, 2))
	{
		setting_load(&DSGR_ANGLE.dgr_angle, 2, DGR_ANGLE_COMP);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void DISPLAY_3PHASE_Default_Settings(void)
{
	//default
	DISPLAY_3PHASE.use = DISABLE;

	if(setting_save(&DISPLAY_3PHASE.use, DISP_3PHASE_USE, 1))
	{
		setting_load(&DISPLAY_3PHASE.use, 1, DISP_3PHASE_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void MODBUS_Default_Settings(void)
{
	//default
	MODBUS.baudrate = 2;  //38400
	MODBUS.delay = 0;  //0ms

	if(setting_save(&MODBUS.baudrate, MODBUS_BAUDRATE, 2))
	{
		setting_load(&MODBUS.baudrate, 2, MODBUS_BAUDRATE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void OCR_MODE_Default_Settings(void)
{
	//default
	OCR_MODE_SET.ocr_mode = OCR_SELECT;

	if(setting_save(&OCR_MODE_SET.ocr_mode, OCR_MODE, 1))
	{
		setting_load(&OCR_MODE_SET.ocr_mode, 1, OCR_MODE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void SYSTEM_ALARM_Default_Settings(void)
{
	SYSTEM_ALARM.use = DISABLE;
	SYSTEM_ALARM.do_relay = 0;

	if(setting_save(&SYSTEM_ALARM.use, SYSTEM_ALARM_USE, 2))
	{
		setting_load(&SYSTEM_ALARM.use, 2, SYSTEM_ALARM_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void OCR50_1_Default_Settings(void)
{
	//default
	OCR50_1.use = DISABLE;
	OCR50_1.mode = DEFINITE;
	if(CORE.rated_ct == CT_5A)	{OCR50_1.current_set = OCR50_I_MAX[0];}
	else												{OCR50_1.current_set = OCR50_I_MAX[1];}
	OCR50_1.delay_time = OCR50_T_MAX;
	OCR50_1.do_relay = 0;
	
	if(setting_save(&OCR50_1.use, OCR50_1_USE, 5))
	{
		setting_load(&OCR50_1.use, 5, OCR50_1_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void OCR50_2_Default_Settings(void)
{
	//default
	OCR50_2.use = DISABLE;
	OCR50_2.mode = DEFINITE;
	if(CORE.rated_ct == CT_5A)	{OCR50_2.current_set = OCR50_I_MAX[0];}
	else												{OCR50_2.current_set = OCR50_I_MAX[1];}
	OCR50_2.delay_time = OCR50_T_MAX;
	OCR50_2.do_relay = 0;

	if(setting_save(&OCR50_2.use, OCR50_2_USE, 5))
	{
		setting_load(&OCR50_2.use, 5, OCR50_2_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void OCGR50_Default_Settings(void)
{
	//default
	OCGR50.use = DISABLE;
	OCGR50.mode = DEFINITE;
	if(CORE.rated_ct == CT_5A)	{OCGR50.current_set = OCGR50_I_MAX[0];}
	else												{OCGR50.current_set = OCGR50_I_MAX[1];}
	OCGR50.delay_time = OCGR50_T_MAX;
	OCGR50.do_relay = 0;

	if(setting_save(&OCGR50.use, OCGR50_USE, 5))
	{
		setting_load(&OCGR50.use, 5, OCGR50_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void OCGR51_Default_Settings(void)
{
	//default
	OCGR51.use = DISABLE;
	OCGR51.mode = INVERSE;
	if(CORE.rated_ct == CT_5A)	{OCGR51.current_set = OCGR51_I_MAX[0];}
	else												{OCGR51.current_set = OCGR51_I_MAX[1];}
	OCGR51.time_lever = OCGR51_TL_MAX;
	OCGR51.do_relay = 0;

	if(setting_save(&OCGR51.use, OCGR51_USE, 5))
	{
		setting_load(&OCGR51.use, 5, OCGR51_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void THR_Default_Settings(void)
{
	//default
	THR.use = DISABLE;
	if(CORE.rated_ct == CT_5A)	{THR.current_set = THR_I_MAX[0];}
	else												{THR.current_set = THR_I_MAX[1];}
	THR.cold_limit = THR_COLD_MAX;
	THR.hot_limit = THR_HOT_MAX;
	THR.tau_limit = THR_TAU_MAX;
	THR.do_relay = 0;

	if(setting_save(&THR.use, THR_USE, 6))
	{
		setting_load(&THR.use, 6, THR_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void NSR_Default_Settings(void)
{
	//default
	NSR.use = DISABLE;
	if(CORE.rated_ct == CT_5A)	{NSR.current_set = NSR_I_MAX[0];}
	else												{NSR.current_set = NSR_I_MAX[1];}
	NSR.delay_time = NSR_T_MAX;
	NSR.do_relay = 0;

	if(setting_save(&NSR.use, NSR_USE, 4))
	{
		setting_load(&NSR.use, 4, NSR_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void LR51_Default_Settings(void)
{
	//default
	LR51.use = DISABLE;
	if(CORE.rated_ct == CT_5A)	{LR51.start_current_set = LR51_ST_I_MAX[0];}
	else												{LR51.start_current_set = LR51_ST_I_MAX[1];}
	LR51.start_delay_time = LR51_ST_T_MAX;
	
	if(CORE.rated_ct == CT_5A)	{LR51.current_set = LR51_I_MAX[0];}
	else												{LR51.current_set = LR51_I_MAX[1];}
	LR51.delay_time = LR51_T_MAX;
	LR51.do_relay = 0;

	if(setting_save(&LR51.use, LR51_USE, 6))
	{
		setting_load(&LR51.use, 6, LR51_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void NCHR_Default_Settings(void)
{
	//default
	NCHR.use = DISABLE;
	NCHR.allow_time_set = NCHR_AL_T_MAX;
	NCHR.trip_number_set = NCHR_TRIP_NO_MAX;
	NCHR.limit_time_set = NCHR_LIMIT_T_MAX;
	NCHR.theta_d_set = NCHR_THETA_D_MAX;
	NCHR.do_relay = 0;

	if(setting_save(&NCHR.use, NCHR_USE, 6))
	{
		setting_load(&NCHR.use, 6, NCHR_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void H50_Default_Settings(void)
{
	//default
	H50.use = DISABLE;
	if(CORE.rated_ct == CT_5A)	{H50.current_set = H50_I_MAX[0];}
	else												{H50.current_set = H50_I_MAX[1];}
	H50.do_relay = 0;

	if(setting_save(&H50.use, H50_USE, 3))
	{
		setting_load(&H50.use, 3, H50_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void UCR_Default_Settings(void)
{
	//default
	UCR.use = DISABLE;
	if(CORE.rated_ct == CT_5A)	{UCR.min_current_set = UCR_Imin_MIN[0];}
	else												{UCR.min_current_set = UCR_Imin_MIN[1];}
	if(CORE.rated_ct == CT_5A)	{UCR.max_current_set = UCR_Imax_MIN[0];}
	else												{UCR.max_current_set = UCR_Imax_MIN[1];}
	UCR.delay_time = UCR_T_MAX;
	UCR.do_relay = 0;

	if(setting_save(&UCR.use, UCR_USE, 5))
	{
		setting_load(&UCR.use, 5, UCR_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void DGR_Default_Settings(void)
{
	//default
	DGR.use = DISABLE;
	if(CORE.rated_ct == CT_5A)			{DGR.current_set = DGR_I_MAX[0];}
	else														{DGR.current_set = DGR_I_MAX[1];}
	if(GPT.pt_tertiary == 110)			{DGR.voltage_set = DGR_V_MAX[0];}
	else if(GPT.pt_tertiary == 120) {DGR.voltage_set = DGR_V_MAX[1];}
	else if(GPT.pt_tertiary == 190) {DGR.voltage_set = DGR_V_MAX[2];}
	DGR.angle_set = DGR_A_MAX;
	DGR.delay_time = DGR_T_MAX;
	DGR.do_relay = 0;   

	if(setting_save(&DGR.use, DGR_USE, 6))
	{
		setting_load(&DGR.use, 6, DGR_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void SGR_Default_Settings(void)
{
	//default
	SGR.use = DISABLE;
	SGR.current_set = SGR_I_MAX;
	if(GPT.pt_tertiary == 110)			{SGR.voltage_set = SGR_V_MAX[0];}
	else if(GPT.pt_tertiary == 120) {SGR.voltage_set = SGR_V_MAX[1];}
	else if(GPT.pt_tertiary == 190) {SGR.voltage_set = SGR_V_MAX[2];}
	SGR.angle_set = SGR_A_MAX;
	SGR.delay_time = SGR_T_MAX;
	SGR.do_relay = 0;

	if(setting_save(&SGR.use, SGR_USE, 6))
	{
		setting_load(&SGR.use, 6, SGR_USE);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void DI_Default_Settings(void)
{
	//default
	DIGITAL_INPUT.debounce[0] = 0;
	DIGITAL_INPUT.debounce[1] = 0;
	DIGITAL_INPUT.debounce[2] = 0;
	DIGITAL_INPUT.debounce[3] = 0;
	DIGITAL_INPUT.debounce[4] = 0;
	DIGITAL_INPUT.debounce[5] = 0;
	DIGITAL_INPUT.debounce[6] = 0;
	DIGITAL_INPUT.debounce[7] = 0;

	if(setting_save(DIGITAL_INPUT.debounce, DI_DEBOUNCE1, 8))
	{
		setting_load(DIGITAL_INPUT.debounce, 8, DI_DEBOUNCE1);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void DO_Default_Settings(void)
{
	//default
	DIGITAL_OUTPUT.property = 0x0;

	if(setting_save(&DIGITAL_OUTPUT.property, DO_PROPERTY, 1))
	{
		setting_load(&DIGITAL_OUTPUT.property, 1, DO_PROPERTY);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void SET66_Default_Settings(void)
{
	//default
	SET_66.ratio = SET66_RATIO_MIN;
	SET_66.start_delay = SET66_ST_DLY_MAX;
	SET_66.stop_delay = SET66_SP_DLY_MAX;

	if(setting_save(&SET_66.ratio, RATIO_66, 3))
	{
		setting_load(&SET_66.ratio, 3, RATIO_66);
	}
	else
	{
		//FLASH WRITE ERROR pop up 화면
	}
}

void ClearFLASH(void)
{
	GPT_Default_Settings(); //설정 순서를 CORE. -> GPT. -> CPT. -> 계전요소 순서를 지켜야 함. (순서대로 계속 참조 해야 하므로)
	CPT_Default_Settings();
	ADDRESS_Default_Settings();
	AUTO_DISPLAY_Default_Settings();
	PASSWORD_Default_Settings();
	LOCAL_CTRL_Default_Settings();
	DSGR_ANGLE_Default_Settings();
	DISPLAY_3PHASE_Default_Settings();
	MODBUS_Default_Settings();
	OCR_MODE_Default_Settings();
	SYSTEM_ALARM_Default_Settings();

	OCR50_1_Default_Settings();
	OCR50_2_Default_Settings();
	OCGR50_Default_Settings();
	OCGR51_Default_Settings();
	THR_Default_Settings();
	NSR_Default_Settings();
	LR51_Default_Settings();
	NCHR_Default_Settings();
	H50_Default_Settings();
	UCR_Default_Settings();
	DGR_Default_Settings();
	SGR_Default_Settings();

	DI_Default_Settings();
	DO_Default_Settings();
	SET66_Default_Settings();

 	//Fault clear
 	//이벤트 clear
 	//누적값 clear (running hour, vo_max 등)
 	//do 출력 설정 초기화
}



