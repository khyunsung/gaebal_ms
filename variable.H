#ifndef __VARIABLE__
#define __VARIABLE__

struct
{
	unsigned int pre_count;
	unsigned int post_count;
	unsigned int post_start;
	int *buffer;
	unsigned int save_index;
	unsigned int pre_count_di;
	unsigned int post_count_di;
	unsigned int relay;
	unsigned int timer;
	unsigned int hold;
} WAVE;

struct
{
	unsigned int destination_count;
	unsigned int source_count;
	unsigned int source_count_end;
	unsigned int end_flag;
} FLASH;

struct
{
	float first;
	float second;
	float third;
	float average;
	float average_ratio;
	unsigned int abnormal[10];
	int abnormal_value[10];
	int rms_12_buffer[10][12];
	int pre_36_buffer[10][36];
	int pre_value;
	unsigned int wave_count;
	unsigned int normal;
	int *dpram;
	unsigned int ending;
} SAMPLE;

struct
{
	unsigned int index_count;
	unsigned int index_count_3times;
	float real_value[10];
	float imag_value[10];
} DFT;

struct
{
	float rms_value[10];
	float true_rms[10];
	float angle[10];

	float real_I1_a;
	float real_I1_b;
	float real_I1_c;
	float imag_I1_a;
	float imag_I1_b;
	float imag_I1_c;
	float real_I1_sum;
	float imag_I1_sum;
	float I1_value;

	float real_I2_a;
	float real_I2_b;
	float real_I2_c;
	float imag_I2_a;
	float imag_I2_b;
	float imag_I2_c;
	float real_I2_sum;
	float imag_I2_sum;
	float I2_value;

	float real_V1_a;
	float real_V1_b;
	float real_V1_c;
	float imag_V1_a;
	float imag_V1_b;
	float imag_V1_c;
	float real_V1_sum;
	float imag_V1_sum;
	float V1_value;

	float real_V2_a;
	float real_V2_b;
	float real_V2_c;
	float imag_V2_a;
	float imag_V2_b;
	float imag_V2_c;
	float real_V2_sum;
	float imag_V2_sum;
	float V2_value;

	unsigned int power_1sec;
	int power_adder;

	float Pa_temp;
	float Pb_temp;
	float Pc_temp;

	float Qa_temp;
	float Qb_temp;
	float Qc_temp;

	float Pa_value;
	float Pb_value;
	float Pc_value;

	float Qa_value;
	float Qb_value;
	float Qc_value;

	float freq_real[12];
	float freq_imag[12];
	float frequency;
	float frequency_temp[6];
	unsigned int frequency_count;

	float freq_real_vn[12];
	float freq_imag_vn[12];
	float frequency_vn;
	float frequency_temp_vn[6];

//	float dgr_rms_Io;
//	float dgr_angle_Io;
//	float sgr_rms_Io;
//	float sgr_angle_Io;
} MEASUREMENT;

struct
{
	float line2line[3];

	float multipllier[10];
	float p_multipllier[3];
	unsigned int index;
	unsigned int sum_count;
	unsigned int switching;
//unsigned int switching_index;
	unsigned int Power_Up;
	float power_s[3];
	float power_p[3];
	float power_q[3];
	float pf[3];
	float p3;
	float q3;
	float pf3;

	float rms_value[10];
	float rms_value_temp[10];
	float rms_value_sum[10];
	float rms_Iavg_value;
	float rms_Vavg_value;
	float V1_value;
	float V2_value;
	float I1_value;
	float I2_value;
	float angle[8];

	unsigned long vo_max;	
} DISPLAY;

struct
{
	int offset[10];
	float slope[10];
	float intercept[10];
	float angle[10];

	float slope_power[3];
	float Power_Cos[3];
	float Power_Sin[3];
	float frequency_offset;

	float low_temp[10];
	float high_temp[10];
	float slope_temp1[10];	
	float slope_temp2[10];

	int offset_temp[10];
	long slope_temp[10];
	float angle_temp[10];

	int offset_origin[10];
	float slope_origin[10];
	float intercept_origin[10];
	float angle_origin[10];
} CALIBRATION;

struct
{
	unsigned int key;
	unsigned int led;
	unsigned int lcd;
	unsigned long backlight;
	unsigned int cb_open;
	unsigned int cb_close;
	unsigned int measurement;
} TIMER;

struct
{
	unsigned int pushed_key;
	unsigned int pushed_key_count;
	
	unsigned long position;
	unsigned long return_position;
	
	unsigned int remote1_local0;
	
//unsigned int do_status;
	unsigned int do_control;
	unsigned int do_out;
	unsigned int di_present;
	unsigned int di_past;
	unsigned int di_debounce_timer[8];
//unsigned int do_status_backup;
	
	unsigned int led_on;
	unsigned int led_mode;
	
	unsigned int diagnostic;
	int adc_ref_monitor;
	unsigned int adc_ref_monitor_count;
} SYSTEM;

struct
{
	char *line_buffer1;
	char *line_buffer2;

	// 붙여쓰기
	char line_data1[20];
	char line_data2[20];
	char *line_1st_adder;
	char *line_2nd_adder;
	unsigned int line_1st_addressing;
	unsigned int line_2nd_addressing;
	unsigned int line_1st_status;
	unsigned int line_2nd_status;
} LCD;

struct
{
	unsigned int debounce[8];
	unsigned int property;
	unsigned int di_status;
	unsigned int do_status;
} DIDO;

