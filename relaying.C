#include "define.h"
#include "extern_variable.h"
#include "extern_prototype.h"

void Save_Relay_Event(float ar_ratio)
{
//  일단 나중에 구현하자 2015-05-11 오후 2:19:04					
//	WAVE.relay |= ar_relay_bit;
//	// wave capture 시작 추가
//	if((WAVE.post_start != 0x1234) && (WAVE.hold == 0))	WAVE.post_start = 0x1234;
						
	EVENT.ratio = (unsigned int)ar_ratio;
	event_direct_save(&EVENT.operation);
}

void relay_dropout_to_normal(unsigned int ar_relay_bit)
{
	WAVE.relay &= ~ar_relay_bit;
}

void RELAY_OCR50_1(void)
{
	if(OCR50_1.use == 0xaaaa)
	{
		if((OCR_MODE_SET.ocr_mode == OCR_NORMAL) || ((OCR_MODE_SET.ocr_mode == OCR_SELECT) && (OCR_MODE_SET.ocr_di_mask == 0x0008))) //DI접점이 4인 경우
		{
			if(PROTECT.Max_I_RMS >= OCR50_1.Pickup_Threshold)
			{
				if(OCR50_1.op_status == RELAY_NORMAL)
				{
					OCR50_1.op_status = RELAY_DETECT;
					OCR50_1.op_count = 0;
				}
				else if(OCR50_1.op_status == RELAY_DETECT)
				{
					if(OCR50_1.op_count >= OCR50_1.pickup_limit)
					{	
						OCR50_1.op_status = RELAY_PICKUP;
						RELAY_STATUS.pickup |= F_OCR50_1;  //alarm ON
						OCR50_1.Pickup_Time = OCR50_1.op_count;
						OCR50_1.op_count = 0;
					}
				}
				else if(OCR50_1.op_status == RELAY_PICKUP)
				{
					if(OCR_MODE_SET.ocr_mode == OCR_SELECT)
					{
						OCR50_1.di_on_flag = 1;
						if(OCR50_1.di_err_flag==1)
						{
							OCR50_1.op_status = RELAY_NORMAL;
							OCR50_1.di_err_flag = 0;
							return;
						}
					}

					if(OCR50_1.op_count >= OCR50_1.delay_ms)
					{
						Relay_On(OCR50_1.do_output);

						OCR50_1.op_status	= RELAY_TRIP;
						OCR50_1.Op_Ratio	= PROTECT.Max_I_RMS / OCR50_1.Pickup_Threshold; //배수
						OCR50_1.Op_Phase	= PROTECT.I_Op_Phase; //상
						OCR50_1.Delay_Time = OCR50_1.op_count;
						OCR50_1.Op_Time		= OCR50_1.Delay_Time + OCR50_1.Pickup_Time + TOTAL_DELAY_50; //동작 시간

						RELAY_STATUS.pickup									&= ~F_OCR50_1; //계전요소 alarm OFF
						RELAY_STATUS.operation_realtime			|= F_OCR50_1;  //현재 동작 상태 변수 설정
						RELAY_STATUS.operation_sum_holding	|= F_OCR50_1;  //누적 동작 상태 변수 설정
						
						EVENT.optime = (unsigned long)OCR50_1.Op_Time;
						EVENT.operation |= (F_OCR50_1 << 16) + OCR50_1.Op_Phase;
						EVENT.fault_type = F_OCR50_1;
						Phase_Info = (Phase_Info == 0)? EVENT.operation: OCR50_1.Op_Phase;
						Save_Relay_Event(OCR50_1.Op_Ratio * 100.0F);
						Save_Screen_Info(OCR50_1.Op_Phase);
					}
				}
			}
			else
			{
				if(PROTECT.Max_I_RMS <= OCR50_1.Dropout_Threshold)  //under 99%
				{
					if((OCR50_1.op_status == RELAY_DETECT) || (OCR50_1.op_status == RELAY_PICKUP))
					{
						OCR50_1.op_status = RELAY_NORMAL;
						RELAY_STATUS.pickup &= ~F_OCR50_1; //계전요소 alarm OFF
					}
					else if(OCR50_1.op_status == RELAY_TRIP)
					{
						Relay_Off(OCR50_1.do_output); //DO open
						OCR50_1.op_status = RELAY_NORMAL; //50_1상태 NORMAL
						RELAY_STATUS.operation_realtime &= ~F_OCR50_1; //동작 상태 변수 해제
					}
				}
			}
		}
		else //OCR_MODE_SET.ocr_mode == OCR_SELECT 이고 DI 정보가 안들어 올 때
		{
			OCR50_1.di_err_flag = 1;
			if(OCR50_1.di_on_flag == 1)	{RELAY_STATUS.pickup &= ~F_OCR50_1;}  //계전요소 alarm OFF
			OCR50_1.di_on_flag = 0;
		}
	}
}

