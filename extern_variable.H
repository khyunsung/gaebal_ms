extern struct
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

extern struct
{
	unsigned int destination_count;
	unsigned int source_count;
	unsigned int source_count_end;
	unsigned int end_flag;
} FLASH;

extern struct
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

extern struct
{
	unsigned int index_count;
	unsigned int index_count_3times;
	
	float real_value[10];
	float imag_value[10];
} DFT;

extern struct
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

extern struct
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

extern struct
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

extern struct
{
	unsigned int key;
	unsigned int led;
	unsigned int lcd;
	
	unsigned long backlight;
	
	unsigned int cb_open;
	unsigned int cb_close;
	
	unsigned int measurement;
} TIMER;

extern struct
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

extern struct
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

extern struct
{
	unsigned int debounce[8];
	unsigned int property;
	unsigned int di_status;
	unsigned int do_status;
} DIDO;

extern struct
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

extern struct
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

extern struct
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

extern struct
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

extern struct
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

extern struct
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

extern struct
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

extern struct
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
	float Pickup_Threshold; //ThrInvSet
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

extern struct
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

extern struct
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

extern struct
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
//	unsigned int pickup_limit;
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

extern struct
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

extern struct
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

extern struct
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

extern struct
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

extern struct
{
	unsigned int pickup;	
	unsigned int operation_realtime;
	unsigned int operation_sum_holding;

	unsigned long popup_property;
	float popup_ratio;
	unsigned long popup_optime;
	unsigned int popup_mask;

} RELAY_STATUS;

//--------- SYSTEM VARIABLE
extern struct
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

extern struct
{
	unsigned int manual_relay_test;
	unsigned int manual_do_out;
	unsigned int Curr_input_flag;
} AUX_RELAY_TEST;

extern struct
{
	unsigned int address;
	unsigned int address_temp;
} ADDRESS;

extern struct
{
	unsigned int mode;
	unsigned int mode_temp;
} AUTO_DISPLAY;

extern struct
{
	unsigned int real;
	unsigned int real_temp;
} PASSWORD;

extern struct
{
	unsigned int pt_secondary;
	unsigned int pt_tertiary;
	
	unsigned int pt_secondary_temp;
	unsigned int pt_tertiary_temp;
} GPT;

extern struct
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

extern struct
{
	unsigned int use;
	unsigned int close_time;
	unsigned int open_time;

	unsigned int use_temp;
	unsigned int close_time_temp;
	unsigned int open_time_temp;
} LOCAL_CTRL;

extern struct
{
	int dgr_angle;
	int sgr_angle;

	int dgr_angle_temp;
	int sgr_angle_temp;
} DSGR_ANGLE;

extern struct
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

extern struct
{
	unsigned int baudrate;
	unsigned int delay;

	unsigned int baudrate_temp;
	unsigned int delay_temp;
} MODBUS;

extern struct
{
	unsigned int ocr_mode;
	unsigned int ocr_di_mask;

	unsigned int ocr_mode_temp;
} OCR_MODE_SET;

extern struct
{
	unsigned int use;
	unsigned int do_relay;

	unsigned int use_temp;
	unsigned int do_relay_temp;
} SYSTEM_ALARM;

extern struct
{
	unsigned int Hz;
	unsigned int rated_ct;	
	unsigned int gr_select;
//unsigned int model;	//2015.02.25

	unsigned int Hz_temp;
	unsigned int rated_ct_temp;	
	unsigned int gr_select_temp;
} CORE;

extern struct
{
	unsigned int debounce[8];
	unsigned int di_status; //DI 상태
	
	unsigned int debounce_temp[8];
} DIGITAL_INPUT;

extern struct
{
	unsigned int property;
	unsigned int do_status; //DO 상태. 기존에 기능 없음

	unsigned int property_temp;
} DIGITAL_OUTPUT;

//2015.10.19
extern struct
{
	unsigned int use;

	unsigned int use_temp;
} WATCHDOG;
//2015.10.19 END

extern struct
{
	unsigned int ratio;
	unsigned int start_delay;
	unsigned int stop_delay;

	unsigned int ratio_temp;
	unsigned int start_delay_temp;
	unsigned int stop_delay_temp;

	unsigned int Stop_Count;
	unsigned int Start_Count;
	unsigned int OverRun_Count;
	unsigned int Run_Count;

	unsigned int Stop_Flag;
	unsigned int Start_Flag;
	unsigned int OverRun_Flag;
	unsigned int Run_Flag;

	float RatioSet_66;
} SET_66;

