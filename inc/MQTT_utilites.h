/**************************************************
 * @file MQTT_utilites.h                     *
 * @brief MQTT_utilites Detiles              *
 * Copyright (c) 2020 E-Vision Corp.               *
 * Created     : 21/08/2020 10:22:38               *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim       *
 * Version     : v_01                              *
 * Edit By     :                                   *
 * Edit Reason :                                   *
 * ************************************************/

#ifndef MQTT_UTILITES_H_
#define MQTT_UTILITES_H_

#define  FIXED_HEADER_SIZE 2
#define FIXED_HEADER_INITIALIZER {0,0}

enum MQTT_PacketType_e {
	RESERVED0 = 0 /*RESERVED*/
	, CONNECT /*Client request to connect to Server*********/
	, CONNACK /*Connect acknowledgment**********************/
	, PUBLISH /*Publish message*****************************/
	, PUBACK /*Publish acknowledgment**********************/
	, PUBREC /*Publish received (assured delivery part 1)**/
	, PUBREL /*Publish release (assured delivery part 2)***/
	, PUBCOMP /*Publish complete (assured delivery part 3)**/
	, SUBSCRIBE /*Client subscribe request********************/
	, SUBACK /*Subscribe acknowledgment********************/
	, UNSUBSCRIBE /*Un-subscribe request************************/
	, UNSUBACK /*Un-subscribe acknowledgment*****************/
	, PINGREQ /*PING request********************************/
	, PINGRESP /*PING response*******************************/
	, DISCONNECT /*Client is disconnecting*********************/
	, Reserved15 /*Reserved15**********************************/



};
typedef enum MQTT_PacketType_e MQTT_PacketType_e;

/**************************************************
 * Structure Fixed header Defined all fixed bytes *
 * 1: (packet type:its flag)                      *
 * 2: Remaining Length                            *
 *************************************************/



struct __attribute__((__packed__)) FixedHeader_s {
	unsigned char Retain     :1; /* RETAIN3 = PUBLISH Retain flag*/
	unsigned char Qos        :2; /* QoS may be 0,1 or 2 */
	unsigned char DUP        :1; /* DUP1 = Duplicate delivery of a PUBLISH Control Packet */
	unsigned char PacketType :4; /* Packet Control type */
	unsigned char RemindLength;  /* Variable Header Length*/
};

typedef struct FixedHeader_s FixedHeader_s;




struct __attribute__((__packed__)) MQTTStrings_s {

	unsigned short Length;
	 char* Ptr;

};

typedef struct MQTTStrings_s MQTTStrings_s;

/**********************************************
 * union Fixed header Defined all fixed bytes  *
 ***********************************************/

union FixedHeader_u {
	unsigned char Bytes[FIXED_HEADER_SIZE]; /*Access Fixed header by byte.  */
	FixedHeader_s Bits; /*Access Fixed header by bit(s).*/
};
typedef union FixedHeader_u FixedHeader_u;



unsigned short int  String_Length( char * Ptr_String);
unsigned char String_Copy(char * Ptr_Source,char * Ptr_Destination);
void Memory_Copy(char * Ptr_Source, char * Ptr_Destination,unsigned short int DestinationSize);

unsigned char MQTT_Encode_RemLength( char *PacketControl_Ptr, int PayLoad_length);


#endif /* MQTT_UTILITES_H_ */