void RELAY_OCR50_2(void)
{
	if(OCR50_2.use == 0xaaaa)
	{
		if((OCR_MODE_SET.ocr_mode == OCR_NORMAL) || ((OCR_MODE_SET.ocr_mode == OCR_SELECT) && (OCR_MODE_SET.ocr_di_mask == 0x0010))) //DI접점이 5인 경우
		{
			if(PROTECT.Max_I_RMS >= OCR50_2.Pickup_Threshold)
			{
				if(OCR50_2.op_status == RELAY_NORMAL)
				{
					OCR50_2.op_status = RELAY_DETECT;
					OCR50_2.op_count = 0;
				}
				else if(OCR50_2.op_status == RELAY_DETECT)
				{
					if(OCR50_2.op_count >= OCR50_2.pickup_limit)
					{
						OCR50_2.op_status = RELAY_PICKUP;
						RELAY_STATUS.pickup |= F_OCR50_2;  //alarm ON
						OCR50_2.Pickup_Time = OCR50_2.op_count;
						OCR50_2.op_count = 0;
					}
				}
				else if(OCR50_2.op_status == RELAY_PICKUP)
				{
					if(OCR_MODE_SET.ocr_mode == OCR_SELECT)
					{
						OCR50_2.di_on_flag = 1;
						if(OCR50_2.di_err_flag==1)
						{
							OCR50_2.op_status = RELAY_NORMAL;
							OCR50_2.di_err_flag = 0;
							return;
						}
					}

					if(OCR50_2.op_count >= OCR50_2.delay_ms)
					{
						Relay_On(OCR50_2.do_output);

						OCR50_2.op_status	= RELAY_TRIP;
						OCR50_2.Op_Ratio	= PROTECT.Max_I_RMS / OCR50_2.Pickup_Threshold; //배수
						OCR50_2.Op_Phase	= PROTECT.I_Op_Phase; //상
						OCR50_2.Delay_Time = OCR50_2.op_count;
						OCR50_2.Op_Time		= OCR50_2.Delay_Time + OCR50_2.Pickup_Time + TOTAL_DELAY_50; //동작 시간

						RELAY_STATUS.pickup									&= ~F_OCR50_2; //계전요소 alarm OFF
						RELAY_STATUS.operation_realtime			|= F_OCR50_2;  //현재 동작 상태 변수 설정
						RELAY_STATUS.operation_sum_holding	|= F_OCR50_2;  //누적 동작 상태 변수 설정
						
						EVENT.optime = (unsigned long)OCR50_2.Op_Time;
						EVENT.operation |= (F_OCR50_2 << 16) + OCR50_2.Op_Phase;
						Phase_Info = (Phase_Info == 0)? EVENT.operation: OCR50_2.Op_Phase;
						EVENT.fault_type = F_OCR50_2;
						Save_Relay_Event(OCR50_2.Op_Ratio * 100.0F);
						Save_Screen_Info(OCR50_2.Op_Phase);
					}
				}
			}
			else
			{
				if(PROTECT.Max_I_RMS <= OCR50_2.Dropout_Threshold)  //under 99%
				{
					if((OCR50_2.op_status == RELAY_DETECT) || (OCR50_2.op_status == RELAY_PICKUP))
					{
						OCR50_2.op_status = RELAY_NORMAL;
						RELAY_STATUS.pickup &= ~F_OCR50_2; //계전요소 alarm OFF
					}
					else if(OCR50_2.op_status == RELAY_TRIP)
					{
						Relay_Off(OCR50_2.do_output); //DO open, test 용
						OCR50_2.op_status = RELAY_NORMAL; //50_1상태 NORMAL
						RELAY_STATUS.operation_realtime &= ~F_OCR50_2; //동작 상태 변수 해제
					}
				}
			}
		}
		else //OCR_MODE_SET.ocr_mode == OCR_SELECT 이고 DI 정보가 안들어 올 때
		{
			OCR50_2.di_err_flag = 1;
			if(OCR50_2.di_on_flag == 1)	{RELAY_STATUS.pickup &= ~F_OCR50_2;}  //계전요소 alarm OFF
			OCR50_2.di_on_flag = 0;
		}
	}
}