struct
{
	unsigned int rx_buffer[0xff];
	unsigned int rx_count;
	unsigned int rx_timeout;
	unsigned int rx_length;
	unsigned int rx_status;
	unsigned int tx_buffer[0xff];
	unsigned int tx_length;
	unsigned int tx_count;
	unsigned int *isr_tx;
	unsigned int temp[10];
	unsigned int event_sp_backup;
	unsigned int event_rollover_backup;
	unsigned int event_send_block;
} MANAGER;

//--------- RELAY VARIABLE
struct
{
	unsigned int I_Op_Phase;
	unsigned int In_Op_Phase;
	unsigned int Is_Op_Phase;
	unsigned int V_Op_Phase;
	unsigned int Vn_Op_Phase;
	
	unsigned int Min_V_Op_Phase;

	float Max_I_RMS;
	float Max_In_RMS;
	float Max_Is_RMS;
	float Max_V_RMS;
	float Max_Vn_RMS;

	float Min_V_RMS;
	float I2_RMS;

	float Thr49_Ratio;
} PROTECT;

struct
{
	unsigned int Stop_Count;
	unsigned int Start_Count;
	unsigned int OverRun_Count;
	unsigned int Run_Count;

	unsigned int Stop_Flag;
	unsigned int Start_Flag;
	unsigned int Overrun_Flag;
	unsigned int Run_Flag;

	unsigned long React_Count;

	float Start_Imax;
	float Disp_Start_Imax;
	float Disp_Start_Imax_temp;
	float Display_Start_Time;
} M_STATE;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int mode;
	unsigned int current_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;
	
	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int mode_temp;
	unsigned int current_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;	

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
	unsigned int di_err_flag;
	unsigned int di_on_flag;
} OCR50_1;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int mode;
	unsigned int current_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;
	
	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int mode_temp;
	unsigned int current_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;	

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
	unsigned int di_err_flag;
	unsigned int di_on_flag;
} OCR50_2;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int mode;
	unsigned int current_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;

	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int mode_temp;
	unsigned int current_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;
	
	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} OCGR50;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int mode;
	unsigned int current_set;
	unsigned int time_lever;
	unsigned int do_relay;

	unsigned long Op_Time_set;
	unsigned long Op_Time_set_temp;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;

	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int mode_temp;
	unsigned int current_set_temp;
	unsigned int time_lever_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} OCGR51;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int current_set;
	unsigned int cold_limit;
	unsigned int hot_limit;
	unsigned int tau_limit;
	unsigned int do_relay;
	
	unsigned long Op_Time_set;
	unsigned long Op_Time_set_temp;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;
	float Cold_Time;
	float Hot_Time;
	float Cold_Thau;

	unsigned long op_count;
	unsigned long theta_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	unsigned int cool_Flag;
	unsigned int hot_Flag;
	float present_theta;
	float ppresent_theta;
	float P_limit;
	float fsteady_theta;
	float tmp_theta;
	float or_theta;
	float re_theta;
	float ThetaTime;
	int his_index;
	int Tem_State;
	int hot_flg;  //unsigned int 안됨
	double temp_theta[12];
	double Pre_Curr;

	// 추가 부분
	unsigned int use_temp;
	unsigned int current_set_temp;
	unsigned int cold_limit_temp;
	unsigned int hot_limit_temp;
	unsigned int tau_limit_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} THR;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int current_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;

	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;
	unsigned int over_volt_flag;

	// 추가 부분
	unsigned int use_temp;
	unsigned int current_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} NSR;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int start_current_set;
	unsigned int start_delay_time;
	unsigned int current_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold_Start;
	float Dropout_Threshold_Start;
	float	Start_Ratio;
	float	Start_Ratio_Set;
	float	Start_OPLevel;
	unsigned long delay_ms_time;
	unsigned long delay_sec_time;
	unsigned long delay_ms_start;
	unsigned long delay_ms_temp;

	float Pickup_Threshold;
	float Dropout_Threshold;
	float	Ratio;

	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	unsigned int Reactor_Start_Flag;
	unsigned long st_count;
	unsigned long Reactor_Start_Time;
	unsigned int Start_Time_Flag;

	// 추가 부분
	unsigned int use_temp;
	unsigned int start_current_set_temp;
	unsigned int start_delay_time_temp;
	unsigned int current_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} LR51;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int allow_time_set;
	unsigned int trip_number_set;
	unsigned int limit_time_set;
	unsigned int theta_d_set;
	unsigned int do_relay;
	
//	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	unsigned long Allow_Time_Threshold;
	unsigned int Trip_Number_Threshold;
	unsigned long Limit_Time_Threshold;
	float	Theta_D_Threshold;

	unsigned long op_count;
	unsigned long start_count;
//unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;
	unsigned int Start_RNum;

	// 추가 부분
	unsigned int use_temp;
	unsigned int allow_time_set_temp;
	unsigned int trip_number_set_temp;
	unsigned int limit_time_set_temp;
	unsigned int theta_d_set_temp;
	unsigned int do_relay_temp;

//	float Op_Ratio;
//	unsigned int Op_Phase;
//	float Op_Time;

//	unsigned long Pickup_Time;
//	unsigned long Delay_Time;
} NCHR;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int current_set;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold;
	float Dropout_Threshold;

	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	unsigned int save_flag;
	unsigned int display_flag;
	unsigned int reset_ready_flag;
	unsigned int trip_flag;

	// 추가 부분
	unsigned int use_temp;
	unsigned int current_set_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} H50;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int min_current_set;
	unsigned int max_current_set;
	unsigned int delay_time;
	unsigned int do_relay;

	unsigned int delay_ms;
	unsigned long Op_Time_set;
	unsigned long Op_Time_set_temp;
	unsigned int do_output;
	
	// 내부운용	
	float Min_Pickup_Threshold;
	float Max_Pickup_Threshold;