extern struct
{
	unsigned long op_count;
	unsigned long RunningHourCNT;

	float Cut_Current;
	unsigned long RunningMeterHour;
	unsigned int RunningMeterHour_F;
} RUNNING;

//--------- SYSTEM VARIABLE END

extern struct
{
	unsigned int use;
	unsigned int address;
	unsigned int baudrate;
	unsigned int index;
} COMM;

//2015.11.6
extern struct
{
	unsigned int mode;	

	unsigned int Local_cnt_flag;
	unsigned int LocalHandleMode; //MRAM에 직접 연결되는 Local/Remote 상태 변수
	unsigned int CB_RLY_OFF_Flag;
	unsigned int CB_RLY_Cnt;
	unsigned int Enter_Open_Key_Flag;
	unsigned int Enter_Close_Key_Flag;

	unsigned int LocalHandleStatus;		//변수에서 사용되는 Local/Remote 상태 변수
	unsigned int LocalHandleOldKey;		//키값 저장 변수
	unsigned int LocalHandleCloseCnt;	
	unsigned int LocalHandleOpenCnt;
	unsigned int LocalHandleClose;
	unsigned int LocalHandleOpen;
	unsigned int LocalHandle_cnt;
	unsigned int LocalContrl_cnt;
} LOCAL_CONTROL;
//2015.11.6 END

extern struct
{
	int dgr;
	int sgr;
} GR_ANGLE;

extern struct
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

extern struct
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

extern struct
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

extern struct
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

extern struct
{
	unsigned int temp16_1;
	unsigned int temp16_2;
	
	float temp_float1;
	float temp_float2;
} TIMER0;

extern struct
{
	unsigned int temp16_1;
	unsigned int temp16_2;
} TIMER1;

extern struct
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

extern struct
{
	float energy_p;
	float energy_q;
	float energy_rp;
	float energy_rq;
} ACCUMULATION;

typedef struct screen_move_info {
	unsigned int x;
	unsigned int y;
	unsigned int select;
	unsigned int data_change;
} Screen_Position_Info;
extern Screen_Position_Info Screen_Position, Cursor_Position, Save_Current_Screen;

extern unsigned int const DO_ON_BIT[8];
extern unsigned int const DO_OFF_BIT[8];
//extern unsigned int const ON_BIT[9];
//extern unsigned int const OFF_BIT[9];

extern float cos_table[12];
extern float sin_table[12];

// 2/N * sum(2pi * n/N) * x[n]
extern float const cos_60Hz[12];
extern float const sin_60Hz[12];
extern float const cos_50Hz[12];
extern float const sin_50Hz[12];

extern float const harmonics_1st_cos[36];
extern float const harmonics_1st_sin[36];
extern float const harmonics_3rd_cos[36];
extern float const harmonics_3rd_sin[36];
extern float const harmonics_5th_cos[36];
extern float const harmonics_5th_sin[36];
extern float const harmonics_7th_cos[36];
extern float const harmonics_7th_sin[36];
extern float const harmonics_9th_cos[36];
extern float const harmonics_9th_sin[36];

extern unsigned int const CRC_High[256];
extern unsigned int const CRC_Low[256];
extern unsigned long const wave_buffer_address[10];
extern unsigned long const wave_buffer_post_address[10];
extern unsigned int const do_control[7];

extern unsigned int const himix_number[10];

extern const unsigned int OCR50_I_MIN[2];
extern const unsigned int OCR50_I_MAX[2];
extern const unsigned int OCR50_T_MIN;
extern const unsigned int OCR50_T_MAX;

extern const unsigned int OCR51_I_MIN[2];
extern const unsigned int OCR51_I_MAX[2];
extern const unsigned int OCR51_TL_MIN;
extern const unsigned int OCR51_TL_MAX;

extern const unsigned int OCGR50_I_MIN[2];
extern const unsigned int OCGR50_I_MAX[2];
extern const unsigned int OCGR50_T_MIN;
extern const unsigned int OCGR50_T_MAX;

extern const unsigned int OCGR51_I_MIN[2];
extern const unsigned int OCGR51_I_MAX[2];
extern const unsigned int OCGR51_TL_MIN;
extern const unsigned int OCGR51_TL_MAX;

