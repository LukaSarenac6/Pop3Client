#ifndef CONST_H
#define CONST_H
#include <QtGlobal>
//#define D_TESTING

const quint8 CH_AUTOMATE_TYPE_ID = 0x00;
const quint8 CL_AUTOMATE_TYPE_ID = 0x01;
const quint8 USER_AUTOMATE_TYPE_ID = 0x02;
const quint8 TEST_AUTOMATE_TYPE_ID = 0x03;

const quint8 CH_AUTOMATE_MBX_ID = 0x00;
const quint8 CL_AUTOMATE_MBX_ID = 0x01;
const quint8 USER_AUTOMATE_MBX_ID = 0x02;
const quint8 TEST_MBX_ID = 0x03;

//	Client states
enum ClStates {	FSM_Cl_Ready,
                FSM_Cl_Connecting,
                FSM_Cl_Authorising,
                FSM_Cl_User_Check,
                FSM_Cl_Pass_Check,
                FSM_Cl_Mail_Check,
                FSM_Cl_Receiving,
                FSM_Cl_Deleting,
                FSM_Cl_Reseting,
                FSM_Cl_Disconnecting };

// channel messages
const quint16 MSG_Connection_Request			= 0x0001;
const quint16 MSG_Sock_Connection_Reject		= 0x0002;
const quint16 MSG_Sock_Connection_Acccept	= 0x0003;
const quint16 MSG_Cl_MSG						= 0x0004;
const quint16 MSG_Sock_MSG					= 0x0005;
const quint16 MSG_Disconnect_Request			= 0x0006;
const quint16 MSG_Sock_Disconected			= 0x0007;
const quint16 MSG_Sock_Disconnecting_Conf	= 0x0008;

// client messages
const quint16 MSG_User_Check_Mail		= 0x0009;
const quint16 MSG_Cl_Connection_Reject	= 0x000a;
const quint16 MSG_Cl_Connection_Accept	= 0x000b;
const quint16 MSG_User_Name_Password		= 0x000c;
const quint16 MSG_MSG					= 0x000d;
const quint16 MSG_Cl_Disconected			= 0x000f;

// user messages
const quint16 MSG_Set_All				= 0x0010;
const quint16 MSG_User_Connected			= 0x0011;
const quint16 MSG_User_Connecton_Fail	= 0x0012;
const quint16 MSG_Mail					= 0x0013;
const quint16 MSG_User_Save_Mail			= 0x0015;
const quint16 MSG_User_Disconnected		= 0x0014;


#define ADRESS "localhost"
//#define ADRESS "mail.spymac.com"
//#define ADRESS "krtlab8"
#define PORT 110

#define TIMER1_ID 0
#define TIMER1_COUNT 10
#define TIMER1_EXPIRED 0x20

#define PARAM_DATA 0x01
#define PARAM_Name 0x02
#define PARAM_Pass 0x03



#endif // CONST_H