//float Dropout_Threshold;
	float RMS;

	unsigned long op_count;
	unsigned int pickup_limit;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int min_current_set_temp;
	unsigned int max_current_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} UCR;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int current_set;
	unsigned int voltage_set;
	unsigned int angle_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold_Io;
	float Dropout_Threshold_Io;
	float Pickup_Threshold_Vo;
	float Dropout_Threshold_Vo;
	int Pickup_Threshold_Angle;
	int Angle;
	int angle_low;
	int angle_high;
	float diff_angle_rad;
	float diff_angle_deg;

	unsigned int pickup_limit;
	unsigned long op_count;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int current_set_temp; 
	unsigned int current_set_temp2;
	unsigned int voltage_set_temp; 
	unsigned int voltage_set_temp2;
	unsigned int angle_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;
	int Op_Angle;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} DGR;

struct
{
	// 설정치들
	unsigned int use;
	unsigned int current_set;
	unsigned int voltage_set;
	unsigned int angle_set;
	unsigned int delay_time;
	unsigned int do_relay;
	
	unsigned int delay_ms;
	unsigned int do_output;
	
	// 내부운용	
	float Pickup_Threshold_Io;
	float Dropout_Threshold_Io;
	float Pickup_Threshold_Vo;
	float Dropout_Threshold_Vo;
	int Pickup_Threshold_Angle;
	int Angle;
	int angle_low;
	int angle_high;
	float diff_angle_rad;
	float diff_angle_deg;
	

	unsigned int pickup_limit;
	unsigned long op_count;
	unsigned long event_ready;
	unsigned int op_status;

	// 추가 부분
	unsigned int use_temp;
	unsigned int current_set_temp; 
	unsigned int current_set_temp2;
	unsigned int voltage_set_temp; 
	unsigned int voltage_set_temp2;
	unsigned int angle_set_temp;
	unsigned int delay_time_temp;
	unsigned int do_relay_temp;

	float Op_Ratio;
	unsigned int Op_Phase;
	float Op_Time;
	int Op_Angle;

	unsigned long Pickup_Time;
	unsigned long Delay_Time;
} SGR;

struct
{
	unsigned int pickup;
	unsigned int operation_realtime;
	unsigned int operation_sum_holding;
		
	unsigned long popup_property;
	float popup_ratio;
	unsigned long popup_optime;
	unsigned int popup_mask;

} RELAY_STATUS;
//--------- RELAY VARIABLE END

//--------- SYSTEM VARIABLE
struct
{
	unsigned int ct_primary;
	unsigned int nct_primary;
	unsigned int pt_primary_high;
	unsigned int pt_primary_low;
	unsigned int rated_current;
	
	float ct_ratio;
	float nct_ratio;
	float pt_ratio;
	float gpt_ratio;
	
	unsigned int ct_primary_temp;
	unsigned int nct_primary_temp;
	unsigned long pt_primary;
	unsigned long pt_primary_temp;
	unsigned int rated_current_temp;
} CPT;

struct
{
	unsigned int manual_relay_test;
	unsigned int manual_do_out;
	unsigned int Curr_input_flag;
} AUX_RELAY_TEST;

struct
{
	unsigned int address;
	unsigned int address_temp;
} ADDRESS;

struct
{
	unsigned int mode;
	unsigned int mode_temp;
} AUTO_DISPLAY;

struct
{
	unsigned int real;
	unsigned int real_temp;
} PASSWORD;

struct
{
	unsigned int pt_secondary;
	unsigned int pt_tertiary;
	
	unsigned int pt_secondary_temp;
	unsigned int pt_tertiary_temp;
} GPT;

struct
{	
	unsigned int mode;
	unsigned int source_level;
	unsigned int tcs_level;
	unsigned int tcs_time;
	unsigned int tcs_do_relay;
	unsigned int ccs_level;
	unsigned int ccs_time;
	unsigned int ccs_do_relay;
	
	//0이 tcs, 1이 ccs
	unsigned int do_output[2];
	long monitoring[2];
	unsigned int pickup_count[2];
	unsigned int pickup[2];
	unsigned int status[2];
	unsigned int time[2];
	
	unsigned int monitor_count;
	unsigned int monitor_update;
	
	long tcs_monitoring;
	long ccs_monitoring;	
	
	unsigned int tcs_ccs_status;
	
	unsigned int cb_close_time;
} SUPERVISION;

struct
{
	unsigned int use;
	unsigned int close_time;
	unsigned int open_time;
	
	unsigned int use_temp;
	unsigned int close_time_temp;
	unsigned int open_time_temp;
} LOCAL_CTRL;

struct
{
	int dgr_angle;
	int sgr_angle;

	int dgr_angle_temp;
	int sgr_angle_temp;
} DSGR_ANGLE;

struct
{
	unsigned int use;

	float Va_float;
	float Vb_float;
	float Vc_float;
	float Vn_float;

	unsigned int Va_point;
	unsigned int Vb_point;
	unsigned int Vc_point;
	unsigned int Vn_point;

	unsigned int use_temp;
} DISPLAY_3PHASE;

struct
{
	unsigned int baudrate;
	unsigned int delay;

	unsigned int baudrate_temp;
	unsigned int delay_temp;
} MODBUS;

struct
{
	unsigned int ocr_mode;
	unsigned int ocr_di_mask;

	unsigned int ocr_mode_temp;
} OCR_MODE_SET;

struct
{
	unsigned int use;
	unsigned int do_relay;

