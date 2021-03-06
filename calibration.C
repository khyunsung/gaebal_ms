#include "define.h"
#include "extern_variable.h"
#include "extern_prototype.h"

// calibration 순서
// 1. offset calibration
// 2. 전채널 동상으로 HIGH LEVEL (정격 5A : 전류 6A, 전압 110V) (정격 1A   : 전류 2A, 전압 110V) (ZCT 10mA)
// 3. 전채널 동상으로 LOW LEVEL  (정격 5A : 전류 1A, 전압  10V) (정격 0.2A : 전류 2A, 전압  10V) (ZCT  5mA)
// 4. slope 구함
// 5. angle 구함

// pt 비 380/3 -> 부담저항 없음
// ct 비 2000/1 상부담 62
//              영상부담 1.5k
int Offset_Check(unsigned int ar_channel)
{
	unsigned int i;
	unsigned int j;
	long temp_long = 0;
	
	TIMER.lcd = 0;
	
	i = 0;
	
	for(;;)
	{
		if(j != DFT.index_count)
		{
			temp_long += SAMPLE.rms_12_buffer[ar_channel][DFT.index_count];
			j =	DFT.index_count;
			++i;
		}
		if(i == 100)
		break;
	}
	temp_long /= 100;
	return((int)temp_long);
}
	
float DFT_Check(unsigned int ar_channel, float ar_min, float ar_max)
{
	unsigned int i;
	unsigned int j;
	float temp_float = 0.;
	unsigned int temp;
	
X:	i = 0;
	
	for(;;)
	{
		temp = *KEY_CS & 0x0fff;
		delay_us(5000);
		if(temp == UP_KEY || Calibration_Menu_Escape == 1) {
			Calibration_Menu_Escape = 1;
			return 0.0;
		}

		if(j != DFT.index_count)
		{
			if((MEASUREMENT.rms_value[ar_channel] > ar_min) && (MEASUREMENT.rms_value[ar_channel] < ar_max))
			{
				temp_float += MEASUREMENT.rms_value[ar_channel];
				j =	DFT.index_count;
				++i;
			}
			else
			{
				i = 0;
				temp_float = 0;
				goto X;
			}
		}
		if(i == 72)
		break;
	}
	temp_float /= 72.;
	return(temp_float);
}

float Degree_Check(unsigned int ar_channel)
{
	unsigned int i;
	unsigned int j;
	float temp_float = 0.;
	unsigned int temp;
	
	i = 0;
	for(;;)
	{
		temp = *KEY_CS & 0x0fff;
		delay_us(5000);
		if(temp == UP_KEY || Calibration_Menu_Escape == 1) {
			Calibration_Menu_Escape = 1;
			return 0.0;
		}

		if(j != DFT.index_count)
		{
			temp_float += MEASUREMENT.angle[Va] - MEASUREMENT.angle[ar_channel];
			j =	DFT.index_count;
			++i;			
		}
		if(i == 50)
		break;
	}
	temp_float /= 50.;
	return(temp_float);
}

int ADC_Offset_Calibration(void) //Offset Calibration에서는 탈출 안되고 무조건 넘어감
{
	Uint16 temp = 0;

	SAMPLE.normal = 0;
	
	Calibration_Menu_Escape = 0;

//-------- 기존 CALIBRATION 값 초기화	
	for(temp = 0; temp < 10; temp++)
	{
		CALIBRATION.offset_origin[temp] = CALIBRATION.offset[temp];
		CALIBRATION.slope_origin[temp] = CALIBRATION.slope[temp];
		CALIBRATION.intercept_origin[temp] = CALIBRATION.intercept[temp];
		CALIBRATION.angle_origin[temp] = CALIBRATION.angle[temp];	
		
		CALIBRATION.offset[temp] = 0;
		CALIBRATION.slope[temp] = 1.;
		CALIBRATION.intercept[temp] = 0.;
		CALIBRATION.angle[temp] = 0.;
	}
//	CALIBRATION.frequency_offset = 0;
//-------- 기존 CALIBRATION 값 초기화 END

	DFT.index_count = 0;
	for(;;)
	{	
		if(DFT.index_count == 11)
			break;
	}
	delay_us(2000);
	
	//-------- offset 측정 시작
	for(temp = 0; temp < 10; temp++)
	{
		CALIBRATION.offset_temp[temp] = Offset_Check(temp);
	}
	return 0;
}

