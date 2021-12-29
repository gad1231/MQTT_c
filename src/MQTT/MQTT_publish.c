/*********************************************
 * @file MQTT_publish.c                      *
 * @brief MQTT_publish API's             	 *
 * Copyright (c) 2020 E-Vision Corp.         *
 * Created     : 21/08/2020 10:22:38         *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim *
 * Version     : v_01                        *
 * Edit By     :                             *
 * Edit Reason :                             *
 * ******************************************/
#include "MQTT_publish.h"

int MQTT_Publish(char *PacketControl_Arr,
		MQTT_PublishPacketControl_s *PacketControl, char* Payload,
		unsigned int PayloadSize) {

	long int s32PayloadLen = 0;
	unsigned short u16PacketControlIndex = 0;

	PacketControl->Header.Bits.PacketType = PUBLISH;
	PacketControl_Arr[u16PacketControlIndex++] = PacketControl->Header.Bytes[0];

	PacketControl->TopicName.Length = String_Length(
			PacketControl->TopicName.Ptr);

	s32PayloadLen = PacketControl->TopicName.Length + 2/*2 bytes indicate of topic length*/
			 + PayloadSize;

	s32PayloadLen +=(PacketControl->Header.Bits.Qos > 0)? sizeof(PacketControl->PacketId):0;

	u16PacketControlIndex+=MQTT_Encode_RemLength(&PacketControl_Arr[u16PacketControlIndex],
			s32PayloadLen); // to write Remind length of Fixed header 2nd Byte


//PacketControl_Arr[u16PacketControlIndex++] =s32PayloadLen;

	PacketControl->Header.Bytes[1]=PacketControl_Arr[1];


	PacketControl_Arr[u16PacketControlIndex++] =
			(PacketControl->TopicName.Length) / 256;
	PacketControl_Arr[u16PacketControlIndex++] =
			(PacketControl->TopicName.Length) % 256;

	u16PacketControlIndex+=String_Copy(PacketControl_Arr + u16PacketControlIndex,
			PacketControl->TopicName.Ptr);

	if (PacketControl->Header.Bits.Qos > 0) {
		PacketControl_Arr[u16PacketControlIndex++] = (PacketControl->PacketId)
				/ 256;
		PacketControl_Arr[u16PacketControlIndex++] = (PacketControl->PacketId)
				% 256;
	}

	Memory_Copy(PacketControl_Arr+u16PacketControlIndex, Payload, PayloadSize);
	u16PacketControlIndex+=PayloadSize;

	return u16PacketControlIndex;
}