	unsigned int use_temp;
	unsigned int do_relay_temp;
} SYSTEM_ALARM;

struct
{
	unsigned int Hz;
	unsigned int rated_ct;	
	unsigned int gr_select;

	unsigned int Hz_temp;
	unsigned int rated_ct_temp;	
	unsigned int gr_select_temp;
} CORE;

struct
{
	unsigned int debounce[8];
	unsigned int di_status; //DI 상태
	
	unsigned int debounce_temp[8];
} DIGITAL_INPUT;

struct
{
	unsigned int property;
	unsigned int do_status; //DO 상태. 기존에 기능 없음

	unsigned int property_temp;
} DIGITAL_OUTPUT;

//2015.10.19
struct
{
	unsigned int use;

	unsigned int use_temp;
} WATCHDOG;
//2015.10.19 END

struct
{
	unsigned int ratio;
	unsigned int start_delay;
	unsigned int stop_delay;

	unsigned int ratio_temp;
	unsigned int start_delay_temp;
	unsigned int stop_delay_temp;
	
	float RatioSet_66;

	unsigned int Stop_Count;
	unsigned int Start_Count;
	unsigned int Run_Count;
	unsigned int OverRun_Count;

	unsigned int Stop_Flag;
	unsigned int Start_Flag;
	unsigned int Run_Flag;
	unsigned int OverRun_Flag;
} SET_66;

struct
{
	unsigned long op_count;
	unsigned long RunningHourCNT;

	float Cut_Current;
	unsigned long RunningMeterHour;
	unsigned int RunningMeterHour_F;
} RUNNING;

//--------- SYSTEM VARIABLE END

struct
{
	unsigned int use;
	unsigned int address;
	unsigned int baudrate;
	unsigned int index;
} COMM;

//2015.11.6
struct
{
	unsigned int mode;

	unsigned int Local_cnt_flag;
	unsigned int LocalHandleMode;	//MRAM에 직접 연결되는 Local/Remote 상태 변수
	unsigned int CB_RLY_OFF_Flag;
	unsigned int CB_RLY_Cnt;
	unsigned int Enter_Open_Key_Flag;
	unsigned int Enter_Close_Key_Flag;

	unsigned int LocalHandleStatus;	//변수에서 사용되는 Local/Remote 상태 변수
	unsigned int LocalHandleOldKey;
	unsigned int LocalHandleCloseCnt;
	unsigned int LocalHandleOpenCnt;
	unsigned int LocalHandleClose;
	unsigned int LocalHandleOpen;
	unsigned int LocalHandle_cnt;
	unsigned int LocalContrl_cnt;
} LOCAL_CONTROL;
//2015.11.6 END

struct
{
	int dgr;
	int sgr;
} GR_ANGLE;

struct
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int milisecond;
	
	unsigned int update;	
	unsigned int *buffer;
	
	unsigned int year_temp;
	unsigned int month_temp;
	unsigned int day_temp;
	unsigned int hour_temp;
	unsigned int minute_temp;
	unsigned int second_temp;
	unsigned int milisecond_temp;

	unsigned int year_temp2;
	unsigned int month_temp2;
	unsigned int day_temp2;
	unsigned int hour_temp2;
	unsigned int minute_temp2;
	unsigned int second_temp2;
	unsigned int milisecond_temp2;
} TIME;

struct
{
	unsigned int sp;
	
	int view_point;
	int view_start;
	
	unsigned int rollover;
	
	unsigned int temp;
	
	unsigned long pickup;
	unsigned long operation;
	
	unsigned long relay_set;
	unsigned long system_set;
	unsigned long data_reset;
	unsigned long di_off;
	unsigned long di_on;
	unsigned long do_off;
	unsigned long do_on;
	unsigned long mode_change;
	unsigned long control;
	
	unsigned int ratio;
	unsigned long optime;
	unsigned int fault_type;
	
	unsigned int group_extra;
} EVENT;

struct
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int milisecond;
	unsigned int fault_type;

	float offset_Ia;
	float scale_factor_Ia;
	float offset_Ib;
	float scale_factor_Ib;
	float offset_Ic;
	float scale_factor_Ic;
	float offset_In;
	float scale_factor_In;
	float offset_Va;
	float scale_factor_Va;
	float offset_Vb;
	float scale_factor_Vb;
	float offset_Vc;
	float scale_factor_Vc;
	float offset_Vn;
	float scale_factor_Vn;
	
	unsigned int modbus_address;
	unsigned int rated_current;
	unsigned int ct_ratio;
	unsigned int pt_ratio;
} FAULT_INFO;

struct
{
	unsigned int tx_buffer[61];
	unsigned int tx_count;
	
	unsigned int index;
	
	unsigned int timer;
	
	unsigned long temp32;
	unsigned int temp16;
	
	unsigned int number_start;
	unsigned int minus_flag;
	
	unsigned int buffer_index;
	
	unsigned int crc[2];
	unsigned int crc_count;
} HIMIX;

struct
{
	unsigned int temp16_1;
	unsigned int temp16_2;
	
	float temp_float1;
	float temp_float2;
} TIMER0;

struct
{
	unsigned int temp16_1;
	unsigned int temp16_2;
} TIMER1;

struct
{
	int sample[36];
	float base;
	float ia_max;
	float ib_max;
	float ic_max;
	
	float ia_max_save;
	float ib_max_save;
	float ic_max_save;
	
	float ia[6];
	float ib[6];
	float ic[6];
	float ftemp[4];
	
	float real;
	float imag;
	float float_temp;
	
	unsigned int index;
	unsigned int timer;
	