void RELAY_OCGR50(void)
{
	if(OCGR50.use == 0xaaaa)
	{
		if(PROTECT.Max_In_RMS >= OCGR50.Pickup_Threshold)
		{
			if(OCGR50.op_status == RELAY_NORMAL)
			{
				OCGR50.op_status = RELAY_DETECT;
				OCGR50.op_count = 0;
			}
			else if(OCGR50.op_status == RELAY_DETECT)
			{
				if(OCGR50.op_count >= OCGR50.pickup_limit)
				{	
					OCGR50.op_status = RELAY_PICKUP;
					RELAY_STATUS.pickup |= F_OCGR50;  //alarm ON
					OCGR50.Pickup_Time = OCGR50.op_count;
					OCGR50.op_count = 0;
				}
			}
			else if(OCGR50.op_status == RELAY_PICKUP)
			{
				if(OCGR50.op_count >= OCGR50.delay_ms)
				{
					Relay_On(OCGR50.do_output);

					OCGR50.op_status	= RELAY_TRIP;
					OCGR50.Op_Ratio	= PROTECT.Max_In_RMS / OCGR50.Pickup_Threshold; //배수
					OCGR50.Op_Phase	= PROTECT.In_Op_Phase; //상
					OCGR50.Delay_Time = OCGR50.op_count;
					OCGR50.Op_Time		= OCGR50.Delay_Time + OCGR50.Pickup_Time + TOTAL_DELAY_50; //동작 시간

					RELAY_STATUS.pickup									&= ~F_OCGR50; //계전요소 alarm OFF
					RELAY_STATUS.operation_realtime			|= F_OCGR50;  //현재 동작 상태 변수 설정
					RELAY_STATUS.operation_sum_holding	|= F_OCGR50;  //누적 동작 상태 변수 설정

					EVENT.optime = (unsigned long)OCGR50.Op_Time;
					EVENT.operation |= (F_OCGR50 << 16) + OCGR50.Op_Phase;
					Phase_Info = (Phase_Info == 0)? EVENT.operation: OCGR50.Op_Phase;
					EVENT.fault_type = F_OCGR50;
					Save_Relay_Event(OCGR50.Op_Ratio * 100.0F);
					Save_Screen_Info(OCGR50.Op_Phase);
				}
			}
		}
		else
		{
			if(PROTECT.Max_In_RMS <= OCGR50.Dropout_Threshold)  //under 99%
			{
				if((OCGR50.op_status == RELAY_DETECT) || (OCGR50.op_status == RELAY_PICKUP))
				{
					OCGR50.op_status = RELAY_NORMAL;
					RELAY_STATUS.pickup &= ~F_OCGR50; //계전요소 alarm OFF
				}
				else if(OCGR50.op_status == RELAY_TRIP)
				{
					Relay_Off(OCGR50.do_output); //DO open
					OCGR50.op_status = RELAY_NORMAL; //50_1상태 NORMAL
					RELAY_STATUS.operation_realtime &= ~F_OCGR50; //동작 상태 변수 해제
				}
			}
		}
	}
}