//  0,  1,  2,  3,   4,   5,  6,  7,  8,  9
// Ia, Ib, Ic, In, In2, ZCT, Va, Vb, Vc, Vn
int ADC_High_Calibration(void)
{
	//-------- high level 측정 시작
	//124옴
	if(CORE.rated_ct == CT_5A)
	{
		DFT_Check(0, 1350, 1650); //초기 DELAY를 위해
		CALIBRATION.high_temp[0] = DFT_Check(0, 1350, 1650); //입력 6A (1502~1510)
		CALIBRATION.high_temp[1] = DFT_Check(1, 1350, 1650); //입력 6A (1502~1510)
		CALIBRATION.high_temp[2] = DFT_Check(2, 1350, 1650); //입력 6A (1502~1510)
//	if(CORE.gr_select == NCT_SELECT)	{CALIBRATION.high_temp[3] = DFT_Check(3, 1350, 1650);} 		//입력 6A (1502~1510)
		if(CORE.gr_select == NCT_SELECT)	{CALIBRATION.high_temp[3] = DFT_Check(3, 0, 50000);} 		//입력 6A (1502~1510)
//	else															{CALIBRATION.high_temp[5] = DFT_Check(5, 10800, 13200);} //입력 10mA (11963.45)
		else															{CALIBRATION.high_temp[5] = DFT_Check(5, 0, 50000);} 			//입력 10mA (11963.45)
	}
	else
	{
//		CALIBRATION.high_temp[0] = DFT_Check(0, 1.0, 3.0); //입력 2A
//		CALIBRATION.high_temp[1] = DFT_Check(1, 1.0, 3.0); //입력 2A
//		CALIBRATION.high_temp[2] = DFT_Check(2, 1.0, 3.0); //입력 2A
//		if(CORE.gr_select == NCT_SELECT)
//		CALIBRATION.high_temp[3] = DFT_Check(3, 1.0, 3.0); //입력 2A
//		else
//		CALIBRATION.high_temp[5] = DFT_Check(5, 5, 15); //입력 10mA	
	}
	DFT_Check(6, 5450, 9845); //초기 DELAY를 위해
	CALIBRATION.high_temp[6] = DFT_Check(6, 5450, 9845);  //입력 110V (8950~8963)
	CALIBRATION.high_temp[7] = DFT_Check(7, 5450, 9845);  //입력 110V (8950~8963)
	CALIBRATION.high_temp[8] = DFT_Check(8, 5450, 9845);  //입력 110V (8950~8963)
	CALIBRATION.high_temp[9] = DFT_Check(9, 14310, 17490); //입력 110V (15900)

	TIMER.lcd = 0;
	
	for(;;) // 1초 대기
	{
		if(TIMER.lcd > 1000)
		break;
		
		if(Calibration_Menu_Escape == 1)
			return 1;
	}
	
	// 위상 보정
	// Vab 기준으로 전체 위상 보정
	CALIBRATION.angle_temp[6] = 0; //Vab
	CALIBRATION.angle_temp[0] = Degree_Check(0);
	CALIBRATION.angle_temp[1] = Degree_Check(1);
	CALIBRATION.angle_temp[2] = Degree_Check(2);
	CALIBRATION.angle_temp[3] = Degree_Check(3);
	CALIBRATION.angle_temp[5] = Degree_Check(5); //ZCT
	CALIBRATION.angle_temp[7] = Degree_Check(7);
	CALIBRATION.angle_temp[8] = Degree_Check(8);
	CALIBRATION.angle_temp[9] = Degree_Check(9);
	
	return 0;
}

