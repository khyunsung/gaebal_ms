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

const char* event31[2]={"   ] 50 PARAMETER   ",
                       "     RE-SETTING.    "};                       
const char* event32[2]={"   ] 50 PARAMETER   ",
                       "     RE-SETTING.    "};                       
const char* event33[2]={"   ] 50G PARAMETER  ",
                       "     RE-SETTING.    "};                       
const char* event34[2]={"   ] 51G PARAMETER  ",
                       "     RE-SETTING.    "};                       
const char* event35[2]={"   ] THR PARAMETER  ",
                       "     RE-SETTING.    "};                       
const char* event36[2]={"   ] NSR PARAMETER  ",
                       "     RE-SETTING.    "};                       
const char* event37[2]={"   ] 51LR PARAMETER ",
                       "     RE-SETTING.    "};                       
const char* event38[2]={"   ] NCHR PARAMETER ",
                       "     RE-SETTING.    "};                       
const char* event39[2]={"   ] 50H PARAMETER  ",
                       "     RE-SETTING.    "};                       
const char* event3a[2]={"   ] UCR PARAMETER  ",
                       "     RE-SETTING.    "};                       
const char* event3b[2]={"   ] 67GD PARAMETER ",
                       "     RE-SETTING.    "};                       
const char* event3c[2]={"   ] 67GS PARAMETER ",
                       "     RE-SETTING.    "};                       
const char* event3d[2]={"   ] RLY PARAMETER  ",
                       "     RE-SETTING.    "};
const char* event3e[2]={"   ] SYS PARAMETER  ",
                       "     RE-SETTING.    "};

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
                                "] 50G ",             // 03
                                "] 51G ",             // 04
                                "] 49  ",             // 05
                                "] 46  ",             // 06
                                "] 51LR",             // 07
                                "] 51LR",             // 08
                                "] NCHR OPERATED.",   // 09
                                "] 50H ",             // 10
                                "] 37  ",             // 11
                                "] 67GD",             // 12, 이벤트에 상정보 자리에 각도 정보가 있다.
                                "] 67GS",             // 13, 이벤트에 상정보 자리에 각도 정보가 있다.
																};
//"ReBT","50-1","50-2","51-1","51-2","50G ","51G ","27R ",
//"27M ","27S ","47P ","47N ","59  ","64  ","67GD","67GS","CCS ","TCS ","SYS ","50  ","51  "

const char* Event_Volt_Curr[17]= {"",
																"Ir",													  //] 50-1",
                                "Ir",                           //] 50-2",
                                "Ir",                           //] 50G",
                                "Ir",                           //] 51G",
                                "Ir",                           //] 49", 
                                "Ir",                           //] 46", 
                                "Ir",                           //] 51LR TOO LONG START",
                                "Ir",                           //] 51LR LOCKED ROTOR",
                                "Vr",                           //] NCHR OPERATED",
                                "Vr",                           //] 50H",
                                "Ir",                           //] 37", 
                                "Ir",                           //] 67GD", 
                                "Ir",                           //] 67GS",  
                                "??",                           //] ",  
                                "??",                           //] ", 
                                "??",                           //] "  
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
													{"  50G GROUND FAULT  ",    //2
                           " [Fault Phase: Ia ] "},
													{"  51G GROUND FAULT  ",    //3
                           " [Fault Phase: Ia ] "},
													{" 49 THERMAL OVERLOAD",    //4
                           " [Fault Phase: Ia ] "},
													{"46 UNBALANCE CURRENT",    //5
                           " [Fault Phase: Ia ] "},
													{" 51LR TOO LONG START",    //6
                           " [Fault Phase: Ia ] "},
													{" 51LR LOCKED ROTOR  ",    //7
                           " [Fault Phase: Ia ] "},
													{" 66 START INHIBIT   ",    //8
                           "                    "},
													{"50H THERMAL BLOCKING",    //9
                           " [Fault Phase: Ia ] "},
													{"  37 UNDER CURRENT  ",    //10
                           " [Fault Phase: Ia ] "},
													{" 67GD GROUND FAULT  ",    //11
                           " [Fault Phase: Ia ] "},
													{" 67GS GROUND FAULT  ",    //12
                           " [Fault Phase: Ia ] "},
                         };