void RELAY_OCGR51(void)
{
	if(OCGR51.use == 0xaaaa)
	{
		if(PROTECT.Max_In_RMS >= OCGR51.Pickup_Threshold)
		{
			if(OCGR51.op_status == RELAY_NORMAL)
			{
				OCGR51.op_status = RELAY_DETECT;
				OCGR51.op_count = 0;
			}
			else if(OCGR51.op_status == RELAY_DETECT)
			{
				if(OCGR51.op_count >= OCGR51.pickup_limit)
				{	
					OCGR51.op_status = RELAY_PICKUP;
					RELAY_STATUS.pickup |= F_OCGR51;  //alarm ON
					OCGR51.Pickup_Time = OCGR51.op_count;
					OCGR51.op_count = 0;
				}
			}
			else if(OCGR51.op_status == RELAY_PICKUP)
			{
				OCGR51.Op_Ratio	= PROTECT.Max_In_RMS / OCGR51.Pickup_Threshold;

				OCGR51.Op_Time_set_temp = Inverse_GetDelayTime(OCGR51.mode, OCGR51.time_lever, OCGR51.Op_Ratio);
				if(OCGR51.Op_Time_set_temp > (INVERSE_PICKUP_LIMIT+TOTAL_DELAY_51G)) OCGR51.Op_Time_set = OCGR51.Op_Time_set_temp - (INVERSE_PICKUP_LIMIT+TOTAL_DELAY_51G);
				else OCGR51.Op_Time_set = OCGR51.Op_Time_set_temp;

				if(OCGR51.op_count >= OCGR51.Op_Time_set)
				{
					Relay_On(OCGR51.do_output);

					OCGR51.op_status	= RELAY_TRIP;
//				OCGR51.Op_Ratio	= PROTECT.Max_In_RMS / OCGR51.Pickup_Threshold; //배수
					OCGR51.Op_Phase	= PROTECT.In_Op_Phase; //상
					OCGR51.Delay_Time = OCGR51.op_count;
					OCGR51.Op_Time		= OCGR51.Delay_Time + OCGR51.Pickup_Time + TOTAL_DELAY_51G; //동작 시간

					RELAY_STATUS.pickup									&= ~F_OCGR51; //계전요소 alarm OFF
					RELAY_STATUS.operation_realtime			|= F_OCGR51;  //현재 동작 상태 변수 설정
					RELAY_STATUS.operation_sum_holding	|= F_OCGR51;  //누적 동작 상태 변수 설정

					EVENT.optime = (unsigned long)OCGR51.Op_Time;
					EVENT.operation |= (F_OCGR51 << 16) + OCGR51.Op_Phase;
					Phase_Info = (Phase_Info == 0)? EVENT.operation: OCGR51.Op_Phase;
					EVENT.fault_type = F_OCGR51;
					Save_Relay_Event(OCGR51.Op_Ratio * 100.0F);
					Save_Screen_Info(OCGR51.Op_Phase);				}
			}
		}
		else
		{
			if(PROTECT.Max_In_RMS <= OCGR51.Dropout_Threshold)  //under 99%
			{
				if((OCGR51.op_status == RELAY_DETECT) || (OCGR51.op_status == RELAY_PICKUP))
				{
					OCGR51.op_status = RELAY_NORMAL;
					RELAY_STATUS.pickup &= ~F_OCGR51; //계전요소 alarm OFF
				}
				else if(OCGR51.op_status == RELAY_TRIP)
				{
					Relay_Off(OCGR51.do_output); //DO open
					OCGR51.op_status = RELAY_NORMAL; //50_1상태 NORMAL
					RELAY_STATUS.operation_realtime &= ~F_OCGR51; //동작 상태 변수 해제
				}
			}
		}
	}
}

void RELAY_THR49(void)
{

}

void RELAY_NSR46(void)
{

}

void RELAY_51LR(void)
{

}

void RELAY_NCHR66(void)
{

}

void RELAY_50H(void)
{

}

void RELAY_UCR37(void)
{

}