	unsigned int timer_15min;
} HARMONICS;

struct
{
	float energy_p;
	float energy_q;
	float energy_rp;
	float energy_rq;
} ACCUMULATION;

	// 비트위치가 반대로 들어가네
	//                   x L1 H1 L2   H2 L3 H3 L4   H4 L5 H5 L6   H6  x  x  x     DISPLAY
	//                  00 01 02 03   04 05 06 07   08 09 10 11   12 13 14 15
	// DO_01-H1-0x2000   0  0  1  0    0  0  0  0    0  0  0  0    0  0  0  0 ->   1   ->ALARM
	// DO_02-L1-0x4000   0  1  0  0    0  0  0  0    0  0  0  0    0  0  0  0 ->   2   ->ALARM
	// DO_03-H2-0x0800   0  0  0  0    1  0  0  0    0  0  0  0    0  0  0  0 ->   3   ->ALARM
	// DO_04-L2-0x1000   0  0  0  1    0  0  0  0    0  0  0  0    0  0  0  0 ->   4   ->ALARM
	// DO_05-H3-0x0200   0  0  0  0    0  0  1  0    0  0  0  0    0  0  0  0 ->   5   ->ALARM
	// DO_06-H4-0x0080   0  0  0  0    0  0  0  0    1  0  0  0    0  0  0  0 ->   6   ->Normal B접점
	// DO_07-H5-0x0020   0  0  0  0    0  0  0  0    0  0  1  0    0  0  0  0 ->   7   ->CB CLOSE(ON)
	// DO_08-H6-0x0008   0  0  0  0    0  0  0  0    0  0  0  0    1  0  0  0 ->   8   ->CB OPEN(OFF)
unsigned int const DO_ON_BIT[8] = 
{
	0x2000, //ALARM1			 	1	(DO_01 ON)
	0x4000, //ALARM2			 	2	(DO_02 ON)
	0x0800, //ALARM3			 	3	(DO_03 ON)
	0x1000, //ALARM4			 	4	(DO_04 ON)
	0x0200, //ALARM5			 	5	(DO_05 ON)
	0x0080, //SYSTEM ALARM	6 (DO_06 ON)
	0x0020, //CB CLOSE(ON) 	7	(DO_07 ON)
	0x0008  //CB OPEN(OFF) 	8	(DO_08 ON)
};

unsigned int const DO_OFF_BIT[8] = 
{
	~0x2000, //ALARM1			 	1	(DO_01 OFF)
	~0x4000, //ALARM2			 	2	(DO_02 OFF)
	~0x0800, //ALARM3			 	3	(DO_03 OFF)
	~0x1000, //ALARM4			 	4	(DO_04 OFF)
	~0x0200, //ALARM5			 	5	(DO_05 OFF)
	~0x0080, //SYSTEM ALARM	6 (DO_06 OFF)
	~0x0020, //CB CLOSE(ON) 	7	(DO_07 OFF)
	~0x0008  //CB OPEN(OFF) 	8	(DO_08 OFF)
};


//unsigned int const ON_BIT[9] = 
//{
//	0x0001,
//	0x0002,
//	0x0004,
//	0x0008,
//	0x0010,
//	0x0020,
//	0x0040,
//	0x0080,
//	0x0100
//};

//unsigned int const OFF_BIT[9] = 
//{
//	0xfffe,
//	0xfffd,
//	0xfffb,
//	0xfff7,
//	0xffef,
//	0xffdf,
//	0xffbf,
//	0xff7f,
//	0xfeff
//};

float cos_table[12];
float sin_table[12];
// 2/N * sum(2pi * n/N) * x[n]
float const cos_60Hz[12] = 
{
	 0.1666667,
	 0.1443375,
	 0.0833333,
	 0.,
	-0.0833333,
	-0.1443375,
	-0.1666667,
	-0.1443375,
	-0.0833333,
	 0.,
	 0.0833333,
	 0.1443375
};
	
float const sin_60Hz[12] = 
{
	 0.,
	 0.0833333,
	 0.1443375,
	 0.1666667,
	 0.1443375,
	 0.0833333,
	 0.,
	-0.0833333,
	-0.1443375,
	-0.1666667,
	-0.1443375,
	-0.0833333
};

float const cos_50Hz[12] = 
{
	 0.1666667,
	 0.1443375,
	 0.0833333,
	 0.,
	-0.0833333,
	-0.1443375,
	-0.1666667,
	-0.1443375,
	-0.0833333,
	 0.,
	 0.0833333,
	 0.1443375
};
	
float const sin_50Hz[12] = {
	 0.,
	 0.0833333,
	 0.1443375,
	 0.1666667,
	 0.1443375,
	 0.0833333,
	 0.,
	-0.0833333,
	-0.1443375,
	-0.1666667,
	-0.1443375,
    -0.0833333 };

float const harmonics_1st_cos[36] = {
	0.055555556,
	0.054711542,
	0.052205146,
	0.048112522,
	0.042558025,
	0.035710423,
	0.027777778,
	0.019001119,
	0.009647121,
	0,
	-0.009647121,
	-0.019001119,
	-0.027777778,
	-0.035710423,
	-0.042558025,
	-0.048112522,
	-0.052205146,
	-0.054711542,
	-0.055555556,
	-0.054711542,
	-0.052205146,
	-0.048112522,
	-0.042558025,
	-0.035710423,
	-0.027777778,
	-0.019001119,
	-0.009647121,
	0,
	0.009647121,
	0.019001119,
	0.027777778,
	0.035710423,
	0.042558025,
	0.048112522,
	0.052205146,
	0.054711542};

