// 시스템 정보
//  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0
//  

//					                //12345678901234567890
//char*  const code_spec[2]={"H4'FS MD 5/60 V01.00",
// 		  			       "14.03.27    00000000"};
//
//					                 //12345678901234567890
//char*  const version_f1[2]={"FMN 110/190V,5A,60Hz",
// 		  			          "14.03.27 V00 0000000"};

//  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0
// 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f 90 91 92 93
// c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf d0 d1 d2 d3
 
                     //12345678901234567890
const char* wave1[2]={"    WAVE CAPTURE ?",
                      "      YES   NO"};
                     //12345678901234567890
const char* wave2[2]={"   WAVE CAPTURING",
                      "   WAIT  A SECOND"};
                     //12345678901234567890
const char* wave3[2]={" WAVE CAPTURE FINISH",
                      "   PRESS ANY KEY"};

const char* event31[2]={"   ] 50   SETTING   ",
                       "                    "};
const char* event32[2]={"   ] 50   SETTING   ",
                       "                    "};
const char* event33[2]={"   ] 51   SETTING   ",
                       "                    "};
const char* event34[2]={"   ] 51   SETTING   ",
                       "                    "};
const char* event35[2]={"   ] 50G  SETTING   ",
                       "                    "};
const char* event36[2]={"   ] 51G  SETTING   ",
                       "                    "};
const char* event37[2]={"   ] 27R  SETTING   ",
                       "                    "};
const char* event38[2]={"   ] 27M  SETTING   ",
                       "                    "};
const char* event39[2]={"   ] 27S  SETTING   ",
                       "                    "};
const char* event3a[2]={"   ] 47P  SETTING   ",
                       "                    "};
const char* event3b[2]={"   ] 47N  SETTING   ",
                       "                    "};
const char* event3c[2]={"   ] 59  SETTING    ",
                       "                    "};
const char* event3d[2]={"   ] 64  SETTING    ",
                       "                    "};
const char* event3e[2]={"   ] 67GD  SETTING  ",
                       "                    "};
const char* event3f[2]={"   ] 67GS  SETTING  ",
                       "                    "};

                      //12345678901234567890
const char* event4[2]={"   ] SYSTEM SETTING ",
                       "                    "};
                      //12345678901234567890
const char* event5[2]={"   ] DATA CLEAR     ",
                       "                    "};
                      //12345678901234567890
const char* event6[2]={"   ] DIGITAL INPUT  ",
                       "                    "};
                      //12345678901234567890
//const char* event7[2]={"   ] DI CLOSE       ",
//                       "                    "};
                      //12345678901234567890
const char* event8[2]={"   ] DO OPEN        ",
                       "                    "};
                      //12345678901234567890
const char* event9[2]={"   ] DO CLOSE       ",
                       "                    "};
                       //12345678901234567890
const char* event10[2]={"   ] SYSTEM REBOOT  ",
                        "                    "};
                       //12345678901234567890
const char* event11[2]={"   ] FAULT ACK     \x01",
                        "     EXECUTION      "};
                       //12345678901234567890
const char* event12[2]={"   ] CONTROL",
                        "                    "};

                       //12345678901234567890
const char* event_t[2]={"   ] 20             ",
                        "                    "};
                       //12345678901234567890
const char* event_d[2]={"   ] RELAY OPERATION",
                        "RATIO:              "};

const char* event_phase[10]={ " ",
	                         "A",
	                         "B",
	                         "C",
	                         "N",
	                         "N2",
	                         "AB",
	                         "BC",
	                         "CA",
	                         "N"};

const char* event_io[10]={ "1 ",
	                         "2 ",
	                         "3 ",
	                         "4 ",
	                         "5 ",
	                         "6 ",
	                         "7 ",
	                         "8 ",
	                         "9 ",
	                         "10"};