void RELAY_DGR(void)
{
	if(DGR.use == 0xaaaa)
	{
		// 위상차
		DGR.diff_angle_rad = MEASUREMENT.angle[In] - MEASUREMENT.angle[Vn];
		DGR.diff_angle_deg = DGR.diff_angle_rad * 57.29577951; // degree로 환산 180/PI = 57.29577951
		DGR.diff_angle_deg += DSGR_ANGLE.dgr_angle;
		if(DGR.diff_angle_deg < 0.)	{DGR.diff_angle_deg += 360;}
		
		if((PROTECT.Max_In_RMS >= DGR.Pickup_Threshold_Io) && (PROTECT.Max_Vn_RMS >= DGR.Pickup_Threshold_Vo) && ((DGR.diff_angle_deg >= DGR.angle_low) || (DGR.diff_angle_deg <= DGR.angle_high)))
		{
			if(DGR.op_status == RELAY_NORMAL)
			{
				DGR.op_status = RELAY_DETECT;
				DGR.op_count = 0;
			}
			else if(DGR.op_status == RELAY_DETECT)
			{
				if(DGR.op_count >= DGR.pickup_limit)
				{	
					DGR.op_status = RELAY_PICKUP;
					RELAY_STATUS.pickup |= F_DGR;  //alarm ON
					DGR.Pickup_Time = DGR.op_count;
					DGR.op_count = 0;
				}
			}
			else if(DGR.op_status == RELAY_PICKUP)
			{
				if(DGR.op_count >= DGR.delay_ms)
				{
					Relay_On(DGR.do_output);

					DGR.op_status	= RELAY_TRIP;
					DGR.Op_Ratio	= PROTECT.Max_In_RMS / DGR.Pickup_Threshold_Io; //배수
					DGR.Op_Phase	= PROTECT.In_Op_Phase; //상
					DGR.Delay_Time = DGR.op_count;
					DGR.Op_Angle = DGR.diff_angle_deg;
					DGR.Op_Time		= DGR.Delay_Time + DGR.Pickup_Time + TOTAL_DELAY_67GD; //동작 시간

					RELAY_STATUS.pickup									&= ~F_DGR; //계전요소 alarm OFF
					RELAY_STATUS.operation_realtime			|= F_DGR;  //현재 동작 상태 변수 설정
					RELAY_STATUS.operation_sum_holding	|= F_DGR;  //누적 동작 상태 변수 설정
					
					EVENT.optime = (unsigned long)DGR.Op_Time;
					EVENT.operation |= (F_DGR << 16) + DGR.Op_Phase;
					EVENT.fault_type = F_DGR;
					Phase_Info = (Phase_Info == 0)? EVENT.operation: DGR.Op_Phase;
					Save_Relay_Event(DGR.Op_Ratio * 100.0F);
					Save_Screen_Info(DGR.Op_Phase);
				}
			}
		}
		else //		if((PROTECT.Max_In_RMS >= DGR.Pickup_Threshold_Io) && (PROTECT.Max_Vn_RMS >= DGR.Pickup_Threshold_Vo) && ((DGR.angle_sub >= DGR.angle_low) || (DGR.angle_sub <= DGR.angle_high)))
		{
			if((PROTECT.Max_In_RMS < DGR.Dropout_Threshold_Io) || (PROTECT.Max_Vn_RMS < DGR.Dropout_Threshold_Vo) || ((DGR.diff_angle_deg < DGR.angle_low) && (DGR.diff_angle_deg > DGR.angle_high)))  //under 97%
			{
				if((DGR.op_status == RELAY_DETECT) || (DGR.op_status == RELAY_PICKUP))
				{
					DGR.op_status = RELAY_NORMAL;
					RELAY_STATUS.pickup &= ~F_DGR; //계전요소 alarm OFF
				}
				else if(DGR.op_status == RELAY_TRIP)
				{
					Relay_Off(DGR.do_output);
					DGR.op_status = RELAY_NORMAL; 
					RELAY_STATUS.operation_realtime &= ~F_DGR; //동작 상태 변수 해제
				}
			}
		}
	}
}