float const harmonics_1st_sin[36] = {
	0,
	0.009647121,
	0.019001119,
	0.027777778,
	0.035710423,
	0.042558025,
	0.048112522,
	0.052205146,
	0.054711542,
	0.055555556,
	0.054711542,
	0.052205146,
	0.048112522,
	0.042558025,
	0.035710423,
	0.027777778,
	0.019001119,
	0.009647121,
	0,
	-0.009647121,
	-0.019001119,
	-0.027777778,
	-0.035710423,
	-0.042558025,
	-0.048112522,
	-0.052205146,
	-0.054711542,
	-0.055555556,
	-0.054711542,
	-0.052205146,
	-0.048112522,
	-0.042558025,
	-0.035710423,
	-0.027777778,
	-0.019001119,
	-0.009647121};
		
float const harmonics_3rd_cos[36] = {
	0.055555556,
	0.048112522,
	0.027777778,
	0,
	-0.027777778,
	-0.048112522,
	-0.055555556,
	-0.048112522,
	-0.027777778,
	0,
	0.027777778,
	0.048112522,
	0.055555556,
	0.048112522,
	0.027777778,
	0,
	-0.027777778,
	-0.048112522,
	-0.055555556,
	-0.048112522,
	-0.027777778,
	0,
	0.027777778,
	0.048112522,
	0.055555556,
	0.048112522,
	0.027777778,
	0,
	-0.027777778,
	-0.048112522,
	-0.055555556,
	-0.048112522,
	-0.027777778,
	0,
	0.027777778,
	0.048112522};

float const harmonics_3rd_sin[36] = {	
	0,
	0.027777778,
	0.048112522,
	0.055555556,
	0.048112522,
	0.027777778,
	0,
	-0.027777778,
	-0.048112522,
	-0.055555556,
	-0.048112522,
	-0.027777778,
	0,
	0.027777778,
	0.048112522,
	0.055555556,
	0.048112522,
	0.027777778,
	0,
	-0.027777778,
	-0.048112522,
	-0.055555556,
	-0.048112522,
	-0.027777778,
	0,
	0.027777778,
	0.048112522,
	0.055555556,
	0.048112522,
	0.027777778,
	0,
	-0.027777778,
	-0.048112522,
	-0.055555556,
	-0.048112522,
	-0.027777778};
	
float const harmonics_5th_cos[36] = {
	0.055555556,
	0.035710423,
	-0.009647121,
	-0.048112522,
	-0.052205146,
	-0.019001119,
	0.027777778,
	0.054711542,
	0.042558025,
	0,
	-0.042558025,
	-0.054711542,
	-0.027777778,
	0.019001119,
	0.052205146,
	0.048112522,
	0.009647121,
	-0.035710423,
	-0.055555556,
	-0.035710423,
	0.009647121,
	0.048112522,
	0.052205146,
	0.019001119,
	-0.027777778,
	-0.054711542,
	-0.042558025,
	0,
	0.042558025,
	0.054711542,
	0.027777778,
	-0.019001119,
	-0.052205146,
	-0.048112522,
	-0.009647121,
	0.035710423};

float const harmonics_5th_sin[36] = {	
	0,
	0.042558025,
	0.054711542,
	0.027777778,
	-0.019001119,
	-0.052205146,
	-0.048112522,
	-0.009647121,
	0.035710423,
	0.055555556,
	0.035710423,
	-0.009647121,
	-0.048112522,
	-0.052205146,
	-0.019001119,
	0.027777778,
	0.054711542,
	0.042558025,
	0,
	-0.042558025,
	-0.054711542,
	-0.027777778,
	0.019001119,
	0.052205146,
	0.048112522,
	0.009647121,
	-0.035710423,
	-0.055555556,
	-0.035710423,
	0.009647121,
	0.048112522,
	0.052205146,
	0.019001119,
	-0.027777778,
	-0.054711542,
	-0.042558025};
	
float const harmonics_7th_cos[36] = {
	0.055555556,
	0.019001119,
	-0.042558025,
	-0.048112522,
	0.009647121,
	0.054711542,
	0.027777778,
	-0.035710423,
	-0.052205146,
	0,
	0.052205146,
	0.035710423,
	-0.027777778,
	-0.054711542,
	-0.009647121,
	0.048112522,
	0.042558025,
	-0.019001119,
	-0.055555556,
	-0.019001119,
	0.042558025,
	0.048112522,
	-0.009647121,
	-0.054711542,
	-0.027777778,
	0.035710423,
	0.052205146,
	0,
	-0.052205146,
	-0.035710423,
	0.027777778,
	0.054711542,
	0.009647121,
	-0.048112522,
	-0.042558025,
	0.019001119};

float const harmonics_7th_sin[36] = {	
	0,
	0.052205146,
	0.035710423,
	-0.027777778,
	-0.054711542,
	-0.009647121,
	0.048112522,
	0.042558025,
	-0.019001119,
	-0.055555556,
	-0.019001119,
	0.042558025,
	0.048112522,
	-0.009647121,
	-0.054711542,
	-0.027777778,
	0.035710423,
	0.052205146,
	0,
	-0.052205146,
	-0.035710423,
	0.027777778,
	0.054711542,
	0.009647121,
	-0.048112522,
	-0.042558025,
	0.019001119,
	0.055555556,
	0.019001119,
	-0.042558025,
	-0.048112522,
	0.009647121,
	0.054711542,
	0.027777778,
	-0.035710423,
	-0.052205146};
	
float const harmonics_9th_cos[36] = {
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0};

