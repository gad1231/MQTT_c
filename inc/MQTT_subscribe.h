/*********************************************
 * @file MQTT_Subscribe.h                    *
 * @brief MQTT_utilites Details              *
 * Copyright (c) 2020 E-Vision Corp.         *
 * Created     : 21/08/2020 10:22:38         *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim *
 * Version     : v_01                        *
 * Edit By     :                             *
 * Edit Reason :                             *
 * ******************************************/

#ifndef MQTT_SUBSCRIBE_H_
#define MQTT_SUBSCRIBE_H_
#include "MQTT_utilites.h"

#define MAX_NO_OF_SUBSCRIBED_TOPICS  50

/**
 * Subscribe Topic Struct
 */

struct __attribute__((__packed__)) MQTT_Subscriber_s {
	MQTTStrings_s TopicName;
	unsigned char RequstedQOS;

};
typedef struct MQTT_Subscriber_s MQTT_Subscriber_s;


/**
 * Subscribe Control Packet Struct
 */

struct __attribute__((__packed__)) MQTT_SubscribePacketControl_s {
	FixedHeader_u Header;
	MQTT_Subscriber_s TopicFilter[MAX_NO_OF_SUBSCRIBED_TOPICS];
	unsigned short PacketId;
};
typedef struct MQTT_SubscribePacketControl_s MQTT_SubscribePacketControl_s;




/**
* Send Subscribe control packet to MQTT broker with configured parameters
* @param PacketControl_Arr This is a pointer to Subscribe control packet array
* @param PacketControl This is a pointer to  Subscribe control packet struct
* @param TopicsNumber Number of subscriptions
* @returns Number of Bytes in Subscribe control packet array
* @see MQTT_Subscribe_Ack()
*/
int MQTT_Subscribe(char *PacketControl_Arr,
		MQTT_SubscribePacketControl_s *PacketControl,unsigned char TopicsNumber);

#endif /* MQTT_SUBSCRIBE_H_ */
