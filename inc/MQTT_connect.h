/**************************************************
 * @file MQTT_ControlPacket.h                     *
 * @brief MQTT_ControlPacket Detiles              *
 * Copyright (c) 2020 E-Vision Corp.               *
 * Created     : 21/08/2020 10:22:38               *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim       *
 * Version     : v_01                              *
 * Edit By     :                                   *
 * Edit Reason :                                   *
 * ************************************************/

#ifndef MQTT_CONNECT_H_
#define MQTT_CONNECT_H_

#include "MQTT_utilites.h"

/******************************************************* Macros *******************************************************/
#define MQTT_CONNECT_FLAGS_INITIALIZER 0
#define MQTT_CONNECT_PAYLOAD_INITIALIZER { {0,NULL} , {0,NULL} , {0,NULL} , {0,NULL} , {0,NULL} }

#define MQTT_CONNECT_PACKET__INITIALIZER { FIXED_HEADER_INITIALIZER , {0,4,'M', 'Q', 'T', 'T'} ,4, MQTT_CONNECT_FLAGS_INITIALIZER,60,MQTT_CONNECT_PAYLOAD_INITIALIZER }

#define CONNECT_VARIABLE_HEADER_BYTES 10
#define PROTOCOL_NAME_SIZE 6


/**
 * Connection ACK Flag Enum
 */
enum MQTT_ConnAck_e {
	CONNECTION_ACCEPTED = 0,
	WRONG_PROTOCOL_VERSION,
	CLIENT_ID_REJECTED,
	SERVER_UNAVAILABLE,
	BAD_USER_OR_PASS,
	NOT_AUTHORIZED
};
typedef enum MQTT_ConnAck_e MQTT_ConnAck_e;

/**
 *  Connection Flags Struct
 */

struct __attribute__((__packed__)) MQTT_ConnectFlags_s {

	unsigned char RESERVED :1;
	unsigned char CleanSession :1;
	unsigned char WillFlag :1;
	unsigned char WillQoS :2;
	unsigned char WillRetain :1;
	unsigned char PasswordFlag :1;
	unsigned char UserNameFlag :1;
};
typedef struct MQTT_ConnectFlags_s MQTT_ConnectFlags_s;

/**
 *  Connection Flags Union
 */
union MQTT_ConnectFlags_u {
	unsigned char Byte;
	MQTT_ConnectFlags_s Bit;

};
typedef union MQTT_ConnectFlags_u MQTT_ConnectFlags_u;

/**
 *  Connection Parameters Struct
 */

struct __attribute__((__packed__)) MQTT_ConnectParameters_s {
	MQTTStrings_s  ClientID      ;
	MQTTStrings_s  WillTopicName;
	MQTTStrings_s  WillMessage  ;
	MQTTStrings_s  Username     ;
	MQTTStrings_s  Password     ;
};

typedef struct MQTT_ConnectParameters_s MQTT_ConnectParameters_s;

/**
 *  Connection Control Packet Struct
 */

struct __attribute__((__packed__)) MQTT_ConnectPacketControl_s {
	FixedHeader_u Header;
	char ProtocolName[6]; /* include length of protocol and name which must be MQTT. */
	unsigned char ProtocolLevel; /*Protocol Version Must Be 3.1*/
	MQTT_ConnectFlags_u ConnectFlags;
	unsigned short keepAliveInterval;
	MQTT_ConnectParameters_s Parammeters;
};
typedef struct MQTT_ConnectPacketControl_s MQTT_ConnectPacketControl_s;


/**
* Send Connection control packet to MQTT broker with configured parameters
* @param PacketControl_Arr This is a pointer to Connection control packet array
* @param PacketControl This is a pointer to  Connection control packet struct
* @returns Number of Bytes in Connection control packet array
* @attention if it's invoked twice the broker will enforce closing the connection
* @see MQTT_Connect_Ack()
*/
int MQTT_Connect(char *PacketControl_Arr, MQTT_ConnectPacketControl_s *PacketControl);

#endif /* MQTT_CONNECT_H_ */