float const harmonics_9th_sin[36] = {	
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556,
	0,
	0.055555556,
	0,
	-0.055555556};
	
// CRC Table for Serial Communication
unsigned int const CRC_High[256] = {
//        0     1     2     3     4     5     6     7     8     9	
/*  0 */  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
/*  1 */  0x80, 0x41, 0x00, 0xC1, 0x81,	0x40, 0x01, 0xC0, 0x80, 0x41, 
/*  2 */  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
/*  3 */  0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
/*  4 */  0x00, 0xC1, 0x81, 0x40, 0x01,	0xC0, 0x80, 0x41, 0x00, 0xC1, 
/*  5 */  0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,	
/*  6 */  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
/*  7 */  0x81, 0x40, 0x00, 0xC1, 0x81,	0x40, 0x01, 0xC0, 0x80, 0x41, 
/*  8 */  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,	
/*  9 */  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
/* 10 */  0x01, 0xC0, 0x80, 0x41, 0x01,	0xC0, 0x80, 0x41, 0x00, 0xC1, 
/* 11 */  0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,	
/* 12 */  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
/* 13 */  0x80, 0x41, 0x00, 0xC1, 0x81,	0x40, 0x00, 0xC1, 0x81, 0x40, 
/* 14 */  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
/* 15 */  0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
/* 16 */  0x00, 0xC1, 0x81, 0x40, 0x01,	0xC0, 0x80, 0x41, 0x01, 0xC0,
/* 17 */  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
/* 18 */  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
/* 19 */  0x80, 0x41, 0x00, 0xC1, 0x81,	0x40, 0x01, 0xC0, 0x80, 0x41,
/* 20 */  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
/* 21 */  0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
/* 22 */  0x01, 0xC0, 0x80, 0x41, 0x01,	0xC0, 0x80, 0x41, 0x00, 0xC1,
/* 23 */  0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
/* 24 */  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
/* 25 */  0x80, 0x41, 0x00, 0xC1, 0x81,	0x40
};


unsigned int const CRC_Low[256] = {
//        0     1     2     3     4     5     6     7     8     9
/*  0 */  0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
/*  1 */  0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
/*  2 */  0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
/*  3 */  0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
/*  4 */  0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
/*  5 */  0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
/*  6 */  0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
/*  7 */  0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
/*  8 */  0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
/*  9 */  0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
/* 10 */  0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
/* 11 */  0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
/* 12 */  0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
/* 13 */  0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
/* 14 */  0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
/* 15 */  0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
/* 16 */  0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
/* 17 */  0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
/* 18 */  0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
/* 19 */  0x70, 0xB0, 0x50, 0x90, 0x91,	0x51, 0x93, 0x53, 0x52, 0x92,
/* 20 */  0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
/* 21 */  0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
/* 22 */  0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
/* 23 */  0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
/* 24 */  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
/* 25 */  0x43, 0x83, 0x41, 0x81, 0x80,	0x40  
};

unsigned long const wave_buffer_address[10] =
{
	0x200000L,	//Ia, 0
	(0x200000L + 0x2a30L), 		 //Ib, 1, 0x202A30
	(0x200000L + (0x2a30L * 2L)), //Ic, 2,	0x205460
	(0x200000L + (0x2a30L * 3L)), //In, 3, 0x207E90
	(0x200000L + (0x2a30L * 4L)), //Iz2 <-- 사용 안함, 0x20A8C0
	(0x200000L + (0x2a30L * 5L)), //Izct <-- 옵션 변수를 보고 사용할지 유무 판단, 0x20D2F0
	(0x200000L + (0x2a30L * 6L)), //Va, 4, 0x20FD20
	(0x200000L + (0x2a30L * 7L)), //Vb, 5, 0x212750
	(0x200000L + (0x2a30L * 8L)), //Vc, 6, 0x215180
	(0x200000L + (0x2a30L * 9L))  //Vn, 7, 0x217BB0
};

unsigned long const wave_buffer_post_address[10] =
{
	0x201518L,	//Ia, 0
	(0x201518L + 0x2a30L), 		 //Ib, 1, 0x203F48
	(0x201518L + (0x2a30L * 2L)), //Ic, 2, 0x206978
	(0x201518L + (0x2a30L * 3L)), //In, 3, 0x2093A8
	(0x201518L + (0x2a30L * 4L)), //Iz2 <-- 사용 안함, 0x20BDD8
	(0x201518L + (0x2a30L * 5L)), //Izct <-- 옵션 변수를 보고 사용할지 유무 판단, 0x20E808
	(0x201518L + (0x2a30L * 6L)), //Va, 4, 0x211238
	(0x201518L + (0x2a30L * 7L)), //Vb, 5, 0x213C68
	(0x201518L + (0x2a30L * 8L)), //Vc, 6, 0x216698
	(0x201518L + (0x2a30L * 9L))  //Vn, 7, 0x2190C8
};

unsigned int const do_control[7] = {0x2000, 0x0800, 0x0200, 0x0080, 0x0020, 0x0010, 0x0008};

