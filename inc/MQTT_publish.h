/*********************************************
 * @file MQTT_Publish.h                      *
 * @brief MQTT_utilites Details              *
 * Copyright (c) 2020 E-Vision Corp.         *
 * Created     : 21/08/2020 10:22:38         *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim *
 * Version     : v_01                        *
 * Edit By     :                             *
 * Edit Reason :                             *
 * ******************************************/

#ifndef MQTT_PUBLISH_H_
#define MQTT_PUBLISH_H_
#include"MQTT_utilites.h"


#define MQTT_PUBLISH_PACKET__INITIALIZER { FIXED_HEADER_INITIALIZER , {0,NULL} ,0 }



/**
 * Publish Control Packet Struct
 */
struct __attribute__((__packed__)) MQTT_PublishPacketControl_s {
	FixedHeader_u Header;
	MQTTStrings_s TopicName;
	unsigned short PacketId;
};
typedef struct MQTT_PublishPacketControl_s MQTT_PublishPacketControl_s;




/**
* Send Publish control packet to MQTT broker with configured parameters
* @param PacketControl_Arr This is a pointer to Publish control packet array
* @param PacketControl This is a pointer to  Publish control packet struct
* @param Payload This is a pointer to the payload
* @param PayloadSize The total payload length
* @returns Number of Bytes in Publish control packet array
* @see MQTT_Publish_Ack()
*/

int MQTT_Publish(char *PacketControl_Arr,
		MQTT_PublishPacketControl_s *PacketControl, char* Payload,
		unsigned int PayloadSize);

#endif /* MQTT_PUBLISH_H_ */
