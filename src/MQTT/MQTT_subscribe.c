/*********************************************
 * @file MQTT_Sibscribe.c                    *
 * @brief MQTT_utilites Details              *
 * Copyright (c) 2020 E-Vision Corp.         *
 * Created     : 21/08/2020 10:22:38         *
 * Contributors: Ahmed_Gad && Khalid_Ibrahim *
 * Version     : v_01                        *
 * Edit By     :                             *
 * Edit Reason :                             *
 * ******************************************/
#include "MQTT_subscribe.h"

int MQTT_Subscribe(char *PacketControl_Arr,
		MQTT_SubscribePacketControl_s *PacketControl,
		unsigned char TopicsNumber) {

	long int s32PayloadLen = 0;
	unsigned short TotalTopicListLength = 0;
	unsigned short u16PacketControlIndex = 0;

	PacketControl->Header.Bits.PacketType = SUBSCRIBE;
	PacketControl->Header.Bits.Qos = 1;

	PacketControl_Arr[u16PacketControlIndex++] = PacketControl->Header.Bytes[0];

	for (unsigned char index = 0; index <= TopicsNumber; index++) {

		PacketControl->TopicFilter[index].TopicName.Length = String_Length(
				PacketControl->TopicFilter[index].TopicName.Ptr);

		TotalTopicListLength = TotalTopicListLength
				+ PacketControl->TopicFilter[index].TopicName.Length;
	}

	s32PayloadLen = TotalTopicListLength
			+ (TopicsNumber * 2/*2 bytes indicate of topic length*/)
			+ (TopicsNumber * 2/*2 bytes  of Requested QoS*/);

	MQTT_Encode_RemLength(&PacketControl_Arr[u16PacketControlIndex],
			s32PayloadLen); // to write Remind length of Fixed header 2nd Byte
	u16PacketControlIndex++;

	for (unsigned char index = 0; index <= TopicsNumber; index++) {

		PacketControl_Arr[u16PacketControlIndex++] =
				PacketControl->TopicFilter[index].TopicName.Length / 256;
		PacketControl_Arr[u16PacketControlIndex++] =
				PacketControl->TopicFilter[index].TopicName.Length % 256;

		u16PacketControlIndex += String_Copy(
				PacketControl_Arr + u16PacketControlIndex,
				PacketControl->TopicFilter[index].TopicName.Ptr);

		PacketControl_Arr[u16PacketControlIndex++] =
				((PacketControl->TopicFilter[index].RequstedQOS) & 0x3) / 256;
		PacketControl_Arr[u16PacketControlIndex++] =
				((PacketControl->TopicFilter[index].RequstedQOS) & 0x3) % 256;
	}

	return u16PacketControlIndex;
}