unsigned int const himix_number[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

const unsigned int OCR50_I_MIN[2] = {5, 100};
const unsigned int OCR50_I_MAX[2] = {900, 1800}; //자리수가 다름
const unsigned int OCR50_T_MIN = 5;
const unsigned int OCR50_T_MAX = 1000;

const unsigned int OCR51_I_MIN[2] = {10, 20};
const unsigned int OCR51_I_MAX[2] = {120, 240};
const unsigned int OCR51_TL_MIN = 5;
const unsigned int OCR51_TL_MAX = 1000;

const unsigned int OCGR50_I_MIN[2] = {5, 10}; //자리수가 다름
const unsigned int OCGR50_I_MAX[2] = {600, 1200}; //자리수가 다름
const unsigned int OCGR50_T_MIN = 5;
const unsigned int OCGR50_T_MAX = 1000;

const unsigned int OCGR51_I_MIN[2] = {10, 2}; //자리수가 같음?
const unsigned int OCGR51_I_MAX[2] = {500, 100};
const unsigned int OCGR51_TL_MIN = 5;
const unsigned int OCGR51_TL_MAX = 1000;

const unsigned int THR_I_MIN[2] = {5, 10}; //자리수 다름
const unsigned int THR_I_MAX[2] = {60, 120};
const unsigned int THR_COLD_MIN = 5;
const unsigned int THR_COLD_MAX = 1800;
const unsigned int THR_HOT_MIN = 5;
const unsigned int THR_HOT_MAX = 1800;
const unsigned int THR_TAU_MIN = 1;
const unsigned int THR_TAU_MAX = 200;
                                           
const unsigned int NSR_I_MIN[2] = {5, 10}; //자리수 다름
const unsigned int NSR_I_MAX[2] = {25, 50};                                    
const unsigned int NSR_T_MIN = 1;
const unsigned int NSR_T_MAX = 100;

const unsigned int LR51_ST_I_MIN[2] = {10, 20}; //자리수 다름
const unsigned int LR51_ST_I_MAX[2] = {720, 1440}; 
const unsigned int LR51_ST_T_MIN = 10;
const unsigned int LR51_ST_T_MAX = 600;
const unsigned int LR51_I_MIN[2] = {10, 20}; //자리수 다름
const unsigned int LR51_I_MAX[2] = {300, 600}; 
const unsigned int LR51_T_MIN = 10;
const unsigned int LR51_T_MAX = 40;

const unsigned int NCHR_AL_T_MIN = 1;
const unsigned int NCHR_AL_T_MAX = 60;
const unsigned int NCHR_TRIP_NO_MIN = 1;
const unsigned int NCHR_TRIP_NO_MAX = 16;
const unsigned int NCHR_LIMIT_T_MIN = 1;
const unsigned int NCHR_LIMIT_T_MAX = 60;
const unsigned int NCHR_THETA_D_MIN = 40;
const unsigned int NCHR_THETA_D_MAX = 100;

const unsigned int H50_I_MIN[2] = {5, 10}; //자리수 다름
const unsigned int H50_I_MAX[2] = {200, 400}; 

const unsigned int UCR_Imin_MIN[2] = {2, 4}; //자리수 다름
const unsigned int UCR_Imin_MAX[2] = {25, 50};
const unsigned int UCR_Imax_MIN[2] = {2, 4}; //자리수 다름
const unsigned int UCR_Imax_MAX[2] = {25, 50};
const unsigned int UCR_T_MIN = 1;
const unsigned int UCR_T_MAX = 600;

const unsigned int DGR_I_MIN[2] = {2,4};
const unsigned int DGR_I_MAX[2] = {20,40};
const unsigned int DGR_V_MIN[3] = {110,120,190};
const unsigned int DGR_V_MAX[3] = {220,240,380};
const unsigned int DGR_T_MIN = 1;
const unsigned int DGR_T_MAX = 100;
const unsigned int DGR_A_MIN = 10;
const unsigned int DGR_A_MAX = 45;

const unsigned int SGR_I_MIN = 10;
const unsigned int SGR_I_MAX = 100;
const unsigned int SGR_V_MIN[3] = {110,120,190};
const unsigned int SGR_V_MAX[3] = {220,240,380};
const unsigned int SGR_T_MIN = 1;
const unsigned int SGR_T_MAX = 100;
const unsigned int SGR_A_MIN = 45;
const unsigned int SGR_A_MAX = 75;

const unsigned int CT_MIN = 1;
const unsigned int CT_MAX = 9999;
const unsigned int PT_MIN = 1;
const unsigned long PT_MAX = 600000;
const unsigned int CT_5A_RATED = 5000;
const unsigned int CT_1A_RATED = 1000;

const unsigned int DEBOUNCE_MIN = 5;
const unsigned int DEBOUNCE_MAX = 1000;

const unsigned int SET66_RATIO_MIN = 5;
const unsigned int SET66_RATIO_MAX = 50;
const unsigned int SET66_ST_DLY_MIN = 10;
const unsigned int SET66_ST_DLY_MAX = 100;
const unsigned int SET66_SP_DLY_MIN = 10;
const unsigned int SET66_SP_DLY_MAX = 100;

const long CALIB_I_MIN = 300000L;		// 약 0.003971225 ~ 0.003993668
const long CALIB_I_MAX = 500000L;		// 약 0.003971225 ~ 0.003993668
const long CALIB_In_MIN = 10;				// ZCT 용
const long CALIB_In_MAX = 500000L;
const long CALIB_V_MIN = 1000000L;	// 약 0.01227344~0.01234097
const long CALIB_V_MAX = 1400000L;	// 약 0.01227344~0.01234097
const long CALIB_Vo_MIN = 600000L;	// 약 0.006921696
const long CALIB_Vo_MAX = 800000L;	// 약 0.006921696

unsigned int Calibration_Menu_Escape = 0;
unsigned int Popup_OpPhase_Info = 0;
unsigned int Phase_Info = 0;
unsigned int Popup_Action = 0;
unsigned int SysParamFlag = 0;
unsigned int Manager_Fault_Wave_Sending_Count = 0;
unsigned int Flash_CRC_Check_Routine = 1;

#endif