void RELAY_SGR(void)
{
	if(SGR.use == 0xaaaa)
	{
		// 위상차
		SGR.diff_angle_rad = MEASUREMENT.angle[Is] - MEASUREMENT.angle[Vn];
		SGR.diff_angle_deg = SGR.diff_angle_rad * 57.29577951; // degree로 환산 180/PI = 57.29577951
		SGR.diff_angle_deg += DSGR_ANGLE.sgr_angle;
		if(SGR.diff_angle_deg < 0.)	{SGR.diff_angle_deg += 360;}
		
		if((PROTECT.Max_Is_RMS >= SGR.Pickup_Threshold_Io) && (PROTECT.Max_Vn_RMS >= SGR.Pickup_Threshold_Vo) && ((SGR.diff_angle_deg >= SGR.angle_low) || (SGR.diff_angle_deg <= SGR.angle_high)))
		{
			if(SGR.op_status == RELAY_NORMAL)
			{
				SGR.op_status = RELAY_DETECT;
				SGR.op_count = 0;
			}
			else if(SGR.op_status == RELAY_DETECT)
			{
				if(SGR.op_count >= SGR.pickup_limit)
				{	
					SGR.op_status = RELAY_PICKUP;
					RELAY_STATUS.pickup |= F_SGR;  //alarm ON
					SGR.Pickup_Time = SGR.op_count;
					SGR.op_count = 0;
				}
			}
			else if(SGR.op_status == RELAY_PICKUP)
			{
				if(SGR.op_count >= SGR.delay_ms)
				{
					Relay_On(SGR.do_output);

					SGR.op_status	= RELAY_TRIP;
					SGR.Op_Ratio	= PROTECT.Max_Is_RMS / SGR.Pickup_Threshold_Io; //배수
					SGR.Op_Phase	= PROTECT.Is_Op_Phase; //상
					SGR.Delay_Time = SGR.op_count;
					SGR.Op_Angle = SGR.diff_angle_deg;
					SGR.Op_Time		= SGR.Delay_Time + SGR.Pickup_Time + TOTAL_DELAY_67GS; //동작 시간

					RELAY_STATUS.pickup									&= ~F_SGR; //계전요소 alarm OFF
					RELAY_STATUS.operation_realtime			|= F_SGR;  //현재 동작 상태 변수 설정
					RELAY_STATUS.operation_sum_holding	|= F_SGR;  //누적 동작 상태 변수 설정
					
					EVENT.optime = (unsigned long)SGR.Op_Time;
					EVENT.operation |= (F_SGR << 16) + SGR.Op_Phase;
					EVENT.fault_type = F_SGR;
					Phase_Info = (Phase_Info == 0)? EVENT.operation: SGR.Op_Phase;
					Save_Relay_Event(SGR.Op_Ratio * 100.0F);
					Save_Screen_Info(SGR.Op_Phase);
				}
			}
		}
		else //		if((PROTECT.Max_Is_RMS >= SGR.Pickup_Threshold_Io) && (PROTECT.Max_Vn_RMS >= SGR.Pickup_Threshold_Vo) && ((SGR.diff_angle_deg >= SGR.angle_low) || (SGR.diff_angle_deg <= SGR.angle_high)))
		{
			if((PROTECT.Max_Is_RMS < SGR.Dropout_Threshold_Io) || (PROTECT.Max_Vn_RMS < SGR.Dropout_Threshold_Vo) || ((SGR.diff_angle_deg < SGR.angle_low) && (SGR.diff_angle_deg > SGR.angle_high)))  //under 97%
			{
				if((SGR.op_status == RELAY_DETECT) || (SGR.op_status == RELAY_PICKUP))
				{
					SGR.op_status = RELAY_NORMAL;
					RELAY_STATUS.pickup &= ~F_SGR; //계전요소 alarm OFF
				}
				else if(SGR.op_status == RELAY_TRIP)
				{
					Relay_Off(SGR.do_output);
					SGR.op_status = RELAY_NORMAL; 
					RELAY_STATUS.operation_realtime &= ~F_SGR; //동작 상태 변수 해제
				}
			}
		}
	}
}