const char* event_relay[16]=   {"",
																"] 50-1",							// 01
                                "] 50-2",             // 02
                                "] 51-1",             // 03
                                "] 51-2",             // 04
                                "] 50G ",             // 05
                                "] 51G ",             // 06
                                "] 27R ",             // 07
                                "] 27M ",             // 08
                                "] 27S ",             // 09
                                "] 47P ",             // 10, 이벤트에 상정보가 없다.
                                "] 47N ",             // 11, 이벤트에 상정보가 없다.
                                "] 59  ",             // 12
                                "] 64  ",             // 13
                                "] 67GD",             // 14, 이벤트에 상정보 자리에 각도 정보가 있다.
                                "] 67GS"              // 15, 이벤트에 상정보 자리에 각도 정보가 있다.
																};
//"ReBT","50-1","50-2","51-1","51-2","50G ","51G ","27R ",
//"27M ","27S ","47P ","47N ","59  ","64  ","67GD","67GS","CCS ","TCS ","SYS ","50  ","51  "

const char* Event_Volt_Curr[16]= {"",
																"Ir",													  //] 50-1",
                                "Ir",                           //] 50-2",
                                "Ir",                           //] 51-1",
                                "Ir",                           //] 51-2",
                                "Ir",                           //] 50G", 
                                "Ir",                           //] 51G", 
                                "Vr",                           //] 27-1",
                                "Vr",                           //] 27-2",
                                "Vr",                           //] 27-3",
                                "??",                           //] 47P", 
                                "??",                           //] 47N", 
                                "Vr",                           //] 59",  
                                "Vr",                           //] 64",  
                                "??",                           //] 67N", 
                                "??",                           //] 67G"  
																};
																
const char* event_set[13]={ "CT/PT",
                            "DI DEBOUNCE",
                            "DO MODE",
                            "SUPERVISION",
                            "PASSWORD",
                            "TIME",
                            "COMM.",
                            "LOCAL CONTROL",
                            "GR SELECT",
                            "ZCT ANGLE",
                            "OCR MODE",
                            "CAPTURE",
                            "DO TEST"};

const char* event_reset[5]={  "EVENT",
                              "ENERGY",
                              "Vo MAX",
                              "Io MAX",
                              "CB CLOSE TIME"};

const char* event_mode_change[7]={  "ACK KEY",
                                    "LOCAL->REMOTE",
                                    "REMOTE->LOCAL",
                                    "TCS FAIL->GOOD",
                                    "CCS FAIL->GOOD",
                                    "TCS GOOD->FAIL",
                                    "CCS GOOD->FAIL"
                                    };

const char* event_control[4]={  "LOCAL CB OPEN",
                                "LOCAL CB CLOSE",
                                "REMOTE CB OPEN",
                                "REMOTE CB CLOSE"
                                };

const char* Trip_Message[15][2]={
													{" 50-1 SHORT CIRCUIT ",		//0
                           " [Fault Phase: Ia ] "},
													{" 50-2 SHORT CIRCUIT ",    //1
                           " [Fault Phase: Ia ] "},
													{" 51-1 SHORT CIRCUIT ",    //2
                           " [Fault Phase: Ia ] "},
													{" 51-2 SHORT CIRCUIT ",    //3
                           " [Fault Phase: Ia ] "},
													{" 50G GROUND FAULT   ",    //4
                           " [Fault Phase: Ia ] "},
													{" 51G GROUND FAULT   ",    //5
                           " [Fault Phase: Ia ] "},
													{" 27R UNDER VOLTAGE1 ",    //6
                           " [Fault Phase: Ia ] "},
													{" 27M UNDER VOLTAGE2 ",    //7
                           " [Fault Phase: Ia ] "},
													{" 27S UNDER VOLTAGE3 ",    //8
                           " [Fault Phase: Ia ] "},
													{"47 UNBALANCE VOLTAGE",    //9
                           "                    "},
													{"47 UNBALANCE VOLTAGE",    //10
                           "                    "},
													{"  59 OVER VOLTAGE   ",    //11
                           " [Fault Phase: Ia ] "},
													{"  64 GROUND FAULT   ",    //12
                           " [Fault Phase: Ia ] "},
													{" 67GD GROUND FAULT  ",    //13
                           " [Fault Phase: Ia ] "},
													{" 67GS GROUND FAULT  ",    //14
                           " [Fault Phase: Ia ] "}
                         };