//  0,  1,  2,  3,   4,   5,  6,  7,  8,  9
// Ia, Ib, Ic, In, In2, ZCT, Va, Vb, Vc, Vn
int ADC_low_Calibration(void)
{
	unsigned int i;
	Uint16 temp = 0;
	unsigned int temp1[70];
	void *void_p;
	unsigned int *temp16_p;
	
	//-------- Low level 측정 시작
	//125옴
	if(CORE.rated_ct == CT_5A)
	{
		DFT_Check(0, 225, 275); //초기 DELAY를 위해
		CALIBRATION.low_temp[0] = DFT_Check(0, 225, 275); //입력 1A (249~251)
		CALIBRATION.low_temp[1] = DFT_Check(1, 225, 275); //입력 1A (249~251)
		CALIBRATION.low_temp[2] = DFT_Check(2, 225, 275); //입력 1A (249~251)
//	if(CORE.gr_select == NCT_SELECT)	{CALIBRATION.low_temp[3] = DFT_Check(3, 225, 275);} //입력 1A (249~251)
		if(CORE.gr_select == NCT_SELECT)	{CALIBRATION.low_temp[3] = DFT_Check(3, 0, 50000);} //입력 1A (249~251)
//	else															{CALIBRATION.low_temp[5] = DFT_Check(5, 5220, 6380);} //입력 5mA (5771.813)
		else															{CALIBRATION.low_temp[5] = DFT_Check(5, 0, 50000);} 		//입력 1mA (?)
	}
	else //1A
	{
//		CALIBRATION.low_temp[0] = DFT_Check(0, 0.1, 0.3); //입력 0.2A
//		CALIBRATION.low_temp[1] = DFT_Check(1, 0.1, 0.3); //입력 0.2A
//		CALIBRATION.low_temp[2] = DFT_Check(2, 0.1, 0.3); //입력 0.2A
//		if(CORE.gr_select == NCT_SELECT)
//		CALIBRATION.low_temp[3] = DFT_Check(3, 0.1, 0.3); //입력 0.2A
//		else
//		CALIBRATION.low_temp[5] = DFT_Check(5, 2, 8); //입력 5mA	
	}
	DFT_Check(6, 774, 946); //초기 DELAY를 위해
	CALIBRATION.low_temp[6] = DFT_Check(6, 774, 946); //입력 10V (860)
	CALIBRATION.low_temp[7] = DFT_Check(7, 774, 946); //입력 10V (815)
	CALIBRATION.low_temp[8] = DFT_Check(8, 774, 946); //입력 10V (815)
	CALIBRATION.low_temp[9] = DFT_Check(9, 1296, 1584); //입력 10V (1440)

//-------- 기본파 슬로프 계산 및 CALIBRATION FACTOR 저장
	for(temp = 0; temp < 5; temp++) //y=ax+b
	{
//		CALIBRATION.slope_temp1[temp] = 5.0 / (CALIBRATION.high_temp[temp] - CALIBRATION.low_temp[temp]); // 1/a완료
//		CALIBRATION.slope[temp] = CALIBRATION.slope_temp1[temp]; 
		CALIBRATION.slope_temp1[temp] = (CALIBRATION.high_temp[temp] - CALIBRATION.low_temp[temp]) / 5.0; // a완료
		CALIBRATION.slope[temp] = 1./CALIBRATION.slope_temp1[temp]; // 1/a완료
		CALIBRATION.slope_temp2[temp] = CALIBRATION.high_temp[temp] - (CALIBRATION.slope_temp1[temp] * 6.0);
		CALIBRATION.intercept[temp] = CALIBRATION.slope_temp2[temp] * CALIBRATION.slope[temp]; // b/a완료
	}

	CALIBRATION.slope_temp1[5] = (CALIBRATION.high_temp[5] - CALIBRATION.low_temp[5]) / 5.0; // a완료
	CALIBRATION.slope[5] = 1./CALIBRATION.slope_temp1[5]; // 1/a완료
	CALIBRATION.slope_temp2[5] = CALIBRATION.high_temp[5] - (CALIBRATION.slope_temp1[5] * 10.0);
	CALIBRATION.intercept[5] = CALIBRATION.slope_temp2[5] * CALIBRATION.slope[5]; // b/a완료
	if(CORE.gr_select == NCT_SELECT)
	{
		CALIBRATION.slope[4] = 1.; //In2 사용하지 않음.
		CALIBRATION.slope[5] = 1.; //ZCT default
	}
	else
	{
		CALIBRATION.slope[3] = 1.; //In default
		CALIBRATION.slope[4] = 1.; //In2 사용하지 않음.
	}

	for(temp = 6; temp < 10; temp++) //전압 slope
	{
//		CALIBRATION.slope_temp1[temp] = 100.0 / (CALIBRATION.high_temp[temp] - CALIBRATION.low_temp[temp]);
//		CALIBRATION.slope[temp] = CALIBRATION.slope_temp1[temp];
		CALIBRATION.slope_temp1[temp] = (CALIBRATION.high_temp[temp] - CALIBRATION.low_temp[temp]) / 100.0; // a완료
		CALIBRATION.slope[temp] = 1./CALIBRATION.slope_temp1[temp]; // 1/a완료
		CALIBRATION.slope_temp2[temp] = CALIBRATION.high_temp[temp] - (CALIBRATION.slope_temp1[temp] * 110.0);
		CALIBRATION.intercept[temp] = CALIBRATION.slope_temp2[temp] * CALIBRATION.slope[temp]; // b/a완료
	}

	for(temp = 0; temp < 10; temp++) //offset
	{
		CALIBRATION.offset[temp] = CALIBRATION.offset_temp[temp];
	}

	CALIBRATION.angle[6] = CALIBRATION.angle_temp[6]; //angle
	CALIBRATION.angle[0] = CALIBRATION.angle_temp[0];
	CALIBRATION.angle[1] = CALIBRATION.angle_temp[1];
	CALIBRATION.angle[2] = CALIBRATION.angle_temp[2];
	CALIBRATION.angle[3] = CALIBRATION.angle_temp[3];
	CALIBRATION.angle[5] = CALIBRATION.angle_temp[5];
	CALIBRATION.angle[7] = CALIBRATION.angle_temp[7];
	CALIBRATION.angle[8] = CALIBRATION.angle_temp[8];
	CALIBRATION.angle[9] = CALIBRATION.angle_temp[9];
//-------- 기본파 슬로프 계산 및 CALIBRATION FACTOR 저장 END

	if(Calibration_Menu_Escape == 1)
		return 1;

//-------- EEROM 저장
	eerom_control(4, 0x80);
	eerom_control(4, 0xc0);
	
	for(i = 0; i < 10; i++)  //offset 저장
	{
		eerom_write(i, &CALIBRATION.offset[i]);
		temp1[i] = CALIBRATION.offset[i]; //[0]~[9]
	}
	for(i = 0; i < 10; i++) //slope 저장
	{
		void_p = &CALIBRATION.slope[i];
		temp16_p = (unsigned int *)void_p;
		eerom_write(0x10 + (i << 1), temp16_p);
		eerom_write(0x11 + (i << 1), temp16_p + 1);
		temp1[10 + (i << 1)] = *temp16_p;  //[10]~[29]
		temp1[11 + (i << 1)] = *(temp16_p + 1);
	}
	for(i = 0; i < 10; i++)
	{
		void_p = &CALIBRATION.intercept[i];
		temp16_p = (unsigned int *)void_p;
		eerom_write(0x30 + (i << 1), temp16_p);
		eerom_write(0x31 + (i << 1), temp16_p + 1);
		temp1[30 + (i << 1)] = *temp16_p;	//[30]~[49]
		temp1[31 + (i << 1)] = *(temp16_p + 1);
	}
	for(i = 0; i < 10; i++) //angle 저장
	{
		void_p = &CALIBRATION.angle[i];
		temp16_p = (unsigned int *)void_p;
		eerom_write(0x50 + (i << 1), temp16_p);
		eerom_write(0x51 + (i << 1), temp16_p + 1);
		temp1[50 + (i << 1)] = *temp16_p;	//[50]~[69]
		temp1[51 + (i << 1)] = *(temp16_p + 1);
	}

	i = Setting_CRC(temp1, 70);
	eerom_write(0xa0, &i);

	return 0;
//-------- EEROM 저장 END
}