extern const unsigned int THR_I_MIN[2];
extern const unsigned int THR_I_MAX[2];
extern const unsigned int THR_COLD_MIN;
extern const unsigned int THR_COLD_MAX;
extern const unsigned int THR_HOT_MIN;
extern const unsigned int THR_HOT_MAX;
extern const unsigned int THR_TAU_MIN;
extern const unsigned int THR_TAU_MAX;

extern const unsigned int NSR_I_MIN[2];
extern const unsigned int NSR_I_MAX[2];
extern const unsigned int NSR_T_MIN;
extern const unsigned int NSR_T_MAX;

extern const unsigned int LR51_ST_I_MIN[2];
extern const unsigned int LR51_ST_I_MAX[2]; 
extern const unsigned int LR51_ST_T_MIN;
extern const unsigned int LR51_ST_T_MAX;
extern const unsigned int LR51_I_MIN[2];
extern const unsigned int LR51_I_MAX[2]; 
extern const unsigned int LR51_T_MIN;
extern const unsigned int LR51_T_MAX;

extern const unsigned int NCHR_AL_T_MIN;
extern const unsigned int NCHR_AL_T_MAX;
extern const unsigned int NCHR_TRIP_NO_MIN;
extern const unsigned int NCHR_TRIP_NO_MAX;
extern const unsigned int NCHR_LIMIT_T_MIN;
extern const unsigned int NCHR_LIMIT_T_MAX;
extern const unsigned int NCHR_THETA_D_MIN;
extern const unsigned int NCHR_THETA_D_MAX;

extern const unsigned int H50_I_MIN[2];
extern const unsigned int H50_I_MAX[2]; 

extern const unsigned int UCR_Imin_MIN[2];
extern const unsigned int UCR_Imin_MAX[2];
extern const unsigned int UCR_Imax_MIN[2];
extern const unsigned int UCR_Imax_MAX[2];
extern const unsigned int UCR_T_MIN;
extern const unsigned int UCR_T_MAX;

extern const unsigned int DGR_I_MIN[2];
extern const unsigned int DGR_I_MAX[2];
extern const unsigned int DGR_V_MIN[3];
extern const unsigned int DGR_V_MAX[3];
extern const unsigned int DGR_T_MIN;
extern const unsigned int DGR_T_MAX;
extern const unsigned int DGR_A_MIN;
extern const unsigned int DGR_A_MAX;

extern const unsigned int SGR_I_MIN;
extern const unsigned int SGR_I_MAX;
extern const unsigned int SGR_V_MIN[3];
extern const unsigned int SGR_V_MAX[3];
extern const unsigned int SGR_T_MIN;
extern const unsigned int SGR_T_MAX;
extern const unsigned int SGR_A_MIN;
extern const unsigned int SGR_A_MAX;

extern const unsigned int CT_MIN;
extern const unsigned int CT_MAX;
extern const unsigned int PT_MIN;
extern const unsigned long PT_MAX;
extern const unsigned int CT_5A_RATED;
extern const unsigned int CT_1A_RATED;

extern const unsigned int DEBOUNCE_MIN;
extern const unsigned int DEBOUNCE_MAX;

extern const unsigned int SET66_RATIO_MIN;
extern const unsigned int SET66_RATIO_MAX;
extern const unsigned int SET66_ST_DLY_MIN;
extern const unsigned int SET66_ST_DLY_MAX;
extern const unsigned int SET66_SP_DLY_MIN;
extern const unsigned int SET66_SP_DLY_MAX;

extern const long CALIB_I_MIN;
extern const long CALIB_I_MAX;
extern const long CALIB_In_MIN;
extern const long CALIB_In_MAX;
extern const long CALIB_V_MIN;
extern const long CALIB_V_MAX;
extern const long CALIB_Vo_MIN;
extern const long CALIB_Vo_MAX;

extern unsigned int KHS_Key_Press;
extern unsigned int Calibration_Menu_Escape;
extern unsigned int Popup_OpPhase_Info;
extern unsigned int Phase_Info;
extern unsigned int Popup_Action;
extern unsigned int SysParamFlag;
extern unsigned int Manager_Fault_Wave_Sending_Count;
extern unsigned int Flash_CRC_Check_Routine;