void PROTECTIVE_RELAY(void)
{
	//-------- 최대 전류 상 저장
	PROTECT.I_Op_Phase = Ia+1;
	PROTECT.Max_I_RMS = MEASUREMENT.rms_value[Ia];
	if(PROTECT.Max_I_RMS  < MEASUREMENT.rms_value[Ib])
	{
		PROTECT.I_Op_Phase = Ib+1;
		PROTECT.Max_I_RMS = MEASUREMENT.rms_value[Ib];
	}
	if(PROTECT.Max_I_RMS < MEASUREMENT.rms_value[Ic])
	{
		PROTECT.I_Op_Phase = Ic+1;
		PROTECT.Max_I_RMS = MEASUREMENT.rms_value[Ic];
	}
	PROTECT.In_Op_Phase = In+1;
	PROTECT.Max_In_RMS = MEASUREMENT.rms_value[In];

	PROTECT.Is_Op_Phase = Is+1;
	PROTECT.Max_Is_RMS = MEASUREMENT.rms_value[Is];
	//-------- 최대 전류 상 저장 END
	
	//-------- 최대 전압 상 저장
	PROTECT.V_Op_Phase = Va+1;
	PROTECT.Max_V_RMS = MEASUREMENT.rms_value[Va];
	if(PROTECT.Max_V_RMS  < MEASUREMENT.rms_value[Vb])
	{
		PROTECT.V_Op_Phase = Vb+1;
		PROTECT.Max_V_RMS = MEASUREMENT.rms_value[Vb];
	}
	if(PROTECT.Max_V_RMS < MEASUREMENT.rms_value[Vc])
	{
		PROTECT.V_Op_Phase = Vc+1;
		PROTECT.Max_V_RMS = MEASUREMENT.rms_value[Vc];
	}
	PROTECT.Vn_Op_Phase = Vn+1;
	PROTECT.Max_Vn_RMS = MEASUREMENT.rms_value[Vn];
	//-------- 최대 전압 상 저장 END

	//-------- 최소 전압 상 저장
	PROTECT.Min_V_Op_Phase = Va+1;
	PROTECT.Min_V_RMS = MEASUREMENT.rms_value[Va];
	if(PROTECT.Min_V_RMS  > MEASUREMENT.rms_value[Vb])
	{
		PROTECT.Min_V_Op_Phase = Vb+1;
		PROTECT.Min_V_RMS = MEASUREMENT.rms_value[Vb];
	}
	if(PROTECT.Min_V_RMS > MEASUREMENT.rms_value[Vc])
	{
		PROTECT.Min_V_Op_Phase = Vc+1;
		PROTECT.Min_V_RMS = MEASUREMENT.rms_value[Vc];
	}
	//-------- 최소 전압 상 저장 END

	//-------- 정상/역상 전압 저장
	PROTECT.V1_RMS = MEASUREMENT.V1_value;
	PROTECT.V2_RMS = MEASUREMENT.V2_value;
	//-------- 정상/역상 전압 저장 END

	OCR_MODE_SET.ocr_di_mask = (DIGITAL_INPUT.di_status & 0x018);

	RELAY_OCR50_1();
	RELAY_OCR50_2();
	RELAY_OCGR50();
	RELAY_OCGR51();
	RELAY_THR49();
	RELAY_NSR46();
	RELAY_51LR();
	RELAY_NCHR66();
	RELAY_50H();
	RELAY_UCR37();
	if(CORE.gr_select == NCT_SELECT)	{RELAY_DGR();}
	if(CORE.gr_select == ZCT_SELECT)	{RELAY_SGR();}

	SAMPLE.ending = 0;
}

unsigned long Inverse_GetDelayTime(int mode, float OP_level, float Ratio)
{
	float DelayTime;

	OP_level *= 0.01; 
	switch(mode)
	{
		case  INVERSE:								//Normal inverse type
				DelayTime=(0.14/(pow(Ratio,0.02)-1))*OP_level;
				break;
		case  V_INVERSE:								//Very inverse type
				DelayTime=(13.5/(pow(Ratio,1.0)-1))*OP_level;
				break;
		case  E_INVERSE:								//Extremely inverse type
				DelayTime=(80.0/(pow(Ratio,2.0)-1))*OP_level;
				break;
		default:
				break;
	}
	return((unsigned long)(DelayTime * 1000.));
}


